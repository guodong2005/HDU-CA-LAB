package cpu

import chisel3._
import chisel3.util._
import cpu.defines.CustomOpcode

class VectorCore extends Module {
  val io = IO(new Bundle {
    val issue = Flipped(Decoupled(UInt(3.W)))
    val op = Input(UInt(2.W))
    val vs1 = Input(UInt(3.W))
    val vs2 = Input(UInt(3.W))
    val shamt = Input(UInt(2.W))
    val write = Output(Bool())
    val writeVd = Output(UInt(3.W))
    val writeData = Output(Vec(4, UInt(32.W)))
    val testWriteEnable = Input(Bool())
    val testWriteAddr = Input(UInt(3.W))
    val testWriteData = Input(Vec(4, UInt(32.W)))
    val testReadAddr = Input(UInt(3.W))
    val testReadData = Output(Vec(4, UInt(32.W)))
    val allData = Output(Vec(8, Vec(4, UInt(32.W))))
  })

  val rf = Module(new VectorRegisterFile)
  val issueFire = io.issue.valid && io.issue.ready
  rf.io.readAddr := Mux(io.issue.valid, io.vs1, io.testReadAddr)
  rf.io.readAddr2 := io.vs2
  rf.io.writeEnable := io.testWriteEnable || issueFire
  rf.io.writeAddr := Mux(io.testWriteEnable, io.testWriteAddr, io.issue.bits)
  val read1 = rf.io.readData
  val read2 = rf.io.readData2

  val result = Wire(Vec(4, UInt(32.W)))
  for (i <- 0 until 4) {
    result(i) := 0.U
    when (io.op === CustomOpcode.VAdd) { result(i) := read1(i) + read2(i) }
    when (io.op === CustomOpcode.VMul) { result(i) := (read1(i) * read2(i))(31, 0) }
  }
  when (io.op === CustomOpcode.VShift) { result := VectorPermute.shiftUp(read1, io.shamt) }
  when (io.op === CustomOpcode.VGather) { result := VectorPermute.gather(read1, read2) }
  when (io.testWriteEnable) { rf.io.writeData := io.testWriteData }
    .otherwise { rf.io.writeData := result }

  io.issue.ready := true.B
  io.write := issueFire
  io.writeVd := io.issue.bits
  io.writeData := result
  io.testReadData := rf.io.readData
  io.allData := rf.io.allData
}
