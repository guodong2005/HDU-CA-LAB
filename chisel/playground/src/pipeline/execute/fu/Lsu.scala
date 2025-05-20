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
    val ready    = Output(Bool()) // Added ready signal
    val diffout  = Output(new DiffOutData())
    val dcache = new Bundle {
      val req  = (Decoupled(new DCacheReq))
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  io.diffout := DontCare
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
  // Construct DCache Request
  // ------------------------------------------------------------
  val dcacheReq = RegInit(0.U.asTypeOf(new DCacheReq))
  // ------------------------------------------------------------
  // LSU FSM
  // ------------------------------------------------------------
  val sIdle :: sWait :: Nil = Enum(2)
  val state                 = RegInit(sIdle)
  dcacheReq.addr  := effectiveAddr
  dcacheReq.write := LSUOpType.isStore(io.info.op)
  dcacheReq.wdata := Mux(LSUOpType.isStore(io.info.op), storeWdata, 0.U)
  dcacheReq.size  := size

  // Default assignments
  io.dcache.req.valid  := false.B
  io.dcache.req.bits   := dcacheReq
  io.dcache.resp.ready := true.B            // Always ready to accept a response
  io.result            := 0.U
  io.ready             := (state === sIdle) // Ready when in Idle state

  switch(state) {
    is(sIdle) {
      // When an LSU operation is active:
      when(io.info.valid && (io.info.fusel === FuType.lsu)) {
        io.dcache.req.valid := true.B
        when(io.dcache.req.ready) {
          // On handshake, if this is a store operation, generate a diffstore event.
          when(LSUOpType.isStore(io.info.op)) {
            // Define the store valid signal as:
            // {4'b0, (llbit && sc_w), st_w, st_h, st_b}
            // For this example, we assume no store‐conditional: false.B.
            val storeSC = false.B
            val st_w    = (io.info.op === LSUOpType.sw).asUInt
            val st_h    = (io.info.op === LSUOpType.sh).asUInt
            val st_b    = (io.info.op === LSUOpType.sb).asUInt
            val store_valid: UInt = Cat(0.U(4.W), storeSC.asUInt, st_w, st_h, st_b)

            io.diffout.storeEvent.valid      := store_valid
            io.diffout.storeEvent.storePAddr := effectiveAddr.asUInt
            io.diffout.storeEvent.storeVAddr := effectiveAddr.asUInt
            io.diffout.storeEvent.storeData  := storeWdata
          }
          state := sWait
        }
      }
    }
    is(sWait) {
      // Wait for the DCache response.
      when(io.dcache.resp.valid) {
        // For a load operation, compute the result and generate a diffload event.
        when(!LSUOpType.isStore(io.info.op)) {
          io.result := LookupTree(
            io.info.op,
            Seq(
              LSUOpType.lb  -> SignedExtend(io.dcache.resp.bits.rdata(7, 0), XLEN),
              LSUOpType.lbu -> ZeroExtend(io.dcache.resp.bits.rdata(7, 0), XLEN),
              LSUOpType.lh  -> SignedExtend(io.dcache.resp.bits.rdata(15, 0), XLEN),
              LSUOpType.lhu -> ZeroExtend(io.dcache.resp.bits.rdata(15, 0), XLEN),
              LSUOpType.lw  -> io.dcache.resp.bits.rdata
            )
          )
          // Define the load valid signal as:
          // {2'b0, ll_w, ld_w, ld_hu, ld_h, ld_bu, ld_b}
          // In this example, we assume no load-linked so ll_w is false.
          val ll_w  = false.B
          val ld_w  = (io.info.op === LSUOpType.lw).asUInt
          val ld_hu = (io.info.op === LSUOpType.lhu).asUInt
          val ld_h  = (io.info.op === LSUOpType.lh).asUInt
          val ld_bu = (io.info.op === LSUOpType.lbu).asUInt
          val ld_b  = (io.info.op === LSUOpType.lb).asUInt
          val load_valid: UInt = Cat(0.U(2.W), ll_w.asUInt, ld_w, ld_hu, ld_h, ld_bu, ld_b)

          io.diffout.loadEvent.valid := load_valid
          io.diffout.loadEvent.paddr := effectiveAddr.asUInt
          io.diffout.loadEvent.vaddr := effectiveAddr.asUInt
        }.otherwise {
          // For stores, the result is typically a dummy value.
          io.result := 0.U
        }
        state := sIdle
      }
    }
  }
}
