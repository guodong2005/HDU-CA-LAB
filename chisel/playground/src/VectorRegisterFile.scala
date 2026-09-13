package cpu

import chisel3._

class VectorRegisterFile extends Module {
  val io = IO(new Bundle {
    val writeEnable = Input(Bool())
    val writeAddr = Input(UInt(3.W))
    val writeData = Input(Vec(4, UInt(32.W)))
    val readAddr = Input(UInt(3.W))
    val readData = Output(Vec(4, UInt(32.W)))
    val readAddr2 = Input(UInt(3.W))
    val readData2 = Output(Vec(4, UInt(32.W)))
    val allData = Output(Vec(8, Vec(4, UInt(32.W))))
  })
  val regs = RegInit(VecInit(Seq.fill(8)(VecInit(Seq.fill(4)(0.U(32.W))))))
  when (io.writeEnable) { regs(io.writeAddr) := io.writeData }
  io.readData := regs(io.readAddr)
  io.readData2 := regs(io.readAddr2)
  io.allData := regs
}
