package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class ControlSignal extends Bundle {
  val allow_to_go = Bool()
  val do_flush    = Bool()
}

// 简化的前递控制信号和数据
class BypassData extends Bundle {
  val src1_bypass = Bool()
  val src2_bypass = Bool()
  val src1_data   = UInt(XLEN.W)
  val src2_data   = UInt(XLEN.W)
}

// 新增：分支控制输出
class BranchControl extends Bundle {
  val branch = Bool()
  val target = UInt(XLEN.W)
}

class Signals extends Bundle {
  val fetchUnitSignal   = Output(new ControlSignal())
  val decodeUnitSignal  = Output(new ControlSignal())
  val executeUnitSignal = Output(new ControlSignal())
  val bypassData        = Output(new BypassData()) // 前递数据
  val branchControl     = Output(new BranchControl()) // 新增：分支控制输出
}

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val decodeInfo       = Input(new Info())
    val executeInfo      = Input(new Info())
    val writeBackInfo    = Input(new Info())
    val executeUnitReady = Input(Bool())
    val signals          = Output(new Signals())

    // 分支信号输入
    val executeBranch = Input(Bool()) // 来自ExecuteUnit的分支信号
    val executeTarget = Input(UInt(XLEN.W)) // 来自ExecuteUnit的跳转目标

    // 来自DecodeUnit的信息
    val decodeRegisterInfo = Input(new DecodeRegisterInfo())

    // 各阶段的结果数据用于前递
    val executeResult   = Input(UInt(XLEN.W))
    val writeBackResult = Input(UInt(XLEN.W))
  })

  // ========== 前递逻辑 ==========
  def canForwardFromStage(stageInfo: Info, srcAddr: UInt, srcEn: Bool): Bool = {
    stageInfo.valid && stageInfo.reg_wen && stageInfo.reg_waddr.orR &&
    srcEn && (srcAddr === stageInfo.reg_waddr)
  }

  // src1前递检查
  val src1_forward_from_ex = canForwardFromStage(
    io.executeInfo,
    io.decodeRegisterInfo.src1_raddr,
    io.decodeRegisterInfo.src1_ren
  )

  val src1_forward_from_wb = canForwardFromStage(
    io.writeBackInfo,
    io.decodeRegisterInfo.src1_raddr,
    io.decodeRegisterInfo.src1_ren
  )

  // src2前递检查
  val src2_forward_from_ex = canForwardFromStage(
    io.executeInfo,
    io.decodeRegisterInfo.src2_raddr,
    io.decodeRegisterInfo.src2_ren
  )

  val src2_forward_from_wb = canForwardFromStage(
    io.writeBackInfo,
    io.decodeRegisterInfo.src2_raddr,
    io.decodeRegisterInfo.src2_ren
  )

  // 前递优先级选择（EX优先级高于WB）
  val src1_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      src1_forward_from_ex -> 1.U(2.W),
      src1_forward_from_wb -> 2.U(2.W)
    )
  )

  val src2_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      src2_forward_from_ex -> 1.U(2.W),
      src2_forward_from_wb -> 2.U(2.W)
    )
  )

  // ========== 生成前递信号和数据 ==========
  io.signals.bypassData.src1_bypass := src1_forward_sel.orR
  io.signals.bypassData.src2_bypass := src2_forward_sel.orR

  io.signals.bypassData.src1_data := MuxCase(
    0.U,
    Seq(
      (src1_forward_sel === 1.U) -> io.executeResult,
      (src1_forward_sel === 2.U) -> io.writeBackResult
    )
  )

  io.signals.bypassData.src2_data := MuxCase(
    0.U,
    Seq(
      (src2_forward_sel === 1.U) -> io.executeResult,
      (src2_forward_sel === 2.U) -> io.writeBackResult
    )
  )

  // ========== 分支控制逻辑 ==========
  // Execute阶段的分支优先级高于Decode阶段
  // 因为Execute阶段的分支表示条件分支已经解析，需要覆盖之前的预测
  val actualBranch = io.executeBranch
  val branchTarget = io.executeTarget

  // 输出分支控制信号给FetchUnit
  io.signals.branchControl.branch := actualBranch
  io.signals.branchControl.target := branchTarget

  // ========== 流水线控制逻辑 ==========
  val pipeline_stall = false.B // 由于有完整的前递，不需要额外的stall

  // Generate control signals
  io.signals.fetchUnitSignal.allow_to_go   := (!pipeline_stall) & io.executeUnitReady
  io.signals.decodeUnitSignal.allow_to_go  := (!pipeline_stall) & io.executeUnitReady
  io.signals.executeUnitSignal.allow_to_go := true.B

  // Flush信号处理：
  // - 如果Execute阶段有分支，刷新F和D阶段
  // - 如果只有Decode阶段有分支（无条件跳转），只刷新F阶段
  io.signals.fetchUnitSignal.do_flush   := actualBranch
  io.signals.decodeUnitSignal.do_flush  := io.executeBranch // 只有Execute的分支才刷新Decode
  io.signals.executeUnitSignal.do_flush := false.B

}
