import chisel3._
import chisel3.util._
import cpu._
import cpu.defines._
import pipeline._

class core_top extends Module {
  val io = IO(new Bundle {
    // val ext_int     = Input(new ExtInterrupt())
    val base_ram_ctrl = new SramCtrlIO
    val ext_ram_ctrl  = new SramCtrlIO
    val rxd           = new RxDIO
    val txd           = new TxDIO
    val diffout       = new DiffOut()
  })

  val core = Module(new Core())

  dontTouch(io)
  io.diffout <> core.io.diff
  io.base_ram_ctrl <> core.io.base_ram_ctrl
  io.ext_ram_ctrl <> core.io.ext_ram_ctrl
  io.rxd <> core.io.rxd
  io.txd <> core.io.txd

}
