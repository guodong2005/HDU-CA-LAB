package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._
import cpu.defines.Instructions.NOP

class FetchAnswer extends Bundle {
  val data  = UInt(XLEN.W)
  val pc    = UInt(XLEN.W)
  val valid = Bool()
}

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage  = new FetchUnitDecodeUnit()
    val fetchanswer  = Input(new FetchAnswer())
    val branch       = Input(Bool())
    val target       = Input(UInt(XLEN.W))
    val signal       = Input(new Signals())
    val fetchrequest = Decoupled(UInt(XLEN.W))
  })

  val pc       = RegInit(0.U(XLEN.W))
  val canStart = RegNext(!reset.asBool) && (!reset.asBool)

  when(canStart && (pc === 0.U)) {
    pc := PC_INIT
  }

  val sIdle :: sWait :: Nil = Enum(2)
  val state                 = RegInit(sIdle)

  val reqPC = Reg(UInt(XLEN.W))

  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  io.fetchrequest.valid := (state === sIdle) && !stall && RegNext(canStart)
  io.fetchrequest.bits  := pc

  io.decodeStage.data := 0.U.asTypeOf(new IfIdData())

  switch(state) {
    is(sIdle) {
      when(io.branch) {
        pc := io.target
      }
      when(canStart === false.B) {
        state := sIdle
      }.elsewhen(io.fetchrequest.valid && io.fetchrequest.ready) {
        reqPC := pc
        state := sWait
      }
    }
    is(sWait) {
      val answerMatches = true.B
      // val answerMatches = (io.fetchanswer.pc === reqPC)
      when(io.branch) {
        pc    := io.target
        state := sIdle
      }.elsewhen(io.fetchanswer.valid && answerMatches) {
        when(decodeReady) {
          io.decodeStage.data.inst  := io.fetchanswer.data
          io.decodeStage.data.pc    := reqPC
          io.decodeStage.data.valid := true.B
          pc                        := Mux(io.branch, io.target, reqPC + 4.U)
          state                     := sIdle
        }.otherwise {
          ifid_reg.inst  := io.fetchanswer.data
          ifid_reg.pc    := reqPC
          ifid_reg.valid := true.B
        }
      }
    }
  }

  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    pc                  := Mux(io.branch, io.target, ifid_reg.pc + 4.U)
    state               := sIdle
  }
}
