package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class DecodeUnit extends Module with HasInstrType {
  val io = IO(new Bundle {
    val decodeStage = Flipped(new FetchUnitDecodeUnit())
    val regfile     = new Src12Read()
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
  })

  // ========== 第一级流水线：MiniBru快速解码和执行 ==========
  val inst  = io.decodeStage.data.inst
  val pc    = io.decodeStage.data.pc
  val valid = io.decodeStage.data.valid

  // 并行提取所有可能用到的字段
  val opcode  = inst(31, 26)
  val rd      = inst(4, 0)
  val rj      = inst(9, 5)
  val offs    = Cat(inst(25, 10), 0.U(2.W))
  val imm_bru = SignedExtend(offs, XLEN)

  // 并行解码所有BRU指令类型（one-hot编码）
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

  // 并行计算所有BRU相关的寄存器地址
  val bru_use_rj = is_bru
  val bru_use_rd = (is_beq || is_bne || is_blt || is_bge || is_bltu || is_bgeu)

  // 寄存器读取地址（考虑BRU优先级）
  io.regfile.src1.raddr := rj // BRU总是使用rj
  io.regfile.src2.raddr := rd // BRU的比较指令使用rd

  // 并行获取源操作数（考虑前递）
  val src1_raw = io.regfile.src1.rdata
  val src2_raw = io.regfile.src2.rdata

  val src1_data = Mux(io.bypassData.src1_bypass && bru_use_rj, io.bypassData.src1_data, src1_raw)

  val src2_data = Mux(io.bypassData.src2_bypass && bru_use_rd, io.bypassData.src2_data, src2_raw)

  // ========== MiniBru逻辑（集成在第一级） ==========
  // 并行计算所有比较结果
  val eq  = src1_data === src2_data
  val lt  = src1_data.asSInt < src2_data.asSInt
  val ltu = src1_data < src2_data

  // 并行计算所有可能的目标地址
  val pc_plus_imm   = pc + imm_bru
  val src1_plus_imm = src1_data + imm_bru

  // 并行判断是否跳转（使用one-hot选择）
  val takeBranch = Mux1H(
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

  // 并行选择目标地址
  val target_bru = Mux(is_jirl, src1_plus_imm, pc_plus_imm)

  // 第一级输出（立即输出给IFU）
  io.branch := is_bru && takeBranch && valid
  io.target := target_bru
  // ========== 调试打印 ==========
  when(is_bru && valid) {
    printf("[DecodeUnit] BRU instruction detected:\n")
    printf("  PC: 0x%x\n", pc)
    printf("  Inst: 0x%x\n", inst)
    printf("  Opcode: 0x%x\n", opcode)
    printf("  Instruction type: ")
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
    printf("  rj: %d, rd: %d\n", rj, rd)
    printf("  offs: 0x%x, imm_bru: 0x%x\n", offs, imm_bru)
    printf("  src1_raw: 0x%x, src2_raw: 0x%x\n", src1_raw, src2_raw)
    printf("  src1_data: 0x%x, src2_data: 0x%x\n", src1_data, src2_data)
    printf("  Bypass: src1_bypass=%d, src2_bypass=%d\n", io.bypassData.src1_bypass, io.bypassData.src2_bypass)
    printf("  pc_plus_imm: 0x%x\n", pc_plus_imm)
    printf("  src1_plus_imm: 0x%x\n", src1_plus_imm)
    printf("  takeBranch: %d\n", takeBranch)
    printf("  target_bru: 0x%x\n", target_bru)
    printf("  io.branch: %d, io.target: 0x%x\n", io.branch, io.target)

    // 特别关注JIRL指令
    when(is_jirl) {
      printf("  [JIRL Debug] src1_data=0x%x + imm_bru=0x%x = 0x%x\n", src1_data, imm_bru, src1_plus_imm)
    }
  }

  // 当branch信号为高时的额外调试
  when(io.branch) {
    printf("[DecodeUnit] Branch taken! Target: 0x%x\n", io.target)
  }
  // ========== 流水线寄存器 ==========
  val stage1_reg = RegInit(0.U.asTypeOf(new Bundle {
    val pc    = UInt(XLEN.W)
    val inst  = UInt(32.W)
    val valid = Bool()
  }))

  stage1_reg.pc    := pc
  stage1_reg.inst  := inst
  stage1_reg.valid := valid

  // ========== 第二级流水线：完整解码 ==========
  val inst_s2  = stage1_reg.inst
  val pc_s2    = stage1_reg.pc
  val valid_s2 = stage1_reg.valid

  // 并行进行完整的指令解码
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst_s2, Instructions.DecodeDefault, Instructions.DecodeTable)

  // 并行提取第二级需要的所有字段
  val rd_s2  = inst_s2(4, 0)
  val rs1_s2 = inst_s2(9, 5)
  val rs2_s2 = inst_s2(14, 10)

  // 并行计算所有立即数格式
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

  // 指令类型one-hot向量
  val isR = instrType === InstrR
  val isI = instrType === InstrI
  val isU = instrType === InstrU
  val isS = instrType === InstrS
  val isB = instrType === InstrB
  val isJ = instrType === InstrJ
  val isN = instrType === InstrN

  // 并行生成所有控制信号
  val imm = Mux1H(
    Seq(
      isI -> Mux(inst_s2(24), imm_i_unsigned, imm_i_signed),
      isS -> imm_s,
      isB -> imm_b,
      isU -> imm_u,
      isJ -> imm_j
    ))

  val reg_waddr = Mux1H(
    Seq(
      isR -> rd_s2,
      isI -> rd_s2,
      isU -> rd_s2,
      isJ -> Mux(fuOpType === BRUOpType.bl, 1.U, rd_s2)
    ))

  val src1_raddr = Mux1H(
    Seq(
      isR -> rs1_s2,
      isI -> rs1_s2,
      isS -> rs1_s2,
      isB -> rs1_s2,
      isJ -> rs1_s2
    ))

  val src2_raddr = Mux1H(
    Seq(
      isR -> rs2_s2,
      isS -> rd_s2,
      isB -> rd_s2
    ))

  val reg_wen  = (isR || isI || isU || (isJ && fuOpType =/= BRUOpType.b))
  val src1_ren = (isR || isI || isS || isB || isJ)
  val src2_ren = (isR || isS || isB)

  // 构建info bundle
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

  // 第二级寄存器读取（如果不是BRU指令）
  when(!isB && !isJ) {
    io.regfile.src1.raddr := src1_raddr
    io.regfile.src2.raddr := src2_raddr
  }

  // 并行计算源操作数
  val src1_select_reg  = src1_ren
  val src1_select_zero = !src1_ren && is_lui
  val src1_select_pc   = !src1_ren && !is_lui

  val src1_data_raw = Mux1H(
    Seq(
      src1_select_reg  -> io.regfile.src1.rdata,
      src1_select_zero -> 0.U,
      src1_select_pc   -> pc_s2
    ))

  val src2_data_raw = Mux(src2_ren, io.regfile.src2.rdata, imm)

  // 前递选择
  val need_src1_forward = src1_ren && io.bypassData.src1_bypass
  val need_src2_forward = src2_ren && io.bypassData.src2_bypass

  val src1_data_s2 = Mux(need_src1_forward, io.bypassData.src1_data, src1_data_raw)
  val src2_data_s2 = Mux(need_src2_forward, io.bypassData.src2_data, src2_data_raw)

  // 输出到执行阶段
  io.executeStage.data.pc                 := pc_s2
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := src1_data_s2
  io.executeStage.data.src_info.src2_data := src2_data_s2

  // 功能单元选择
  io.islsu := fuType === FuType.lsu
}
