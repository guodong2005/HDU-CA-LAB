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
      0.U  -> ZeroExtend(io.dataSram.rdata(63, 0), XLEN),
      8.U  -> ZeroExtend(io.dataSram.rdata(63, 8), XLEN),
      16.U -> ZeroExtend(io.dataSram.rdata(63, 16), XLEN),
      24.U -> ZeroExtend(io.dataSram.rdata(63, 24), XLEN),
      32.U -> ZeroExtend(io.dataSram.rdata(63, 32), XLEN),
      40.U -> ZeroExtend(io.dataSram.rdata(63, 40), XLEN),
      48.U -> ZeroExtend(io.dataSram.rdata(63, 48), XLEN),
      56.U -> ZeroExtend(io.dataSram.rdata(63, 56), XLEN)
    )
  )
  printf(p"addr3: ${Hexadecimal(io.dataSram.addr)}, rdata: ${Hexadecimal(io.dataSram.rdata)},memData : ${Hexadecimal(memData)}\n")

// opcode(1,0)
// 00 byte 1
// 01 half word 2
// 10 word 4
// 11 double-word 8
// one byte = 8 bits
// Use memData in your Mux logic

  val finalMemData = LookupTree(
    info.op,
    Seq(
      LSUOpType.lb -> memData(7, 0),  // Store Byte: lowest 8 bits
      LSUOpType.lh -> memData(15, 0), // Store Halfword: lowest 16 bits
      LSUOpType.lw -> memData(31, 0), // Store Word: lowest 32 bits
      LSUOpType.ld -> memData                // Store Doubleword: full 64 bits
    )
  )
  printf(p"finalMemData: ${Hexadecimal(finalMemData)},info.op : ${info.op}\n")
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
