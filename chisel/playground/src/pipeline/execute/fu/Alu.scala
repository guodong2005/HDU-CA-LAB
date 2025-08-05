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

  // 并行计算所有可能的结果
  val src1 = io.src_info.src1_data
  val src2 = io.src_info.src2_data

  // 算术运算单元 - 并行计算
  val adder_result = src1 + src2
  val sub_result   = src1 - src2

  // 逻辑运算单元 - 并行计算
  val and_result = src1 & src2
  val or_result  = src1 | src2
  val xor_result = src1 ^ src2

  // 移位运算单元 - 并行计算
  val shift_amount = src2(4, 0) // 只取低5位作为移位量
  val sll_result   = src1 << shift_amount
  val srl_result   = src1 >> shift_amount

  // 比较运算单元 - 用于分支指令
  val eq_result = (src1 === src2)
  val ne_result = (src1 =/= src2)

  // 输出逻辑 - 使用并行MUX选择
  io.result := MuxLookup(io.info.op, 0.U)(
    Seq(
      ALUOpType.add -> adder_result(31, 0), // add.w, addi.w, pcaddu12i, 地址计算
      ALUOpType.sub -> sub_result(31, 0),   // sub.w
      ALUOpType.and -> and_result(31, 0),   // and, andi
      ALUOpType.or  -> or_result(31, 0),    // or, ori
      ALUOpType.xor -> xor_result(31, 0),   // xor
      ALUOpType.sll -> sll_result(31, 0),   // slli.w
      ALUOpType.srl -> srl_result(31, 0)    // srli.w

    ))

  io.valid := io.info.valid

  // 可选：添加性能计数器
  // val op_counter = RegInit(VecInit(Seq.fill(16)(0.U(32.W))))
  // when(io.info.valid) {
  //   op_counter(io.info.op) := op_counter(io.info.op) + 1.U
  // }
}
