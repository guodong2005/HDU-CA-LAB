package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class DecodeUnit extends Module with HasInstrType{
  val io = IO(new Bundle {
    // 输入
    val decodeStage = Flipped(new FetchUnitDecodeUnit())
    val regfile     = new Src12Read()
    // 输出
    val executeStage = Output(new DecodeUnitExecuteUnit())
    val imm = UInt()
  })

  val decoder = Module(new Decoder())
  decoder.io.in.inst := io.decodeStage.data.inst

  val pc     = io.decodeStage.data.pc
  val info   = Wire(new Info())
  val is_lui = decoder.io.out.info.instr(6, 0) === "b0110111".U

  val inst = decoder.io.out.info.instr
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)
  /*
  io.imm := MuxCase(
    0.U,
    Array(
      (instrType === InstrI) -> Cat(Fill(52,inst(31)),inst(31, 20)),
      (instrType === InstrU) -> Cat(Fill(32,inst(31)),inst(31, 12),Fill(12,0.U))
    )
  ) // has a warning, I will ignore it for now  3/19/2025
   */
  // val imm = io.imm
  val imm = LookupTree(
    instrType,
    Seq(
      InstrI -> SignedExtend(inst(31, 20), XLEN),
      InstrU -> SignedExtend(Cat(inst(31, 12),0.U(12.W)),XLEN)
    ) 
  )

  info       := decoder.io.out.info
  info.valid := io.decodeStage.data.valid

  io.regfile.src1.raddr := decoder.io.out.info.src1_raddr
  io.regfile.src2.raddr := decoder.io.out.info.src2_raddr

  io.executeStage.data.pc                 := pc
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := Mux(info.src1_ren, io.regfile.src1.rdata, Mux(is_lui, 0.U, pc))
  io.executeStage.data.src_info.src2_data := Mux(info.src2_ren, io.regfile.src2.rdata, imm)
  // why doesnt need op type ?

  // io.executeStage.data.info               :=
  // io.executeStage.data.src_info.src1_data :=
  // io.executeStage.data.src_info.src2_data :=

}
