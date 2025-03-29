package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class ControlSignal extends Bundle {
  val allow_to_go = Bool()
  val do_flush    = Bool()
}

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val decodeInfo    = Input(new Info())
    val executeInfo   = Input(new Info())
    val memoryInfo    = Input(new Info())
    val writeBackInfo = Input(new Info())

    val fetchUnitSignal    = Output(new ControlSignal())
    val decodeStageSignal  = Output(new ControlSignal())
    val executeStageSignal = Output(new ControlSignal())
    val fetchSignal        = Output(new ControlSignal())
  })
}
