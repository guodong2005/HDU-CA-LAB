package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class WriteBackUnit extends Module {
  val io = IO(new Bundle {
    val writeBackStage = Input(new ExecuteUnitWriteBackUnit())
    val regfile        = Output(new RegWrite())
    val debug          = new DEBUG()
    val info           = Output(new Info())
    val result         = Output(UInt(XLEN.W))
  })
  // Register Destination info

  val validData = io.writeBackStage.data

  val canStart = RegNext(reset.asBool) & (!reset.asBool)
  // Write to the register file
  val r11data =
    io.regfile.wen := validData.info.reg_wen & validData.info.valid // Enable register write based on control signal
  io.regfile.waddr := validData.info.reg_waddr // Write to the destination register
  io.regfile.wdata := validData.rd_info.wdata // Write the computed or memory-loaded value

  io.result         := validData.rd_info.wdata
  io.info           := io.writeBackStage.data.info
  io.info.reg_wen   := io.regfile.wen
  io.info.reg_waddr := io.regfile.waddr
  // Debugging output
  io.debug.pc       := validData.pc // Track the program counter for debugging
  io.debug.wen      := io.regfile.wen
  io.debug.rf_wdata := validData.rd_info.wdata
  io.debug.rf_wnum  := validData.info.reg_waddr
  // io.debug.commit   := Fill(4, validData.info.valid && !(io.info.fusel === FuType.lsu && io.info.instr(24) === 1.U)) // ? store 不commit
  io.debug.commit := Fill(4, validData.info.valid) // ? store 不commit

  /*
  printf(p"writeBackUnit ${Hexadecimal(io.info.instr)}\n");
  printf(p"futype ${Hexadecimal(io.info.fusel)}\n");
  printf(p"wen ${Hexadecimal(io.info.reg_wen)}\n");
  printf(p"commit ${Hexadecimal(io.debug.commit)}\n");
   */
  // io.debug.commit := Fill(4, validData.info.valid) // && !(io.info.fusel === FuType.bru && io.info.instr(24) === 1.U)) // ? store 不commit

  // printf(p"PC: 0x${Hexadecimal(io.debug.pc)}, commit: 0x${Hexadecimal(io.debug.commit)}, Hexadecimal rf_wdata: 0x${Hexadecimal(io.debug.rf_wdata)}, Hexadecimal rf_wnum: 0x${Hexadecimal(io.debug.rf_wnum)}\n");
}
