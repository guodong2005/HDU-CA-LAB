package cpu

import chisel3.util._
import cpu.defines.Const._

case class CpuConfig(
  // ISA baseline: RV32IM (privileged and optional extensions remain disabled).
  val isRV32:               Boolean = true,
  val hasMExtension:        Boolean = true,  // RV32M multiplication/division
  val hasZicsrExtension:    Boolean = false, // 是否实现Zicsr扩展，即CSR指令
  val hasZifenceiExtension: Boolean = false, // 是否实现Zifencei扩展，即FENCE.I指令
  val hasAExtension:        Boolean = false, // 是否实现A扩展，即原子指令
  // 特权模式
  val hasSMode: Boolean = false, // 是否有S模式
  val hasUMode: Boolean = false  // 是否有U模式
)
