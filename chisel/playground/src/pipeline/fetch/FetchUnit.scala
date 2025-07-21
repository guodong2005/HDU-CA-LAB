package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(new ICacheReq)
    val icache_resp = Flipped(Valid(new InstPacket))
  })

  // ========================================================
  //  PC 和启动控制
  // ========================================================
  val pc       = RegInit(PC_INIT)
  val canStart = RegNext(!reset.asBool) && (!reset.asBool)
  when(canStart && pc === 0.U) {
    pc := PC_INIT
  }

  // ========================================================
  //  Pipeline 暂存，用于处理 decode stall
  // ========================================================
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val ifid_reg    = RegInit(0.U.asTypeOf(new IfIdData()))
  val stall       = !decodeReady || ifid_reg.valid

  // ========================================================
  //  单请求在飞标志
  // ========================================================
  val reqActive = RegInit(false.B)
  val reqPC     = Reg(UInt(XLEN.W))

  // 默认全部信号
  io.decodeStage.data     := 0.U.asTypeOf(new IfIdData())
  io.icache_req.valid     := false.B
  io.icache_req.bits.addr := Mux(reqActive, reqPC, pc)

  // ========================================================
  //  分支优先：遇到跳转，PC 立即跳并取消未完成请求
  // ========================================================
  when(io.branch) {
    pc             := io.target
    reqActive      := false.B
    ifid_reg.valid := false.B
  }

  // ========================================================
  //  发起请求：未在飞 && 可以启动 && 不 stall && 非分支周期
  // ========================================================
  when(!reqActive && canStart && !stall && !io.branch) {
    reqActive := true.B
    reqPC     := pc
  }

  // 持续保持 valid 直到收到 resp
  io.icache_req.valid := reqActive

  // ========================================================
  //  响应到达：处理指令并更新 PC
  // ========================================================
  when(io.icache_resp.valid) {
    // 根据 offset 选择指令的条目
    val instIdx = reqPC(ICACHE_OFFSET_WIDTH - 1, 2)
    val inst    = io.icache_resp.bits.data(instIdx)

    when(decodeReady) {
      // 直接发给 decodeStage
      io.decodeStage.data.inst  := inst
      io.decodeStage.data.pc    := reqPC
      io.decodeStage.data.valid := true.B
      // 顺序执行：PC+4
      pc := reqPC + 4.U
    }.otherwise {
      // decode 阶段 busy，暂存
      ifid_reg.inst  := inst
      ifid_reg.pc    := reqPC
      ifid_reg.valid := true.B
    }
    // 请求完成，清除 in-flight
    reqActive := false.B
  }

  // ========================================================
  //  如果 decode 阶段空闲且有暂存指令，释放到 decodeStage
  // ========================================================
  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    pc                  := ifid_reg.pc + 4.U
  }
}
