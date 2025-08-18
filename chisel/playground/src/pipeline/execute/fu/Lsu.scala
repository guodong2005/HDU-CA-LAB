package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Lsu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
    val ready    = Output(Bool())
    val valid    = Output(Bool())
    val diffout  = Output(new DiffOut())
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
  writeBuffer.io.bypassAddr   := DontCare
  writeBuffer.io.bypassEnable := false.B

  val isStore       = isLsu && LSUOpType.isStore(io.info.op)
  val isLoad        = isLsu && !isStore
  val effectiveAddr = (io.src_info.src1_data.asSInt + SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0)

  val addr_low2 = effectiveAddr(1, 0)

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

  // ============= 添加指令完成状态跟踪 =============
  val storeCompleted = RegInit(false.B)
  val loadCompleted  = RegInit(false.B)

  // 当新指令到来时重置完成状态
  when(io.info.valid && (state === sIdle)) {
    storeCompleted := false.B
    loadCompleted  := false.B
  }
  // =============================================

  // Store请求缓冲寄存器
  val storeReqReg   = RegInit(0.U.asTypeOf(new DCacheReq))
  val storeReqValid = RegInit(false.B)

  writeBuffer.io.enq.valid := storeReqValid
  writeBuffer.io.enq.bits  := storeReqReg

  when(writeBuffer.io.enq.fire) {
    storeReqValid := false.B
    // ============= Store指令完成标记 =============
    storeCompleted := true.B
    // ==========================================
  }

  when((state === sIdle) && isStore && io.info.valid && !storeReqValid) {
    storeReqReg   := newReq
    storeReqValid := true.B
  }

  // ============= 修改输出逻辑确保只valid一次 =============
  io.valid  := false.B
  io.result := 0.U

  // Store指令：只在WriteBuffer接受请求的周期输出valid
  when(isStore && writeBuffer.io.enq.fire && !storeCompleted) {
    io.valid  := true.B
    io.result := io.src_info.src1_data
  }
  // ====================================================

  io.dcache.req.valid  := false.B
  io.dcache.req.bits   := 0.U.asTypeOf(new DCacheReq)
  io.dcache.resp.ready := true.B

  val canAcceptStore = !storeReqValid || writeBuffer.io.enq.ready
  io.ready := ((state === sIdle) && ((isStore && canAcceptStore) || !isLsu))

  writeBuffer.io.deq.ready := true.B

  val drainReq   = writeBuffer.io.deq
  val loadReqReg = Reg(new DCacheReq)
  val loadOpReg  = Reg(UInt(4.W))

  def gen_load_data(data: UInt, mem_addr: UInt, op: UInt): UInt = {
    val addr_low2 = mem_addr(1, 0)
    val byte_data = (0 until 4).map(i => Mux(addr_low2 === i.U(2.W), data(i * 8 + 7, i * 8), 0.U(8.W))).reduce(_ | _)
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
        io.dcache.req.valid := true.B
        io.dcache.req.bits  := loadReqReg
        when(io.dcache.req.ready) {
          state := sWaitResp
        }
      }
    }

    is(sWaitResp) {
      when(io.dcache.resp.valid && !loadCompleted) {
        val res = gen_load_data(io.dcache.resp.bits.data, loadReqReg.addr, loadOpReg)
        io.ready      := true.B
        io.result     := res
        io.valid      := true.B
        loadCompleted := true.B // ============= 标记Load完成 =============
        state         := sIdle
      }
    }
  }

  // Diffout信号
  io.diffout                       := DontCare
  io.diffout.storeEvent.valid      := isStore && isLsu && writeBuffer.io.enq.fire && !storeCompleted
  io.diffout.storeEvent.storePAddr := newReq.addr.asUInt
  io.diffout.storeEvent.storeVAddr := newReq.addr.asUInt
  io.diffout.storeEvent.storeData  := newReq.wdata
  io.diffout.loadEvent.valid       := isLoad && isLsu && io.dcache.resp.valid && !loadCompleted
  io.diffout.loadEvent.paddr       := loadReqReg.addr.asUInt
  io.diffout.loadEvent.vaddr       := loadReqReg.addr.asUInt
}
