package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class IfIdData extends Bundle {
  val inst  = UInt(XLEN.W)
  val valid = Bool()
  val pc    = UInt(XLEN.W)
}

class FetchUnitDecodeUnit extends Bundle {
  val data = new IfIdData()
}

class DecodeStage extends Module {
  val io = IO(new Bundle {
    val fetchUnit     = Input(new FetchUnitDecodeUnit())
    val controlSignal = Input(new Signals())
    val decodeUnit    = Output(new FetchUnitDecodeUnit())

  })

  val data = RegInit(0.U.asTypeOf(new IfIdData()))
  when(io.controlSignal.fetchUnitSignal.allow_to_go === false.B) {
    data := data // Retain the previous data
  }.otherwise {
    data := io.fetchUnit.data // Update data if units are allowed to proceed
  }
  // flush logic:
  when(io.controlSignal.fetchUnitSignal.do_flush === true.B) {
    // data := 0.U.asTypeOf(new IfIdData()) // Reset data if flush signal is high
    data.valid := false.B
    // data.inst  := 0x00000013.U
    // data.valid := true.B
  }

  io.decodeUnit.data := data
}
