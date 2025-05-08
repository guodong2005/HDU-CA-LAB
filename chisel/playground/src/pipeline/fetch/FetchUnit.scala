package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._

class FetchRequest extends Bundle {
  val addr  = UInt(XLEN.W)
  val valid = Bool()
}
class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage  = new FetchUnitDecodeUnit()
    val branch       = Input(Bool())
    val target       = Input(UInt(XLEN.W))
    val signal       = Input(new Signals())
    val inst         = Input(UInt(32.W))
    val valid        = Input(new Bool())
    val fetchrequest = Output(new FetchRequest())
  })

  val boot :: send :: receive :: Nil = Enum(3)
  val state                          = RegInit(boot)

  val pc      = RegInit(0.U)
  val isValid = RegInit(0.U)

  val answerValid = io.valid
  val nxtpc       = Mux(io.branch === 0.U, pc + Mux(io.signal.fetchUnitSignal.allow_to_go === true.B, (4.U), (0.U)), io.target)

  // 问的不可能马上达到，所以
  io.decodeStage.data.valid := answerValid
  io.decodeStage.data.pc    := pc
  io.decodeStage.data.inst  := io.inst

  when(pc === 0.U) {
    pc      := PC_INIT
    isValid := true.B
  }.otherwise {
    pc      := nxtpc
    isValid := Mux(io.signal.fetchUnitSignal.allow_to_go === true.B, true.B, false.B)
  }

  /*
  switch(state) {
    is(boot) {
      state := send
    }
    is(send) {
      state := receive
    }
    is(receive) {}
  }
   */

  // 初始直接 +0， 因为接收到的 valid 是 0, 所以 allow to go = 0

}

//
