package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class DecodeUnit extends Module {
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
  val is_lui = decoder.io.out.info.instr(6, 0) === "b0110111".U

  info       := decoder.io.out.info
  info.valid := io.decodeStage.data.valid

  io.regfile.src1.raddr := decoder.io.out.info.src1_raddr
  io.regfile.src2.raddr := decoder.io.out.info.src2_raddr

  io.executeStage.data.pc                 := pc
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := io.regfile.src1.rdata
  io.executeStage.data.src_info.src2_data := Mux(
    info.src2_ren,
    io.regfile.src2.rdata,
    Cat(Fill(52, info.imm(11)), info.imm(11, 0)))
  // why doesnt need op type ?

  // io.executeStage.data.info               :=
  // io.executeStage.data.src_info.src1_data :=
  // io.executeStage.data.src_info.src2_data :=

}
