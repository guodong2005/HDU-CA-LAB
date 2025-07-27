package cpu.pipeline

import chisel3._
import chisel3.util._
import chisel3.util.experimental.BoringUtils
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig
import upickle.default

class MemoryUnit extends Module {
  val io = IO(new Bundle {
    val memoryStage    = Input(new ExecuteUnitMemoryUnit())
    val writeBackStage = Output(new MemoryUnitWriteBackUnit())
    val result         = Output(UInt(XLEN.W))
  })

  io.result                            := io.memoryStage.data.rd_info.wdata
  io.writeBackStage.data.pc            := io.memoryStage.data.pc
  io.writeBackStage.data.info          := io.memoryStage.data.info
  io.writeBackStage.data.rd_info.wdata := io.memoryStage.data.rd_info.wdata
}
