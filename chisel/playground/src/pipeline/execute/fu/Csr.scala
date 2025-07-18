package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

import chisel3._
import chisel3.util._

class ACsrFile(width: Int) extends Module {
  val io = IO(new Bundle {
    val address   = Input(UInt(width.W))
    val readMask  = Input(UInt(width.W))
    val writeMask = Input(UInt(width.W))
    val csrOut    = Output(UInt(width.W))
  })

  val csrMap = Map(
    0xc00.U -> RegInit(0.U(width.W)), // Example CSR
    0xf11.U -> RegInit(0.U(width.W)),
    0x300.U -> RegInit(0.U(width.W))  // Add as many CSRs as needed
  )

  val readData = WireDefault(0.U(width.W))
  csrMap.foreach { case (addr, reg) =>
    when(io.address === addr) {
      readData := reg & io.readMask
      reg      := (reg & ~io.writeMask) | (io.csrOut & io.writeMask)
    }
  }

  io.csrOut := readData
}

class Csr extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val csrrw    = new ACsrFile(32) // I dont think it needs 64
    val result   = Output(UInt(XLEN.W))
  })

}
