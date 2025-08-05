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

  // ========== 第一级流水线：MiniBru快速解码 ==========
  val inst  = io.decodeStage.data.inst
  val pc    = io.decodeStage.data.pc
  val valid = io.decodeStage.data.valid
  info.diffout := DontCare

  // 根据图片进行BRU指令的快速解码
  val is_jirl = inst(31, 26) === "b010011".U
  val is_b    = inst(31, 26) === "b010100".U
  val is_bl   = inst(31, 26) === "b010101".U
  val is_beq  = inst(31, 26) === "b010110".U
  val is_bne  = inst(31, 26) === "b010111".U
  val is_blt  = inst(31, 26) === "b011000".U
  val is_bge  = inst(31, 26) === "b011001".U
  val is_bltu = inst(31, 26) === "b011010".U
  val is_bgeu = inst(31, 26) === "b011011".U

  val is_bru = is_jirl || is_b || is_bl || is_beq || is_bne ||
    is_blt || is_bge || is_bltu || is_bgeu

  // 快速提取BRU相关字段
  val rd_bru   = inst(4, 0)
  val rj_bru   = inst(9, 5)
  val offs_bru = Cat(inst(25, 10), 0.U(2.W))

  // BRU指令的操作类型快速解码
  val bru_op = MuxCase(
    0.U,
    Seq(
      is_jirl -> BRUOpType.jirl,
      is_b    -> BRUOpType.b,
      is_bl   -> BRUOpType.bl,
      is_beq  -> BRUOpType.beq,
      is_bne  -> BRUOpType.bne,
      is_blt  -> BRUOpType.blt,
      is_bge  -> BRUOpType.bge,
      is_bltu -> BRUOpType.bltu,
      is_bgeu -> BRUOpType.bgeu
    )
  )

  // 快速生成BRU的Info（只包含BRU需要的信息）
  val bru_info = Wire(new Info())
  bru_info.instr := inst
  bru_info.op    := bru_op
  bru_info.fusel := FuType.bru
  bru_info.valid := valid && is_bru

  // BRU相关的寄存器地址（用于前递判断）
  val bru_src1_addr = rj_bru
  val bru_src2_addr = Mux(is_jirl || is_b || is_bl, 0.U, rd_bru)

  // 从寄存器文件读取BRU源操作数
  io.regfile.src1.raddr := bru_src1_addr
  io.regfile.src2.raddr := bru_src2_addr

  // BRU源操作数选择（考虑前递）
  val bru_src1_data = Mux(io.bypassData.src1_bypass && is_bru, io.bypassData.src1_data, io.regfile.src1.rdata)

  val bru_src2_data = Mux(io.bypassData.src2_bypass && is_bru && bru_src2_addr =/= 0.U, io.bypassData.src2_data, io.regfile.src2.rdata)

  // BRU立即数计算
  val bru_imm = SignedExtend(offs_bru, XLEN)

  // MiniBru实例化（第一级）
  val minibru = Module(new MiniBru())
  minibru.io.info               := bru_info
  minibru.io.pc                 := pc
  minibru.io.src_info.src1_data := bru_src1_data
  minibru.io.src_info.src2_data := bru_src2_data

  // 第一级输出（立即输出给IFU）
  io.branch := minibru.io.valid && minibru.io.branch
  io.target := minibru.io.target

  // ========== 流水线寄存器 ==========
  val stage1_reg = RegInit(0.U.asTypeOf(new Bundle {
    val pc    = UInt(XLEN.W)
    val inst  = UInt(32.W)
    val valid = Bool()
  }))

  stage1_reg.pc    := pc
  stage1_reg.inst  := inst
  stage1_reg.valid := valid

  // ========== 第二级流水线：普通解码 ==========
  val inst_s2  = stage1_reg.inst
  val pc_s2    = stage1_reg.pc
  val valid_s2 = stage1_reg.valid

  // 完整的指令解码
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst_s2, Instructions.DecodeDefault, Instructions.DecodeTable)

  // 并行提取所有字段
  val rd  = inst_s2(4, 0)
  val rs1 = inst_s2(9, 5)
  val rs2 = inst_s2(14, 10)

  // 特殊指令检测
  val is_lui     = inst_s2(31, 25) === "b0001010".U
  val is_jirl_s2 = fuOpType === BRUOpType.jirl
  val is_bl_s2   = fuOpType === BRUOpType.bl
  val is_b_s2    = fuOpType === BRUOpType.b

  // 并行计算所有可能的立即数格式
  val imm_i_signed   = SignedExtend(inst_s2(21, 10), XLEN)
  val imm_i_unsigned = ZeroExtend(inst_s2(21, 10), XLEN)
  val imm_s          = SignedExtend(inst_s2(21, 10), XLEN)
  val imm_b          = SignedExtend(Cat(inst_s2(25, 10), 0.U(2.W)), XLEN)
  val imm_u          = SignedExtend(Cat(inst_s2(24, 5), 0.U(12.W)), XLEN)
  val imm_j = SignedExtend(
    Cat(Cat(Mux(is_jirl_s2, 0.U, inst_s2(9, 0)), inst_s2(25, 10)), 0.U(2.W)),
    XLEN
  )

  // 创建指令类型的one-hot向量
  val isR = instrType === InstrR
  val isI = instrType === InstrI
  val isU = instrType === InstrU
  val isS = instrType === InstrS
  val isB = instrType === InstrB
  val isJ = instrType === InstrJ
  val isN = instrType === InstrN

  // 使用Mux1H并行选择各个字段
  val imm = Mux1H(
    Seq(
      isI -> Mux(inst_s2(24), imm_i_unsigned, imm_i_signed),
      isS -> imm_s,
      isB -> imm_b,
      isU -> imm_u,
      isJ -> imm_j
    ))

  // 并行生成控制信号
  val reg_waddr = Mux1H(
    Seq(
      isR -> rd,
      isI -> rd,
      isU -> rd,
      isS -> 0.U,
      isB -> 0.U,
      isJ -> Mux(is_bl_s2, 1.U, rd),
      isN -> 0.U
    ))

  val src1_raddr = Mux1H(
    Seq(
      isR -> rs1,
      isI -> rs1,
      isU -> 0.U,
      isS -> rs1,
      isB -> rs1,
      isJ -> rs1,
      isN -> 0.U
    ))

  val src2_raddr = Mux1H(
    Seq(
      isR -> rs2,
      isI -> 0.U,
      isU -> 0.U,
      isS -> rd,
      isB -> rd,
      isJ -> 0.U,
      isN -> 0.U
    ))

  val op = Mux1H(
    Seq(
      isR -> fuOpType,
      isI -> fuOpType,
      isU -> ALUOpType.add,
      isS -> fuOpType,
      isB -> fuOpType,
      isJ -> fuOpType,
      isN -> 0.U
    ))

  val reg_wen = Mux1H(
    Seq(
      isR -> true.B,
      isI -> true.B,
      isU -> true.B,
      isS -> false.B,
      isB -> false.B,
      isJ -> !is_b_s2,
      isN -> false.B
    ))

  val src1_ren = Mux1H(
    Seq(
      isR -> true.B,
      isI -> true.B,
      isU -> false.B,
      isS -> true.B,
      isB -> true.B,
      isJ -> true.B,
      isN -> false.B
    ))

  val src2_ren = Mux1H(
    Seq(
      isR -> true.B,
      isI -> false.B,
      isU -> false.B,
      isS -> true.B,
      isB -> true.B,
      isJ -> false.B,
      isN -> false.B
    ))

  // 构建info bundle
  val info = Wire(new Info())
  info.instr      := Mux(isN, Instructions.NOP, inst_s2)
  info.reg_waddr  := reg_waddr
  info.src1_raddr := src1_raddr
  info.src2_raddr := src2_raddr
  info.op         := op
  info.reg_wen    := reg_wen
  info.src1_ren   := src1_ren
  info.src2_ren   := src2_ren
  info.valid      := valid_s2 && !isN
  info.fusel      := fuType
  info.imm        := imm
  info.diffout    := DontCare

  // 第二级需要重新读取寄存器（如果不是BRU指令）
  when(!isB && !isJ) {
    io.regfile.src1.raddr := src1_raddr
    io.regfile.src2.raddr := src2_raddr
  }

  // 并行计算源操作数选择信号
  val src1_select_reg  = src1_ren
  val src1_select_zero = !src1_ren && is_lui
  val src1_select_pc   = !src1_ren && !is_lui

  val src2_select_reg = src2_ren
  val src2_select_imm = !src2_ren

  // 源操作数数据选择
  val src1_data_raw = Mux1H(
    Seq(
      src1_select_reg  -> io.regfile.src1.rdata,
      src1_select_zero -> 0.U,
      src1_select_pc   -> pc_s2
    ))

  val src2_data_raw = Mux1H(
    Seq(
      src2_select_reg -> io.regfile.src2.rdata,
      src2_select_imm -> imm
    ))

  // 前递数据选择（第二级也需要考虑前递）
  val src1_data = Mux(io.bypassData.src1_bypass && src1_ren, io.bypassData.src1_data, src1_data_raw)
  val src2_data = Mux(io.bypassData.src2_bypass && src2_ren, io.bypassData.src2_data, src2_data_raw)

  // 输出到执行阶段
  io.executeStage.data.pc                 := pc_s2
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := src1_data
  io.executeStage.data.src_info.src2_data := src2_data

  // 功能单元选择
  io.islsu := fuType === FuType.lsu
}
