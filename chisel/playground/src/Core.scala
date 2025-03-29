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
  val controlUnit    = Module(new ControlUnit())

  // 取指单元
  fetchUnit.io.instSram    <> io.instSram
  fetchUnit.io.decodeStage <> decodeStage.io.fetchUnit

  controlUnit.io.branch := executeUnit.io.branch
  fetchUnit.io.branch   := executeUnit.io.branch
  fetchUnit.io.target   := executeUnit.io.target
  //
  decodeUnit.io.decodeStage  <> decodeStage.io.decodeUnit
  decodeUnit.io.regfile      <> regfile.io.read
  decodeUnit.io.executeStage <> executeStage.io.decodeUnit

  executeUnit.io.executeStage <> executeStage.io.executeUnit

  executeUnit.io.dataSram.wen   <> io.dataSram.wen
  executeUnit.io.dataSram.addr  <> io.dataSram.addr
  executeUnit.io.dataSram.wdata <> io.dataSram.wdata
  executeUnit.io.dataSram.en    <> io.dataSram.en
  executeUnit.io.dataSram.rdata := DontCare

  memoryUnit.io.dataSram.rdata <> io.dataSram.rdata

  executeUnit.io.memoryStage <> memoryStage.io.executeUnit

  memoryUnit.io.memoryStage    <> memoryStage.io.memoryUnit
  memoryUnit.io.writeBackStage <> writeBackStage.io.memoryUnit

  writeBackUnit.io.writeBackStage <> writeBackStage.io.writeBackUnit
  writeBackUnit.io.regfile        <> regfile.io.write
  writeBackUnit.io.debug          <> io.debug

  controlUnit.io.decodeInfo    := decodeUnit.io.executeStage.data.info
  controlUnit.io.executeInfo   := executeUnit.io.memoryStage.data.info
  controlUnit.io.memoryInfo    := memoryUnit.io.writeBackStage.data.info
  controlUnit.io.writeBackInfo := writeBackUnit.io.info

  decodeStage.io.controlSignal    := controlUnit.io.signals
  executeStage.io.controlSignal   := controlUnit.io.signals
  memoryStage.io.controlSignal    := controlUnit.io.signals
  writeBackStage.io.controlSignal := controlUnit.io.signals
  fetchUnit.io.signal             := controlUnit.io.signals
}
