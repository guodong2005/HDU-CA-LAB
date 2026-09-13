import chisel3._
import cpu._

class core_top extends Module {
  val io = IO(new Bundle {
    val mei = Input(Bool()); val msi = Input(Bool()); val mti = Input(Bool()); val sei = Input(Bool())
    val axi = new cpu.defines.AxiMaster
    val debug_commit = Output(Bool()); val debug_pc = Output(UInt(32.W)); val debug_instr = Output(UInt(32.W))
    val debug_rf_wnum = Output(UInt(5.W)); val debug_rf_wdata = Output(UInt(32.W)); val debug_rf_wen = Output(Bool()); val debug_illegal = Output(Bool()); val halted = Output(Bool())
  })
  val core = Module(new Core)
  val cache = Module(new AxiCache(4))
  cache.io.cpu <> core.io.axi
  io.axi <> cache.io.mem
  io.debug_commit := core.io.debug_commit; io.debug_pc := core.io.debug_pc; io.debug_instr := core.io.debug_instr
  io.debug_rf_wnum := core.io.debug_rd; io.debug_rf_wdata := core.io.debug_wdata; io.debug_rf_wen := core.io.debug_wen; io.debug_illegal := core.io.debug_illegal; io.halted := core.io.halted
}
