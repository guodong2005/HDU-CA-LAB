package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Icache extends Module {
  val io = IO(new Bundle {
    val axi          = new AXI()
    val fetchrequest = Input(new FetchRequest())
    val inst         = Output(UInt(32.W))
    val valid        = Output(Bool())
    val icacheStall  = Output(Bool())
  })

  io.axi := DontCare
// icacheStall 代表现在要一个指令，指令还没回来之前，需要 stall 住 fetchUnit.
// 有两个状态，为是否存在一个未被应答的指令.
  val yes :: no :: Nil = Enum(2)
  val hasWait          = RegInit(no)

  when(hasWait === yes) {
    when(io.valid === true.B) {
      hasWait := no
    }
  }.otherwise {
    hasWait := io.fetchrequest.valid
  }
  io.icacheStall := hasWait

  io.axi.ar.valid     := io.fetchrequest.valid
  io.axi.ar.bits.addr := io.fetchrequest.addr
  io.axi.ar.bits.size := 2.U

  io.valid := io.axi.r.valid;
  io.inst  := io.axi.r.bits.data;
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
