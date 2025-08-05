package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class DecodeUnit extends Module with HasInstrType {
  val io = IO(new Bundle {
    val decodeStage = Flipped(new FetchUnitDecodeUnit())
    val regfile     = new Src1234Read() // 修改为4个读端口
    val bypassData = Input(new Bundle {
      val src1_bypass = Bool()
      val src2_bypass = Bool()
      val src1_data   = UInt(XLEN.W)
      val src2_data   = UInt(XLEN.W)
    })
    val executeStage = Output(new DecodeUnitExecuteUnit())
    val islsu        = Output(Bool())
    val branch       = Output(Bool())
    val target       = Output(UInt(XLEN.W))
    val executeready = Input(Bool())
    val decodeStall  = Output(Bool()) // 输出给ControlUnit的解码内部stall信号
  })

  // ========== 第一级流水线：MiniBru专用寄存器读取 ==========
  val inst  = io.decodeStage.data.inst
  val pc    = io.decodeStage.data.pc
  val valid = io.decodeStage.data.valid

  // 提取所有可能的寄存器地址
  val rd = inst(4, 0)
  val rj = inst(9, 5)   // rs1
  val rk = inst(14, 10) // rs2

  // 快速解码
  val opcode  = inst(31, 26)
  val offs    = Cat(inst(25, 10), 0.U(2.W))
  val imm_bru = SignedExtend(offs, XLEN)

  // BRU指令识别
  val is_jirl = opcode === "b010011".U
  val is_b    = opcode === "b010100".U
  val is_bl   = opcode === "b010101".U
  val is_beq  = opcode === "b010110".U
  val is_bne  = opcode === "b010111".U
  val is_blt  = opcode === "b011000".U
  val is_bge  = opcode === "b011001".U
  val is_bltu = opcode === "b011010".U
  val is_bgeu = opcode === "b011011".U

  val is_bru = is_jirl || is_b || is_bl || is_beq || is_bne ||
    is_blt || is_bge || is_bltu || is_bgeu

  // 分支比较指令需要rd作为第二个源
  val bru_need_rd = is_beq || is_bne || is_blt || is_bge || is_bltu || is_bgeu

  // ========== 流水线寄存器 ==========
  val stage1_reg = RegInit(0.U.asTypeOf(new Bundle {
    val pc    = UInt(XLEN.W)
    val inst  = UInt(32.W)
    val valid = Bool()
  }))

  // ========== 解码内部冲突检测 ==========
  // 获取第二级的信息
  val stage2_inst  = stage1_reg.inst
  val stage2_valid = stage1_reg.valid

  // 快速解码第二级指令是否会写寄存器
  val stage2_rd     = stage2_inst(4, 0)
  val stage2_opcode = stage2_inst(31, 26)

  val stage2_will_write = true.B

  // 检测冲突：第一级BRU要读的寄存器是否是第二级要写的
  val stage1_needs_rj = is_bru && (is_jirl || bru_need_rd) // BRU需要读rj
  val stage1_needs_rd = is_bru && bru_need_rd              // BRU比较指令需要读rd

  val decode_internal_conflict = valid && stage2_will_write && (
    (stage1_needs_rj && rj === stage2_rd && rj.orR) ||
      (stage1_needs_rd && rd === stage2_rd && rd.orR)
  )

  // 输出stall信号
  io.decodeStall := decode_internal_conflict

  // ========== MiniBRU专用读端口（src1和src2） ==========
  // 只有BRU指令才使用这两个端口
  io.regfile.src1.raddr := Mux(is_bru, rj, 0.U)
  io.regfile.src2.raddr := Mux(is_bru && bru_need_rd, rd, 0.U)

  // 获取寄存器数据（仅用于BRU）
  val bru_src1_raw = io.regfile.src1.rdata
  val bru_src2_raw = io.regfile.src2.rdata

  // 前递处理（仅用于BRU）
  val bru_src1_data = Mux(io.bypassData.src1_bypass && is_bru, io.bypassData.src1_data, bru_src1_raw)
  val bru_src2_data = Mux(io.bypassData.src2_bypass && is_bru && bru_need_rd, io.bypassData.src2_data, bru_src2_raw)

  // ========== MiniBru逻辑（第一级） ==========
  // BRU比较
  val eq  = bru_src1_data === bru_src2_data
  val lt  = bru_src1_data.asSInt < bru_src2_data.asSInt
  val ltu = bru_src1_data < bru_src2_data

  // 目标地址计算
  val pc_plus_imm   = pc + imm_bru
  val src1_plus_imm = bru_src1_data + imm_bru

  // 分支判断
  val takeBranch = is_bru && Mux1H(
    Seq(
      is_beq  -> eq,
      is_bne  -> !eq,
      is_blt  -> lt,
      is_bge  -> !lt,
      is_bltu -> ltu,
      is_bgeu -> !ltu,
      is_b    -> true.B,
      is_bl   -> true.B,
      is_jirl -> true.B
    ))

  val target_bru = Mux(is_jirl, src1_plus_imm, pc_plus_imm)

  io.branch := is_bru && takeBranch && valid
  io.target := target_bru

  // ========== 流水线寄存器更新 ==========
  // 当执行级未准备好或存在解码内部冲突时，保持当前值；否则更新
  when(io.executeready && !decode_internal_conflict) {
    stage1_reg.pc    := pc
    stage1_reg.inst  := inst
    stage1_reg.valid := valid
  }

  // ========== 第二级流水线：完整解码 ==========
  val inst_s2  = stage1_reg.inst
  val pc_s2    = stage1_reg.pc
  val valid_s2 = stage1_reg.valid

  // 完整指令解码
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst_s2, Instructions.DecodeDefault, Instructions.DecodeTable)

  // 提取字段
  val rd_s2  = inst_s2(4, 0)
  val rs1_s2 = inst_s2(9, 5)
  val rs2_s2 = inst_s2(14, 10)

  // 计算立即数
  val imm_field      = inst_s2(21, 10)
  val imm_i_signed   = SignedExtend(imm_field, XLEN)
  val imm_i_unsigned = ZeroExtend(imm_field, XLEN)
  val imm_s          = SignedExtend(imm_field, XLEN)
  val imm_b          = SignedExtend(Cat(inst_s2(25, 10), 0.U(2.W)), XLEN)
  val imm_u          = SignedExtend(Cat(inst_s2(24, 5), 0.U(12.W)), XLEN)
  val imm_j = SignedExtend(
    Cat(Cat(Mux(fuOpType === BRUOpType.jirl, 0.U, inst_s2(9, 0)), inst_s2(25, 10)), 0.U(2.W)),
    XLEN
  )

  // 特殊指令检测
  val is_lui = inst_s2(31, 25) === "b0001010".U

  // 指令类型判断
  val isR = instrType === InstrR
  val isI = instrType === InstrI
  val isU = instrType === InstrU
  val isS = instrType === InstrS
  val isB = instrType === InstrB
  val isJ = instrType === InstrJ
  val isN = instrType === InstrN

  // 选择立即数
  val imm = Mux1H(
    Seq(
      isI -> Mux(inst_s2(24), imm_i_unsigned, imm_i_signed),
      isS -> imm_s,
      isB -> imm_b,
      isU -> imm_u,
      isJ -> imm_j
    ))

  // 生成控制信号
  val reg_waddr = Mux1H(
    Seq(
      isR -> rd_s2,
      isI -> rd_s2,
      isU -> rd_s2,
      isJ -> Mux(fuOpType === BRUOpType.bl, 1.U, rd_s2)
    ))

  val src1_raddr = rs1_s2
  val src2_raddr = Mux(isR, rs2_s2, Mux(isS || isB, rd_s2, 0.U))

  val reg_wen  = (isR || isI || isU || (isJ && fuOpType =/= BRUOpType.b))
  val src1_ren = (isR || isI || isS || isB || isJ)
  val src2_ren = (isR || isS || isB)

  // ========== 其他指令的寄存器读取（src3和src4） ==========
  // 根据指令类型读取寄存器
  io.regfile.src3.raddr := Mux(src1_ren, src1_raddr, 0.U)
  io.regfile.src4.raddr := Mux(src2_ren, src2_raddr, 0.U)

  // 获取寄存器数据
  val other_src1_data = io.regfile.src3.rdata
  val other_src2_data = io.regfile.src4.rdata

  // 构建info
  val info = Wire(new Info())
  info.instr      := Mux(isN, Instructions.NOP, inst_s2)
  info.reg_waddr  := reg_waddr
  info.src1_raddr := src1_raddr
  info.src2_raddr := src2_raddr
  info.op         := fuOpType
  info.reg_wen    := reg_wen && valid_s2 && !isN
  info.src1_ren   := src1_ren
  info.src2_ren   := src2_ren
  info.valid      := valid_s2 && !isN
  info.fusel      := fuType
  info.imm        := imm
  info.diffout    := DontCare

  // 选择正确的源操作数
  val src1_select_reg  = src1_ren
  val src1_select_zero = !src1_ren && is_lui
  val src1_select_pc   = !src1_ren && !is_lui

  val src1_data_final = Mux1H(
    Seq(
      src1_select_reg  -> other_src1_data,
      src1_select_zero -> 0.U,
      src1_select_pc   -> pc_s2
    ))

  val src2_data_final = Mux(src2_ren, other_src2_data, imm)

  // 输出到执行阶段
  io.executeStage.data.pc                 := pc_s2
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := src1_data_final
  io.executeStage.data.src_info.src2_data := src2_data_final

  // 功能单元选择
  io.islsu := fuType === FuType.lsu

  // ========== 调试打印 ==========
  when(decode_internal_conflict) {
    printf("[DecodeUnit] Internal conflict detected!\n")
    printf("  Stage1: inst=0x%x, rj=%d, rd=%d, is_bru=%d\n", inst, rj, rd, is_bru)
    printf("  Stage2: inst=0x%x, rd=%d, will_write=%d\n", stage2_inst, stage2_rd, stage2_will_write)
  }

  when(is_bru && valid) {
    printf("[DecodeUnit] BRU instruction detected:\n")
    printf("  PC: 0x%x, Inst: 0x%x\n", pc, inst)
    printf("  Type: ")
    when(is_jirl) { printf("JIRL") }
    when(is_b) { printf("B") }
    when(is_bl) { printf("BL") }
    when(is_beq) { printf("BEQ") }
    when(is_bne) { printf("BNE") }
    when(is_blt) { printf("BLT") }
    when(is_bge) { printf("BGE") }
    when(is_bltu) { printf("BLTU") }
    when(is_bgeu) { printf("BGEU") }
    printf("\n")
    printf("  rj=%d, rd=%d, rk=%d\n", rj, rd, rk)
    printf("  bru_src1_data=0x%x, bru_src2_data=0x%x\n", bru_src1_data, bru_src2_data)
    printf("  takeBranch=%d, target=0x%x\n", takeBranch, target_bru)
  }
}
