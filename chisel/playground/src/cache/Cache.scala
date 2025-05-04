package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Icache extends Module {
  val io = IO(new Bundle {
    val axi   = new AXI()
    val addr  = Input(UInt(32.W))
    val inst  = Output(UInt(32.W))
    val valid = Output(UInt(32.W))
  })
  io.axi              := DontCare
  io.axi.ar.valid     := true.B
  io.axi.ar.bits.addr := io.addr
  io.axi.ar.bits.size := 4.U

  io.valid := io.axi.r.valid;
  io.inst  := io.axi.r.bits.data;
}
