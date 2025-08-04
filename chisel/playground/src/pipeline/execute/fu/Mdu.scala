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

  // 2级流水线寄存器（第三级变为组合逻辑）
  val stage1_result = RegInit(0.U(64.W))
  val stage2_result = RegInit(0.U(64.W))

  // 操作类型流水线
  val stage1_op = RegInit(0.U(4.W))
  val stage2_op = RegInit(0.U(4.W))

  // 有效信号流水线
  val stage1_valid = RegInit(false.B)
  val stage2_valid = RegInit(false.B)

  // 忙状态寄存器
  val busy = RegInit(false.B)

  val isMdu = io.info.valid && (io.info.fusel === FuType.mdu)

  // 组合逻辑：第三级输出选择
  val stage3_result = Wire(UInt(XLEN.W))
  val stage3_valid  = Wire(Bool())

  stage3_valid  := stage2_valid
  stage3_result := stage2_result(31, 0) // mul.w 只需要低32位

  // Ready逻辑：当有结果输出时立即变为ready，或者在空闲状态
  io.ready := !isMdu || stage3_valid

  // 忙状态控制
  when(isMdu && !busy) {
    // 新指令进入，设置忙状态
    busy := true.B
  }.elsewhen(stage3_valid) {
    // 第三级输出有效时，清除忙状态（组合逻辑）
    busy := false.B
  }

  // 第一级：开始计算
  when(isMdu && !busy) {
    stage1_op    := io.info.op
    stage1_valid := true.B

    // 只处理 mul.w 指令
    stage1_result := io.src_info.src1_data * io.src_info.src2_data
  }.elsewhen(!isMdu && !busy) {
    // 非MDU指令且不忙时，清除第一级有效信号
    stage1_valid := false.B
  }

  // 第二级：直接传递结果
  stage2_result := stage1_result
  stage2_op     := stage1_op
  stage2_valid  := stage1_valid

  // 输出赋值（组合逻辑）
  io.result := stage3_result
  io.valid  := stage3_valid
}
