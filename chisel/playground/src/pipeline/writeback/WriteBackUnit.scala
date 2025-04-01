package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class WriteBackUnit extends Module {
  val io = IO(new Bundle {
    val writeBackStage = Input(new MemoryUnitWriteBackUnit())
    val regfile        = Output(new RegWrite())
    val debug          = new DEBUG()
  })
  // Register Destination info
  
  val validData = io.writeBackStage.data

  // Write to the register file
  io.regfile.wen := validData.info.reg_wen&validData.info.valid // Enable register write based on control signal
  io.regfile.waddr := validData.info.reg_waddr // Write to the destination register
  io.regfile.wdata := validData.rd_info.wdata // Write the computed or memory-loaded value

  // Debugging output
  io.debug.pc := validData.pc // Track the program counter for debugging
  io.debug.rf_wdata := validData.rd_info.wdata
  io.debug.rf_wnum := validData.info.reg_waddr
  //io.debug.commit := validData.info.reg_wen&validData.info.valid // ?
  io.debug.commit := validData.info.valid // ?
}
