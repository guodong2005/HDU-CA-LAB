package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class ControlSignal extends Bundle {
  val allow_to_go = Bool()
  val do_flush    = Bool()
}
class Signals extends Bundle {
  val fetchUnitSignal   = Output(new ControlSignal())
  val decodeUnitSignal  = Output(new ControlSignal())
  val executeUnitSignal = Output(new ControlSignal())
  val memoryUnitSignal  = Output(new ControlSignal())
}

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val decodeInfo       = Input(new Info())
    val executeInfo      = Input(new Info())
    val memoryInfo       = Input(new Info())
    val writeBackInfo    = Input(new Info())
    val executeUnitReady = Input(Bool())
    val signals          = Output(new Signals())
    val branch           = Input(Bool()) // Changed to Input for modularity
  })

  // Conflict detection logic
  val exe_conflict = io.executeInfo.valid && io.executeInfo.reg_wen && io.executeInfo.reg_waddr.orR &&
    ((io.decodeInfo.src1_ren && io.decodeInfo.src1_raddr === io.executeInfo.reg_waddr) ||
      (io.decodeInfo.src2_ren && io.decodeInfo.src2_raddr === io.executeInfo.reg_waddr))

  val mem_conflict = io.memoryInfo.valid && io.memoryInfo.reg_wen && io.memoryInfo.reg_waddr.orR &&
    ((io.decodeInfo.src1_ren && io.decodeInfo.src1_raddr === io.memoryInfo.reg_waddr) ||
      (io.decodeInfo.src2_ren && io.decodeInfo.src2_raddr === io.memoryInfo.reg_waddr))

  val wb_conflict = io.writeBackInfo.valid && io.writeBackInfo.reg_wen && io.writeBackInfo.reg_waddr.orR &&
    ((io.decodeInfo.src1_ren && io.decodeInfo.src1_raddr === io.writeBackInfo.reg_waddr) ||
      (io.decodeInfo.src2_ren && io.decodeInfo.src2_raddr === io.writeBackInfo.reg_waddr))

  val pipeline_stall = exe_conflict || mem_conflict || wb_conflict

  // Generate control signals using modular assignment
  io.signals.fetchUnitSignal.allow_to_go   := (!pipeline_stall) & io.signals.decodeUnitSignal.allow_to_go
  io.signals.decodeUnitSignal.allow_to_go  := (!pipeline_stall) & io.signals.executeUnitSignal.allow_to_go
  io.signals.executeUnitSignal.allow_to_go := io.executeUnitReady
// icache stall 只会影响 fetchUnit

  io.signals.executeUnitSignal.allow_to_go := true.B
  io.signals.memoryUnitSignal.allow_to_go  := true.B

  io.signals.fetchUnitSignal.do_flush   := io.branch
  io.signals.decodeUnitSignal.do_flush  := io.branch
  io.signals.executeUnitSignal.do_flush := false.B
  io.signals.memoryUnitSignal.do_flush  := false.B
}
