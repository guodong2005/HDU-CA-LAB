package cpu.defines

object Const {
  val Xlen = 32
  val ResetPc = BigInt("80000000", 16)
  val Nop = BigInt("00000013", 16)
}
