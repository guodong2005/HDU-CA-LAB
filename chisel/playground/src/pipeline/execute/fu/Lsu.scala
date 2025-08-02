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
    val diffout  = Output(new DiffOut())
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
  writeBuffer.io.bypassEnable := true.B

  val isStore       = isLsu && LSUOpType.isStore(io.info.op)
  val isLoad        = isLsu && !isStore
  val effectiveAddr = (io.src_info.src1_data.asSInt + SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0)

  writeBuffer.io.bypassAddr := effectiveAddr

  val addr_low2 = effectiveAddr(1, 0)
  val size = MuxCase(
    2.U(2.W),
    Seq(
      (!LSUOpType.isStore(io.info.op) && (io.info.op === LSUOpType.lb)) -> 0.U(2.W),
      (!LSUOpType.isStore(io.info.op) && (io.info.op === LSUOpType.lh)) -> 1.U(2.W),
      (!LSUOpType.isStore(io.info.op) && (io.info.op === LSUOpType.lw)) -> 2.U(2.W)
    )
  )

// Generate write strobe (`strb`) based on the operation and address alignment
  val strb = MuxCase(
    0.U(4.W),
    Seq(
      (io.info.op === LSUOpType.sb) -> (1.U(4.W) << addr_low2), // Byte write
      (io.info.op === LSUOpType.sh) -> (3.U(4.W) << addr_low2), // Half-word write (2 bytes)
      (io.info.op === LSUOpType.sw) -> 15.U(4.W) // Full-word write (4 bytes, all bits set)
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
  io.ready := ((state === sIdle) && ((isStore && canEnqueue) || !isLsu))

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
            LSUOpType.lb  -> SignedExtend(io.dcache.resp.bits.rdata(31, 24), XLEN),
            LSUOpType.lbu -> ZeroExtend(io.dcache.resp.bits.rdata(31, 24), XLEN),
            LSUOpType.lh  -> SignedExtend(io.dcache.resp.bits.rdata(31, 16), XLEN),
            LSUOpType.lhu -> ZeroExtend(io.dcache.resp.bits.rdata(31, 16), XLEN),
            LSUOpType.lw  -> io.dcache.resp.bits.rdata
          )
        )
        io.ready  := true.B
        io.result := res
        io.valid  := true.B
        state     := sIdle
      }
    }
  }
  io.diffout                       := DontCare
  io.diffout.storeEvent.valid      := isStore && isLsu && io.valid
  io.diffout.storeEvent.storePAddr := newReq.addr.asUInt
  io.diffout.storeEvent.storeVAddr := newReq.addr.asUInt
  io.diffout.storeEvent.storeData  := newReq.wdata
  io.diffout.loadEvent.valid       := isLoad && isLsu && io.valid
  io.diffout.loadEvent.paddr       := loadReqReg.addr.asUInt
  io.diffout.loadEvent.vaddr       := loadReqReg.addr.asUInt

}
