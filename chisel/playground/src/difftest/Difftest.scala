package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Diff extends Module {
  val io = IO(new Bundle {
    val debug = Flipped(new DEBUG())
    val info  = Input(new Info())
    // Outputs :
    val diffout = Output(new DiffOut())
  })
  // if I want to change store/load event, I will decode here.
  // because this module wont get boarded so no need to worry for the resource
  io.diffout.instrCommit.instr := io.info.instr
  io.diffout.instrCommit.valid := io.debug.commit
  io.diffout.instrCommit.pc    := io.debug.pc
  io.diffout.instrCommit.wdest := io.debug.rf_wnum
  io.diffout.instrCommit.wdata := io.debug.rf_wdata

}
