package cpu

case class CpuConfig(xlen: Int = 32, resetPc: BigInt = BigInt("80000000", 16))
