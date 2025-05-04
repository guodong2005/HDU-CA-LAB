package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    val inst        = Input(UInt(32.W))
    val valid       = Input(new Bool())
    val addr        = Output(UInt(32.W))
  })

  val boot :: send :: receive :: Nil = Enum(3)
  val state                          = RegInit(boot)

  switch(state) {
    is(boot) {
      state := send
    }
    is(send) {
      state := receive
    }
    is(receive) {}
  }

  // val pc = RegEnable(io.instSram.addr, (PC_INIT - 4.U), state =/= boot)
  val pc = RegEnable(io.addr, (PC_INIT), state =/= boot)
  // 初始直接 +0， 因为接收到的 valid 是 0, 所以 allow to go = 0

  io.addr := Mux(io.branch === 0.U, pc + Mux(io.signal.fetchUnitSignal.allow_to_go === true.B, (4.U), (0.U)), io.target)

  io.decodeStage.data.valid := state === receive
  io.decodeStage.data.pc    := pc
  io.decodeStage.data.inst  := io.inst
}

//
