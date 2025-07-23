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

  val pc       = RegInit(PC_INIT)
  val reqPC    = RegInit(PC_INIT)
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  // 是否可以发起新请求（无障碍且 cache 准备好）
  val allowRequest = !stall && io.icache_req.ready

  // 请求地址：使用当前 PC
  io.icache_req.bits.addr := pc
  io.icache_req.valid     := allowRequest

  // 发起请求时记录 PC
  when(allowRequest) {
    reqPC := pc
  }

  // 分支跳转处理：立即更新 PC，发起新请求
  when(io.branch) {
    pc    := io.target
    reqPC := io.target
  }

  // 解析指令所在位置
  val instIdx = reqPC(ICACHE_OFFSET_WIDTH - 1, 2)
  val inst    = io.icache_resp.bits.data(instIdx)

  // 默认输出无效
  io.decodeStage.data := 0.U.asTypeOf(new IfIdData())

  // 响应正确则处理指令
  when(io.icache_resp.valid && io.icache_resp.bits.addr === reqPC) {
    when(decodeReady) {
      io.decodeStage.data.inst  := inst
      io.decodeStage.data.pc    := reqPC
      io.decodeStage.data.valid := true.B
      pc                        := Mux(io.branch, io.target, reqPC + 4.U)
    }.otherwise {
      ifid_reg.inst  := inst
      ifid_reg.pc    := reqPC
      ifid_reg.valid := true.B
    }
  }

  // Pipeline 回填
  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    pc                  := Mux(io.branch, io.target, reqPC + 4.U)
  }
}
