package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

/** Minimal machine-mode CSR block for RV32 bare-metal programs. */
class Csr extends Module {
  val io = IO(new Bundle {
    val info = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result = Output(UInt(XLEN.W))
    val valid = Output(Bool())
  })

  val mstatus = RegInit(0.U(XLEN.W))
  val mtvec   = RegInit(0.U(XLEN.W))
  val mepc    = RegInit(0.U(XLEN.W))
  val mcause  = RegInit(0.U(XLEN.W))
  val addr    = io.info.instr(31, 20)
  val oldVal  = MuxLookup(addr, 0.U(XLEN.W))(Seq(
    "h300".U -> mstatus, "h305".U -> mtvec, "h341".U -> mepc, "h342".U -> mcause
  ))
  val writeMask = io.src_info.src1_data
  val newVal = MuxLookup(io.info.op, writeMask)(Seq(
    CSROpType.write -> writeMask,
    CSROpType.set   -> (oldVal | writeMask),
    CSROpType.clear -> (oldVal & ~writeMask)
  ))

  io.valid := io.info.valid && io.info.fusel === FuType.csr
  io.result := oldVal
  when(io.valid) {
    switch(addr) {
      is("h300".U) { mstatus := newVal }
      is("h305".U) { mtvec := newVal }
      is("h341".U) { mepc := newVal }
      is("h342".U) { mcause := newVal }
    }
  }
}
