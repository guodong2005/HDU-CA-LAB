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

  io.diffout := DontCare
//   io.diffout.instrCommit.instr := io.info.instr
//   io.diffout.instrCommit.valid := io.debug.commit
//   io.diffout.instrCommit.pc    := io.debug.pc
//   io.diffout.instrCommit.wdest := io.debug.rf_wnum
//   io.diffout.instrCommit.wdata := io.debug.rf_wdata
  io.diffout.instrCommit.instr := RegNext(io.info.instr)
  io.diffout.instrCommit.valid := RegNext(io.debug.commit)
  io.diffout.instrCommit.pc    := RegNext(io.debug.pc)
  io.diffout.instrCommit.wdest := RegNext(io.debug.rf_wnum)
  io.diffout.instrCommit.wdata := RegNext(io.debug.rf_wdata)
  io.diffout.instrCommit.wen   := RegNext(io.debug.wen)

  io.diffout.loadEvent  := RegNext(io.info.diffout.loadEvent)
  io.diffout.storeEvent := RegNext(io.info.diffout.storeEvent)

  io.diffout.gRegState := io.regs_in
}
