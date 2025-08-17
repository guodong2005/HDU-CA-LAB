package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val icache_resp = Flipped(Valid(new InstPacket))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(new ICacheReq)
    val canStart    = Output(Bool())
  })
  io.decodeStage.data.inst  := false.B
  io.decodeStage.data.pc    := 0.U
  io.decodeStage.data.valid := false.B

  // ========== State Definitions ==========
  val pc         = RegInit(PC_INIT) // 当前正确的PC
  val prefetchPC = RegInit(PC_INIT + 4.U) // 预取PC
  val reqPC      = Reg(UInt(XLEN.W)) // 正在等待响应的PC
  val pendingReq = RegInit(false.B) // 是否有未响应的请求
  val ifid_reg   = RegInit(0.U.asTypeOf(new IfIdData()))

  // ========== Control Signals ==========
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val branch      = io.signal.branchControl.branch
  val target      = io.signal.branchControl.target

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := canStart

  // ========== Response Handling (先处理响应，避免组合逻辑环) ==========
  val respValid = RegNext(io.icache_resp.valid) // 打破组合逻辑环
  val respData  = RegNext(io.icache_resp.bits)
  val respAddr  = respData.addr
  val matchAddr = respAddr === reqPC

  // 用寄存器记录上一周期是否收到了有效响应
  val gotResponse = RegInit(false.B)
  gotResponse := io.icache_resp.valid && pendingReq

  // ========== Prefetch Logic ==========
  // 决定是否可以发送新请求（使用寄存器版本的响应信号）
  val canSendReq = canStart && (!pendingReq || gotResponse)

  // 选择请求的PC
  val nextReqPC = Wire(UInt(XLEN.W))
  when(branch) {
    nextReqPC := target
  }.elsewhen(pendingReq && gotResponse) {
    // 如果刚收到响应，发送预取地址
    nextReqPC := prefetchPC
  }.otherwise {
    // 否则发送当前PC
    nextReqPC := pc
  }

  // 发送请求
  io.icache_req.valid     := canSendReq
  io.icache_req.bits.addr := nextReqPC

  // ========== Request Tracking ==========
  when(io.icache_req.fire) {
    reqPC      := nextReqPC
    pendingReq := true.B

    // 更新prefetchPC（如果不是分支）
    when(!branch) {
      prefetchPC := nextReqPC + 4.U
    }
  }

  // ========== Process Response ==========
  when(respValid && pendingReq && matchAddr) {
    pendingReq := false.B

    // 提取对应的指令
    val instIdx = reqPC(ICACHE_OFFSET_WIDTH - 1, 2)
    val inst = MuxLookup(instIdx, 0.U)(
      Seq(
        0.U -> respData.data(31, 0),
        1.U -> respData.data(63, 32),
        2.U -> respData.data(95, 64),
        3.U -> respData.data(127, 96),
        4.U -> respData.data(159, 128),
        5.U -> respData.data(191, 160),
        6.U -> respData.data(223, 192),
        7.U -> respData.data(255, 224)
      )
    )

    // 检查是否是我们期望的PC（可能因为分支而改变）
    val isExpectedPC = reqPC === pc

    when(isExpectedPC) {
      when(decodeReady && !ifid_reg.valid) {
        // 直接发送到decode stage
        io.decodeStage.data.inst  := inst
        io.decodeStage.data.pc    := reqPC
        io.decodeStage.data.valid := true.B
        pc                        := pc + 4.U
      }.otherwise {
        // 缓存指令
        ifid_reg.inst  := inst
        ifid_reg.pc    := reqPC
        ifid_reg.valid := true.B
        pc             := pc + 4.U
      }
    }
    // 如果不是期望的PC（比如分支后的错误预取），忽略该响应
  }.otherwise {
    // 没有有效响应时，输出默认值
    when(!ifid_reg.valid || !decodeReady) {
      io.decodeStage.data.valid := false.B
      io.decodeStage.data.inst  := 0.U
      io.decodeStage.data.pc    := 0.U
    }
  }

  // ========== Buffered Instruction Handling ==========
  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
  }

  // ========== Branch Handling ==========
  when(branch) {
    pc         := target
    prefetchPC := target + 4.U

    // 清除缓存的指令（如果是错误路径上的）
    when(ifid_reg.valid && ifid_reg.pc =/= target) {
      ifid_reg.valid := false.B
    }

    // 如果有pending请求且不是目标地址，标记为需要忽略
    // 响应会在后续周期被忽略（通过isExpectedPC检查）
  }

  // ========== Cache Miss Handling ==========
  // Cache miss通过长时间没有响应来检测
  val missCounter = RegInit(0.U(8.W))
  when(pendingReq && !gotResponse) {
    missCounter := missCounter + 1.U
  }.otherwise {
    missCounter := 0.U
  }

  // 超时重试（可选，可以根据需要调整超时值）
  val timeout = missCounter === 255.U
  when(timeout) {
    pendingReq  := false.B
    missCounter := 0.U
    // 重新请求相同的地址
    pc := reqPC
  }

  // ========== Debug Signals (Optional) ==========
  // dontTouch(pc)
  // dontTouch(prefetchPC)
  // dontTouch(reqPC)
  // dontTouch(pendingReq)
  // dontTouch(gotResponse)
}
