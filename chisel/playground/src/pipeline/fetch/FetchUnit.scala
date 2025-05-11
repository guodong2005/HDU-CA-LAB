package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._

class FetchRequest extends Bundle {
  val addr  = UInt(XLEN.W)
  val valid = Bool()
}
class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage  = new FetchUnitDecodeUnit()
    val branch       = Input(Bool())
    val target       = Input(UInt(XLEN.W))
    val signal       = Input(new Signals())
    val valid        = Input(Bool())
    val inst         = Input(UInt(XLEN.W))
    val fetchrequest = Output(new FetchRequest())
  })

  val pc      = RegInit(0.U)
  val isValid = RegInit(0.U)

  val answerValid = io.valid
  val nxtpc       = Mux(io.branch === 0.U, pc + Mux(io.signal.fetchUnitSignal.allow_to_go === true.B, (4.U), (0.U)), io.target)

  val canStart = RegNext(reset.asBool) & (reset.asBool)

  // 问的不可能马上达到，所以
  io.decodeStage.data.valid := answerValid
  io.decodeStage.data.pc    := pc
  io.decodeStage.data.inst  := io.inst

  when(pc === 0.U) {
    when(canStart === false.B) {
      pc      := 0.U
      isValid := false.B
    }.otherwise {
      pc      := PC_INIT
      isValid := true.B
    }
  }.otherwise {
    pc      := nxtpc
    isValid := Mux(io.signal.fetchUnitSignal.allow_to_go === true.B, true.B, false.B)
  }

  io.fetchrequest.addr  := pc
  io.fetchrequest.valid := isValid

}

//
