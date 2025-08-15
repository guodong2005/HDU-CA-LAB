package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

/** CPU–side request for a data memory access. For a store the accompanying wdata is used. For a load, wdata is "don't care." */

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
  dontTouch(writeBuffer.io)

  val isStore       = isLsu && LSUOpType.isStore(io.info.op)
  val isLoad        = isLsu && !isStore
  val effectiveAddr = (io.src_info.src1_data.asSInt + SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0)

  writeBuffer.io.bypassAddr := effectiveAddr

  val addr_low2 = effectiveAddr(1, 0)

  // 改进的size计算，模仿第一份代码的逻辑
  val size = LookupTree(
    io.info.op,
    Seq(
      LSUOpType.lb  -> 0.U(2.W),
      LSUOpType.lbu -> 0.U(2.W),
      LSUOpType.lh  -> 1.U(2.W),
      LSUOpType.lhu -> 1.U(2.W),
      LSUOpType.lw  -> 2.U(2.W),
      LSUOpType.sb  -> 0.U(2.W),
      LSUOpType.sh  -> 1.U(2.W),
      LSUOpType.sw  -> 2.U(2.W)
    )
  )

  // 改进的写掩码生成，模仿第一份代码的逻辑
  val strb = MuxCase(
    0.U(4.W),
    Seq(
      (io.info.op === LSUOpType.sb && addr_low2 === "b00".U(2.W))   -> "b0001".U(4.W),
      (io.info.op === LSUOpType.sb && addr_low2 === "b01".U(2.W))   -> "b0010".U(4.W),
      (io.info.op === LSUOpType.sb && addr_low2 === "b10".U(2.W))   -> "b0100".U(4.W),
      (io.info.op === LSUOpType.sb && addr_low2 === "b11".U(2.W))   -> "b1000".U(4.W),
      (io.info.op === LSUOpType.sh && addr_low2(0) === "b0".U(1.W)) -> "b0011".U(4.W),
      (io.info.op === LSUOpType.sh && addr_low2(0) === "b1".U(1.W)) -> "b1100".U(4.W),
      (io.info.op === LSUOpType.sw)                                 -> "b1111".U(4.W)
    )
  )

  val storeAddr = effectiveAddr(31, 2) << 2

  // 改进的写数据生成，模仿第一份代码的逻辑
  val storeWdata = LookupTree(
    io.info.op,
    Seq(
      LSUOpType.sb -> Fill(4, io.src_info.src2_data(7, 0)),
      LSUOpType.sh -> Fill(2, io.src_info.src2_data(15, 0)),
      LSUOpType.sw -> io.src_info.src2_data
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

  // 改进的load数据处理函数，模仿第一份代码的逻辑
  def gen_load_data(data: UInt, mem_addr: UInt, op: UInt): UInt = {
    val addr_low2 = mem_addr(1, 0)

    // 根据地址低2位选择正确的字节
    val byte_data = (0 until 4).map(i => Mux(addr_low2 === i.U(2.W), data(i * 8 + 7, i * 8), 0.U(8.W))).reduce(_ | _)

    // 根据地址低1位选择正确的半字
    val half_data =
      (0 until 2).map(i => Mux(addr_low2(1) === i.U(1.W), data(i * 16 + 15, i * 16), 0.U(16.W))).reduce(_ | _)

    val final_data = LookupTree(
      op,
      Seq(
        LSUOpType.lb  -> Cat(Fill(24, byte_data(7)), byte_data),
        LSUOpType.lbu -> Cat(Fill(24, 0.U(1.W)), byte_data),
        LSUOpType.lh  -> Cat(Fill(16, half_data(15)), half_data),
        LSUOpType.lhu -> Cat(Fill(16, 0.U(1.W)), half_data),
        LSUOpType.lw  -> data
      )
    )
    final_data
  }

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
        // 使用改进的load数据处理函数
        val res = gen_load_data(io.dcache.resp.bits.data, loadReqReg.addr, loadOpReg)
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
