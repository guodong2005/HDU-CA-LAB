import chisel3._
import cpu._

class core_top extends Module {
  val io = IO(new Bundle {
    val mei = Input(Bool()); val msi = Input(Bool()); val mti = Input(Bool()); val sei = Input(Bool())
    val axi = new cpu.defines.AxiMaster
    val debug_commit = Output(Bool()); val debug_pc = Output(UInt(32.W)); val debug_instr = Output(UInt(32.W))
    val debug_rf_wnum = Output(UInt(5.W)); val debug_rf_wdata = Output(UInt(32.W)); val debug_rf_wen = Output(Bool()); val debug_illegal = Output(Bool()); val halted = Output(Bool())
    val debug_vector_issue = Output(Bool()); val debug_vector_write = Output(Bool()); val debug_vector_vd = Output(UInt(3.W))
    val debug_cube_launch = Output(Bool()); val debug_cube_busy = Output(Bool()); val debug_cube_done = Output(Bool())
    val debug_cube_wait_stall = Output(Bool()); val debug_stall_reason = Output(UInt(4.W))
    val perf_cache_access = Output(Bool()); val perf_cache_hit = Output(Bool()); val perf_cache_miss = Output(Bool()); val perf_cache_miss_stall = Output(Bool())
  })
  val core = Module(new Core)
  val cache = Module(new AxiCache(4))
  cache.io.cpu <> core.io.axi
  io.axi <> cache.io.mem
  io.debug_commit := core.io.debug_commit; io.debug_pc := core.io.debug_pc; io.debug_instr := core.io.debug_instr
  io.debug_rf_wnum := core.io.debug_rd; io.debug_rf_wdata := core.io.debug_wdata; io.debug_rf_wen := core.io.debug_wen; io.debug_illegal := core.io.debug_illegal; io.halted := core.io.halted
  io.debug_vector_issue := core.io.debug_vector_issue; io.debug_vector_write := core.io.debug_vector_write; io.debug_vector_vd := core.io.debug_vector_vd
  io.debug_cube_launch := core.io.debug_cube_launch; io.debug_cube_busy := core.io.debug_cube_busy; io.debug_cube_done := core.io.debug_cube_done
  io.debug_cube_wait_stall := core.io.debug_cube_wait_stall; io.debug_stall_reason := core.io.debug_stall_reason
  io.perf_cache_access := cache.io.perfAccess; io.perf_cache_hit := cache.io.perfHit
  io.perf_cache_miss := cache.io.perfMiss; io.perf_cache_miss_stall := cache.io.perfMissStall
}
