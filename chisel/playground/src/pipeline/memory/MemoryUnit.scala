package cpu.pipeline

import chisel3._
import chisel3.util._
import chisel3.util.experimental.BoringUtils
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig
import upickle.default

class MemoryUnit extends Module {
  val io = IO(new Bundle {
    val memoryStage    = Input(new ExecuteUnitMemoryUnit())
    val writeBackStage = Output(new MemoryUnitWriteBackUnit())
    val dataSram       = new DataSram()
  })

  val info = io.memoryStage.data.info
  io.writeBackStage.data.pc   := io.memoryStage.data.pc
  io.writeBackStage.data.info := io.memoryStage.data.info
  //  val memAddr = io.dataSram.addr // I guess this wont work
  val memAddr = io.memoryStage.data.rd_info.addr3.asUInt * 8.U

// Generate LookUpTree to assign memData based on memAddr
  val memData = LookupTree(
  memAddr,
  Seq(
    0.U  -> io.dataSram.rdata(63, 0).asUInt,
    8.U  -> io.dataSram.rdata(63, 8).asUInt,
    16.U -> io.dataSram.rdata(63, 16).asUInt,
    24.U -> io.dataSram.rdata(63, 24).asUInt,
    32.U -> io.dataSram.rdata(63, 32).asUInt,
    40.U -> io.dataSram.rdata(63, 40).asUInt,
    48.U -> io.dataSram.rdata(63, 48).asUInt,
    56.U -> io.dataSram.rdata(63, 56).asUInt
  )
)
 printf(p"addr3: ${Hexadecimal(io.dataSram.addr)}, rdata: ${Hexadecimal(io.dataSram.rdata)},memData : ${Hexadecimal(memData)}\n")

  val cut = (((1.U << info.op(1,0)) << 3.U) - 1.U) // times 8

// opcode(1,0)
// 00 byte 1
// 01 half word 2
// 10 word 4 
// 11 double-word 8
// one byte = 8 bits
// Use memData in your Mux logic

  val finalMemData = Mux(
    info.fusel === FuType.lsu,
    cut & memData,
    0.U
  )
  val extendedData = Mux(
    info.op(2) === 1.U,
    ZeroExtend(finalMemData, XLEN),
    SignedExtend(finalMemData, XLEN)
  )
  io.writeBackStage.data.rd_info.wdata := Mux(info.fusel === FuType.lsu, extendedData, io.memoryStage.data.rd_info.wdata)
  io.writeBackStage.data.rd_info.addr3 := DontCare

  io.dataSram.en    := DontCare
  io.dataSram.addr  := DontCare
  io.dataSram.wdata := DontCare
  io.dataSram.wen   := DontCare
}
