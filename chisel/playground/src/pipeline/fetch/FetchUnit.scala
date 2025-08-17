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

  // 队列结构 - 长度为2的PC队列
  val pc_queue    = Reg(Vec(2, UInt(XLEN.W)))
  val valid_queue = RegInit(VecInit(false.B, false.B))
  val head        = RegInit(0.U(1.W))
  val tail        = RegInit(1.U(1.W))

  // 控制信号
  val decodeReady      = io.signal.fetchUnitSignal.allow_to_go
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

  // 默认输出 - 每个周期都尝试发送请求
  io.icache_req.valid     := canStart && !io.branch
  io.icache_req.bits.addr := pc_queue(head)

  // 默认不发送指令
  io.decodeStage.data.valid := false.B
  io.decodeStage.data.inst  := DontCare
  io.decodeStage.data.pc    := DontCare
  val stall = !io.signal.fetchUnitSignal.allow_to_go

  // ========== 响应处理 ==========
  when(io.icache_resp.valid && valid_queue(tail)) {
    val resp_addr  = io.icache_resp.bits.addr
    val addr_match = resp_addr === pc_queue(tail)

    when(addr_match) {
      // 地址匹配，提取指令并发送给decode阶段
      val inst = extractInst(io.icache_resp.bits.data, pc_queue(tail))

      io.decodeStage.data.inst  := inst
      io.decodeStage.data.pc    := pc_queue(tail)
      io.decodeStage.data.valid := true.B

      // 如果decode阶段ready且没有stall，流水线正常推进
      when(!stall && !io.branch) {
        // 交换head和tail
        head := head ^ 1.U
        tail := tail ^ 1.U
        // 更新新head位置的PC
        pc_queue(head ^ 1.U) := pc_queue(tail) + 4.U
      }
    }
  }.elsewhen(!valid_queue(tail) && valid_queue(head)) {
    pc_queue(tail) := pc_queue(tail) + 4.U // 下一个周期的 head
    head           := head ^ 1.U
    tail           := tail ^ 1.U

  }

  // ========== 分支处理 ==========
  when(io.branch) {
    // flush队列：pc[head] = target, valid[tail] = false
    pc_queue(0)       := io.target
    valid_queue(tail) := false.B
    pc_queue(tail)    := false.B
    // 重置head和tail指针
    head := 0.U
    tail := 1.U
  }
  when(stall) {
    pc_queue(head)    := pc_queue(tail)
    valid_queue(head) := true.B
    valid_queue(tail) := false.B
  }
  // ========== 初始化处理 ==========
  when(canStart && pc_queue(head) === 0.U && !io.branch) {
    pc_queue(0)    := PC_INIT
    valid_queue(0) := true.B
  }

  // ========== Debug信号 ==========
  dontTouch(head)
  dontTouch(tail)
  dontTouch(pc_queue)
  dontTouch(valid_queue)
}
