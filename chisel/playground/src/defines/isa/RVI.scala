package cpu.defines

import chisel3._
import chisel3.util._

/** RV32I/M instruction patterns implemented by the current pipeline. */
object RV32I_ALUInstr extends HasInstrType with CoreParameter {
  private def r(f7: String, f3: String) = BitPat(s"b$f7??????????$f3?????0110011")
  private def i(f3: String, op: String) = BitPat(s"b???????????? ????? $f3 ????? $op".replace(" ", ""))
  private def s(f3: String) = i(f3, "0100011")
  private def b(f3: String) = i(f3, "1100011")

  val LUI   = BitPat("b???????????????????????0110111")
  val AUIPC = BitPat("b???????????????????????0010111")
  val JAL   = BitPat("b???????????????????????1101111")
  val JALR  = i("000", "1100111")
  val ADDI  = i("000", "0010011"); val SLTI = i("010", "0010011"); val SLTIU = i("011", "0010011")
  val XORI  = i("100", "0010011"); val ORI = i("110", "0010011"); val ANDI = i("111", "0010011")
  val SLLI  = BitPat("b0000000??????????001?????0010011")
  val SRLI  = BitPat("b0000000??????????101?????0010011")
  val SRAI  = BitPat("b0100000??????????101?????0010011")
  val ADD = r("0000000", "000"); val SUB = r("0100000", "000"); val SLL = r("0000000", "001")
  val SLT = r("0000000", "010"); val SLTU = r("0000000", "011"); val XOR = r("0000000", "100")
  val SRL = r("0000000", "101"); val SRA = r("0100000", "101"); val OR = r("0000000", "110"); val AND = r("0000000", "111")
  val MUL = r("0000001", "000"); val MULH = r("0000001", "001"); val MULHU = r("0000001", "011")
  val DIV = r("0000001", "100"); val DIVU = r("0000001", "101"); val REM = r("0000001", "110"); val REMU = r("0000001", "111")
  val LB = i("000", "0000011"); val LH = i("001", "0000011"); val LW = i("010", "0000011")
  val LBU = i("100", "0000011"); val LHU = i("101", "0000011")
  val SB = s("000"); val SH = s("001"); val SW = s("010")
  val BEQ = b("000"); val BNE = b("001"); val BLT = b("100"); val BGE = b("101"); val BLTU = b("110"); val BGEU = b("111")
  val CSRRW = i("001", "1110011"); val CSRRS = i("010", "1110011"); val CSRRC = i("011", "1110011")

  val table = Array(
    LUI -> List(InstrU, FuType.alu, ALUOpType.add), AUIPC -> List(InstrU, FuType.alu, ALUOpType.add),
    ADDI -> List(InstrI, FuType.alu, ALUOpType.add), SLTI -> List(InstrI, FuType.alu, ALUOpType.slt), SLTIU -> List(InstrI, FuType.alu, ALUOpType.sltu),
    XORI -> List(InstrI, FuType.alu, ALUOpType.xor), ORI -> List(InstrI, FuType.alu, ALUOpType.or), ANDI -> List(InstrI, FuType.alu, ALUOpType.and),
    SLLI -> List(InstrI, FuType.alu, ALUOpType.sll), SRLI -> List(InstrI, FuType.alu, ALUOpType.srl), SRAI -> List(InstrI, FuType.alu, ALUOpType.sra),
    ADD -> List(InstrR, FuType.alu, ALUOpType.add), SUB -> List(InstrR, FuType.alu, ALUOpType.sub), SLL -> List(InstrR, FuType.alu, ALUOpType.sll),
    SLT -> List(InstrR, FuType.alu, ALUOpType.slt), SLTU -> List(InstrR, FuType.alu, ALUOpType.sltu), XOR -> List(InstrR, FuType.alu, ALUOpType.xor),
    SRL -> List(InstrR, FuType.alu, ALUOpType.srl), SRA -> List(InstrR, FuType.alu, ALUOpType.sra), OR -> List(InstrR, FuType.alu, ALUOpType.or), AND -> List(InstrR, FuType.alu, ALUOpType.and),
    MUL -> List(InstrR, FuType.mdu, MDUOpType.mul), MULH -> List(InstrR, FuType.mdu, MDUOpType.mulh), MULHU -> List(InstrR, FuType.mdu, MDUOpType.mulhu),
    DIV -> List(InstrR, FuType.mdu, MDUOpType.div), DIVU -> List(InstrR, FuType.mdu, MDUOpType.divu), REM -> List(InstrR, FuType.mdu, MDUOpType.rem), REMU -> List(InstrR, FuType.mdu, MDUOpType.remu),
    LB -> List(InstrI, FuType.lsu, LSUOpType.lb), LBU -> List(InstrI, FuType.lsu, LSUOpType.lbu), LH -> List(InstrI, FuType.lsu, LSUOpType.lh), LHU -> List(InstrI, FuType.lsu, LSUOpType.lhu), LW -> List(InstrI, FuType.lsu, LSUOpType.lw),
    SB -> List(InstrS, FuType.lsu, LSUOpType.sb), SH -> List(InstrS, FuType.lsu, LSUOpType.sh), SW -> List(InstrS, FuType.lsu, LSUOpType.sw),
    BEQ -> List(InstrB, FuType.bru, BRUOpType.beq), BNE -> List(InstrB, FuType.bru, BRUOpType.bne), BLT -> List(InstrB, FuType.bru, BRUOpType.blt), BGE -> List(InstrB, FuType.bru, BRUOpType.bge), BLTU -> List(InstrB, FuType.bru, BRUOpType.bltu), BGEU -> List(InstrB, FuType.bru, BRUOpType.bgeu),
    JAL -> List(InstrJ, FuType.bru, BRUOpType.bl), JALR -> List(InstrJ, FuType.bru, BRUOpType.jirl),
    CSRRW -> List(InstrI, FuType.csr, CSROpType.write), CSRRS -> List(InstrI, FuType.csr, CSROpType.set), CSRRC -> List(InstrI, FuType.csr, CSROpType.clear)
  )
}

object RVIInstr extends CoreParameter {
  val table = RV32I_ALUInstr.table
}
