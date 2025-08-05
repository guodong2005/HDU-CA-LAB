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

  // 提前计算所有可能的结果以增加并行性
  val src1 = io.src_info.src1_data
  val src2 = io.src_info.src2_data

  // 并行计算所有操作结果
  val add_result = (src1 + src2)(31, 0)
  val sub_result = (src1 - src2)(31, 0)
  val and_result = (src1 & src2)(31, 0)
  val or_result  = (src1 | src2)(31, 0)
  val xor_result = (src1 ^ src2)(31, 0)

  // 移位操作 - 只使用低5位作为移位量
  val shift_amount = src2(4, 0)
  val sll_result   = (src1 << shift_amount)(31, 0)
  val srl_result   = (src1 >> shift_amount)(31, 0)

  // 使用多路选择器选择最终结果
  io.result := MuxLookup(io.info.op, 0.U)(
    Seq(
      ALUOpType.add -> add_result, // ADD/ADDI.W
      ALUOpType.sub -> sub_result, // SUB.W
      ALUOpType.and -> and_result, // AND/ANDI
      ALUOpType.or  -> or_result,  // OR/ORI
      ALUOpType.xor -> xor_result, // XOR
      ALUOpType.sll -> sll_result, // SLLI.W
      ALUOpType.srl -> srl_result  // SRLI.W
    ))

  // 输出有效信号
  io.valid := io.info.valid
}
