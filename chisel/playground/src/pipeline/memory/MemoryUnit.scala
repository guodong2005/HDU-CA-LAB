package cpu.pipeline

import chisel3._
import chisel3.util._
import chisel3.util.experimental.BoringUtils
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class MemoryUnit extends Module {
  val io = IO(new Bundle {
    val memoryStage    = Input(new ExecuteUnitMemoryUnit())
    val writeBackStage = Output(new MemoryUnitWriteBackUnit())
    val dataSram       = new DataSram()
  })

  val info = io.memoryStage.data.info
  io.writeBackStage.data.pc   := io.memoryStage.data.pc
  io.writeBackStage.data.info := io.memoryStage.data.info
  // val memAddr = dataSram.addr  I guess this wont work
  val memAddr = io.memoryStage.data.rd_info.addr3.asUInt * 8.U
  val memData = Wire(UInt(8.W)) // Define memData as a 8-bit wide wire for flexibility

// Generate LookUpTree to assign memData based on memAddr
  switch(memAddr) {
    is(0.U) { memData := io.dataSram.rdata(7, 0).asUInt }
    is(8.U) { memData := io.dataSram.rdata(15, 8).asUInt }
    is(16.U) { memData := io.dataSram.rdata(23, 16).asUInt }
    is(24.U) { memData := io.dataSram.rdata(31, 24).asUInt }
    is(32.U) { memData := io.dataSram.rdata(39, 32).asUInt }
    is(40.U) { memData := io.dataSram.rdata(47, 40).asUInt }
    is(48.U) { memData := io.dataSram.rdata(55, 48).asUInt }
    is(56.U) { memData := io.dataSram.rdata(63, 56).asUInt }
  }

// Use memData in your Mux logic
  val finalMemData = Mux(
    info.fusel === FuType.lsu,
    memData,
    0.U
  )
  val extendedData = Mux(
    info.op(2) === 1.U,
    ZeroExtend(finalMemData, XLEN),
    SignedExtend(finalMemData, XLEN)
  )
  io.writeBackStage.data.rd_info.wdata := Mux(info.fusel === FuType.lsu, extendedData, io.memoryStage.data.rd_info.wdata)

  io.dataSram.en    := DontCare
  io.dataSram.addr  := DontCare
  io.dataSram.wdata := DontCare
  io.dataSram.wen   := DontCare
}
