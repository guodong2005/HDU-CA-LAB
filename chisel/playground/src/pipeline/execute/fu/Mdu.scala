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

  // 3级流水线寄存器
  val stage1_result = RegInit(0.U(64.W))
  val stage2_result = RegInit(0.U(64.W))
  val stage3_result = RegInit(0.U(XLEN.W))

  // 操作类型流水线
  val stage1_op = RegInit(0.U(4.W))
  val stage2_op = RegInit(0.U(4.W))
  val stage3_op = RegInit(0.U(4.W))

  // 有效信号流水线
  val stage1_valid = RegInit(false.B)
  val stage2_valid = RegInit(false.B)
  val stage3_valid = RegInit(false.B)

  // 源操作数流水线（用于除法余数计算）
  val stage1_src1 = RegInit(0.U(XLEN.W))
  val stage1_src2 = RegInit(0.U(XLEN.W))
  val stage2_src1 = RegInit(0.U(XLEN.W))
  val stage2_src2 = RegInit(0.U(XLEN.W))

  // 忙状态寄存器 - 用于控制ready信号
  val busy = RegInit(false.B)

  val isMdu = io.info.valid && (io.info.fusel === FuType.mdu)

  // 零值检测
  val iszero  = io.src_info.src2_data === 0.U
  val neg1_32 = (-1).S(32.W)

  // ready逻辑修改：只有在空闲状态下才能接受新指令
  io.ready := !busy

  // 忙状态控制
  when(isMdu && !busy) {
    // 新指令进入，设置忙状态
    busy := true.B
  }.elsewhen(stage3_valid) {
    // 第三级输出有效时，清除忙状态
    busy := false.B
  }

  // 第一级：开始计算
  when(isMdu && !busy) {
    stage1_src1  := io.src_info.src1_data
    stage1_src2  := io.src_info.src2_data
    stage1_op    := io.info.op
    stage1_valid := true.B

    switch(io.info.op) {
      // 乘法操作
      is(MDUOpType.mul) {
        stage1_result := io.src_info.src1_data * io.src_info.src2_data
      }
      is(MDUOpType.mulh) {
        stage1_result := (io.src_info.src1_data.asSInt * io.src_info.src2_data.asSInt).asUInt
      }
      is(MDUOpType.mulhu) {
        stage1_result := io.src_info.src1_data * io.src_info.src2_data
      }

      // 除法操作
      is(MDUOpType.div) {
        val overflow = io.src_info.src2_data.asSInt === neg1_32 &&
          io.src_info.src1_data.asSInt === -(1 << 31).S
        val div_result = Mux(
          iszero,
          (-1).S(64.W).asUInt,
          Mux(
            overflow,
            io.src_info.src1_data.asUInt,
            (io.src_info.src1_data.asSInt / io.src_info.src2_data.asSInt).asUInt
          )
        )
        stage1_result := div_result
      }
      is(MDUOpType.divu) {
        val div_result = Mux(iszero, (-1).S(64.W).asUInt, (io.src_info.src1_data / io.src_info.src2_data).asUInt)
        stage1_result := div_result
      }

      // 余数操作 - 第一级先计算商
      is(MDUOpType.rem) {
        val quotient = Mux(iszero, 0.U, (io.src_info.src1_data.asSInt / io.src_info.src2_data.asSInt).asUInt)
        stage1_result := quotient
      }
      is(MDUOpType.remu) {
        val quotient = Mux(iszero, 0.U, (io.src_info.src1_data / io.src_info.src2_data).asUInt)
        stage1_result := quotient
      }
    }
  }.elsewhen(!isMdu && !busy) {
    // 非MDU指令且不忙时，清除第一级有效信号
    stage1_valid := false.B
  }

  // 第二级：继续处理
  stage2_result := stage1_result
  stage2_op     := stage1_op
  stage2_valid  := stage1_valid
  stage2_src1   := stage1_src1
  stage2_src2   := stage1_src2

  // 对于余数操作，在第二级计算实际余数
  when(stage1_valid) {
    switch(stage1_op) {
      is(MDUOpType.rem) {
        val iszero_stage1 = stage1_src2 === 0.U
        val remainder =
          Mux(iszero_stage1, stage1_src1.asSInt, stage1_src1.asSInt - stage1_result.asSInt * stage1_src2.asSInt)
        stage2_result := remainder.asUInt
      }
      is(MDUOpType.remu) {
        val iszero_stage1 = stage1_src2 === 0.U
        val remainder     = Mux(iszero_stage1, stage1_src1, stage1_src1 - stage1_result * stage1_src2)
        stage2_result := remainder
      }
    }
  }

  // 第三级：最终输出选择
  stage3_op    := stage2_op
  stage3_valid := stage2_valid

  when(stage2_valid) {
    switch(stage2_op) {
      is(MDUOpType.mul) {
        stage3_result := stage2_result(31, 0) // 低32位
      }
      is(MDUOpType.mulh) {
        stage3_result := stage2_result(63, 32) // 高32位，有符号
      }
      is(MDUOpType.mulhu) {
        stage3_result := stage2_result(63, 32) // 高32位，无符号
      }
      is(MDUOpType.div) {
        stage3_result := stage2_result(31, 0)
      }
      is(MDUOpType.divu) {
        stage3_result := stage2_result(31, 0)
      }
      is(MDUOpType.rem) {
        stage3_result := stage2_result(31, 0)
      }
      is(MDUOpType.remu) {
        stage3_result := stage2_result(31, 0)
      }
    }
  }.otherwise {
    stage3_result := 0.U
  }

  // 输出赋值
  io.result := stage3_result
  io.valid  := stage3_valid
}
