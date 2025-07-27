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
    val valid    = Output(Bool())
//    val flush    = Input(Bool())
    val dcache = new Bundle {
      val req  = Decoupled(new DCacheReq)
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  val isLsu                                     = (io.info.fusel === FuType.lsu) && io.info.valid
  val sIdle :: sDrainStores :: sWaitResp :: Nil = Enum(3)
  val state                                     = RegInit(sIdle)

  val writeBuffer = Module(new WriteBuffer(depth = 4))
  writeBuffer.io.flush        := false.B
  writeBuffer.io.bypassAddr   := false.B
  writeBuffer.io.bypassEnable := false.B

  val isStore       = isLsu && LSUOpType.isStore(io.info.op)
  val isLoad        = isLsu && !isStore
  val effectiveAddr = (io.src_info.src1_data.asSInt + SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0)

  val addr_low2 = effectiveAddr(1, 0)
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
      LSUOpType.sb -> (1.U << addr_low2),
      LSUOpType.sh -> (3.U << addr_low2),
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

  // Default
  io.valid             := Mux(isStore, true.B, false.B)
  io.result            := 0.U
  io.dcache.req.valid  := false.B
  io.dcache.req.bits   := 0.U.asTypeOf(new DCacheReq)
  io.dcache.resp.ready := true.B

  // 默认接受指令
  val canEnqueue = writeBuffer.io.enq.ready
  io.ready := ((state === sIdle) && ((isStore && canEnqueue) || !isLsu)) && (!(state === sIdle && isStore))

  // Store enqueuing
  writeBuffer.io.enq.valid := (state === sIdle) && isStore && io.info.valid
  writeBuffer.io.enq.bits  := newReq
  writeBuffer.io.deq.ready := true.B

  val drainReq   = writeBuffer.io.deq
  val loadReqReg = Reg(new DCacheReq)
  val loadOpReg  = Reg(UInt(4.W))

  switch(state) {
    is(sIdle) {
      when(io.info.valid && isLoad) {
        // 收到 load 请求，进入 drain 状态
        loadReqReg := newReq
        loadOpReg  := io.info.op
        state      := sDrainStores
      }
      when(drainReq.valid && drainReq.bits.write) {
        io.dcache.req.valid := true.B
        io.dcache.req.bits  := drainReq.bits
        drainReq.ready      := io.dcache.req.ready
      }
    }

    is(sDrainStores) {
      when(drainReq.valid && drainReq.bits.write) {
        io.dcache.req.valid := true.B
        io.dcache.req.bits  := drainReq.bits
        drainReq.ready      := io.dcache.req.ready
      }
      when(!drainReq.valid) {
        // 队列清空，可以发 load
        io.dcache.req.valid := true.B
        io.dcache.req.bits  := loadReqReg
        when(io.dcache.req.ready) {
          state := sWaitResp
        }
      }
    }

    is(sWaitResp) {
      when(io.dcache.resp.valid) {
        val res = LookupTree(
          loadOpReg,
          Seq(
            LSUOpType.lb  -> SignedExtend(io.dcache.resp.bits.rdata(7, 0), XLEN),
            LSUOpType.lbu -> ZeroExtend(io.dcache.resp.bits.rdata(7, 0), XLEN),
            LSUOpType.lh  -> SignedExtend(io.dcache.resp.bits.rdata(15, 0), XLEN),
            LSUOpType.lhu -> ZeroExtend(io.dcache.resp.bits.rdata(15, 0), XLEN),
            LSUOpType.lw  -> io.dcache.resp.bits.rdata
          )
        )

        io.result := res
        io.valid  := true.B
        state     := sIdle
      }
    }
  }
}
