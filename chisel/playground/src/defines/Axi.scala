package cpu.defines

import chisel3._
import chisel3.util.Decoupled

class AxiAR extends Bundle {
  val id = UInt(4.W); val addr = UInt(32.W); val len = UInt(8.W)
  val size = UInt(3.W); val burst = UInt(2.W); val prot = UInt(3.W)
}
class AxiR extends Bundle {
  val id = UInt(4.W); val data = UInt(32.W); val resp = UInt(2.W); val last = Bool()
}
class AxiAW extends Bundle {
  val id = UInt(4.W); val addr = UInt(32.W); val len = UInt(8.W)
  val size = UInt(3.W); val burst = UInt(2.W); val prot = UInt(3.W)
}
class AxiW extends Bundle { val id = UInt(4.W); val data = UInt(32.W); val strb = UInt(4.W); val last = Bool() }
class AxiB extends Bundle { val id = UInt(4.W); val resp = UInt(2.W) }

/** AXI4-Lite-shaped single-beat master channels, with AR/R and AW/W/B decoupled. */
class AxiMaster extends Bundle {
  val ar = Decoupled(new AxiAR)
  val r = Flipped(Decoupled(new AxiR))
  val aw = Decoupled(new AxiAW)
  val w = Decoupled(new AxiW)
  val b = Flipped(Decoupled(new AxiB))
}
