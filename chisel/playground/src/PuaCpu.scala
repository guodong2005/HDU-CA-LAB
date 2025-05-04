import chisel3._
import chisel3.util._
import cpu._
import cpu.defines._

class core_top extends Module {
  val io = IO(new Bundle {
    val ext_int      = Input(new ExtInterrupt())
    val break_pointk = Input(Bool())
    val infor_flag   = Input(Bool())
    val reg_num      = Input(UInt(4.W))
    val ws_valid     = Output(Bool())
    val rf_data      = Output(UInt(32.W))

    val axi   = new AXI()
    val debug = new DEBUG()
  })

  val core = Module(new Core())

  dontTouch(io)
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
