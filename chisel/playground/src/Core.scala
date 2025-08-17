package cpu

import chisel3._
import chisel3.util._

import defines._
import defines.Const._
import pipeline._
import dataclass.data

class Core extends Module {
  val io = IO(new Bundle {
    val base_ram_ctrl = new SramCtrlIO
    val ext_ram_ctrl  = new SramCtrlIO
    val rxd           = new RxDIO
    val txd           = new TxDIO
    val diff          = new DiffOut()
  })

  // ============================================================================
  // Module instantiation
  // ============================================================================
  val iocontrol      = Module(new IoControl())
  val icache         = Module(new ICache())
  val dcache         = Module(new DCache())
  val fetchUnit      = Module(new FetchUnit())
  val decodeStage    = Module(new DecodeStage())
  val decodeUnit     = Module(new DecodeUnit())
  val regfile        = Module(new ARegFile())
  val executeStage   = Module(new ExecuteStage())
  val executeUnit    = Module(new ExecuteUnit())
  val writeBackStage = Module(new WriteBackStage())
  val writeBackUnit  = Module(new WriteBackUnit())
  val controlUnit    = Module(new ControlUnit())
  val diff           = Module(new Diff())

  // ============================================================================
  // Control Unit connections
  // ============================================================================
  controlUnit.io.executeResult      := executeUnit.io.result
  controlUnit.io.writeBackResult    := writeBackUnit.io.result
  controlUnit.io.executeBranch      := executeUnit.io.branch
  controlUnit.io.executeTarget      := executeUnit.io.target
  controlUnit.io.executeUnitReady   := executeUnit.io.ready
  controlUnit.io.decodeRegisterInfo := decodeUnit.io.registerInfo
  controlUnit.io.decodeInfo         := decodeUnit.io.executeStage.data.info
  controlUnit.io.executeInfo        := executeUnit.io.writeBackStage.data.info
  controlUnit.io.writeBackInfo      := writeBackStage.io.writeBackUnit.data.info

  // ============================================================================
  // IoControl connections (Memory System)
  // ============================================================================
  io.base_ram_ctrl <> iocontrol.io.base_ram_ctrl
  io.ext_ram_ctrl <> iocontrol.io.ext_ram_ctrl
  io.rxd <> iocontrol.io.rxd
  io.txd <> iocontrol.io.txd

  // DCache connections to IoControl
  iocontrol.io.dcache_read_req <> dcache.io.io_read_req
  iocontrol.io.dcache_read_resp <> dcache.io.io_read_resp
  iocontrol.io.dcache_write_req <> dcache.io.io_write_req

  // ICache connections to IoControl
  iocontrol.io.icache_read_req <> icache.io.io_read_req
  iocontrol.io.icache_read_resp <> icache.io.io_read_resp

  // ============================================================================
  // ICache and FetchUnit connections (Optimized for pipelining)
  // ============================================================================

  // Connect FetchUnit to ICache
  icache.io.icache_req <> fetchUnit.io.icache_req

  // Connect ICache response to FetchUnit
  fetchUnit.io.icache_resp.valid := icache.io.icache_resp.valid
  fetchUnit.io.icache_resp.bits  := icache.io.icache_resp.bits

  // Connect branch signals from ExecuteUnit to FetchUnit
  fetchUnit.io.branch := executeUnit.io.branch
  fetchUnit.io.target := executeUnit.io.target

  // Connect control signals to FetchUnit
  fetchUnit.io.signal := controlUnit.io.signals

  // Connect FetchUnit to DecodeStage
  fetchUnit.io.decodeStage <> decodeStage.io.fetchUnit

  // ICache debug signals
  icache.io.icache_debug := DontCare

  // ============================================================================
  // Decode Stage connections
  // ============================================================================
  decodeUnit.io.executeready := executeUnit.io.ready
  decodeUnit.io.bypassData   := controlUnit.io.signals.bypassData
  decodeUnit.io.decodeStage <> decodeStage.io.decodeUnit
  decodeUnit.io.regfile <> regfile.io.read
  decodeUnit.io.executeStage <> executeStage.io.decodeUnit

  // Control signals to DecodeStage
  decodeStage.io.controlSignal := controlUnit.io.signals

  // ============================================================================
  // Execute Stage connections
  // ============================================================================
  executeUnit.io.executeStage <> executeStage.io.executeUnit
  executeUnit.io.writeBackStage <> writeBackStage.io.executeUnit

  // DCache connections to ExecuteUnit
  executeUnit.io.dcache.req <> dcache.io.req
  executeUnit.io.dcache.resp <> dcache.io.resp

  // Ready signal and control signals to ExecuteStage
  executeStage.io.ready         := executeUnit.io.ready
  executeStage.io.controlSignal := controlUnit.io.signals

  // ============================================================================
  // WriteBack Stage connections
  // ============================================================================
  writeBackUnit.io.writeBackStage <> writeBackStage.io.writeBackUnit
  writeBackUnit.io.regfile <> regfile.io.write

  // Control signals to WriteBackStage
  writeBackStage.io.controlSignal := controlUnit.io.signals

  // ============================================================================
  // Difftest connections
  // ============================================================================
  diff.io.debug <> writeBackUnit.io.debug
  diff.io.info    := writeBackUnit.io.info
  diff.io.regs_in := regfile.io.regs_out
  io.diff         := diff.io.diffout
}
