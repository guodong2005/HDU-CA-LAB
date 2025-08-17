package cpu

import chisel3._
import chisel3.util._

import defines._
import defines.Const._
import pipeline._
import dataclass.data
// Modified Core.scala with PrefetchUnit integration

class Core extends Module {
  val io = IO(new Bundle {
    val base_ram_ctrl = new SramCtrlIO
    val ext_ram_ctrl  = new SramCtrlIO
    val rxd           = new RxDIO
    val txd           = new TxDIO
    val diff          = new DiffOut()
  })

  // Module instantiation
  val iocontrol = Module(new IoControl())
  val icache    = Module(new ICache())
  icache.io.icache_debug := DontCare
  val dcache = Module(new DCache)

  // ===== NEW: Instantiate PrefetchUnit =====
  val prefetchUnit = Module(new PrefetchUnit())

  // ===== Modified: Use FetchUnitWithPrefetch instead of FetchUnit =====
  val fetchUnit = Module(new FetchUnitWithPrefetch())

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
  // Control Unit connections (unchanged)
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
  // IoControl connections (unchanged)
  // ============================================================================
  io.base_ram_ctrl <> iocontrol.io.base_ram_ctrl
  io.ext_ram_ctrl <> iocontrol.io.ext_ram_ctrl
  io.rxd <> iocontrol.io.rxd
  io.txd <> iocontrol.io.txd
  iocontrol.io.dcache_read_req <> dcache.io.io_read_req
  iocontrol.io.dcache_read_resp <> dcache.io.io_read_resp
  iocontrol.io.dcache_write_req <> dcache.io.io_write_req
  iocontrol.io.icache_read_req <> icache.io.io_read_req
  iocontrol.io.icache_read_resp <> icache.io.io_read_resp

  // ============================================================================
  // NEW: PrefetchUnit connections
  // ============================================================================

  // Connect PrefetchUnit to ICache
  prefetchUnit.io.icache_req <> icache.io.icache_req
  prefetchUnit.io.icache_resp <> icache.io.icache_resp

  // Connect PrefetchUnit to FetchUnit
  fetchUnit.io.prefetch_resp <> prefetchUnit.io.fetch_resp
  prefetchUnit.io.fetch_ready := fetchUnit.io.fetch_ready

  // Connect branch signals to PrefetchUnit (same as FetchUnit)
  prefetchUnit.io.branch := controlUnit.io.signals.branchControl.branch
  prefetchUnit.io.target := controlUnit.io.signals.branchControl.target

  // ============================================================================
  // Modified FetchUnit connections (removed ICache connections)
  // ============================================================================

  // FetchUnit now only connects to DecodeStage and receives control signals
  fetchUnit.io.decodeStage <> decodeStage.io.fetchUnit
  fetchUnit.io.signal := controlUnit.io.signals

  // Note: ICache connections are now handled by PrefetchUnit
  // Removed: icache.io.icache_req <> fetchUnit.io.icache_req
  // Removed: icache.io.icache_resp <> fetchUnit.io.icache_resp

  // ============================================================================
  // Rest of connections (unchanged)
  // ============================================================================

  // Decode Unit connections
  decodeUnit.io.executeready := executeUnit.io.ready
  decodeUnit.io.bypassData   := controlUnit.io.signals.bypassData
  decodeUnit.io.decodeStage <> decodeStage.io.decodeUnit
  decodeUnit.io.regfile <> regfile.io.read
  decodeUnit.io.executeStage <> executeStage.io.decodeUnit

  // Execute Unit connections
  executeUnit.io.executeStage <> executeStage.io.executeUnit
  executeUnit.io.writeBackStage <> writeBackStage.io.executeUnit
  executeUnit.io.dcache.req <> dcache.io.req
  executeUnit.io.dcache.resp <> dcache.io.resp

  // WriteBack Unit connections
  writeBackUnit.io.writeBackStage <> writeBackStage.io.writeBackUnit
  writeBackUnit.io.regfile <> regfile.io.write

  // Stage Ready signals
  executeStage.io.ready := executeUnit.io.ready

  // Control Signal distribution
  decodeStage.io.controlSignal    := controlUnit.io.signals
  executeStage.io.controlSignal   := controlUnit.io.signals
  writeBackStage.io.controlSignal := controlUnit.io.signals

  // Difftest connections
  diff.io.debug <> writeBackUnit.io.debug
  diff.io.info    := writeBackUnit.io.info
  diff.io.regs_in := regfile.io.regs_out
  io.diff         := diff.io.diffout
}
