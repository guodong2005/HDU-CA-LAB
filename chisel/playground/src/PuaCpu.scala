import chisel3._
import chisel3.util._
import cpu._
import cpu.defines._

class core_top extends Module {
  val io = IO(new Bundle {
    // val ext_int     = Input(new ExtInterrupt())
    val ext_int     = Input(UInt(8.W))
    val break_point = Input(Bool())
    val infor_flag  = Input(Bool())
    val reg_num     = Input(UInt(4.W))
    val ws_valid    = Output(Bool())
    val rf_data     = Output(UInt(32.W))

    val axi     = new AXI()
    val debug   = new DEBUG()
    val diffout = new DiffOut()
  })

  val core = Module(new Core())

  io.ws_valid := DontCare
  io.rf_data  := DontCare
  /*
  io.break_point := true.B
  io.infor_flag  := true.B
  io.reg_num     := 4.U
   */

  dontTouch(io)
  io.ext_int <> core.io.interrupt
  io.axi     <> core.io.axi
  io.debug   <> core.io.debug
  io.diffout <> core.io.diff

  io.axi.ar.bits.burst := 1.U
  io.axi.ar.bits.lock  := 0.U
  io.axi.ar.bits.cache := 0.U
  io.axi.ar.bits.prot  := 0.U

  io.axi.aw.bits.burst := 1.U
  io.axi.aw.bits.len   := 0.U
  io.axi.aw.bits.id    := 1.U
  io.axi.aw.bits.lock  := 0.U
  io.axi.aw.bits.cache := 0.U
  io.axi.aw.bits.prot  := 0.U

  io.axi.w.bits.id   := 1.U
  io.axi.w.bits.last := 1.U

  core.io.dataSram := DontCare
}
