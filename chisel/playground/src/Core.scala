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
    val base_ram_ctrl = new SramCtrlIO
    val ext_ram_ctrl  = new SramCtrlIO
    val rxd           = new RxDIO
    val txd           = new TxDIO
    val diff          = new DiffOut()
  })

  val iocontrol = Module(new IoControl());
  val icache    = Module(new ICache())
  icache.io.icache_debug := DontCare
  val dcache       = Module(new DCache)
  val fetchUnit    = Module(new FetchUnit())
  val decodeStage  = Module(new DecodeStage())
  val decodeUnit   = Module(new DecodeUnit())
  val regfile      = Module(new ARegFile())
  val executeStage = Module(new ExecuteStage())
  val executeUnit  = Module(new ExecuteUnit())

  val writeBackStage = Module(new WriteBackStage())
  val writeBackUnit  = Module(new WriteBackUnit())
  val controlUnit    = Module(new ControlUnit())
  val diff           = Module(new Diff())

  // 取指单元
  dontTouch(fetchUnit.io)
  dontTouch(icache.io)

  controlUnit.io.executeResult   := executeUnit.io.result // EX阶段完成所有计算（包括load）
  controlUnit.io.writeBackResult := writeBackUnit.io.result
  // ============================================================================
  // IoControl 外部接口连接
  // ============================================================================

  // 连接SRAM控制信号
  io.base_ram_ctrl <> iocontrol.io.base_ram_ctrl
  io.ext_ram_ctrl <> iocontrol.io.ext_ram_ctrl

  // 连接UART信号
  io.rxd <> iocontrol.io.rxd
  io.txd <> iocontrol.io.txd

  iocontrol.io.dcache_read_req <> dcache.io.io_read_req
  iocontrol.io.dcache_read_resp <> dcache.io.io_read_resp
  iocontrol.io.dcache_write_req <> dcache.io.io_write_req

  // ============================================================================
  // ICache 连接 (去掉AXI，直接连接IoControl)
  // ============================================================================

  // ICache 与 IoControl 的连接
  iocontrol.io.icache_read_req <> icache.io.io_read_req
  iocontrol.io.icache_read_resp <> icache.io.io_read_resp

  fetchUnit.io.decodeStage <> decodeStage.io.fetchUnit
  decodeUnit.io.executeready := executeUnit.io.ready

  icache.io.icache_req <> fetchUnit.io.icache_req
  icache.io.icache_resp <> fetchUnit.io.icache_resp

  dcache.io.req <> executeUnit.io.dcache.req
  dcache.io.resp <> executeUnit.io.dcache.resp

// ============ Control Unit 连接 ============
  controlUnit.io.executeBranch := executeUnit.io.branch
  controlUnit.io.executeTarget := executeUnit.io.target
  controlUnit.io.decodeBranch  := decodeUnit.io.branch
  controlUnit.io.decodeTarget  := decodeUnit.io.target

  controlUnit.io.executeUnitReady := executeUnit.io.ready
  controlUnit.io.executeResult    := executeUnit.io.result // EX阶段完成所有计算（包括load）
  controlUnit.io.writeBackResult  := writeBackUnit.io.result
// 注意：去掉了 controlUnit.io.memoryResult，因为没有memory stage了

// ============ Fetch Unit 连接 ============
  fetchUnit.io.signal := controlUnit.io.signals

// ============ Decode Unit 连接 ============
  decodeUnit.io.bypassData := controlUnit.io.signals.bypassData
  decodeUnit.io.decodeStage <> decodeStage.io.decodeUnit
  decodeUnit.io.regfile <> regfile.io.read
  decodeUnit.io.executeStage <> executeStage.io.decodeUnit

// ============ Execute Unit 连接 ============
  executeUnit.io.executeStage <> executeStage.io.executeUnit
  executeUnit.io.writeBackStage <> writeBackStage.io.executeUnit // 直接连接到WriteBack阶段
  executeUnit.io.dcache.req <> dcache.io.req
  executeUnit.io.dcache.resp <> dcache.io.resp

// ============ WriteBack Unit 连接 ============
  writeBackUnit.io.writeBackStage <> writeBackStage.io.writeBackUnit
  writeBackUnit.io.regfile <> regfile.io.write

// ============ Stage Ready 信号连接 ============
  executeStage.io.ready := executeUnit.io.ready
// 注意：去掉了memory stage相关的ready信号

// ============ Control Unit 的Info信号连接 ============
  controlUnit.io.decodeRegisterInfo := decodeUnit.io.registerInfo
  controlUnit.io.decodeInfo         := decodeUnit.io.executeStage.data.info
  controlUnit.io.executeInfo        := executeUnit.io.writeBackStage.data.info // 直接从execute到writeback
  controlUnit.io.writeBackInfo      := writeBackStage.io.writeBackUnit.data.info
// 注意：去掉了 controlUnit.io.memoryInfo

// ============ Control Signal 分发 ============
  decodeStage.io.controlSignal    := controlUnit.io.signals
  executeStage.io.controlSignal   := controlUnit.io.signals
  writeBackStage.io.controlSignal := controlUnit.io.signals
// 注意：去掉了 memoryStage.io.controlSignal
  // difftest:
  diff.io.debug <> writeBackUnit.io.debug
  diff.io.info    := writeBackUnit.io.info
  diff.io.regs_in := regfile.io.regs_out

  io.diff := diff.io.diffout

}
