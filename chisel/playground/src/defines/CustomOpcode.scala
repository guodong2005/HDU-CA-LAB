package cpu.defines

import chisel3._

object CustomOpcode {
  val Vector = "b0001011".U(7.W) // CUSTOM-0
  val Cube = "b0101011".U(7.W)   // CUSTOM-1
  val VAdd = 0.U(3.W)
  val VMul = 1.U(3.W)
  val VShift = 2.U(3.W)
  val VGather = 3.U(3.W)
  val CubeMmaAsync = 0.U(3.W)
  val CubeWait = 1.U(3.W)
}
