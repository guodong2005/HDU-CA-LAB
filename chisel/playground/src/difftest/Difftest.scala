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
    val diffout = Output(new DiffOut())
  })

  // Register to store previous diffout state
  val diffout_reg = RegInit(0.U.asTypeOf(chiselTypeOf(io.diffout)))

  // When commit is true, update diffout with new values from debug/info
  io.diffout := DontCare
  when(io.debug.commit =/= false.B) {
    io.diffout.instrCommit.instr := io.info.instr
    io.diffout.instrCommit.valid := io.debug.commit
    io.diffout.instrCommit.pc    := io.debug.pc
    io.diffout.instrCommit.wdest := io.debug.rf_wnum
    io.diffout.instrCommit.wdata := io.debug.rf_wdata
    io.diffout.gRegState         := io.regs_in
  }.otherwise {
    // Otherwise, retain previous state from register
    io.diffout                   := diffout_reg
    io.diffout.instrCommit.valid := 0.U // Explicitly set valid to false
  }

  // Store the current `diffout` state into the register for future cycles
  diffout_reg := io.diffout
}
