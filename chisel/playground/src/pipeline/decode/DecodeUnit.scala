package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class DecodeUnit extends Module with HasInstrType {
  val io = IO(new Bundle {
    // 输入
    val decodeStage = Flipped(new FetchUnitDecodeUnit())
    val regfile     = new Src12Read()
    // 输出
    val executeStage = Output(new DecodeUnitExecuteUnit())
  })

  val decoder = Module(new Decoder())
  decoder.io.in.inst := io.decodeStage.data.inst

  val pc     = io.decodeStage.data.pc
  val info   = Wire(new Info())
  val is_lui = decoder.io.out.info.instr(31, 25) === "b0001110".U // is pccadd12ui
  printf(p"decodeUnit ${Hexadecimal(inst)}\n");
  printf(p"islui ${Hexadecimal(is_lui)}\n");

  val inst = decoder.io.out.info.instr
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)

  val imm = LookupTree(
    instrType,
    Seq(
      // inst24 代表 I 指令是否要符号拓展 0 -> s, 1 -> u
      InstrI -> Mux(inst(24), ZeroExtend(inst(21, 10), XLEN), SignedExtend(inst(21, 10), XLEN)),
      InstrS -> SignedExtend(inst(21, 10), XLEN),
      InstrB -> SignedExtend(Cat(inst(25, 0), 0.U(2.W)), XLEN), // 没有压缩指令
      InstrU -> SignedExtend(Cat(inst(24, 5), 0.U(12.W)), XLEN),
      InstrJ -> SignedExtend(Cat(inst(25, 10), 0.U(2.W)), XLEN) // 没有压缩指令
    )
  )

  info       := decoder.io.out.info
  info.valid := io.decodeStage.data.valid
  info.imm   := imm

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
