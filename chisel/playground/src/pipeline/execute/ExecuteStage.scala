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

class ExecuteStage extends Module {
  val io = IO(new Bundle {
    val decodeUnit    = Input(new DecodeUnitExecuteUnit())
    val controlSignal = Input(new Signals())
    val ready         = Input(Bool())
    val executeUnit   = Output(new DecodeUnitExecuteUnit())
  })

  // 状态定义
  val sIdle :: sExec :: sFlush :: Nil = Enum(3)
  val state                           = RegInit(sIdle)

  // 数据寄存器
  val data = RegInit(0.U.asTypeOf(new IdExeData()))

  // 加入握手锁存机制
  val validReg   = RegInit(false.B) // 是否有待处理数据
  val latchData  = Reg(new IdExeData()) // 预锁存的数据
  val latchValid = io.controlSignal.decodeUnitSignal.allow_to_go && io.ready

  when(latchValid) {
    latchData := io.decodeUnit.data
    validReg  := true.B
  }

  // 默认输出
  io.executeUnit.data := data

  // 状态转移逻辑（只依赖 validReg）
  switch(state) {
    is(sIdle) {
      when(validReg) {
        data     := latchData
        state    := sExec
        validReg := false.B
      }
    }

    is(sExec) {
      when(io.controlSignal.decodeUnitSignal.do_flush) {
        data  := 0.U.asTypeOf(new IdExeData())
        state := sFlush
      }.elsewhen(validReg) {
        data     := latchData
        validReg := false.B
        state    := sExec
      }.otherwise {
        state := sExec
      }
    }

    is(sFlush) {
      state := sIdle
    }
  }
}
