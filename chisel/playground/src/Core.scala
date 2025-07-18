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
    val diff      = new DiffOut()
  })

  val icache         = Module(new ICache())
  val dcache         = Module(new DCache)
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
  axibridge.io.axi                      <> io.axi
  axibridge.io.icacheInput.ar.bits.id   := 0.U // AXI ID for icache
  axibridge.io.icacheInput.ar.bits.size := 2.U
  axibridge.io.icacheInput.ar.valid     := icache.io.io_read_req.valid
  axibridge.io.icacheInput.ar.bits.addr := icache.io.io_read_req.bits.addr
  icache.io.io_read_req.ready           := axibridge.io.icacheInput.ar.ready

  axibridge.io.icacheInput.r.ready := true.B
  icache.io.io_read_resp.valid     := axibridge.io.icacheInput.r.valid
  icache.io.io_read_resp.bits.data := axibridge.io.icacheInput.r.bits.data
  dcache.io.axi                    <> axibridge.io.dcacheInput

  fetchUnit.io.decodeStage <> decodeStage.io.fetchUnit

  icache.io.icache_req.valid     := fetchUnit.io.fetchrequest.valid
  icache.io.icache_req.bits.addr := fetchUnit.io.fetchrequest.bits

  fetchUnit.io.fetchrequest.ready := icache.io.icache_req.ready
  fetchUnit.io.fetchanswer.valid  := icache.io.icache_resp.valid
  fetchUnit.io.fetchanswer.data   := icache.io.icache_resp.bits.data(0)
  fetchUnit.io.fetchanswer.data   := icache.io.icache_resp.bits.addr(0)
  fetchUnit.io.fetchanswer.pc     := DontCare

  dcache.io.req  <> executeUnit.io.dcache.req
  dcache.io.resp <> executeUnit.io.dcache.resp

  controlUnit.io.branch           := executeUnit.io.branch
  controlUnit.io.executeUnitReady := executeUnit.io.ready
  // executeUnit.fu.lsu.busy         := decodeUnit.io.islsu

  fetchUnit.io.branch := executeUnit.io.branch
  fetchUnit.io.target := executeUnit.io.target
  //
  decodeUnit.io.decodeStage  <> decodeStage.io.decodeUnit
  decodeUnit.io.regfile      <> regfile.io.read
  decodeUnit.io.executeStage <> executeStage.io.decodeUnit

  executeUnit.io.executeStage <> executeStage.io.executeUnit

  io.dataSram := DontCare

  executeUnit.io.memoryStage   <> memoryStage.io.executeUnit
  executeUnit.io.dcache.req    <> dcache.io.req
  executeUnit.io.dcache.resp   <> dcache.io.resp
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

  io.diff := diff.io.diffout

}
