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
  val inst = io.in.inst
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)

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

  val (rd, rs1, rs2) = (inst(11, 7), inst(19, 15), inst(24, 20))
  val funct3         = inst(14, 12)
  val op = LookupTree(
    instrType,
    Seq(
      InstrR -> Mux(fuType === FuType.alu, Cat(inst(3), inst(30), inst(14, 12)), Cat(inst(3), funct3)),
      InstrI -> Mux(fuType === FuType.lsu,Cat(inst(5),funct3),Cat(inst(3), Mux((fuOpType === ALUOpType.sra) || (fuOpType === ALUOpType.sraw), 1.U, 0.U), inst(14, 12))),
      //  these part's readability is very bad. 
      InstrU -> ALUOpType.add
    )
  )
  when(instrType === InstrR) {
    setInfo(inst, rd, rs1, rs2, op, true.B, true.B, true.B, true.B)
  }.elsewhen(instrType === InstrI) {
    //                     src2     writeback src1en src2en   valid
    setInfo(inst, rd, rs1, 0.U, op, true.B, true.B, false.B, true.B)
  }.elsewhen(instrType === InstrU) {
    setInfo(inst, rd, 0.U, 0.U, ALUOpType.add, true.B, false.B, false.B, true.B)
  }.elsewhen(instrType === InstrS){
    //                     src2     writeback src1en src2en   valid
    setInfo(inst, rd, rs1, 0.U, op, false.B, true.B, false.B, true.B)
  }.otherwise {
    setInfo(inst, 0.U, 0.U, 0.U, 0.U, false.B, false.B, false.B, false.B)
  }
  io.out.info.fusel := fuType

  // setInfo(inst, regWAddr, src1RAddr, src2RAddr, op, regWEn, src1REn, src2REn, valid)
  /*
  io.out.info := DontCare
  io.out.info.valid := false.B
  when(instrType === InstrR){
    val (rd,rs1,rs2) = (inst(11,7),inst(19,15),inst(24,20))
    io.out.info.reg_waddr := rd
    io.out.info.src1_raddr := rs1
    io.out.info.src2_raddr := rs2

    io.out.info.op := Cat(io.in.inst(3), io.in.inst(30), io.in.inst(14, 12))
    io.out.info.reg_wen := true.B
    io.out.info.valid := true.B
  }.elsewhen(instrType === InstrI){
    val (rd,rs1,imm12)  =  (inst(11,7),inst(19,15),inst(31,20))
    io.out.info.imm := imm12
    io.out.info.src1_raddr := rs1
    io.out.info.reg_waddr := rd

    io.out.info.op := DontCare // Use a decoding function
    io.out.info.src2_raddr := 0.U
    io.out.info.src1_ren := true.B
    io.out.info.src2_ren := false.B
    io.out.info.reg_wen := true.B
    io.out.info.valid := true.B

  }.otherwise{
    io.out.info.src1_raddr := DontCare
    io.out.info.src2_raddr := DontCare
    io.out.info.op := DontCare // Use a decoding function
    io.out.info.reg_wen := false.B  // unneccesary ?
    io.out.info.reg_waddr := DontCare
    io.out.info.valid := false.B

  }
   */
}
