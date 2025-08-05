package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
class Alu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
    val valid    = Output(Bool())
  })

  val src1 = io.src_info.src1_data
  val src2 = io.src_info.src2_data

  // 位级并行加法器
  val sum_with_carry = src1 +& src2 // +& 会返回扩展位宽的结果，包含进位

  // 并行计算多个结果
  val results = Wire(Vec(8, UInt(32.W)))
  results(0) := (src1 + src2)(31, 0)        // ADD
  results(1) := (src1 - src2)(31, 0)        // SUB
  results(2) := (src1 & src2)(31, 0)        // AND
  results(3) := (src1 | src2)(31, 0)        // OR
  results(4) := (src1 ^ src2)(31, 0)        // XOR
  results(5) := (src1 << src2(4, 0))(31, 0) // SLL
  results(6) := (src1 >> src2(4, 0))(31, 0) // SRL
  results(7) := 0.U                         // Reserved

  // 使用独热编码进行快速选择
  val op_onehot = UIntToOH(io.info.op)
  io.result := Mux1H(op_onehot, results)
  io.valid  := io.info.valid
}
