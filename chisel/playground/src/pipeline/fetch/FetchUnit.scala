package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._
import cpu.defines.Instructions.NOP

class FetchRequest extends Bundle {
  val addr  = UInt(XLEN.W)
  val valid = Bool()
}
class FetchAnswer extends Bundle {
  val data  = UInt(XLEN.W)
  val pc    = UInt(XLEN.W)
  val valid = Bool()
}
class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage  = new FetchUnitDecodeUnit()
    val fetchanswer  = Input(new FetchAnswer())
    val icacheStall  = Input(Bool())
    val branch       = Input(Bool())
    val target       = Input(UInt(XLEN.W))
    val signal       = Input(new Signals())
    val fetchrequest = Output(new FetchRequest())
  })

  val pc         = RegInit(0.U)
  val isValid    = RegInit(0.U)
  val currentget = RegInit(true.B)
  val inst       = RegInit(0.U(XLEN.W))

  val instvalid = io.fetchanswer.valid & (io.fetchanswer.pc === pc)
  val ready     = io.signal.fetchUnitSignal.allow_to_go
  val data      = RegInit(0.U.asTypeOf(new IfIdData()))

  when(instvalid) {
    data.inst  := io.fetchanswer.data
    data.pc    := io.fetchanswer.pc
    data.valid := true.B
  }

  val canStart = RegNext(!reset.asBool) & (!reset.asBool)

  val stall = (!ready) | data.valid // 有一个指令没发送，当前就要 stall
  val nxtpc = Mux(io.branch === 0.U, pc + 4.U, io.target)
  io.decodeStage.data := 0.U.asTypeOf(new IfIdData())
  when(data.valid) {
    when(ready) {
      io.decodeStage.data.pc    := data.pc
      io.decodeStage.data.valid := data.valid
      io.decodeStage.data.inst  := data.inst
      data                      := 0.U.asTypeOf(new IfIdData())
    }
  }

  when(pc === 0.U) {
    when(canStart === false.B) {
      pc      := 0.U
      isValid := false.B
    }.otherwise {
      pc      := PC_INIT
      isValid := true.B
    }
  }.otherwise {
    pc := Mux(stall | io.icacheStall, pc, nxtpc)
  }
  io.fetchrequest.addr  := pc
  io.fetchrequest.valid := !stall & !io.icacheStall & isValid // stall 不要发送请求

}

//
