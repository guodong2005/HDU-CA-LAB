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

  val inst  = io.decodeStage.data.inst
  val pc    = io.decodeStage.data.pc
  val valid = io.decodeStage.data.valid

  // ========== LoongArch32 指令格式解析 ==========
  // LoongArch32 寄存器字段位置
  val rd = inst(4, 0)   // 目标寄存器
  val rj = inst(9, 5)   // 源寄存器1
  val rk = inst(14, 10) // 源寄存器2

  // 快速解码：基于高位快速判断指令类型
  val op_31_26 = inst(31, 26)
  val op_31_22 = inst(31, 22)
  val op_31_20 = inst(31, 20)
  val op_31_15 = inst(31, 15)

  // ========== 优化1：并行判断指令类型 ==========
  // ALU 立即数指令 (I型)
  val isALU_I = (op_31_22 === "b0000001000".U) || // SLTI
    (op_31_22 === "b0000001001".U) || // SLTUI
    (op_31_22 === "b0000001010".U) || // ADDI_W
    (op_31_22 === "b0000001101".U) || // ANDI
    (op_31_22 === "b0000001110".U) || // ORI
    (op_31_22 === "b0000001111".U)    // XORI

  // ALU 移位立即数指令
  val isShift_I = (op_31_15 === "b00000000010000001".U) || // SLLI_W
    (op_31_15 === "b00000000010001001".U) || // SRLI_W
    (op_31_15 === "b00000000010010001".U)    // SRAI_W

  // ALU 寄存器指令 (R型)
  val isALU_R = (op_31_15 === "b00000000000100100".U) || // SLT
    (op_31_15 === "b00000000000101000".U) || // NOR
    (op_31_15 === "b00000000000100101".U) || // SLTU
    (op_31_15 === "b00000000000100000".U) || // ADD_W
    (op_31_15 === "b00000000000100010".U) || // SUB_W
    (op_31_15 === "b00000000000101001".U) || // AND
    (op_31_15 === "b00000000000101010".U) || // OR
    (op_31_15 === "b00000000000101011".U) || // XOR
    (op_31_15 === "b00000000000101110".U) || // SLL_W
    (op_31_15 === "b00000000000101111".U) || // SRL_W
    (op_31_15 === "b00000000000110000".U) || // SRA_W
    (op_31_15 === "b00000000000111000".U)    // MUL_W

  // Load/Store 指令
  val isLoad = (op_31_22 === "b0010100000".U) || // LB
    (op_31_22 === "b0010101000".U) || // LBU
    (op_31_22 === "b0010100001".U) || // LH
    (op_31_22 === "b0010101001".U) || // LHU
    (op_31_22 === "b0010100010".U)    // LW

  val isStore = (op_31_22 === "b0010100100".U) || // SB
    (op_31_22 === "b0010100101".U) || // SH
    (op_31_22 === "b0010100110".U)    // SW

  // 分支指令
  val isBranch_cond = (op_31_26 === "b010110".U) || // BEQ
    (op_31_26 === "b010111".U) || // BNE
    (op_31_26 === "b011000".U) || // BLT
    (op_31_26 === "b011001".U) || // BGE
    (op_31_26 === "b011010".U) || // BLTU
    (op_31_26 === "b011011".U)    // BGEU

  val isBranch_uncond = (op_31_26 === "b010100".U) || // B
    (op_31_26 === "b010101".U) // BL

  val isJIRL = op_31_26 === "b010011".U // JIRL

  // U型指令
  val isLU12I     = op_31_26 === "b0001010".U // LU12I_W
  val isPCADDU12I = op_31_26 === "b0001110".U // PCADDU12I

  // ========== 优化2：指令类型归类 ==========
  val isI = isALU_I || isShift_I || isLoad
  val isR = isALU_R
  val isS = isStore
  val isB = isBranch_cond
  val isJ = isBranch_uncond || isJIRL
  val isU = isLU12I || isPCADDU12I

  // ========== 优化3：并行计算立即数 ==========
  // LoongArch32 立即数格式
  val si12   = inst(21, 10)                  // 12位有符号立即数
  val ui12   = inst(21, 10)                  // 12位无符号立即数
  val si14   = inst(23, 10)                  // 14位有符号立即数（移位量）
  val si16   = inst(25, 10)                  // 16位有符号立即数（分支偏移）
  val si20   = inst(24, 5)                   // 20位有符号立即数（高位）
  val offs26 = Cat(inst(9, 0), inst(25, 10)) // 26位偏移（B/BL）

  // 立即数扩展
  val imm_si12          = SignedExtend(si12, XLEN)
  val imm_ui12          = ZeroExtend(ui12, XLEN)
  val imm_si14_shift2   = SignedExtend(Cat(si14, 0.U(2.W)), XLEN)
  val imm_si16_shift2   = SignedExtend(Cat(si16, 0.U(2.W)), XLEN)
  val imm_si20_shift12  = SignedExtend(Cat(si20, 0.U(12.W)), XLEN)
  val imm_offs26_shift2 = SignedExtend(Cat(offs26, 0.U(2.W)), XLEN)

  // 根据指令类型选择立即数
  val imm = Mux1H(
    Seq(
      isALU_I         -> imm_si12,
      isShift_I       -> ZeroExtend(inst(14, 10), XLEN), // 移位量
      isLoad          -> imm_si12,
      isStore         -> imm_si12,
      isBranch_cond   -> imm_si16_shift2,
      isBranch_uncond -> imm_offs26_shift2,
      isJIRL          -> imm_si16_shift2,
      isU             -> imm_si20_shift12
    ))

  // ========== 优化4：功能单元和操作类型 ==========
  val fuType = Mux1H(
    Seq(
      (isR || isI || isU) -> FuType.alu,
      (isLoad || isStore) -> FuType.lsu,
      (isB || isJ)        -> FuType.bru
    ))

  // 简化的操作类型（使用部分解码）
  val aluOpType = MuxCase(
    ALUOpType.add,
    Seq(
      (op_31_22 === "b0000001000".U)        -> ALUOpType.slt,  // SLTI
      (op_31_22 === "b0000001001".U)        -> ALUOpType.sltu, // SLTUI
      (op_31_22 === "b0000001010".U)        -> ALUOpType.add,  // ADDI_W
      (op_31_22 === "b0000001101".U)        -> ALUOpType.and,  // ANDI
      (op_31_22 === "b0000001110".U)        -> ALUOpType.or,   // ORI
      (op_31_22 === "b0000001111".U)        -> ALUOpType.xor,  // XORI
      (op_31_15 === "b00000000010000001".U) -> ALUOpType.sll,  // SLLI_W
      (op_31_15 === "b00000000010001001".U) -> ALUOpType.srl,  // SRLI_W
      (op_31_15 === "b00000000010010001".U) -> ALUOpType.sra,  // SRAI_W
      // R型指令
      (op_31_15 === "b00000000000100000".U) -> ALUOpType.add, // ADD_W
      (op_31_15 === "b00000000000100010".U) -> ALUOpType.sub, // SUB_W
      (op_31_15 === "b00000000000101001".U) -> ALUOpType.and, // AND
      (op_31_15 === "b00000000000101010".U) -> ALUOpType.or,  // OR
      (op_31_15 === "b00000000000101011".U) -> ALUOpType.xor, // XOR
      // U型指令
      isU -> ALUOpType.add
    )
  )

  val lsuOpType = Mux(isLoad, LSUOpType.ld, LSUOpType.st)

  val bruOpType = MuxCase(
    BRUOpType.b,
    Seq(
      (op_31_26 === "b010110".U) -> BRUOpType.beq,
      (op_31_26 === "b010111".U) -> BRUOpType.bne,
      (op_31_26 === "b011000".U) -> BRUOpType.blt,
      (op_31_26 === "b011001".U) -> BRUOpType.bge,
      (op_31_26 === "b011010".U) -> BRUOpType.bltu,
      (op_31_26 === "b011011".U) -> BRUOpType.bgeu,
      (op_31_26 === "b010100".U) -> BRUOpType.b,
      (op_31_26 === "b010101".U) -> BRUOpType.bl,
      (op_31_26 === "b010011".U) -> BRUOpType.jirl
    )
  )

  val fuOpType = Mux1H(
    Seq(
      (fuType === FuType.alu) -> aluOpType,
      (fuType === FuType.lsu) -> lsuOpType,
      (fuType === FuType.bru) -> bruOpType
    ))

  // ========== 优化5：控制信号生成 ==========
  // 寄存器地址选择
  val reg_waddr = Mux1H(
    Seq(
      (isR || isI || isLoad || isJIRL)           -> rd,
      (op_31_26 === "b010101".U)                 -> 1.U, // BL写$ra
      (isU)                                      -> rd,
      (isS || isB || (op_31_26 === "b010100".U)) -> 0.U  // Store/Branch/B不写寄存器
    ))

  val src1_raddr = Mux(isU, 0.U, rj) // U型指令不读rj
  val src2_raddr = Mux1H(
    Seq(
      isR                           -> rk,
      (isS || isB)                  -> rd, // Store和Branch的rd实际是rk
      (isI || isU || isJ || isLoad) -> 0.U
    ))

  val reg_wen  = !isS && !isB && !(op_31_26 === "b010100".U) && valid // B指令不写寄存器
  val src1_ren = !isU && valid
  val src2_ren = (isR || isS || isB) && valid

  // ========== 构建Info ==========
  val info = Wire(new Info())
  info.instr      := inst
  info.reg_waddr  := reg_waddr
  info.src1_raddr := src1_raddr
  info.src2_raddr := src2_raddr
  info.op         := fuOpType
  info.reg_wen    := reg_wen
  info.src1_ren   := src1_ren
  info.src2_ren   := src2_ren
  info.valid      := valid
  info.fusel      := fuType
  info.imm        := imm

  // ========== 寄存器读取 ==========
  io.regfile.src1.raddr := src1_raddr
  io.regfile.src2.raddr := src2_raddr

  // ========== 源操作数选择 ==========
  val src1_data_raw = Mux(
    src1_ren,
    io.regfile.src1.rdata,
    Mux(isLU12I, 0.U, pc) // LU12I使用0，PCADDU12I使用PC
  )

  val src2_data_raw = Mux(src2_ren, io.regfile.src2.rdata, imm)

  // 前递选择
  val src1_data = Mux(io.bypassData.src1_bypass, io.bypassData.src1_data, src1_data_raw)
  val src2_data = Mux(io.bypassData.src2_bypass, io.bypassData.src2_data, src2_data_raw)

  // ========== 输出 ==========
  io.executeStage.data.pc                 := pc
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := src1_data
  io.executeStage.data.src_info.src2_data := src2_data
  io.islsu                                := fuType === FuType.lsu

  // MiniBru
  val bru = Module(new MiniBru())
  bru.io.info               := info
  bru.io.pc                 := pc
  bru.io.src_info.src1_data := src1_data
  bru.io.src_info.src2_data := src2_data

  io.target := bru.io.target
  io.branch := bru.io.valid && bru.io.branch
}
