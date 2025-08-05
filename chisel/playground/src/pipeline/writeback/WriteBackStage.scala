package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

// 重新定义WriteBack阶段的数据束，直接使用ExeMemData或者简化版本
class ExeWbData extends Bundle {
  val pc      = UInt(XLEN.W)
  val info    = new Info()
  val rd_info = new RdInfo()
  // 注意：去掉了src_info，因为WriteBack阶段通常不需要源操作数信息
}

class ExecuteUnitWriteBackUnit extends Bundle {
  val data = new ExeWbData()
}

class WriteBackStage extends Module {
  val io = IO(new Bundle {
    val executeUnit   = Input(new ExecuteUnitWriteBackUnit())  // 直接从execute unit接收数据
    val controlSignal = Input(new Signals())
    val writeBackUnit = Output(new ExecuteUnitWriteBackUnit()) // 输出到WriteBack单元
  })

  val data = RegInit(0.U.asTypeOf(new ExeWbData()))

  // 控制信号逻辑：当不允许进行时保持数据
  when(io.controlSignal.executeUnitSignal.allow_to_go === false.B) {
    data := data // 保持之前的数据
  }.otherwise {
    // 从ExeMemData转换到ExeWbData（去掉src_info字段）
    data.pc      := io.executeUnit.data.pc
    data.info    := io.executeUnit.data.info
    data.rd_info := io.executeUnit.data.rd_info
  }

  // 冲刷逻辑：当冲刷信号为高时重置数据
  when(io.controlSignal.executeUnitSignal.do_flush === true.B) {
    data := 0.U.asTypeOf(new ExeWbData()) // 重置数据
  }

  // 输出数据到下一阶段
  io.writeBackUnit.data := data
}
