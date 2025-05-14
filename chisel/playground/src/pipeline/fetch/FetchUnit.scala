package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._
import cpu.defines.Instructions.NOP

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

  val freetogo = io.signal.fetchUnitSignal.allow_to_go
  val nxtpc    = Mux(io.branch === 0.U, pc + Mux(freetogo === true.B, (4.U), (0.U)), io.target)
  // printf(p"nxtpc: ${Hexadecimal(nxtpc)}\n");
  val canStart = RegNext(!reset.asBool) & (!reset.asBool)

  io.decodeStage.data.valid := io.valid
  io.decodeStage.data.pc    := pc
  io.decodeStage.data.inst  := Mux(io.valid === true.B, io.inst, NOP)

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
    isValid := io.signal.fetchUnitSignal.allow_to_go
  }

  io.fetchrequest.addr  := pc
  io.fetchrequest.valid := isValid

}

//
