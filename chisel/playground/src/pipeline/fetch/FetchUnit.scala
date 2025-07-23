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

  val pc        = RegInit(PC_INIT)
  val nextPC    = WireDefault(pc)
  val reqActive = RegInit(false.B)
  val reqPC     = Reg(UInt(XLEN.W))
  val blockResp = RegInit(false.B)

  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val ifid_reg    = RegInit(0.U.asTypeOf(new IfIdData()))
  val stall       = !decodeReady || ifid_reg.valid

  val allowRequest = !reqActive && !stall && !blockResp
  io.icache_req.bits.addr := Mux(reqActive, reqPC, nextPC)
  io.icache_req.valid     := reqActive && !blockResp

  io.decodeStage.data := 0.U.asTypeOf(new IfIdData())

  // ============================ 分支处理 =============================
  when(io.branch) {
    nextPC         := io.target
    pc             := io.target
    reqActive      := false.B
    blockResp      := true.B
    ifid_reg.valid := false.B
  }

  when(blockResp && io.icache_req.ready) {
    reqActive := true.B
    reqPC     := pc
    blockResp := false.B
  }

  when(allowRequest && io.icache_req.ready && !io.branch) {
    reqActive := true.B
    reqPC     := pc
  }

  // =========================== 响应处理 ==============================
  val instIdx = reqPC(ICACHE_OFFSET_WIDTH - 1, 2)
  val inst    = io.icache_resp.bits.data(instIdx)

  when(reqActive && io.icache_resp.valid && !blockResp) {
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
    reqActive := false.B
  }
  when(blockResp) {
    io.decodeStage.data.inst  := 0.U
    io.decodeStage.data.pc    := 0.U
    io.decodeStage.data.valid := false.B

  }

  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    pc                  := Mux(io.branch, io.target, ifid_reg.pc + 4.U)
  }
}
