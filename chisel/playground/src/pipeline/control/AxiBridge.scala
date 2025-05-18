package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class readRequest extends Bundle {
  val valid = Bool()
  val id    = UInt(4.W)
  val addr  = UInt(32.W)
  val size  = UInt(3.W)
}
class Axibridge extends Module { // 总线能支持流水线吗
  val io = IO(new Bundle {
    val axi         = new AXI()
    val dcacheInput = Flipped(new AXI())
    val icacheInput = Flipped(new AXI())
  })
  val icache = RegInit(0.U.asTypeOf(new readRequest))
  val dcache = RegInit(0.U.asTypeOf(new readRequest))

  io.axi         := DontCare
  io.icacheInput := DontCare
  io.dcacheInput := DontCare

  when(io.icacheInput.ar.valid) {
    icache.valid := io.icacheInput.ar.valid
    icache.addr  := io.icacheInput.ar.bits.addr
    icache.size  := io.icacheInput.ar.bits.size
    icache.id    := io.icacheInput.ar.bits.id

  }
  when(io.dcacheInput.ar.valid) {
    dcache.valid := io.dcacheInput.ar.valid
    dcache.addr  := io.dcacheInput.ar.bits.addr
    dcache.size  := io.dcacheInput.ar.bits.size
    dcache.id    := io.dcacheInput.ar.bits.id

  }

  val ar_sel_lock = RegInit(false.B)
  val ar_sel_val  = RegInit(false.B)

  val ar_id = Mux(ar_sel_lock, ar_sel_val, dcache.valid)

  when(io.axi.ar.valid) {
    when(io.axi.ar.ready) { //  握手成功, 此时返回的不一定为 valid, 此时不能有新的
      when(dcache.valid) {
        io.axi.ar.bits.id   := Cat(0.U(3.W), dcache.id)
        io.axi.ar.valid     := dcache.valid
        io.axi.ar.bits.addr := dcache.addr
        io.axi.ar.bits.size := dcache.size
        dcache              := 0.U.asTypeOf(new readRequest)
      }.otherwise {
        io.axi.ar.bits.id   := Cat(0.U(3.W), icache.id)
        io.axi.ar.valid     := icache.valid
        io.axi.ar.bits.addr := icache.addr
        io.axi.ar.bits.size := icache.size
        icache              := 0.U.asTypeOf(new readRequest)
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
