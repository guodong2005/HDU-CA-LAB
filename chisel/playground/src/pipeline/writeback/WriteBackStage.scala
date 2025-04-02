package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class MemWbData extends Bundle {
  val pc      = UInt(XLEN.W)
  val info    = new Info()
  val rd_info = new RdInfo()
}

class MemoryUnitWriteBackUnit extends Bundle {
  val data = new MemWbData()
}
class WriteBackStage extends Module {
  val io = IO(new Bundle {
    val memoryUnit    = Input(new MemoryUnitWriteBackUnit())
    val controlSignal = Input(new Signals())
    val writeBackUnit = Output(new MemoryUnitWriteBackUnit())
  })

  val data = RegInit(0.U.asTypeOf(new MemWbData()))
  when(io.controlSignal.memoryUnitSignal.allow_to_go === false.B) {
    data := data
  }.otherwise {
    data := io.memoryUnit.data // Update data if units are allowed to proceed
  }
  // flush logic:
  when(io.controlSignal.memoryUnitSignal.do_flush === true.B) {
    data := 0.U.asTypeOf(new MemWbData()) // Reset data if flush signal is high
  }
  // Output the data to the next stage

  data                  := io.memoryUnit.data
  io.writeBackUnit.data := data
}
