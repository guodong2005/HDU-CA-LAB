package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class MiniBru extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val pc       = Input(UInt(XLEN.W))
    val src_info = Input(new SrcInfo())
    val branch   = Output(Bool())
    val target   = Output(UInt(XLEN.W))
    val valid    = Output(Bool())
  })

  val src1 = io.src_info.src1_data
  val src2 = io.src_info.src2_data
  val imm  = io.info.imm
  val op   = io.info.op

  // 并行计算所有可能的比较结果
  val eq  = src1 === src2
  val ne  = !eq
  val lt  = src1.asSInt < src2.asSInt
  val ge  = !lt
  val ltu = src1 < src2
  val geu = !ltu

  // 使用简单的Mux选择
  val takeBranch = MuxCase(
    false.B,
    Seq(
      (op === BRUOpType.beq)  -> eq,
      (op === BRUOpType.bne)  -> ne,
      (op === BRUOpType.blt)  -> lt,
      (op === BRUOpType.bge)  -> ge,
      (op === BRUOpType.bltu) -> ltu,
      (op === BRUOpType.bgeu) -> geu,
      (op === BRUOpType.b)    -> true.B,
      (op === BRUOpType.bl)   -> true.B,
      (op === BRUOpType.jirl) -> true.B
    )
  )

  // 并行计算所有可能的目标地址
  val branchTarget   = io.pc + imm
  val jumpTarget     = io.pc + imm
  val indirectTarget = src1 + imm

  // 选择正确的目标地址
  io.target := Mux(op === BRUOpType.jirl, indirectTarget, Mux(op === BRUOpType.b || op === BRUOpType.bl, jumpTarget, branchTarget))

  io.branch := takeBranch
  io.valid  := io.info.fusel === FuType.bru && io.info.valid
}
