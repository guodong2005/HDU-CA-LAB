package cpu.defines

import chisel3._
import chisel3.util._

trait HasInstrType {
  def InstrN = "b000".U
  def InstrI = "b100".U
  def InstrR = "b101".U
  def InstrS = "b010".U
  def InstrB = "b001".U
  def InstrU = "b110".U
  def InstrJ = "b111".U

  def isRegWen(instrType: UInt): Bool = instrType(2)
}

object FuType {
  def num     = 4
  def alu     = 0.U // arithmetic logic unit
  def mdu     = 1.U // multiplication division unit
  def lsu     = 2.U // multiplication division unit
  def bru     = 3.U // branch unit
  def apply() = UInt(log2Up(num).W)
}

object FuOpType {
  def apply() = UInt(5.W)
}

object MDUOpType {
  def mul    = "b0000".U // Multiply
  def mulh   = "b0001".U // Multiply High
  def mulhsu = "b0010".U // Multiply High Signed-Unsigned
  def mulhu  = "b0011".U // Multiply High Unsigned
  def div    = "b0100".U // Divide
  def divu   = "b0101".U // Unsigned Divide
  def rem    = "b0110".U // Remainder
  def remu   = "b0111".U // Unsigned Remainder
  def mulw   = "b1000".U // Multiply Word
  def divw   = "b1100".U // Divide Word
  def divuw  = "b1101".U // Unsigned Divide Word
  def remw   = "b1110".U // Remainder Word
  def remuw  = "b1111".U // Unsigned Remainder Word

  // below is recommended in tutorial. but I forget it so I dont use these...
  def isDiv(op:     UInt) = op(2)
  def isDivSign(op: UInt) = isDiv(op) && !op(0)
  def isWordOp(op:  UInt) = op(3)

}

// ALU
object ALUOpType {
  def add  = "b00000".U
  def sub  = "b01000".U
  def sll  = "b00001".U
  def slt  = "b00010".U
  def sltu = "b00011".U
  def xor  = "b00100".U
  def srl  = "b00101".U
  def sra  = "b01101".U
  def or   = "b00110".U
  def and  = "b00111".U
  def addw = "b10000".U
  def subw = "b11000".U
  def sllw = "b10001".U
  def srlw = "b10101".U
  def sraw = "b11101".U

  def isWordOp(func: UInt) = func(4)

}

object LSUOpType {
  def lb  = "b0000".U
  def lbu = "b0100".U
  def lh  = "b0001".U
  def lhu = "b0101".U
  def lw  = "b0010".U
  def lwu = "b0110".U
  def ld  = "b0011".U

  def sb = "b1000".U
  def sh = "b1001".U
  def sw = "b1010".U
  def sd = "b1011".U

  def isStore(func: UInt): Bool = func(3)
  def isLoad(func:  UInt): Bool = !isStore(func)
}

object BRUOpType {
  def beq  = "b0000".U
  def bne  = "b0001".U
  def blt  = "b0100".U
  def bge  = "b0101".U
  def bltu = "b0110".U
  def bgeu = "b0111".U

  def jal  = "b1111".U
  def jalr = "b1010".U

  def isBranch(func: UInt) = !func(3)
  def isJump(func:   UInt) = !isBranch(func)
}
