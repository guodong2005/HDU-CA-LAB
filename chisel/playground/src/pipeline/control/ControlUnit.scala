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
  // Stage1 (MiniBRU) 前递
  val stage1_src1_bypass = Bool()
  val stage1_src2_bypass = Bool()
  val stage1_src1_data   = UInt(XLEN.W)
  val stage1_src2_data   = UInt(XLEN.W)
  // Stage2 前递
  val stage2_src1_bypass = Bool()
  val stage2_src2_bypass = Bool()
  val stage2_src1_data   = UInt(XLEN.W)
  val stage2_src2_data   = UInt(XLEN.W)
}

class Signals extends Bundle {
  val fetchUnitSignal   = Output(new ControlSignal())
  val decodeUnitSignal  = Output(new ControlSignal())
  val executeUnitSignal = Output(new ControlSignal())
  val memoryUnitSignal  = Output(new ControlSignal())
  val bypassData        = Output(new BypassData()) // 前递数据
  val decodeStage1Stall = Output(Bool())           // 控制DecodeUnit第一级的stall信号
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

    // 来自DecodeUnit的信息
    val decodeInternalStall = Input(Bool())
    val decodeRegisterInfo  = Input(new DecodeRegisterInfo())

    // 各阶段的结果数据用于前递
    val executeResult   = Input(UInt(XLEN.W))
    val memoryResult    = Input(UInt(XLEN.W))
    val writeBackResult = Input(UInt(XLEN.W))
  })

  // ========== Stage1 (MiniBRU) 前递逻辑 ==========
  def canForwardFromStage(stageInfo: Info, srcAddr: UInt, srcEn: Bool): Bool = {
    stageInfo.valid && stageInfo.reg_wen && stageInfo.reg_waddr.orR &&
    srcEn && (srcAddr === stageInfo.reg_waddr)
  }

  // Stage1 src1前递检查
  val stage1_src1_forward_from_ex = canForwardFromStage(
    io.executeInfo,
    io.decodeRegisterInfo.stage1_src1_raddr,
    io.decodeRegisterInfo.stage1_src1_ren
  )
  val stage1_src1_forward_from_mem = canForwardFromStage(
    io.memoryInfo,
    io.decodeRegisterInfo.stage1_src1_raddr,
    io.decodeRegisterInfo.stage1_src1_ren
  )
  val stage1_src1_forward_from_wb = canForwardFromStage(
    io.writeBackInfo,
    io.decodeRegisterInfo.stage1_src1_raddr,
    io.decodeRegisterInfo.stage1_src1_ren
  )

  // Stage1 src2前递检查
  val stage1_src2_forward_from_ex = canForwardFromStage(
    io.executeInfo,
    io.decodeRegisterInfo.stage1_src2_raddr,
    io.decodeRegisterInfo.stage1_src2_ren
  )
  val stage1_src2_forward_from_mem = canForwardFromStage(
    io.memoryInfo,
    io.decodeRegisterInfo.stage1_src2_raddr,
    io.decodeRegisterInfo.stage1_src2_ren
  )
  val stage1_src2_forward_from_wb = canForwardFromStage(
    io.writeBackInfo,
    io.decodeRegisterInfo.stage1_src2_raddr,
    io.decodeRegisterInfo.stage1_src2_ren
  )

  // Stage1前递优先级选择
  val stage1_src1_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      stage1_src1_forward_from_wb  -> 3.U(2.W),
      stage1_src1_forward_from_mem -> 2.U(2.W),
      stage1_src1_forward_from_ex  -> 1.U(2.W)
    )
  )

  val stage1_src2_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      stage1_src2_forward_from_wb  -> 3.U(2.W),
      stage1_src2_forward_from_mem -> 2.U(2.W),
      stage1_src2_forward_from_ex  -> 1.U(2.W)
    )
  )

  // ========== Stage2 前递逻辑 ==========
  // Stage2 src1前递检查
  val stage2_src1_forward_from_ex = canForwardFromStage(
    io.executeInfo,
    io.decodeRegisterInfo.stage2_src1_raddr,
    io.decodeRegisterInfo.stage2_src1_ren
  )
  val stage2_src1_forward_from_mem = canForwardFromStage(
    io.memoryInfo,
    io.decodeRegisterInfo.stage2_src1_raddr,
    io.decodeRegisterInfo.stage2_src1_ren
  )
  val stage2_src1_forward_from_wb = canForwardFromStage(
    io.writeBackInfo,
    io.decodeRegisterInfo.stage2_src1_raddr,
    io.decodeRegisterInfo.stage2_src1_ren
  )

  // Stage2 src2前递检查
  val stage2_src2_forward_from_ex = canForwardFromStage(
    io.executeInfo,
    io.decodeRegisterInfo.stage2_src2_raddr,
    io.decodeRegisterInfo.stage2_src2_ren
  )
  val stage2_src2_forward_from_mem = canForwardFromStage(
    io.memoryInfo,
    io.decodeRegisterInfo.stage2_src2_raddr,
    io.decodeRegisterInfo.stage2_src2_ren
  )
  val stage2_src2_forward_from_wb = canForwardFromStage(
    io.writeBackInfo,
    io.decodeRegisterInfo.stage2_src2_raddr,
    io.decodeRegisterInfo.stage2_src2_ren
  )

  // Stage2前递优先级选择
  val stage2_src1_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      stage2_src1_forward_from_wb  -> 3.U(2.W),
      stage2_src1_forward_from_mem -> 2.U(2.W),
      stage2_src1_forward_from_ex  -> 1.U(2.W)
    )
  )

  val stage2_src2_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      stage2_src2_forward_from_wb  -> 3.U(2.W),
      stage2_src2_forward_from_mem -> 2.U(2.W),
      stage2_src2_forward_from_ex  -> 1.U(2.W)
    )
  )

  // ========== 生成前递信号和数据 ==========
  // Stage1前递
  io.signals.bypassData.stage1_src1_bypass := stage1_src1_forward_sel.orR
  io.signals.bypassData.stage1_src2_bypass := stage1_src2_forward_sel.orR

  io.signals.bypassData.stage1_src1_data := MuxCase(
    0.U,
    Seq(
      (stage1_src1_forward_sel === 1.U) -> io.executeResult,
      (stage1_src1_forward_sel === 2.U) -> io.memoryResult,
      (stage1_src1_forward_sel === 3.U) -> io.writeBackResult
    )
  )

  io.signals.bypassData.stage1_src2_data := MuxCase(
    0.U,
    Seq(
      (stage1_src2_forward_sel === 1.U) -> io.executeResult,
      (stage1_src2_forward_sel === 2.U) -> io.memoryResult,
      (stage1_src2_forward_sel === 3.U) -> io.writeBackResult
    )
  )

  // Stage2前递
  io.signals.bypassData.stage2_src1_bypass := stage2_src1_forward_sel.orR
  io.signals.bypassData.stage2_src2_bypass := stage2_src2_forward_sel.orR

  io.signals.bypassData.stage2_src1_data := MuxCase(
    0.U,
    Seq(
      (stage2_src1_forward_sel === 1.U) -> io.executeResult,
      (stage2_src1_forward_sel === 2.U) -> io.memoryResult,
      (stage2_src1_forward_sel === 3.U) -> io.writeBackResult
    )
  )

  io.signals.bypassData.stage2_src2_data := MuxCase(
    0.U,
    Seq(
      (stage2_src2_forward_sel === 1.U) -> io.executeResult,
      (stage2_src2_forward_sel === 2.U) -> io.memoryResult,
      (stage2_src2_forward_sel === 3.U) -> io.writeBackResult
    )
  )

  // ========== 流水线控制逻辑 ==========
  val pipeline_stall = false.B // 由于有完整的前递，不需要额外的stall

  // 判断是否需要阻塞DecodeUnit的第一级
  val decode_stage1_stall = io.decodeInternalStall || !io.executeUnitReady

  // 输出给DecodeUnit的第一级stall信号
  io.signals.decodeStage1Stall := decode_stage1_stall

  // Generate control signals
  io.signals.fetchUnitSignal.allow_to_go   := (!pipeline_stall) & (!decode_stage1_stall)
  io.signals.decodeUnitSignal.allow_to_go  := (!pipeline_stall) & io.executeUnitReady
  io.signals.executeUnitSignal.allow_to_go := true.B
  io.signals.memoryUnitSignal.allow_to_go  := true.B

  io.signals.fetchUnitSignal.do_flush   := io.branch
  io.signals.decodeUnitSignal.do_flush  := false.B
  io.signals.executeUnitSignal.do_flush := false.B
  io.signals.memoryUnitSignal.do_flush  := false.B

  // 调试输出
  when(io.decodeRegisterInfo.stage1_src1_ren && stage1_src1_forward_sel.orR) {
    printf("[ControlUnit] Stage1 src1 forward: addr=%d, sel=%d\n", io.decodeRegisterInfo.stage1_src1_raddr, stage1_src1_forward_sel)
  }

  when(io.decodeRegisterInfo.stage1_src2_ren && stage1_src2_forward_sel.orR) {
    printf("[ControlUnit] Stage1 src2 forward: addr=%d, sel=%d\n", io.decodeRegisterInfo.stage1_src2_raddr, stage1_src2_forward_sel)
  }

  when(decode_stage1_stall) {
    printf("[ControlUnit] Decode stage 1 stall activated\n")
  }
}
