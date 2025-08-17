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
  val pc      = RegInit(PC_INIT) // 当前要取的PC
  val next_pc = RegInit(PC_INIT + 4.U) // 下一个要取的PC（用于流水线）

  // 请求追踪 - 支持流水线化
  val req_valid = RegInit(false.B) // 是否有未完成的请求
  val req_pc    = RegInit(0.U(XLEN.W)) // 正在等待响应的PC
  val req_count = RegInit(0.U(2.W)) // 未完成请求数量（最多2个）

  // 指令缓冲
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  // 控制信号
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady && ifid_reg.valid // 只有当decode不ready且有缓存指令时才stall

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := canStart

  // 分支处理标志
  val branch_taken   = RegInit(false.B)
  val flush_pipeline = io.branch || branch_taken

  // ========== ICache请求逻辑 ==========
  // 发送请求的条件：
  // 1. 系统已启动
  // 2. 没有stall
  // 3. 请求数量未满（支持最多2个流水线请求）
  // 4. 没有分支
  val can_send_req = canStart && !stall && (req_count < 2.U) && !flush_pipeline

  io.icache_req.valid     := can_send_req
  io.icache_req.bits.addr := pc

  // 更新请求状态
  when(io.icache_req.fire) {
    when(req_count === 0.U) {
      req_pc    := pc // 记录第一个请求的PC
      req_valid := true.B
    }
    req_count := req_count + 1.U
    pc        := next_pc
    next_pc   := next_pc + 4.U
  }

  // ========== ICache响应处理 ==========
  when(io.icache_resp.valid && req_valid) {
    // 提取对应的指令
    val instIdx = req_pc(ICACHE_OFFSET_WIDTH - 1, 2)
    val inst = MuxLookup(instIdx, 0.U)(
      Seq(
        0.U -> io.icache_resp.bits.data(31, 0),
        1.U -> io.icache_resp.bits.data(63, 32),
        2.U -> io.icache_resp.bits.data(95, 64),
        3.U -> io.icache_resp.bits.data(127, 96),
        4.U -> io.icache_resp.bits.data(159, 128),
        5.U -> io.icache_resp.bits.data(191, 160),
        6.U -> io.icache_resp.bits.data(223, 192),
        7.U -> io.icache_resp.bits.data(255, 224)
      )
    )

    // 响应处理
    when(flush_pipeline) {
      // 分支时丢弃响应
      req_count := req_count - 1.U
      when(req_count === 1.U) {
        req_valid := false.B
      }.otherwise {
        // 还有其他请求在路上，更新req_pc
        req_pc := req_pc + 4.U
      }
    }.otherwise {
      // 正常处理响应
      when(decodeReady && !ifid_reg.valid) {
        // 直接传递给decode
        io.decodeStage.data.inst  := inst
        io.decodeStage.data.pc    := req_pc
        io.decodeStage.data.valid := true.B
      }.otherwise {
        // 缓存指令
        ifid_reg.inst  := inst
        ifid_reg.pc    := req_pc
        ifid_reg.valid := true.B
      }

      // 更新请求追踪
      req_count := req_count - 1.U
      when(req_count === 1.U) {
        req_valid := false.B
      }.otherwise {
        // 还有请求在路上，更新req_pc为下一个
        req_pc := req_pc + 4.U
      }
    }
  }

  // ========== 缓存指令传递 ==========
  when(ifid_reg.valid && decodeReady && !io.branch) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
  }.otherwise {
    io.decodeStage.data.valid := false.B
    io.decodeStage.data.inst  := DontCare
    io.decodeStage.data.pc    := DontCare
  }

  // ========== 分支处理 ==========
  when(io.branch) {
    // 立即更新PC
    pc      := io.target
    next_pc := io.target + 4.U

    // 清空流水线
    req_count      := 0.U
    req_valid      := false.B
    ifid_reg.valid := false.B
    branch_taken   := true.B
  }.elsewhen(branch_taken && req_count === 0.U) {
    // 分支处理完成
    branch_taken := false.B
  }

  // ========== 初始化处理 ==========
  when(canStart && pc === 0.U && !io.branch) {
    pc      := PC_INIT
    next_pc := PC_INIT + 4.U
  }

  // ========== Debug信号 ==========
  dontTouch(req_count)
  dontTouch(req_pc)
  dontTouch(pc)
  dontTouch(next_pc)
}
