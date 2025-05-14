package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Diff extends Module {
  val io = IO(new Bundle {
    val debug   = Flipped(new DEBUG())
    val info    = Input(new Info())
    val regs_in = Input(Vec(AREG_NUM, UInt(XLEN.W)))
    // Outputs:
    val diffout = Output(new DiffOut())
  })

  // Register to store previous diffout state
  val diffout_reg = RegInit(0.U.asTypeOf(new DiffOut()))

  when(io.debug.commit =/= false.B) {
    // Update diffout_reg when commit is valid
    diffout_reg.instrCommit.instr := io.info.instr
    diffout_reg.instrCommit.valid := io.debug.commit
    diffout_reg.instrCommit.pc    := io.debug.pc
    diffout_reg.instrCommit.wdest := io.debug.rf_wnum
    diffout_reg.instrCommit.wdata := io.debug.rf_wdata
    diffout_reg.gRegState         := io.regs_in
    io.diffout.instrCommit.instr  := io.info.instr
    io.diffout.instrCommit.valid  := io.debug.commit
    io.diffout.instrCommit.pc     := io.debug.pc
    io.diffout.instrCommit.wdest  := io.debug.rf_wnum
    io.diffout.instrCommit.wdata  := io.debug.rf_wdata
    io.diffout.gRegState          := io.regs_in
  }.otherwise {
    io.diffout := diffout_reg
  }

  // Set output based on stored state
  io.diffout.instrCommit.valid := Mux(io.debug.commit =/= false.B, io.debug.commit, 0.U)
}
