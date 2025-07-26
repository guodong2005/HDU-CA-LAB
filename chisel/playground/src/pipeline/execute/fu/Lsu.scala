package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

/** CPU–side request for a data memory access. For a store the accompanying wdata is used. For a load, wdata is “don’t care.” */
class DCacheReq extends Bundle {
  val addr  = UInt(XLEN.W)
  val write = Bool() // false: load; true: store
  val wdata = UInt(XLEN.W) // valid only if write is true
  val wstrb = UInt(4.W) // byte write mask
  val size  = UInt(2.W) // 0: byte, 1: half-word, 2: word
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
    val ready    = Output(Bool())
    val diffout  = Output(new DiffOut())
    val valid    = Output(Bool())
//    val enableLoadBypass = Input(Bool()) // 控制是否打开 bypass
    val dcache = new Bundle {
      val req  = Decoupled(new DCacheReq)
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  val writeBuffer = Module(new WriteBuffer(4))

  val sIdle :: sWaitingResp :: Nil = Enum(2)
  val state                        = RegInit(sIdle)

  val isStore = LSUOpType.isStore(io.info.op)
  val isLoad  = !isStore

  val effectiveAddr = (io.src_info.src1_data.asSInt + SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0)
  val addrLow2      = effectiveAddr(1, 0)
  val size = LookupTree(
    io.info.op,
    Seq(
      LSUOpType.lb -> 0.U,
      LSUOpType.lh -> 1.U,
      LSUOpType.lw -> 2.U
    )
  )
  val strb = LookupTree(
    io.info.op,
    Seq(
      LSUOpType.sb -> (1.U << addrLow2),
      LSUOpType.sh -> (3.U << addrLow2),
      LSUOpType.sw -> 15.U
    )
  )

  val storeAddr = effectiveAddr(31, 2) << 2
  val storeWdata = LookupTree(
    io.info.op,
    Seq(
      LSUOpType.sb -> Fill(4, io.src_info.src2_data(7, 0)),
      LSUOpType.sh -> Fill(2, io.src_info.src2_data(15, 0)),
      LSUOpType.sw -> io.src_info.src2_data(31, 0)
    )
  )

  val newReq = Wire(new DCacheReq)
  newReq.addr  := Mux(isStore, storeAddr, effectiveAddr)
  newReq.write := isStore
  newReq.wdata := Mux(isStore, storeWdata, 0.U)
  newReq.wstrb := strb
  newReq.size  := size

  // Enqueue into WriteBuffer
  val canAcceptReq = writeBuffer.io.enq.ready
  io.ready                 := (state === sIdle) && canAcceptReq
  writeBuffer.io.enq.valid := io.info.valid && (state === sIdle)
  writeBuffer.io.enq.bits  := newReq

  // Query load bypass
  writeBuffer.io.bypassAddr   := effectiveAddr
  writeBuffer.io.bypassEnable := isLoad && false.B
  val bypassHit  = writeBuffer.io.bypassHit
  val bypassData = writeBuffer.io.bypassData

  // Issue store
  val issueReq       = writeBuffer.io.deq
  val isIssuingStore = issueReq.valid && issueReq.bits.write
  issueReq.ready := false.B // default

  io.dcache.req.valid := false.B
  io.dcache.req.bits  := 0.U.asTypeOf(new DCacheReq)

  val currentReq = Reg(new DCacheReq)
  val currentOp  = Reg(UInt(4.W))

  switch(state) {
    is(sIdle) {
      when(isIssuingStore) {
        io.dcache.req.valid := true.B
        io.dcache.req.bits  := issueReq.bits
        issueReq.ready      := io.dcache.req.ready
        when(io.dcache.req.ready) {
          state := sWaitingResp
        }
      }
        .elsewhen(issueReq.valid && !issueReq.bits.write && writeBuffer.io.deq.ready) {
          // Load logic: wait until writeBuffer empty
          io.dcache.req.valid := true.B
          io.dcache.req.bits  := issueReq.bits
          issueReq.ready      := io.dcache.req.ready
          when(io.dcache.req.ready) {
            currentReq := issueReq.bits
            currentOp  := io.info.op
            state      := sWaitingResp
          }
        }
    }

    is(sWaitingResp) {
      io.dcache.req.valid := false.B
      when(io.dcache.resp.valid) {
        state    := sIdle
        io.valid := true.B
        when(!currentReq.write) {
          val res = LookupTree(
            currentOp,
            Seq(
              LSUOpType.lb  -> SignedExtend(io.dcache.resp.bits.rdata(7, 0), XLEN),
              LSUOpType.lbu -> ZeroExtend(io.dcache.resp.bits.rdata(7, 0), XLEN),
              LSUOpType.lh  -> SignedExtend(io.dcache.resp.bits.rdata(15, 0), XLEN),
              LSUOpType.lhu -> ZeroExtend(io.dcache.resp.bits.rdata(15, 0), XLEN),
              LSUOpType.lw  -> io.dcache.resp.bits.rdata
            )
          )

          io.result := Mux(bypassHit, bypassData, res)
        }.otherwise {
          io.result := 0.U
        }
      }
    }
  }

  io.dcache.resp.ready := true.B
  io.diffout           := DontCare
}
