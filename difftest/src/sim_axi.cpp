#include "verilated.h"
#include "Vcore_top.h"
#include "axi_memory.hpp"
#include "rv32_reference.hpp"
#include <cstdio>
#include <cstring>

int main(int argc, char** argv) {
  if (argc < 2) { std::fprintf(stderr, "usage: %s program.bin [--inject-difftest-error|--backpressure]\n", argv[0]); return 2; }
  const bool inject_error = argc > 2 && std::strcmp(argv[2], "--inject-difftest-error") == 0;
  const bool backpressure = argc > 2 && std::strcmp(argv[2], "--backpressure") == 0;
  Verilated::commandArgs(argc, argv); Vcore_top top; AxiMemory mem(0x80000000, 16*1024*1024, 2, backpressure); Rv32Reference ref;
  if (!mem.load_binary(argv[1]) || !ref.load_binary(argv[1])) { std::fprintf(stderr, "cannot load %s\n", argv[1]); return 2; }
  top.reset = 1; top.io_mei = top.io_msi = top.io_mti = top.io_sei = 0; top.clock = 0; top.eval();
  unsigned commits = 0;
  unsigned cycle = 0;
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
  return 0;
}
