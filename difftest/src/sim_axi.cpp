#include "verilated.h"
#include "Vcore_top.h"
#include "axi_memory.hpp"
#include "rv32_reference.hpp"
#include <cstdio>
#include <cstring>

int main(int argc, char** argv) {
  if (argc < 2) { std::fprintf(stderr, "usage: %s program.bin [--inject-difftest-error|--backpressure|--heterogeneous-trace|--metrics]\n", argv[0]); return 2; }
  bool inject_error = false, backpressure = false, trace = false, metrics = false;
  for (int i = 2; i < argc; ++i) {
    inject_error |= std::strcmp(argv[i], "--inject-difftest-error") == 0;
    backpressure |= std::strcmp(argv[i], "--backpressure") == 0;
    trace |= std::strcmp(argv[i], "--heterogeneous-trace") == 0;
    metrics |= std::strcmp(argv[i], "--metrics") == 0;
  }
  Verilated::commandArgs(argc, argv); Vcore_top top; AxiMemory mem(0x80000000, 16*1024*1024, 2, backpressure); Rv32Reference ref;
  if (!mem.load_binary(argv[1]) || !ref.load_binary(argv[1])) { std::fprintf(stderr, "cannot load %s\n", argv[1]); return 2; }
  top.reset = 1; top.io_mei = top.io_msi = top.io_mti = top.io_sei = 0; top.clock = 0; top.eval();
  unsigned commits = 0;
  unsigned cycle = 0;
  uint64_t active_cycles = 0, cache_accesses = 0, cache_hits = 0, cache_misses = 0;
  uint64_t cache_miss_stall = 0, stores = 0, axi_ar_stall = 0, axi_aw_stall = 0, axi_w_stall = 0;
  uint64_t vector_issues = 0, cube_launches = 0, cube_busy_cycles = 0, cube_wait_cycles = 0;
  for (; cycle<100000000 && !top.io_halted && !Verilated::gotFinish(); ++cycle) {
    bool ar_ready, r_valid, r_last, aw_ready, w_ready, b_valid; uint32_t r_data; uint8_t r_id, b_id;
    if (top.reset) {
      top.io_axi_ar_ready = top.io_axi_aw_ready = top.io_axi_w_ready = 0; top.io_axi_r_valid = top.io_axi_b_valid = 0;
      top.clock = 1; top.eval(); top.clock = 0; top.eval(); top.reset = 0; continue;
    }
    mem.read_request(top.io_axi_ar_valid, ar_ready, top.io_axi_ar_bits_addr, top.io_axi_ar_bits_id);
    mem.read_response(r_valid, r_data, r_id, r_last);
    mem.accept_aw(top.io_axi_aw_valid, aw_ready, top.io_axi_aw_bits_addr, top.io_axi_aw_bits_id);
    mem.accept_w(top.io_axi_w_valid, w_ready, top.io_axi_w_bits_data, top.io_axi_w_bits_strb, top.io_axi_w_bits_id);
    mem.write_response(b_valid, b_id);
    mem.accept_read_response(r_valid && top.io_axi_r_ready); mem.accept_write_response(b_valid && top.io_axi_b_ready);
    top.io_axi_ar_ready = ar_ready; top.io_axi_r_valid = r_valid; top.io_axi_r_bits_data = r_data; top.io_axi_r_bits_id = r_id; top.io_axi_r_bits_last = r_last; top.io_axi_r_bits_resp = 0;
    top.io_axi_aw_ready = aw_ready; top.io_axi_w_ready = w_ready; top.io_axi_b_valid = b_valid; top.io_axi_b_bits_id = b_id; top.io_axi_b_bits_resp = 0;
    top.clock = 1; top.eval();
    ++active_cycles;
    cache_accesses += top.io_perf_cache_access;
    cache_hits += top.io_perf_cache_hit;
    cache_misses += top.io_perf_cache_miss;
    cache_miss_stall += top.io_perf_cache_miss_stall;
    stores += top.io_axi_aw_valid && top.io_axi_aw_ready;
    axi_ar_stall += top.io_axi_ar_valid && !top.io_axi_ar_ready;
    axi_aw_stall += top.io_axi_aw_valid && !top.io_axi_aw_ready;
    axi_w_stall += top.io_axi_w_valid && !top.io_axi_w_ready;
    vector_issues += top.io_debug_vector_issue;
    cube_launches += top.io_debug_cube_launch;
    cube_busy_cycles += top.io_debug_cube_busy;
    cube_wait_cycles += top.io_debug_cube_wait_stall;
    if (trace) {
      std::printf("TRACE cycle=%u commit=%d pc=%08x instr=%08x vector_issue=%d vector_write=%d vector_vd=%u cube_launch=%d cube_busy=%d cube_done=%d cube_wait_stall=%d stall_reason=%u\n",
                  cycle - 1, top.io_debug_commit, top.io_debug_pc, top.io_debug_instr,
                  top.io_debug_vector_issue, top.io_debug_vector_write, top.io_debug_vector_vd,
                  top.io_debug_cube_launch, top.io_debug_cube_busy, top.io_debug_cube_done,
                  top.io_debug_cube_wait_stall, top.io_debug_stall_reason);
    }
    if (top.io_debug_illegal) { std::fprintf(stderr, "ILLEGAL instruction reported by RTL\\n"); return 1; }
    if (top.io_debug_commit) {
      if (top.io_debug_instr == 0x00100073u) { std::fprintf(stderr, "DIFFTEST FAIL: EBREAK was committed as a normal instruction\\n"); return 1; }
      RefCommit expected;
      if (!ref.step(expected)) { std::fprintf(stderr, "DIFFTEST FAIL: %s\n", ref.error().c_str()); return 1; }
      if (inject_error && commits == 0) expected.wdata ^= 1;
      const bool mismatch = top.io_debug_pc != expected.pc || top.io_debug_instr != expected.instr ||
                            static_cast<bool>(top.io_debug_rf_wen) != expected.wen ||
                            (expected.wen && (top.io_debug_rf_wnum != expected.rd || top.io_debug_rf_wdata != expected.wdata));
      if (mismatch) {
        if (inject_error) { std::printf("EXPECTED DIFFTEST MISMATCH at commit %u\n", commits); return 3; }
        std::fprintf(stderr, "DIFFTEST FAIL at commit %u\n", commits);
        std::fprintf(stderr, "reference pc=%08x instr=%08x wen=%d rd=%u data=%08x\n", expected.pc, expected.instr, expected.wen, expected.rd, expected.wdata);
        std::fprintf(stderr, "rtl       pc=%08x instr=%08x wen=%d rd=%u data=%08x\n", top.io_debug_pc, top.io_debug_instr, top.io_debug_rf_wen, top.io_debug_rf_wnum, top.io_debug_rf_wdata);
        return 1;
      }
      ++commits;
    }
    mem.tick(); top.clock = 0; top.eval();
  }
  if (!top.io_halted) { std::fprintf(stderr, "DIFFTEST FAIL: core did not halt after %u cycles and %u commits\n", cycle, commits); return 1; }
  if (!ref.at_ebreak()) { std::fprintf(stderr, "DIFFTEST FAIL: RTL halted but reference is not at EBREAK\n"); return 1; }
  if (!commits) { std::fprintf(stderr, "DIFFTEST FAIL: zero instructions compared\n"); return 1; }
  std::printf("DIFFTEST PASS: compared %u commits; RTL and RV32IM reference reached EBREAK\n", commits);
  if (metrics) {
    const double cpi = static_cast<double>(active_cycles) / commits;
    const double hit_rate = cache_accesses ? 100.0 * cache_hits / cache_accesses : 0.0;
    std::printf("METRICS cycles=%llu instructions=%u cpi=%.6f cache_accesses=%llu cache_hits=%llu cache_misses=%llu cache_hit_rate=%.6f cache_miss_stall_cycles=%llu stores=%llu axi_ar_stall_cycles=%llu axi_aw_stall_cycles=%llu axi_w_stall_cycles=%llu vector_issues=%llu cube_launches=%llu cube_busy_cycles=%llu cube_wait_cycles=%llu\n",
      static_cast<unsigned long long>(active_cycles), commits, cpi,
      static_cast<unsigned long long>(cache_accesses), static_cast<unsigned long long>(cache_hits),
      static_cast<unsigned long long>(cache_misses), hit_rate,
      static_cast<unsigned long long>(cache_miss_stall), static_cast<unsigned long long>(stores),
      static_cast<unsigned long long>(axi_ar_stall), static_cast<unsigned long long>(axi_aw_stall),
      static_cast<unsigned long long>(axi_w_stall), static_cast<unsigned long long>(vector_issues),
      static_cast<unsigned long long>(cube_launches), static_cast<unsigned long long>(cube_busy_cycles),
      static_cast<unsigned long long>(cube_wait_cycles));
  }
  return 0;
}
