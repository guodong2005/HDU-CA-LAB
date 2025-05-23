package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

/** CPU–side request for a data memory access. For a store the accompanying wdata is used. For a load, wdata is “don’t care.” */
class DCacheReq extends Bundle {
  val addr  = UInt(XLEN.W)
  val write = Bool()       // false: load; true: store
  val wdata = UInt(XLEN.W) // valid only if write is true
  val wstrb = UInt(4.W)    // byte write mask
  val size  = UInt(2.W)    // 0: byte, 1: half-word, 2: word
}

/** CPU–side response for a memory access. For a load, rdata holds the loaded word. For a store, a dummy value (here 0) is returned. */
class DCacheResp extends Bundle {
  val rdata = UInt(XLEN.W)
}

class Lsu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
    val ready    = Output(Bool()) // LSU ready signal
    val diffout  = Output(new DiffOut())
    val valid    = Output(Bool())
    val dcache = new Bundle {
      val req  = Decoupled(new DCacheReq)
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  io.diffout                  := DontCare
  io.diffout.storeEvent.valid := 0.U
  io.diffout.loadEvent.valid  := 0.U

  // ------------------------------------------------------------
  // Effective Address Computation
  // ------------------------------------------------------------
  val effectiveAddr = LookupTree(
    LSUOpType.isStore(io.info.op),
    Seq(
      true.B -> (io.src_info.src1_data.asSInt +
        SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0),
      false.B -> (io.src_info.src1_data.asSInt +
        SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0)
    )
  )

  val storeWdata = LookupTree(
    io.info.op,
    Seq(
      LSUOpType.sb -> Fill(4, io.src_info.src2_data(7, 0)),
      LSUOpType.sh -> Fill(2, io.src_info.src2_data(15, 0)),
      LSUOpType.sw -> io.src_info.src2_data(31, 0)
    )
  )

  // Extract the lower two bits of the effective address
  val addr_low2 = effectiveAddr(1, 0)

// Determine the size field based on memory operation type
  val size = MuxCase(
    2.U(2.W),
    Seq(
      (!LSUOpType.isStore(io.info.op) && (io.info.op === LSUOpType.sb)) -> 0.U(2.W),
      (!LSUOpType.isStore(io.info.op) && (io.info.op === LSUOpType.sh)) -> 1.U(2.W),
      (!LSUOpType.isStore(io.info.op) && (io.info.op === LSUOpType.sw)) -> 2.U(2.W)
    )
  )

// Generate write strobe (`strb`) based on the operation and address alignment
  val strb = MuxCase(
    0.U(4.W),
    Seq(
      (io.info.op === LSUOpType.sb) -> (1.U(4.W) << addr_low2), // Byte write
      (io.info.op === LSUOpType.sh) -> (3.U(4.W) << addr_low2), // Half-word write (2 bytes)
      (io.info.op === LSUOpType.sw) -> 15.U(4.W)                // Full-word write (4 bytes, all bits set)
    )
  )

// Assign the computed values
  val storeAddr = effectiveAddr(31, 2) << 2
  val storeStrb = strb

  // ------------------------------------------------------------
  // Construct the new DCache Request combinationally.
  // ------------------------------------------------------------
  val newReq = Wire(new DCacheReq)
  newReq.addr  := Mux(LSUOpType.isStore(io.info.op), storeAddr, effectiveAddr)
  newReq.write := LSUOpType.isStore(io.info.op)
  newReq.wdata := Mux(LSUOpType.isStore(io.info.op), storeWdata, 0.U)
  newReq.wstrb := storeStrb
  newReq.size  := size

  val dcacheReqReg = RegInit(0.U.asTypeOf(new DCacheReq))
  val reqValidReg  = RegInit(false.B) // Holds whether a request is pending.
  val opReg        = RegInit(0.U(4.W))

  val sIdle :: sWait :: Nil = Enum(2)
  val state                 = RegInit(sIdle)

  // printf(p"dcacheReqReg: ${Hexadecimal(dcacheReqReg.addr)}\n")
  when((state === sIdle) && io.info.valid && (io.info.fusel === FuType.lsu) && !reqValidReg) {
    dcacheReqReg := newReq
    reqValidReg  := true.B
    opReg        := io.info.op
  }

  val dcacheReq = Wire(Decoupled(new DCacheReq))
  dcacheReq.valid := Mux(reqValidReg, reqValidReg, io.info.valid && (io.info.fusel === FuType.lsu))
  dcacheReq.ready := DontCare
  dcacheReq.bits  := Mux(reqValidReg, dcacheReqReg, newReq)
  val op = Wire(UInt())
  op := Mux(io.info.valid, io.info.op, opReg)
  // ------------------------------------------------------------
  // Drive the decoupled DCache request interface.
  // ------------------------------------------------------------
  io.dcache.req.bits   := dcacheReq.bits
  io.dcache.req.valid  := dcacheReq.valid
  io.dcache.resp.ready := true.B

  // Default outputs
  io.result := 0.U
  io.ready  := (state === sIdle)
  // when((!reqValidReg && io.info.valid && (io.info.fusel === FuType.lsu))) { // 进来了一个新的 load 指令，并且我们要处理他
  // io.ready := false.B
  // }
  // ------------------------------------------------------------
  // FSM for Issuing the Request and Handling the Response
  // ------------------------------------------------------------

  io.valid := io.dcache.resp.valid
  switch(state) {
    is(sIdle) {
      // If a request is pending and the slave is ready, handshake occurs.
      when(io.dcache.req.valid) {
        io.valid := false.B
        when(io.dcache.req.ready) {

          // On handshake, clear the stored request flag and proceed.
          reqValidReg := false.B
          state       := sWait
        }
      }
    }
    is(sWait) {
      io.dcache.req.valid := false.B
      // Wait for the DCache response.
      when(io.dcache.resp.valid) {
        // If this was a load operation, generate a diffload event.
        io.valid := true.B
        when(LSUOpType.isStore(op)) { // Use the latched op from opReg.
          // Build an 8-bit valid signal for a store as: {4'b0, (llbit && sc_w), st_w, st_h, st_b}
          // For this example, we assume no store-conditional, so storeSC is false.
          val signal  = true.B
          val storeSC = false.B
          val st_w    = (op === LSUOpType.sw).asUInt
          val st_h    = (op === LSUOpType.sh).asUInt
          val st_b    = (op === LSUOpType.sb).asUInt
          val store_valid: UInt = Cat(0.U(4.W), storeSC, st_w, st_h, st_b)

          io.diffout.storeEvent.valid      := store_valid
          io.diffout.storeEvent.storePAddr := dcacheReq.bits.addr.asUInt
          io.diffout.storeEvent.storeVAddr := dcacheReq.bits.addr.asUInt
          io.diffout.storeEvent.storeData  := dcacheReq.bits.wdata
        }
        when(!LSUOpType.isStore(op)) {
          io.result := LookupTree(
            op,
            Seq(
              LSUOpType.lb  -> SignedExtend(io.dcache.resp.bits.rdata(7, 0), XLEN),
              LSUOpType.lbu -> ZeroExtend(io.dcache.resp.bits.rdata(7, 0), XLEN),
              LSUOpType.lh  -> SignedExtend(io.dcache.resp.bits.rdata(15, 0), XLEN),
              LSUOpType.lhu -> ZeroExtend(io.dcache.resp.bits.rdata(15, 0), XLEN),
              LSUOpType.lw  -> io.dcache.resp.bits.rdata
            )
          )

          // Build an 8-bit valid signal for a load as: {2'b0, ll_w, ld_w, ld_hu, ld_h, ld_bu, ld_b}
          // For this example, assume no load-linked so ll_w is false.
          val ll_w  = false.B
          val ld_w  = (op === LSUOpType.lw).asUInt
          val ld_hu = (op === LSUOpType.lhu).asUInt
          val ld_h  = (op === LSUOpType.lh).asUInt
          val ld_bu = (op === LSUOpType.lbu).asUInt
          val ld_b  = (op === LSUOpType.lb).asUInt
          val load_valid: UInt = Cat(0.U(2.W), ll_w, ld_w, ld_hu, ld_h, ld_bu, ld_b)

          io.diffout.loadEvent.valid := load_valid
          io.diffout.loadEvent.paddr := dcacheReq.bits.addr.asUInt
          io.diffout.loadEvent.vaddr := dcacheReq.bits.addr.asUInt

        }.otherwise {
          // For store ops, result is typically not used.
          io.result := 0.U
        }
        state := sIdle
      }
    }
  }
}
