package cpu.defines

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class ExtInterrupt extends Bundle {
  val mei = Bool()
  val mti = Bool()
  val msi = Bool()
}

class SrcInfo extends Bundle {
  val src1_data = UInt(XLEN.W)
  val src2_data = UInt(XLEN.W)
}

class RdInfo extends Bundle {
  val wdata = UInt(XLEN.W)
  val addr3 = UInt(3.W)
}

class Info extends Bundle {
  val instr      = UInt(XLEN.W)
  val valid      = Bool()
  val src1_raddr = UInt(REG_ADDR_WID.W)
  val src2_raddr = UInt(REG_ADDR_WID.W)
  val op         = FuOpType()
  val reg_wen    = Bool()
  val reg_waddr  = UInt(REG_ADDR_WID.W)
  val imm        = UInt(XLEN.W)
  val src1_ren   = Bool()
  val src2_ren   = Bool()
  val fusel      = UInt(3.W)
}

class SrcReadSignal extends Bundle {
  val ren   = Bool()
  val raddr = UInt(REG_ADDR_WID.W)
}

class InstSram extends Bundle {
  val en    = Output(Bool())
  val addr  = Output(UInt(SRAM_ADDR_WID.W))
  val wdata = Output(UInt(INST_SRAM_DATA_WID.W))
  val wen   = Output(UInt(INST_SRAM_WEN_WID.W))
  val rdata = Input(UInt(INST_SRAM_DATA_WID.W))
}

class DataSram extends Bundle {
  val en    = Output(Bool())
  val addr  = Output(UInt(SRAM_ADDR_WID.W))      // address to write
  val wdata = Output(UInt(DATA_SRAM_DATA_WID.W)) // write data
  val wen   = Output(UInt(DATA_SRAM_WEN_WID.W))  // write en
  val rdata = Input(UInt(DATA_SRAM_DATA_WID.W))  // read data
}

class DEBUG extends Bundle {
  val pc       = Output(UInt(XLEN.W))
  val commit   = Output(UInt(4.W))
  val rf_wnum  = Output(UInt(REG_ADDR_WID.W))
  val rf_wdata = Output(UInt(XLEN.W))
}

class AR extends Bundle { // Read request (ar)
  val id    = UInt(4.W)
  val addr  = UInt(32.W)
  val len   = UInt(8.W)
  val size  = UInt(3.W)
  val burst = UInt(2.W)
  val lock  = UInt(2.W)
  val cache = UInt(4.W)
  val prot  = UInt(3.W)
}

class R extends Bundle { // Read response (r)
  val id   = UInt(4.W)
  val data = UInt(32.W)
  val resp = UInt(2.W)
  val last = Bool()
}

class AW extends Bundle { // Write request (aw)
  val id    = UInt(4.W)
  val addr  = UInt(32.W)
  val len   = UInt(8.W)
  val size  = UInt(3.W)
  val burst = UInt(2.W)
  val lock  = UInt(2.W)
  val cache = UInt(4.W)
  val prot  = UInt(3.W)
}

class W extends Bundle { // Write data (w)
  val id   = UInt(4.W)
  val data = UInt(32.W)
  val strb = UInt(4.W)
  val last = Bool()
}

class B extends Bundle { // Write response (b)
  val id   = UInt(4.W)
  val resp = UInt(2.W)
}

class AXI extends Bundle {
  // Decoupled Read Request & Response
  val ar = Decoupled(new AR())         // Handshake for read request
  val r  = Flipped(Decoupled(new R())) // Read response handshake

  // Decoupled Write Request, Data & Response
  val aw = Decoupled(new AW())         // Write request handshake
  val w  = Decoupled(new W())          // Write data handshake
  val b  = Flipped(Decoupled(new B())) // Write response handshake
}
