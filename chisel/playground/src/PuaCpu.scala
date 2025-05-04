import chisel3._
import chisel3.util._
import cpu._
import cpu.defines._

class PuaCpu extends Module {
  val io = IO(new Bundle {
    val ext_int = Input(new ExtInterrupt())
    val axi     = new AXI()
    val debug   = new DEBUG()
  })

  val core = Module(new Core())

  io.ext_int <> core.io.interrupt
  io.axi     <> core.io.axi
  io.debug   <> core.io.debug

  io.axi.ar.bits.burst := 1.U
  io.axi.ar.bits.len   := 0.U
  io.axi.ar.bits.lock  := 0.U
  io.axi.ar.bits.cache := 0.U
  io.axi.ar.bits.prot  := 0.U

  core.io.dataSram := DontCare
}
