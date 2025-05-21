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
      LSUOpType.sb -> io.src_info.src2_data(7, 0),
      LSUOpType.sh -> io.src_info.src2_data(15, 0),
      LSUOpType.sw -> io.src_info.src2_data(31, 0)
    )
  )

  val size = LookupTree(
    io.info.op,
    Seq(
      LSUOpType.lb -> 0.U(2.W),
      LSUOpType.lh -> 1.U(2.W),
      LSUOpType.lw -> 2.U(2.W),
      LSUOpType.sb -> 0.U(2.W),
      LSUOpType.sh -> 1.U(2.W),
      LSUOpType.sw -> 2.U(2.W)
    )
  )

  // ------------------------------------------------------------
  // Construct the new DCache Request combinationally.
  // ------------------------------------------------------------
  val newReq = Wire(new DCacheReq)
  newReq.addr  := effectiveAddr
  newReq.write := LSUOpType.isStore(io.info.op)
  newReq.wdata := Mux(LSUOpType.isStore(io.info.op), storeWdata, 0.U)
  newReq.size  := size

  val dcacheReqReg = RegInit(0.U.asTypeOf(new DCacheReq))
  val reqValidReg  = RegInit(false.B) // Holds whether a request is pending.
  val opReg        = RegInit(0.U(4.W))

  val sIdle :: sWait :: Nil = Enum(2)
  val state                 = RegInit(sIdle)

  dontTouch(dcacheReqReg)
  // printf(p"dcacheReqReg: ${Hexadecimal(dcacheReqReg.addr)}\n")
  when((state === sIdle) && io.info.valid && (io.info.fusel === FuType.lsu) && !reqValidReg) {
    dcacheReqReg := newReq
    reqValidReg  := true.B
    opReg        := io.info.op
  }

  // ------------------------------------------------------------
  // Drive the decoupled DCache request interface.
  // ------------------------------------------------------------
  io.dcache.req.bits   := dcacheReqReg
  io.dcache.req.valid  := reqValidReg
  io.dcache.resp.ready := true.B

  // Default outputs
  io.result := 0.U
  io.ready  := (state === sIdle) && !reqValidReg

  // ------------------------------------------------------------
  // FSM for Issuing the Request and Handling the Response
  // ------------------------------------------------------------
  switch(state) {
    is(sIdle) {
      // If a request is pending and the slave is ready, handshake occurs.
      when(reqValidReg) {
        when(io.dcache.req.ready) {
          when(LSUOpType.isStore(opReg)) { // Use the latched op from opReg.
            // Build an 8-bit valid signal for a store as: {4'b0, (llbit && sc_w), st_w, st_h, st_b}
            // For this example, we assume no store-conditional, so storeSC is false.
            val storeSC = false.B
            val st_w    = (opReg === LSUOpType.sw).asUInt
            val st_h    = (opReg === LSUOpType.sh).asUInt
            val st_b    = (opReg === LSUOpType.sb).asUInt
            val store_valid: UInt = Cat(0.U(4.W), storeSC, st_w, st_h, st_b)

            io.diffout.storeEvent.valid      := store_valid
            io.diffout.storeEvent.storePAddr := dcacheReqReg.addr.asUInt
            io.diffout.storeEvent.storeVAddr := dcacheReqReg.addr.asUInt
            io.diffout.storeEvent.storeData  := dcacheReqReg.wdata
          }
          // On handshake, clear the stored request flag and proceed.
          reqValidReg := false.B
          state       := sWait
        }
      }
    }
    is(sWait) {
      // Wait for the DCache response.
      when(io.dcache.resp.valid) {
        // If this was a load operation, generate a diffload event.
        when(!LSUOpType.isStore(opReg)) {
          io.result := LookupTree(
            opReg,
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
          val ld_w  = (opReg === LSUOpType.lw).asUInt
          val ld_hu = (opReg === LSUOpType.lhu).asUInt
          val ld_h  = (opReg === LSUOpType.lh).asUInt
          val ld_bu = (opReg === LSUOpType.lbu).asUInt
          val ld_b  = (opReg === LSUOpType.lb).asUInt
          val load_valid: UInt = Cat(0.U(2.W), ll_w, ld_w, ld_hu, ld_h, ld_bu, ld_b)

          io.diffout.loadEvent.valid := load_valid
          io.diffout.loadEvent.paddr := dcacheReqReg.addr.asUInt
          io.diffout.loadEvent.vaddr := dcacheReqReg.addr.asUInt

        }.otherwise {
          // For store ops, result is typically not used.
          io.result := 0.U
        }
        state := sIdle
      }
    }
  }
}
