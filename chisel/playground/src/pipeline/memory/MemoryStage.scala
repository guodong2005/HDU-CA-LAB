package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class ExeMemData extends Bundle {
  val pc       = UInt(XLEN.W)
  val info     = new Info()
  val rd_info  = new RdInfo()
  val src_info = new SrcInfo()
}

class ExecuteUnitMemoryUnit extends Bundle {
  val data = new ExeMemData()
}

class MemoryStage extends Module {
  val io = IO(new Bundle {
    val executeUnit   = Input(new ExecuteUnitMemoryUnit())
    val controlSignal = Input(new Signals())
    val memoryUnit    = Output(new ExecuteUnitMemoryUnit())
  })

  val data = RegInit(0.U.asTypeOf(new ExeMemData()))
  when(
    io.controlSignal.executeUnitSignal.allow_to_go === false.B &&  // Execute unit stall
      io.controlSignal.memoryUnitSignal.allow_to_go === false.B) { // Memory unit stall
    data := data // Retain the previous data
  }.otherwise {
    data := io.executeUnit.data // Update data if units are allowed to proceed
  }
  // flush logic:
  val stalledge = io.controlSignal.executeUnitSignal.allow_to_go === false.B &&
    io.controlSignal.memoryUnitSignal.allow_to_go === true.B
  when(io.controlSignal.executeUnitSignal.do_flush === true.B || stalledge) {
    data := 0.U.asTypeOf(new ExeMemData()) // Reset data if flush signal is high
  }
  // Output the data to the next stage
  data               := io.executeUnit.data
  io.memoryUnit.data := data
  // where is DataMem ?
  // only for R-type

}
