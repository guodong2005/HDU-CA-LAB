package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class IdExeData extends Bundle {
  val pc       = UInt(XLEN.W)
  val info     = new Info()
  val src_info = new SrcInfo()
}

class DecodeUnitExecuteUnit extends Bundle {
  val data = new IdExeData()
}

class ExecuteStageFSM extends Module {
  val io = IO(new Bundle {
    val decodeUnit    = Input(new DecodeUnitExecuteUnit())
    val controlSignal = Input(new Signals())
    val ready         = Input(Bool()) // 下游 ready，相当于 AXI 的 ready
    val executeUnit   = Output(new DecodeUnitExecuteUnit())
  })

  // 状态定义
  val sIdle :: sExec :: sFlush :: Nil = Enum(3)
  val state                           = RegInit(sIdle)

  // 数据寄存器
  val data = RegInit(0.U.asTypeOf(new IdExeData()))

  // 默认输出
  io.executeUnit.data := data

  // 状态跳转逻辑
  switch(state) {
    is(sIdle) {
      // 输入有效，进入执行态
      when(io.controlSignal.decodeUnitSignal.allow_to_go && io.ready) {
        data  := io.decodeUnit.data
        state := sExec
      }
    }

    is(sExec) {
      when(io.controlSignal.decodeUnitSignal.do_flush) {
        data  := 0.U.asTypeOf(new IdExeData())
        state := sFlush
      }.elsewhen(io.controlSignal.decodeUnitSignal.allow_to_go && io.ready) {
        data := io.decodeUnit.data
        // 保持执行状态，继续处理下一个数据
        state := sExec
      }.otherwise {
        // 等待 valid/ready 对齐
        state := sExec
      }
    }

    is(sFlush) {
      // flush后回到空闲状态
      state := sIdle
    }
  }
}
