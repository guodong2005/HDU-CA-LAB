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
  val valid = Bool()
}
class Lsu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
    val ready    = Output(Bool()) // Added ready signal
    val diffout  = Output(new DiffOut())
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
  val dcacheReq = Wire(new DCacheReq)
  dcacheReq.addr  := effectiveAddr
  dcacheReq.write := LSUOpType.isStore(io.info.op)
  dcacheReq.wdata := Mux(LSUOpType.isStore(io.info.op), storeWdata, 0.U)
  dcacheReq.size  := size

  // ------------------------------------------------------------
  // LSU FSM
  // ------------------------------------------------------------
  val sIdle :: sWait :: Nil = Enum(2)
  val state                 = RegInit(sIdle)

  // Default assignments
  io.dcache.req.valid  := false.B
  io.dcache.req.bits   := dcacheReq
  io.dcache.resp.ready := true.B            // Always ready to accept a response
  io.result            := 0.U
  io.ready             := (state === sIdle) // Ready when in Idle state
  switch(state) {
    is(sIdle) {
      // When an LSU op is active:
      when(io.info.valid && (io.info.fusel === FuType.lsu)) {
        io.dcache.req.valid := true.B
        when(io.dcache.req.ready) {
          // On handshake, if this is a store operation, generate a diffstore event.
          when(LSUOpType.isStore(io.info.op)) {
            io.diffout.storeEvent.valid      := true.B
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
          io.diffout.loadEvent.valid := true.B
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
