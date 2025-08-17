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

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := canStart

  // PC管理
  val pc = RegInit(PC_INIT)

  // 简单的2项循环队列
  val queue       = Reg(Vec(2, new IfIdData()))
  val queue_valid = RegInit(VecInit(Seq.fill(2)(false.B)))
  val queue_pc    = Reg(Vec(2, UInt(XLEN.W))) // 记录每个队列项对应的请求PC

  // 队列指针 - 只需要1位因为队列大小是2
  val head = RegInit(0.U(1.W)) // 指向下一个要输出的位置
  val tail = head ^ 1.U // 指向下一个要写入的位置

  // 队列状态
  val isEmpty = !queue_valid(head)
  val isFull  = queue_valid(tail)

  // 等待响应标志
  val waitingResp = RegInit(false.B)
  val reqPC       = RegInit(PC_INIT)

  // 控制信号
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go

  // 指令提取函数
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

  // ========== 请求发送 ==========
  // 队列不满且没有等待响应时发送请求
  io.icache_req.valid     := canStart && !isFull && !waitingResp && !io.branch
  io.icache_req.bits.addr := pc

  when(io.icache_req.fire) {
    reqPC       := pc
    pc          := pc + 4.U
    waitingResp := true.B
  }

  // ========== 响应接收 ==========
  when(io.icache_resp.valid && waitingResp && !io.branch) {
    // 检查响应的PC是否匹配我们请求的PC
    val resp_addr = io.icache_resp.bits.addr
    when(resp_addr === reqPC) {
      // 将指令写入队列的tail位置
      val inst = extractInst(io.icache_resp.bits.data, reqPC)
      queue(tail).inst  := inst
      queue(tail).pc    := reqPC
      queue(tail).valid := true.B
      queue_valid(tail) := true.B
      queue_pc(tail)    := reqPC

      waitingResp := false.B
    }
    // 如果PC不匹配，忽略这个响应（可能是分支前的）
  }

  // ========== 输出到Decode ==========
  io.decodeStage.data.valid := !isEmpty && decodeReady && !io.branch
  io.decodeStage.data.inst  := queue(head).inst
  io.decodeStage.data.pc    := queue(head).pc

  // 出队操作
  when(!isEmpty && decodeReady && !io.branch) {
    queue_valid(head) := false.B
    head              := head ^ 1.U // 移动到下一个位置
  }

  // ========== 分支处理 ==========
  when(io.branch) {
    // 更新PC
    pc    := io.target
    reqPC := io.target

    // 清空队列
    queue_valid.foreach(_ := false.B)
    waitingResp           := false.B
    head                  := 0.U // 重置队列指针
  }

  // ========== 初始化 ==========
  when(canStart && pc === 0.U && !io.branch) {
    pc    := PC_INIT
    reqPC := PC_INIT
  }

  // Debug
  dontTouch(head)
  dontTouch(isEmpty)
  dontTouch(isFull)
  dontTouch(waitingResp)
}
