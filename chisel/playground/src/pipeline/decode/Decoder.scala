package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Decoder extends Module with HasInstrType {
  val io = IO(new Bundle {
    // inputs
    val in = Input(new Bundle {
      val inst = UInt(XLEN.W)
    })
    // outputs
    val out = Output(new Bundle {
      val info = new Info()
    })
  })
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(io.in.inst, Instructions.DecodeDefault, Instructions.DecodeTable)
  val inst = Mux(instrType === InstrN, Instructions.NOP, io.in.inst)
  io.out.info := DontCare

  io.out.info.valid := false.B

  def setInfo(
    instr:     UInt,
    regWAddr:  UInt,
    src1RAddr: UInt,
    src2RAddr: UInt,
    op:        UInt,
    regWEn:    Bool = true.B,
    src1REn:   Bool = true.B,
    src2REn:   Bool = false.B,
    valid:     Bool = true.B): Unit = {
    io.out.info.instr      := instr
    io.out.info.reg_waddr  := regWAddr
    io.out.info.src1_raddr := src1RAddr
    io.out.info.src2_raddr := src2RAddr
    io.out.info.op         := op
    io.out.info.reg_wen    := regWEn
    io.out.info.src1_ren   := src1REn
    io.out.info.src2_ren   := src2REn
    io.out.info.valid      := valid
  }

  val (rd, rs1, rs2) = (inst(4, 0), inst(9, 5), inst(14, 10))

  when(instrType === InstrR) {
    setInfo(inst, rd, rs1, rs2, fuOpType, true.B, true.B, true.B, true.B)
  }.elsewhen(instrType === InstrI) {
    //                     src2     writeback src1en src2en   valid
    setInfo(inst, rd, rs1, 0.U, fuOpType, true.B, true.B, false.B, true.B)
  }.elsewhen(instrType === InstrU) {
    setInfo(inst, rd, 0.U, 0.U, ALUOpType.add, true.B, false.B, false.B, true.B)
  }.elsewhen(instrType === InstrS) {
    //                     src2     writeback src1en src2en   valid
    setInfo(inst, rd, rs1, rs2, fuOpType, false.B, true.B, true.B, true.B)
  }.elsewhen(instrType === InstrB) {
    //                     src2     writeback src1en src2en   valid
    setInfo(inst, 0.U, rs1, rs2, fuOpType, false.B, true.B, true.B, true.B)

  }.elsewhen(instrType === InstrJ) {
    setInfo(inst, Mux(fuOpType === BRUOpType.bl, 1.U, rd), 0.U, 0.U, fuOpType, Mux(instrType === BRUOpType.b, false.B, true.B), false.B, false.B, true.B)
  }.otherwise {
    setInfo(inst, 0.U, 0.U, 0.U, 0.U, false.B, false.B, false.B, false.B)
  }
  io.out.info.fusel := fuType
}
