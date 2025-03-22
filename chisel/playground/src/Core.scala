package cpu

import chisel3._
import chisel3.util._

import defines._
import defines.Const._
import pipeline._

class Core extends Module {
  val io = IO(new Bundle {
    val interrupt = Input(new ExtInterrupt())
    val instSram  = new InstSram()
    val dataSram  = new DataSram()
    val debug     = new DEBUG()
  })

  val fetchUnit      = Module(new FetchUnit())
  val decodeStage    = Module(new DecodeStage())
  val decodeUnit     = Module(new DecodeUnit())
  val regfile        = Module(new ARegFile())
  val executeStage   = Module(new ExecuteStage())
  val executeUnit    = Module(new ExecuteUnit())
  val memoryStage    = Module(new MemoryStage())
  val memoryUnit     = Module(new MemoryUnit())
  val writeBackStage = Module(new WriteBackStage())
  val writeBackUnit  = Module(new WriteBackUnit())

  // 取指单元
  fetchUnit.io.instSram <> io.instSram
  fetchUnit.io.decodeStage <> decodeStage.io.fetchUnit
  //
  decodeUnit.io.decodeStage <> decodeStage.io.decodeUnit
  decodeUnit.io.regfile <> regfile.io.read
  decodeUnit.io.executeStage <> executeStage.io.decodeUnit

  executeUnit.io.executeStage <> executeStage.io.executeUnit
  executeUnit.io.dataSram <> io.dataSram
  executeUnit.io.memoryStage <> memoryStage.io.executeUnit


  memoryUnit.io.memoryStage <> memoryStage.io.memoryUnit
  memoryUnit.io.dataSram <> io.dataSram
  memoryUnit.io.writeBackStage <> writeBackStage.io.memoryUnit

  writeBackUnit.io.writeBackStage <> writeBackStage.io.writeBackUnit
  writeBackUnit.io.regfile <> regfile.io.write
  writeBackUnit.io.debug <> io.debug



}
