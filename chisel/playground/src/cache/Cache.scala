package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Icache extends Module {
  val io = IO(new Bundle {
    val axi          = new AXI()
    val fetchrequest = Input(new FetchRequest())
    val icacheStall  = Output(Bool())
    val fetchanswer  = Output(new FetchAnswer())
  })

  io.axi              := DontCare
  io.axi.ar.valid     := io.fetchrequest.valid
  io.axi.ar.bits.addr := io.fetchrequest.addr
  io.axi.ar.bits.size := 2.U

  // 当放出了请求，并且请求还没被响应时，icache 处于 stall 状态
  val no :: yes :: Nil = Enum(2)
  val hasWait          = RegInit(no)
  val waitingPC        = RegInit(0.U(XLEN.W))
  when(io.fetchrequest.valid) {
    waitingPC := io.fetchrequest.addr
  }

  io.fetchanswer.valid := io.axi.r.valid
  io.fetchanswer.data  := io.axi.r.bits.data
  io.fetchanswer.pc    := waitingPC

  io.icacheStall := hasWait | io.fetchrequest.valid // 这里会吞掉一个时钟周期，或许我应该使用 combinational logic
  when(io.axi.r.valid) {
    hasWait := no
  }.elsewhen(io.fetchrequest.valid) {
    hasWait := yes
  }
}
class Dcache extends Module {
  val io = IO(new Bundle {
    val axi          = new AXI()
    val fetchrequest = Input(new FetchRequest())
    val inst         = Output(UInt(32.W))
    val valid        = Output(Bool())
  })

  io.axi := DontCare
  // 先用一个笨方法，假设 ready 跟 response 同时到达

  io.axi.ar.valid     := io.fetchrequest.valid
  io.axi.ar.bits.addr := io.fetchrequest.addr
  io.axi.ar.bits.size := 2.U

  io.valid := io.axi.r.valid;
  io.inst  := io.axi.r.bits.data;
}
