package cpu

import chisel3._

object VectorPermute {
  def shiftUp(value: Vec[UInt], amount: UInt): Vec[UInt] = {
    val out = Wire(Vec(4, UInt(32.W)))
    for (i <- 0 until 4) {
      out(i) := Mux(amount <= i.U, value(i.U - amount), 0.U)
    }
    out
  }

  def gather(value: Vec[UInt], indices: Vec[UInt]): Vec[UInt] = {
    val out = Wire(Vec(4, UInt(32.W)))
    for (i <- 0 until 4) out(i) := value(indices(i)(1, 0))
    out
  }
}
