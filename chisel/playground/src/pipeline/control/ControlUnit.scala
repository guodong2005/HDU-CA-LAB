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
    val executeBranch = Input(Bool()) // 来自ExecuteUnit的分支信号（分支预测失败时为true）
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
      src1_forward_from_wb -> 2.U(2.W),
      src1_forward_from_ex -> 1.U(2.W)
    )
  )

  val src2_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      src2_forward_from_wb -> 2.U(2.W),
      src2_forward_from_ex -> 1.U(2.W)
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
  // 修改：只有ExecuteUnit的分支信号才用于实际的分支控制
  // ExecuteUnit的分支信号表示分支预测失败，需要进行流水线flush和跳转
  // DecodeUnit的分支信号可用于其他目的（如分支预测），但不直接控制flush

  // 输出分支控制信号给FetchUnit（只响应ExecuteUnit的分支）
  io.signals.branchControl.branch := io.executeBranch
  io.signals.branchControl.target := io.executeTarget

  // ========== 流水线控制逻辑 ==========
  val pipeline_stall = false.B // 由于有完整的前递，不需要额外的stall

  // Generate control signals
  io.signals.fetchUnitSignal.allow_to_go   := (!pipeline_stall) & io.executeUnitReady
  io.signals.decodeUnitSignal.allow_to_go  := (!pipeline_stall) & io.executeUnitReady
  io.signals.executeUnitSignal.allow_to_go := true.B

  // 修改：Flush信号处理
  // 只有ExecuteUnit检测到分支预测失败时才进行flush
  // - executeBranch为true表示分支预测失败，需要刷新F和D阶段
  // - 不再响应DecodeUnit的分支信号进行flush
  io.signals.fetchUnitSignal.do_flush   := io.executeBranch
  io.signals.decodeUnitSignal.do_flush  := io.executeBranch
  io.signals.executeUnitSignal.do_flush := false.B

  // ========== 调试输出 ==========
  when(io.decodeRegisterInfo.src1_ren && src1_forward_sel.orR) {
    printf(
      "[ControlUnit] src1 forward: addr=%d, sel=%d, data=0x%x\n",
      io.decodeRegisterInfo.src1_raddr,
      src1_forward_sel,
      io.signals.bypassData.src1_data
    )
  }

  when(io.decodeRegisterInfo.src2_ren && src2_forward_sel.orR) {
    printf(
      "[ControlUnit] src2 forward: addr=%d, sel=%d, data=0x%x\n",
      io.decodeRegisterInfo.src2_raddr,
      src2_forward_sel,
      io.signals.bypassData.src2_data
    )
  }

  // 修改：调试输出只关注ExecuteUnit的分支控制
  when(io.executeBranch) {
    printf("[ControlUnit] Branch misprediction detected! Flushing F and D stages, target=0x%x\n", io.executeTarget)
  }

}
