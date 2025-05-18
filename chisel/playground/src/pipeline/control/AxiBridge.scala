package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Axibridge extends Module { // 总线能支持流水线吗
  val io = IO(new Bundle {
    val axi         = new AXI()
    val dcacheInput = Flipped(new AXI())
    val icacheInput = Flipped(new AXI())
  })
  val icache = RegInit(0.U.asTypeOf(new AXI()))
  val dcache = RegInit(0.U.asTypeOf(new AXI()))
  io.axi         := DontCare
  io.icacheInput := DontCare
  io.dcacheInput := DontCare

  when(io.icacheInput.ar.valid) {
    icache := io.icacheInput
  }
  when(io.dcacheInput.ar.valid) {
    dcache := io.dcacheInput
  }

  val ar_sel_lock = RegInit(false.B)
  val ar_sel_val  = RegInit(false.B)

  val ar_id = Mux(ar_sel_lock, ar_sel_val, dcache.ar.valid)

  when(io.axi.ar.valid) {
    when(io.axi.ar.ready) { //  握手成功, 此时返回的不一定为 valid, 此时不能有新的
      when(dcache.ar.valid) {
        io.axi.ar.bits.id   := Cat(0.U(3.W), dcache.ar.bits.id)
        io.axi.ar.valid     := dcache.ar.valid
        io.axi.ar.bits.addr := dcache.ar.bits.addr
        io.axi.ar.bits.size := dcache.ar.bits.size
        dcache              := 0.U.asTypeOf(new AXI())
      }.otherwise {
        io.axi.ar.bits.id   := Cat(0.U(3.W), icache.ar.bits.id)
        io.axi.ar.valid     := icache.ar.valid
        io.axi.ar.bits.addr := icache.ar.bits.addr
        io.axi.ar.bits.size := icache.ar.bits.size
        icache              := 0.U.asTypeOf(new AXI())
      }
    }.otherwise {
      // ar_sel_lock := true.B
      // ar_sel_val  := ar_id
    }
  }

  io.axi.r.ready := true.B

  val r_sel = io.axi.r.bits.id(0)
  io.icacheInput.r.valid     := RegNext { !r_sel && io.axi.r.valid }
  io.icacheInput.r.bits.data := io.axi.r.bits.data
  io.dcacheInput.r.valid     := RegNext { r_sel && io.axi.r.valid }
  io.dcacheInput.r.bits.data := io.axi.r.bits.data

}
