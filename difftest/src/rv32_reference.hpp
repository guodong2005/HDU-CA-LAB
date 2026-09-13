#pragma once
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

struct RefCommit {
  uint32_t pc = 0, instr = 0, wdata = 0;
  uint8_t rd = 0;
  bool wen = false;
};

class Rv32Reference {
 public:
  explicit Rv32Reference(uint32_t base = 0x80000000, size_t bytes = 16 * 1024 * 1024)
      : base_(base), mem_(bytes, 0), pc_(base) {}

  bool load_binary(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;
    file.seekg(0, std::ios::end); const auto n = file.tellg(); file.seekg(0);
    if (n < 0 || static_cast<size_t>(n) > mem_.size()) return false;
    file.read(reinterpret_cast<char*>(mem_.data()), n);
    return static_cast<bool>(file);
  }

  bool at_ebreak() const { return load32(pc_) == 0x00100073u; }
  const std::string& error() const { return error_; }

  bool step(RefCommit& out) {
    const uint32_t insn = load32(pc_);
    const uint32_t opcode = insn & 0x7f, rd = (insn >> 7) & 31;
    const uint32_t funct3 = (insn >> 12) & 7, rs1 = (insn >> 15) & 31;
    const uint32_t rs2 = (insn >> 20) & 31, funct7 = insn >> 25;
    const uint32_t a = regs_[rs1], b = regs_[rs2];
    const int32_t iimm = static_cast<int32_t>(insn) >> 20;
    const int32_t simm = sign_extend((((insn >> 25) & 0x7fu) << 5) | ((insn >> 7) & 0x1fu), 12);
    const int32_t bimm = sign_extend(((insn >> 31) << 12) | (((insn >> 7) & 1) << 11) |
                                    (((insn >> 25) & 0x3f) << 5) | (((insn >> 8) & 0xf) << 1), 13);
    const int32_t jimm = sign_extend(((insn >> 31) << 20) | (((insn >> 12) & 0xff) << 12) |
                                    (((insn >> 20) & 1) << 11) | (((insn >> 21) & 0x3ff) << 1), 21);
    uint32_t next = pc_ + 4, value = 0; bool wen = false;
    out = {pc_, insn, 0, static_cast<uint8_t>(rd), false};

    switch (opcode) {
      case 0x37: value = insn & 0xfffff000u; wen = true; break;
      case 0x17: value = pc_ + (insn & 0xfffff000u); wen = true; break;
      case 0x6f: value = pc_ + 4; wen = true; next = pc_ + jimm; break;
      case 0x67:
        if (funct3 != 0) return illegal(insn);
        value = pc_ + 4; wen = true; next = (a + iimm) & ~1u; break;
      case 0x63:
        switch (funct3) {
          case 0: if (a == b) next = pc_ + bimm; break;
          case 1: if (a != b) next = pc_ + bimm; break;
          case 4: if (static_cast<int32_t>(a) < static_cast<int32_t>(b)) next = pc_ + bimm; break;
          case 5: if (static_cast<int32_t>(a) >= static_cast<int32_t>(b)) next = pc_ + bimm; break;
          case 6: if (a < b) next = pc_ + bimm; break;
          case 7: if (a >= b) next = pc_ + bimm; break;
          default: return illegal(insn);
        } break;
      case 0x03: {
        const uint32_t address = a + iimm;
        switch (funct3) {
          case 0: value = static_cast<int8_t>(load8(address)); break;
          case 1: value = static_cast<int16_t>(load16(address)); break;
          case 2: value = load32(address); break;
          case 4: value = load8(address); break;
          case 5: value = load16(address); break;
          default: return illegal(insn);
        }
        wen = true; break;
      }
      case 0x23: {
        const uint32_t address = a + simm;
        switch (funct3) {
          case 0: store8(address, b); break;
          case 1: store16(address, b); break;
          case 2: store32(address, b); break;
          default: return illegal(insn);
        } break;
      }
      case 0x13:
        wen = true;
        switch (funct3) {
          case 0: value = a + iimm; break;
          case 2: value = static_cast<int32_t>(a) < iimm; break;
          case 3: value = a < static_cast<uint32_t>(iimm); break;
          case 4: value = a ^ static_cast<uint32_t>(iimm); break;
          case 6: value = a | static_cast<uint32_t>(iimm); break;
          case 7: value = a & static_cast<uint32_t>(iimm); break;
          case 1: if (funct7) return illegal(insn); value = a << (rs2 & 31); break;
          case 5: if (funct7 == 0) value = a >> (rs2 & 31); else if (funct7 == 0x20) value = static_cast<int32_t>(a) >> (rs2 & 31); else return illegal(insn); break;
        } break;
      case 0x33:
        wen = true;
        if (funct7 == 1) {
          switch (funct3) {
            case 0: value = static_cast<uint64_t>(a) * b; break;
            case 1: value = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(a)) * static_cast<int64_t>(static_cast<int32_t>(b))) >> 32; break;
            case 2: value = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(a)) * static_cast<int64_t>(static_cast<uint64_t>(b))) >> 32; break;
            case 3: value = (static_cast<uint64_t>(a) * b) >> 32; break;
            case 4: value = divs(a, b); break;
            case 5: value = b ? a / b : 0xffffffffu; break;
            case 6: value = rems(a, b); break;
            case 7: value = b ? a % b : a; break;
          }
        } else {
          switch (funct3) {
            case 0: if (funct7 == 0) value = a + b; else if (funct7 == 0x20) value = a - b; else return illegal(insn); break;
            case 1: if (funct7) return illegal(insn); value = a << (b & 31); break;
            case 2: if (funct7) return illegal(insn); value = static_cast<int32_t>(a) < static_cast<int32_t>(b); break;
            case 3: if (funct7) return illegal(insn); value = a < b; break;
            case 4: if (funct7) return illegal(insn); value = a ^ b; break;
            case 5: if (funct7 == 0) value = a >> (b & 31); else if (funct7 == 0x20) value = static_cast<int32_t>(a) >> (b & 31); else return illegal(insn); break;
            case 6: if (funct7) return illegal(insn); value = a | b; break;
            case 7: if (funct7) return illegal(insn); value = a & b; break;
          }
        } break;
      case 0x0f: break; // FENCE is a no-op in this single-core memory model.
      default: return illegal(insn);
    }
    if (wen && rd) regs_[rd] = value;
    regs_[0] = 0; pc_ = next;
    out.wen = wen && rd; out.wdata = value;
    return true;
  }

 private:
  uint32_t base_, pc_; uint32_t regs_[32]{}; std::vector<uint8_t> mem_; std::string error_;
  static int32_t sign_extend(uint32_t value, unsigned bits) { return static_cast<int32_t>(value << (32 - bits)) >> (32 - bits); }
  bool range(uint32_t a, size_t n) const { return a >= base_ && static_cast<uint64_t>(a - base_) + n <= mem_.size(); }
  uint8_t load8(uint32_t a) const { return range(a, 1) ? mem_[a - base_] : 0; }
  uint16_t load16(uint32_t a) const { return load8(a) | (static_cast<uint16_t>(load8(a + 1)) << 8); }
  uint32_t load32(uint32_t a) const { return load16(a) | (static_cast<uint32_t>(load16(a + 2)) << 16); }
  void store8(uint32_t a, uint32_t v) { if (range(a, 1)) mem_[a - base_] = v; }
  void store16(uint32_t a, uint32_t v) { store8(a, v); store8(a + 1, v >> 8); }
  void store32(uint32_t a, uint32_t v) { store16(a, v); store16(a + 2, v >> 16); }
  bool illegal(uint32_t insn) { char text[80]; std::snprintf(text, sizeof(text), "illegal instruction %08x at %08x", insn, pc_); error_ = text; return false; }
  static uint32_t divs(uint32_t a, uint32_t b) { const int32_t x = a, y = b; if (!y) return 0xffffffffu; if (x == std::numeric_limits<int32_t>::min() && y == -1) return a; return static_cast<uint32_t>(x / y); }
  static uint32_t rems(uint32_t a, uint32_t b) { const int32_t x = a, y = b; if (!y) return a; if (x == std::numeric_limits<int32_t>::min() && y == -1) return 0; return static_cast<uint32_t>(x % y); }
};
