package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Diff extends Bundle {
  val io = IO(new Bundle {
    val debug = Flipped(new DEBUG())
    val info  = Input(new Info())
    // Outputs :
    val instrCommit = new DifftestInstrCommit()
    val excpEvent   = new DifftestExcpEvent()
    val trapEvent   = new DifftestTrapEvent()
    val storeEvent  = new DifftestStoreEvent()
    val loadEvent   = new DifftestLoadEvent()
    val csrRegState = new DifftestCSRRegState()
    val gRegState   = new DifftestGRegState()
  })
  // if I want to change store/load event, I will decode here.
  // because this module wont get boarded so no need to worry for the resource
  io.instrCommit.instr := io.info.instr
  io.instrCommit.valid := io.debug.commit
  io.instrCommit.pc    := io.debug.pc
  io.instrCommit.wdest := io.debug.rf_wnum
  io.instrCommit.wdata := io.debug.rf_wdata

}
