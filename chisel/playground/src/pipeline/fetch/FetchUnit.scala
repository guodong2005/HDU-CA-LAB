package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val icache_resp = Flipped(Valid(new InstPacket))
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(new ICacheReq)
    val canStart    = Output(Bool())
  })

  // PC管理
  val pc = RegInit(PC_INIT)

  // 使用一个大小为2的队列来缓存指令
  // 队列存储的是 (inst, pc, valid) 元组
  val instQueue = Module(new Queue(new IfIdData(), entries = 2))

  // 跟踪未完成的请求数量（最多2个）
  val pendingReqs = RegInit(0.U(2.W))

  // 控制信号
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := canStart

  // 指令提取辅助函数
  def extractInst(data: UInt, pc: UInt): UInt = {
    val instIdx = pc(ICACHE_OFFSET_WIDTH - 1, 2)
    MuxLookup(instIdx, 0.U)(
      Seq(
        0.U -> data(31, 0),
        1.U -> data(63, 32),
        2.U -> data(95, 64),
        3.U -> data(127, 96),
        4.U -> data(159, 128),
        5.U -> data(191, 160),
        6.U -> data(223, 192),
        7.U -> data(255, 224)
      )
    )
  }

  // ========== 分支处理 ==========
  // 分支时清空队列和请求
  when(io.branch) {
    pc                     := io.target
    pendingReqs            := 0.U
    instQueue.io.deq.ready := true.B // 清空队列
    // 队列会自动清空（通过flush信号或连续出队）
  }

  // ========== 请求发送逻辑 ==========
  // 当队列有空间且有未完成请求的空间时，发送新请求
  val canSendReq = canStart &&
    !instQueue.io.enq.ready.asBool && // 队列未满
    pendingReqs < 2.U && // 未达到最大请求数
    !io.branch // 没有分支

  io.icache_req.valid     := canSendReq
  io.icache_req.bits.addr := pc

  // 更新PC和pending计数
  when(io.icache_req.fire) {
    pc          := pc + 4.U
    pendingReqs := pendingReqs + 1.U
  }

  // ========== 响应处理逻辑 ==========
  // 接收ICache响应并放入队列
  instQueue.io.enq.valid := false.B
  instQueue.io.enq.bits  := DontCare

  when(io.icache_resp.valid && pendingReqs > 0.U && !io.branch) {
    val resp_addr = io.icache_resp.bits.addr
    val inst      = extractInst(io.icache_resp.bits.data, resp_addr)

    // 将指令加入队列
    instQueue.io.enq.valid      := true.B
    instQueue.io.enq.bits.inst  := inst
    instQueue.io.enq.bits.pc    := resp_addr
    instQueue.io.enq.bits.valid := true.B

    // 更新pending计数
    when(instQueue.io.enq.ready) {
      pendingReqs := pendingReqs - 1.U
    }
  }.elsewhen(io.icache_resp.valid && (pendingReqs === 0.U || io.branch)) {
    // 收到了不需要的响应（可能是分支前的），忽略它
    // 不做任何操作
  }

  // ========== 输出到Decode阶段 ==========
  // 从队列出队到decode阶段
  instQueue.io.deq.ready := decodeReady && !io.branch

  io.decodeStage.data.valid := instQueue.io.deq.valid && !io.branch
  io.decodeStage.data.inst  := instQueue.io.deq.bits.inst
  io.decodeStage.data.pc    := instQueue.io.deq.bits.pc

  // ========== 初始化处理 ==========
  when(canStart && pc === 0.U && !io.branch) {
    pc := PC_INIT
  }

  // ========== 分支时的队列清空机制 ==========
  // 为了确保分支时队列被完全清空，我们需要一个flush机制
  val flushQueue = RegInit(false.B)
  when(io.branch) {
    flushQueue := true.B
  }.elsewhen(instQueue.io.count === 0.U) {
    flushQueue := false.B
  }

  when(flushQueue) {
    instQueue.io.deq.ready := true.B
    instQueue.io.enq.valid := false.B
  }

  // ========== Debug信号 ==========
  dontTouch(pendingReqs)
  dontTouch(instQueue.io.count)
}
