package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class ControlSignal extends Bundle {
  val allow_to_go = Bool()
  val do_flush    = Bool()
}

// 前递控制信号和数据
class BypassData extends Bundle {
  val src1_bypass = Bool() // src1是否需要前递
  val src2_bypass = Bool() // src2是否需要前递
  val src1_data   = UInt(XLEN.W) // src1前递的数据
  val src2_data   = UInt(XLEN.W) // src2前递的数据
}

class Signals extends Bundle {
  val fetchUnitSignal   = Output(new ControlSignal())
  val decodeUnitSignal  = Output(new ControlSignal())
  val executeUnitSignal = Output(new ControlSignal())
  val memoryUnitSignal  = Output(new ControlSignal())
  val bypassData        = Output(new BypassData()) // 新增前递数据
}

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val decodeInfo       = Input(new Info())
    val executeInfo      = Input(new Info())
    val memoryInfo       = Input(new Info())
    val writeBackInfo    = Input(new Info())
    val executeUnitReady = Input(Bool())
    val signals          = Output(new Signals())
    val branch           = Input(Bool())

    // 新增：各阶段的结果数据用于前递（MEM阶段无实际功能，但保留接口）
    val executeResult   = Input(UInt(XLEN.W)) // EXU的计算结果（包括load结果）
    val memoryResult    = Input(UInt(XLEN.W)) // MEM阶段的结果（实际上就是EX结果的传递）
    val writeBackResult = Input(UInt(XLEN.W)) // WB阶段的结果
  })

  // 前递逻辑：检查是否可以通过前递解决数据冲突
  def canForwardFromStage(stageInfo: Info, srcAddr: UInt, srcEn: Bool): Bool = {
    stageInfo.valid && stageInfo.reg_wen && stageInfo.reg_waddr.orR &&
    srcEn && (srcAddr === stageInfo.reg_waddr)
  }

  // 检查各阶段是否可以前递到src1
  val src1_forward_from_ex  = canForwardFromStage(io.executeInfo, io.decodeInfo.src1_raddr, io.decodeInfo.src1_ren)
  val src1_forward_from_mem = canForwardFromStage(io.memoryInfo, io.decodeInfo.src1_raddr, io.decodeInfo.src1_ren)
  val src1_forward_from_wb  = canForwardFromStage(io.writeBackInfo, io.decodeInfo.src1_raddr, io.decodeInfo.src1_ren)

  // 检查各阶段是否可以前递到src2
  val src2_forward_from_ex  = canForwardFromStage(io.executeInfo, io.decodeInfo.src2_raddr, io.decodeInfo.src2_ren)
  val src2_forward_from_mem = canForwardFromStage(io.memoryInfo, io.decodeInfo.src2_raddr, io.decodeInfo.src2_ren)
  val src2_forward_from_wb  = canForwardFromStage(io.writeBackInfo, io.decodeInfo.src2_raddr, io.decodeInfo.src2_ren)

  // 前递优先级：EX > MEM > WB（越近的阶段优先级越高）
  val src1_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      src1_forward_from_wb  -> 3.U(2.W), // 从WB前递
      src1_forward_from_mem -> 2.U(2.W), // 从MEM前递
      src1_forward_from_ex  -> 1.U(2.W) // 从EX前递
    )
  )

  val src2_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      src2_forward_from_wb  -> 3.U(2.W), // 从WB前递
      src2_forward_from_mem -> 2.U(2.W), // 从MEM前递
      src2_forward_from_ex  -> 1.U(2.W) // 从EX前递
    )
  )

  // 生成bypassData信号和数据
  io.signals.bypassData.src1_bypass := src1_forward_sel.orR
  io.signals.bypassData.src2_bypass := src2_forward_sel.orR

  io.signals.bypassData.src1_data := MuxCase(
    0.U,
    Seq(
      (src1_forward_sel === 1.U) -> io.executeResult,
      (src1_forward_sel === 2.U) -> io.memoryResult,
      (src1_forward_sel === 3.U) -> io.writeBackResult
    )
  )

  io.signals.bypassData.src2_data := MuxCase(
    0.U,
    Seq(
      (src2_forward_sel === 1.U) -> io.executeResult,
      (src2_forward_sel === 2.U) -> io.memoryResult,
      (src2_forward_sel === 3.U) -> io.writeBackResult
    )
  )

  // 检查Load-Use冲突（由于load指令在execute阶段就完成，所以不存在Load-Use冲突）
  // val load_use_hazard = false.B  // 没有Load-Use冲突

  // 更新后的冲突检测：由于有前递机制，大部分冲突都可以通过前递解决
  val exe_conflict = false.B // EX阶段可以前递，不需要stall
  val mem_conflict = false.B // MEM阶段没有实际功能，不需要stall
  val wb_conflict  = false.B // WB阶段可以前递，不需要stall

  val pipeline_stall = exe_conflict || mem_conflict || wb_conflict

  // Generate control signals using modular assignment
  io.signals.fetchUnitSignal.allow_to_go   := (!pipeline_stall) & (io.executeUnitReady)
  io.signals.decodeUnitSignal.allow_to_go  := (!pipeline_stall) & (io.executeUnitReady)
  io.signals.executeUnitSignal.allow_to_go := true.B
  io.signals.memoryUnitSignal.allow_to_go  := true.B

  io.signals.fetchUnitSignal.do_flush   := io.branch
  io.signals.decodeUnitSignal.do_flush  := io.branch
  io.signals.executeUnitSignal.do_flush := false.B
  io.signals.memoryUnitSignal.do_flush  := false.B
}
