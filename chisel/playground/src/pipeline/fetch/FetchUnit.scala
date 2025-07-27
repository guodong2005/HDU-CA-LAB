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

  val pc    = RegInit(0.U(XLEN.W))
  val reqPC = Reg(UInt(XLEN.W))
  val state = RegInit(0.U(2.W)) // sIdle :: sWait
  val sIdle = 0.U
  val sWait = 1.U

  val ifid_reg    = RegInit(0.U.asTypeOf(new IfIdData()))
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  val alignedPC = pc & ~((1 << ICACHE_OFFSET_WIDTH) - 1).U
  val instIdx   = pc(ICACHE_OFFSET_WIDTH - 1, 2)

  // ✅ 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := state === sIdle && !stall && RegNext(canStart)

  // ✅ 默认输出
  io.icache_req.bits.addr := pc
  io.icache_req.valid     := io.canStart
  io.decodeStage.data     := 0.U.asTypeOf(new IfIdData())

  pc := Mux(io.branch, io.target, pc)
  switch(state) {
    is(sIdle) {
      when(canStart && pc === 0.U) {
        pc := PC_INIT
      }

      when(io.canStart && io.icache_req.ready) {
        reqPC := pc
        state := sWait
      }
    }

    is(sWait) {
      val respLineAddr = io.icache_resp.bits.addr
      val reqLineAddr  = reqPC & ~((1 << ICACHE_OFFSET_WIDTH) - 1).U
      val inst         = io.icache_resp.bits.data(reqPC(ICACHE_OFFSET_WIDTH - 1, 2))
      val matchAddr    = respLineAddr === reqPC

      when(io.branch) {
        pc    := io.target
        state := sIdle
      }.elsewhen(io.icache_resp.valid && matchAddr) {
        when(decodeReady) {
          io.decodeStage.data.inst  := inst
          io.decodeStage.data.pc    := reqPC
          io.decodeStage.data.valid := true.B
          pc                        := Mux(io.branch, io.target, reqPC + 4.U)
          state                     := sIdle
        }.otherwise {
          ifid_reg.inst  := inst
          ifid_reg.pc    := reqPC
          ifid_reg.valid := true.B
        }
      }
    }
  }

  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    pc                  := Mux(io.branch, io.target, ifid_reg.pc + 4.U)
    state               := sIdle
  }
}
