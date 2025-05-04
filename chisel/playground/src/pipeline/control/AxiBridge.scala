package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Axibridge extends Module { // 总线能支持流水线吗
  val io = IO(new Bundle {
    val axi    = new AXI()
    val dcache = Flipped(new AXI())
    val icache = Flipped(new AXI())
  })
  val ar_sel_lock = RegInit(false.B)
  val ar_sel_val  = RegInit(false.B)

  val ar_id = Mux(ar_sel_lock, ar_sel_val, io.dcache.ar.valid)
  when(io.axi.ar.valid) {
    when(io.axi.ar.ready) {
      ar_sel_lock := false.B
    }.otherwise {
      ar_sel_lock := true.B
      ar_sel_val  := ar_id
    }
  }

  io.axi.ar.bits.id   := Cat(0.U(3.W), ar_id)
  io.axi.ar.valid     := Mux(ar_id, io.dcache.ar.valid, io.icache.ar.valid)
  io.axi.ar.bits.addr := Mux(ar_id, io.dcache.ar.bits.addr, io.icache.ar.bits.addr)
  io.axi.ar.bits.size := Mux(ar_id, io.dcache.ar.bits.size, io.icache.ar.bits.size)

  val r_sel = io.axi.r.bits.id(0)
  io.icache.r.valid     := !r_sel && io.axi.r.valid
  io.icache.r.bits.data := io.axi.r.bits.data
  io.dcache.r.valid     := r_sel && io.axi.r.valid
  io.dcache.r.bits.data := io.axi.r.bits.data

}
