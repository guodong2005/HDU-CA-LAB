package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Mdu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
    val valid    = Output(Bool())
    val ready    = Output(Bool())
  })

  val isMulW = io.info.valid && (io.info.fusel === FuType.mdu) && (io.info.op === MDUOpType.mul)

  // 流水线寄存器
  val stage1_result = RegInit(0.U(32.W))
  val stage2_result = RegInit(0.U(32.W))
  val stage1_valid  = RegInit(false.B)
  val stage2_valid  = RegInit(false.B)

  // 忙状态寄存器
  val busy = RegInit(false.B)

  // 第三级组合逻辑输出
  val stage3_valid  = stage2_valid
  val stage3_result = stage2_result.asSInt.asUInt // 符号扩展到XLEN位

  // Ready逻辑：当有结果输出时立即变为ready，或者在空闲状态
  io.ready := !isMulW || stage3_valid

  // 忙状态控制
  when(isMulW && !busy) {
    busy := true.B
  }.elsewhen(stage3_valid) {
    busy := false.B
  }

  // 第一级：32位乘法计算
  when(isMulW && !busy) {
    stage1_result := io.src_info.src1_data(31, 0) * io.src_info.src2_data(31, 0)
    stage1_valid  := true.B
  }.elsewhen(!isMulW && !busy) {
    stage1_valid := false.B
  }

  // 第二级：流水线传递
  stage2_result := stage1_result
  stage2_valid  := stage1_valid

  // 输出赋值
  io.result := stage3_result
  io.valid  := stage3_valid
}
