package cpu

import chisel3._
import chisel3.util._

import defines._
import defines.Const._
import pipeline._
import dataclass.data

class Core extends Module {
  val io = IO(new Bundle {
    // val interrupt = Input(new ExtInterrupt())
    val interrupt = Input(UInt(8.W))
    val axi       = new AXI()
    val debug     = new DEBUG()
    val dataSram  = new DataSram()
    val Diff      = Output(new DiffOut())
  })

  val icache         = Module(new Icache())
  val axibridge      = Module(new Axibridge())
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
  val diff           = Module(new Diff())

  // 取指单元
  axibridge.io.axi    <> io.axi
  icache.io.axi       <> axibridge.io.icache
  axibridge.io.dcache := DontCare

  fetchUnit.io.decodeStage <> decodeStage.io.fetchUnit
  fetchUnit.io.inst        := icache.io.inst
  fetchUnit.io.valid       := icache.io.valid
  icache.io.fetchrequest   := fetchUnit.io.fetchrequest

  controlUnit.io.branch     := executeUnit.io.branch
  controlUnit.io.cacheStall := !icache.io.valid

  fetchUnit.io.branch := executeUnit.io.branch
  fetchUnit.io.target := executeUnit.io.target
  //
  decodeUnit.io.decodeStage  <> decodeStage.io.decodeUnit
  decodeUnit.io.regfile      <> regfile.io.read
  decodeUnit.io.executeStage <> executeStage.io.decodeUnit

  executeUnit.io.executeStage <> executeStage.io.executeUnit

  io.dataSram := DontCare

  executeUnit.io.dataSram    := DontCare
  memoryUnit.io.dataSram     := DontCare
  executeUnit.io.memoryStage <> memoryStage.io.executeUnit

  memoryUnit.io.memoryStage    <> memoryStage.io.memoryUnit
  memoryUnit.io.writeBackStage <> writeBackStage.io.memoryUnit

  writeBackUnit.io.writeBackStage <> writeBackStage.io.writeBackUnit
  writeBackUnit.io.regfile        <> regfile.io.write
  writeBackUnit.io.debug          <> io.debug

  controlUnit.io.decodeInfo    := decodeUnit.io.executeStage.data.info
  controlUnit.io.executeInfo   := executeUnit.io.memoryStage.data.info
  controlUnit.io.memoryInfo    := memoryUnit.io.writeBackStage.data.info
  controlUnit.io.writeBackInfo := writeBackStage.io.writeBackUnit.data.info

  decodeStage.io.controlSignal    := controlUnit.io.signals
  executeStage.io.controlSignal   := controlUnit.io.signals
  memoryStage.io.controlSignal    := controlUnit.io.signals
  writeBackStage.io.controlSignal := controlUnit.io.signals
  fetchUnit.io.signal             := controlUnit.io.signals

  // difftest:
  diff.io.debug   <> writeBackUnit.io.debug
  diff.io.info    := writeBackUnit.io.info
  diff.io.regs_in := regfile.io.regs_out

  io.Diff := diff.io.diffout

}
