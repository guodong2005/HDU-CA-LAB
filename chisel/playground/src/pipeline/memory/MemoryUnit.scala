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
    val dataSram     = new DataSram()
  })

  val info = io.memoryStage.data.info
  io.writeBackStage.data.pc                        := io.memoryStage.data.pc
  io.writeBackStage.data.info                      := io.memoryStage.data.info
  // val memAddr = dataSram.addr  I guess this wont work
  val memAddr = io.memoryStage.data.rd_info.addr3.asUInt * 7.U
  val memData = Mux(
    info.fusel === FuType.lsu,
    io.dataSram.rdata(63, memAddr.asUInt.litValue.toInt).asUInt,
    0.U
  )
  val extendedData = Mux(
    info.op(2) === 1.U,
    ZeroExtend(memData,XLEN),
    SignedExtend(memData,XLEN)
  )
  io.writeBackStage.data.rd_info.wdata             := Mux(info.fusel === FuType.lsu,extendedData,io.memoryStage.data.rd_info.wdata)
}
