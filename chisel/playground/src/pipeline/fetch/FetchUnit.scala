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

  // ========== Prefetch Logic ==========
  // 现在ICache是流水线化的，不会产生组合逻辑环
  // 可以直接使用io.icache_resp.valid
  val canSendReq = canStart && (!pendingReq || io.icache_resp.valid)

  // 选择请求的PC
  val nextReqPC = Wire(UInt(XLEN.W))
  when(branch) {
    nextReqPC := target
  }.elsewhen(pendingReq && io.icache_resp.valid) {
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
    }.otherwise {
      prefetchPC := target + 4.U
    }
  }

  // ========== Response Handling ==========
  val respValid = io.icache_resp.valid && pendingReq
  val respAddr  = io.icache_resp.bits.addr
  val matchAddr = respAddr === reqPC

  // 默认输出
  io.decodeStage.data.valid := false.B
  io.decodeStage.data.inst  := 0.U
  io.decodeStage.data.pc    := 0.U

  when(respValid && matchAddr) {
    pendingReq := false.B

    // 提取对应的指令
    val instIdx = reqPC(ICACHE_OFFSET_WIDTH - 1, 2)
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

    // 如果有pending请求且不是目标地址，后续会通过isExpectedPC检查忽略
  }

  // ========== Cache Miss Handling ==========
  // Cache miss通过长时间没有响应来检测
  val missCounter = RegInit(0.U(10.W))
  when(pendingReq && !io.icache_resp.valid) {
    missCounter := missCounter + 1.U
  }.otherwise {
    missCounter := 0.U
  }

  // 超时重试（可选，可以根据需要调整超时值）
  val timeout = missCounter === 1023.U
  when(timeout) {
    pendingReq  := false.B
    missCounter := 0.U
    // 不改变PC，下个周期会重新请求
  }

  // ========== Debug Signals (Optional) ==========
  // dontTouch(pc)
  // dontTouch(prefetchPC)
  // dontTouch(reqPC)
  // dontTouch(pendingReq)
}
