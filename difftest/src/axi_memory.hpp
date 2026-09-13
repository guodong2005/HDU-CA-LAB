#pragma once
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>



// Cycle-accurate, single-beat AXI memory slave for Verilator.
// Reads have a programmable response delay; writes require independent AW/W handshakes.
class AxiMemory {
 public:
  explicit AxiMemory(uint32_t base = 0x80000000, size_t bytes = 16 * 1024 * 1024,
                     unsigned read_delay = 2)
      : base_(base), mem_(bytes, 0), read_delay_(read_delay) {}

  bool load_binary(const std::string& path, uint32_t address = 0x80000000) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;
    file.seekg(0, std::ios::end); const auto n = file.tellg(); file.seekg(0);
    if (n < 0) return false;
    std::vector<uint8_t> data(static_cast<size_t>(n)); file.read(reinterpret_cast<char*>(data.data()), n);
    return write_bytes(address, data.data(), data.size());
  }
  void read_request(bool valid, bool& ready, uint32_t addr, uint8_t id) {
    ready = !read_pending_;
    if (valid && ready) { read_pending_ = true; read_addr_ = addr; read_id_ = id; countdown_ = read_delay_; }
  }
  void read_response(bool& valid, uint32_t& data, uint8_t& id, bool& last) {
    valid = read_pending_ && countdown_ == 0;
    data = load_word(read_addr_); id = read_id_; last = true;


  }
  void accept_read_response(bool fire) { if (fire) read_pending_ = false; }
  void accept_aw(bool valid, bool& ready, uint32_t addr, uint8_t id) {
    ready = !aw_pending_;
    if (valid && ready) { aw_pending_ = true; aw_addr_ = addr; aw_id_ = id; }
  }
  void accept_w(bool valid, bool& ready, uint32_t data, uint8_t strb, uint8_t id) {
    ready = aw_pending_ && !w_pending_;
    if (valid && ready) {
      w_pending_ = true; w_data_ = data; w_strb_ = strb; w_id_ = id;
      store_word(aw_addr_, data, strb); b_id_ = aw_id_; b_pending_ = true;
      aw_pending_ = false; w_pending_ = false;
    }
  }
  void write_response(bool& valid, uint8_t& id) { valid = b_pending_; id = b_id_; }
  void accept_write_response(bool fire) { if (fire) b_pending_ = false; }
  void tick() { if (read_pending_ && countdown_) --countdown_; }
 private:
  uint32_t base_; std::vector<uint8_t> mem_; unsigned read_delay_; unsigned countdown_ = 0;
  bool read_pending_ = false; uint32_t read_addr_ = 0; uint8_t read_id_ = 0;
  bool aw_pending_ = false, w_pending_ = false, b_pending_ = false;
  uint32_t aw_addr_ = 0, w_data_ = 0; uint8_t aw_id_ = 0, w_id_ = 0, b_id_ = 0, w_strb_ = 0;
  bool in_range(uint32_t a) const { return a >= base_ && static_cast<uint64_t>(a - base_) + 4 <= mem_.size(); }
  uint32_t load_word(uint32_t a) const { if (!in_range(a)) return 0; const auto o = a - base_; return mem_[o] | (mem_[o+1]<<8) | (mem_[o+2]<<16) | (mem_[o+3]<<24); }
  void store_word(uint32_t a, uint32_t d, uint8_t s) { if (!in_range(a)) return; const auto o = a - base_; for (unsigned i=0;i<4;i++) if (s & (1u<<i)) mem_[o+i] = d>>(8*i); }
  bool write_bytes(uint32_t a, const uint8_t* p, size_t n) { if (a < base_ || static_cast<uint64_t>(a-base_)+n > mem_.size()) return false; std::copy(p,p+n,mem_.begin()+(a-base_)); return true; }
};
