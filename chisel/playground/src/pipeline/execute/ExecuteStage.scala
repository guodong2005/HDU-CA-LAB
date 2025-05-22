package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class IdExeData extends Bundle {
  val pc       = UInt(XLEN.W)
  val info     = new Info()
  val src_info = new SrcInfo()
}

class DecodeUnitExecuteUnit extends Bundle {
  val data = new IdExeData()
}

class ExecuteStage extends Module {
  val io = IO(new Bundle {
    val decodeUnit    = Input(new DecodeUnitExecuteUnit())
    val controlSignal = Input(new Signals())
    val executeUnit   = Output(new DecodeUnitExecuteUnit())
  })

  // Register to hold data
  val data = RegInit(0.U.asTypeOf(new IdExeData()))

  // Stall logic: Keep the previous data if both units' allow_to_go signals are 0
  when(
    io.controlSignal.decodeUnitSignal.allow_to_go === false.B &&
      io.controlSignal.executeUnitSignal.allow_to_go === false.B) {
    data := 0.U.asTypeOf(new IdExeData()) // Retain the previous data
  }.otherwise {
    data := io.decodeUnit.data // Update data if units are allowed to proceed
  }
  // flush logic:
  val stalledge = io.controlSignal.decodeUnitSignal.allow_to_go === false.B &&
    io.controlSignal.executeUnitSignal.allow_to_go === true.B

  when(io.controlSignal.decodeUnitSignal.do_flush === true.B || stalledge) {
    data := 0.U.asTypeOf(new IdExeData()) // Reset data if flush signal is high
    // data.info := Info.default
  }
  // Output the data to the next stage
  io.executeUnit.data := data
}
