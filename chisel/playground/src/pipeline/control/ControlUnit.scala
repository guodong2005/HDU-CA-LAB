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
  val src1_bypass = Bool()       // src1是否需要前递
  val src2_bypass = Bool()       // src2是否需要前递
  val src1_data   = UInt(XLEN.W) // src1前递的数据
  val src2_data   = UInt(XLEN.W) // src2前递的数据
}

class Signals extends Bundle {
  val fetchUnitSignal   = Output(new ControlSignal())
  val decodeUnitSignal  = Output(new ControlSignal())
  val executeUnitSignal = Output(new ControlSignal())
  val memoryUnitSignal  = Output(new ControlSignal())
  val bypassData        = Output(new BypassData()) // 前递数据
  val decodeStall       = Output(Bool())           // 新增：解码阶段内部stall信号
}

// 新增：解码阶段的信息，包含两个流水级的信息
class DecodeStageInfo extends Bundle {
  val stage1_inst  = UInt(32.W) // 第一级的指令
  val stage1_valid = Bool()     // 第一级是否有效
  val stage2_inst  = UInt(32.W) // 第二级的指令
  val stage2_valid = Bool()     // 第二级是否有效
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

    // 新增：解码阶段的详细信息
    val decodeStageInfo = Input(new DecodeStageInfo())

    // 各阶段的结果数据用于前递
    val executeResult   = Input(UInt(XLEN.W)) // EXU的计算结果（包括load结果）
    val memoryResult    = Input(UInt(XLEN.W)) // MEM阶段的结果
    val writeBackResult = Input(UInt(XLEN.W)) // WB阶段的结果
  })

  // ========== 解码阶段内部冲突检测 ==========
  // 从第一级指令中提取信息
  val stage1_inst  = io.decodeStageInfo.stage1_inst
  val stage1_valid = io.decodeStageInfo.stage1_valid

  // 第一级指令的寄存器地址（用于BRU指令）
  val stage1_rj = stage1_inst(9, 5) // rs1
  val stage1_rd = stage1_inst(4, 0) // rd (用作BRU比较指令的第二个源)

  // 第一级BRU指令识别
  val stage1_opcode  = stage1_inst(31, 26)
  val stage1_is_beq  = stage1_opcode === "b010110".U
  val stage1_is_bne  = stage1_opcode === "b010111".U
  val stage1_is_blt  = stage1_opcode === "b011000".U
  val stage1_is_bge  = stage1_opcode === "b011001".U
  val stage1_is_bltu = stage1_opcode === "b011010".U
  val stage1_is_bgeu = stage1_opcode === "b011011".U
  val stage1_is_jirl = stage1_opcode === "b010011".U

  val stage1_bru_need_rj = stage1_is_jirl || stage1_is_beq || stage1_is_bne ||
    stage1_is_blt || stage1_is_bge || stage1_is_bltu || stage1_is_bgeu
  val stage1_bru_need_rd = stage1_is_beq || stage1_is_bne || stage1_is_blt ||
    stage1_is_bge || stage1_is_bltu || stage1_is_bgeu

  // 从第二级获取目标寄存器信息
  val stage2_inst  = io.decodeStageInfo.stage2_inst
  val stage2_valid = io.decodeStageInfo.stage2_valid
  val stage2_rd    = stage2_inst(4, 0)

  // 简单的指令类型判断（判断第二级是否会写寄存器）
  val stage2_opcode     = stage2_inst(31, 26)
  val stage2_is_b       = stage2_opcode === "b010100".U                                   // B指令不写寄存器
  val stage2_is_store   = stage2_opcode === "b001010".U && stage2_inst(25, 22)(2) === 1.U // Store指令不写寄存器
  val stage2_will_write = stage2_valid && stage2_rd.orR && !stage2_is_b && !stage2_is_store

  // 检测解码阶段内部的冲突：
  // 如果第二级要写的寄存器是第一级BRU指令要读的寄存器，则需要stall
  val decode_internal_conflict = stage1_valid && stage2_will_write && (
    (stage1_bru_need_rj && stage1_rj === stage2_rd) ||
      (stage1_bru_need_rd && stage1_rd === stage2_rd)
  )

  // ========== 前递逻辑 ==========
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

  // 前递优先级：EX > MEM > WB
  val src1_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      src1_forward_from_wb  -> 3.U(2.W),
      src1_forward_from_mem -> 2.U(2.W),
      src1_forward_from_ex  -> 1.U(2.W)
    )
  )

  val src2_forward_sel = MuxCase(
    0.U(2.W),
    Seq(
      src2_forward_from_wb  -> 3.U(2.W),
      src2_forward_from_mem -> 2.U(2.W),
      src2_forward_from_ex  -> 1.U(2.W)
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

  // ========== 流水线控制信号生成 ==========
  val pipeline_stall = false.B // 由于有前递，后续阶段不需要stall

  // 输出解码阶段内部stall信号
  io.signals.decodeStall := decode_internal_conflict

  // 生成控制信号
  // 当解码阶段内部有冲突时，需要stall fetch和decode的第一级
  io.signals.fetchUnitSignal.allow_to_go   := (!pipeline_stall) & (!decode_internal_conflict) & io.executeUnitReady
  io.signals.decodeUnitSignal.allow_to_go  := (!pipeline_stall) & io.executeUnitReady
  io.signals.executeUnitSignal.allow_to_go := true.B
  io.signals.memoryUnitSignal.allow_to_go  := true.B

  io.signals.fetchUnitSignal.do_flush   := io.branch
  io.signals.decodeUnitSignal.do_flush  := false.B
  io.signals.executeUnitSignal.do_flush := false.B
  io.signals.memoryUnitSignal.do_flush  := false.B

  // 调试输出
  when(decode_internal_conflict) {
    printf("[ControlUnit] Decode internal conflict detected!\n")
    printf("  Stage1: rj=%d, rd=%d, need_rj=%d, need_rd=%d\n", stage1_rj, stage1_rd, stage1_bru_need_rj, stage1_bru_need_rd)
    printf("  Stage2: rd=%d, will_write=%d\n", stage2_rd, stage2_will_write)
  }
}
