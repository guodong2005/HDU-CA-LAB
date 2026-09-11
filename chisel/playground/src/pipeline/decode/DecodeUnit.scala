package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

// 简化后的寄存器读取信息
class DecodeRegisterInfo extends Bundle {
  val src1_raddr = UInt(REG_ADDR_WID.W)
  val src2_raddr = UInt(REG_ADDR_WID.W)
  val src1_ren   = Bool()
  val src2_ren   = Bool()
}

class DecodeUnit extends Module with HasInstrType {
  val io = IO(new Bundle {
    val decodeStage = Flipped(new FetchUnitDecodeUnit())
    val regfile     = new Src12Read() // 改回2个读端口
    val bypassData = Input(new Bundle {
      val src1_bypass = Bool()
      val src2_bypass = Bool()
      val src1_data   = UInt(XLEN.W)
      val src2_data   = UInt(XLEN.W)
    })
    val executeStage = Output(new DecodeUnitExecuteUnit())
    val islsu        = Output(Bool())
    val executeready = Input(Bool())
    val registerInfo = Output(new DecodeRegisterInfo()) // 发送给ControlUnit的寄存器信息
  })

  // 获取输入
  val inst  = io.decodeStage.data.inst
  val pc    = io.decodeStage.data.pc
  val valid = io.decodeStage.data.valid

  // 完整指令解码
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)

  // 提取字段
  // Standard RISC-V register fields.
  val rd  = inst(11, 7)
  val rs1 = inst(19, 15)
  val rs2 = inst(24, 20)

  // 计算立即数
  val imm_i = SignedExtend(inst(31, 20), XLEN)
  val imm_s = SignedExtend(Cat(inst(31, 25), inst(11, 7)), XLEN)
  val imm_b = SignedExtend(Cat(inst(31), inst(7), inst(30, 25), inst(11, 8), 0.U(1.W)), XLEN)
  val imm_u = Cat(inst(31, 12), 0.U(12.W))
  val imm_j = SignedExtend(Cat(inst(31), inst(19, 12), inst(20), inst(30, 21), 0.U(1.W)), XLEN)

  // 特殊指令检测
  val is_lui   = inst(6, 0) === "b0110111".U
  val is_auipc = inst(6, 0) === "b0010111".U

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
      isI -> imm_i,
      isS -> imm_s,
      isB -> imm_b,
      isU -> imm_u,
      isJ -> imm_j
    )
  )

  // 生成控制信号
  val reg_waddr = Mux1H(
    Seq(
      isR -> rd,
      isI -> rd,
      isU -> rd,
      isJ -> rd
    )
  )

  val src1_raddr = rs1
  val src2_raddr = Mux(isR || isB, rs2, Mux(isS, rd, 0.U))

  val reg_wen  = (isR || isI || isU || (isJ && fuOpType =/= BRUOpType.b))
  val src1_ren = (isR || isI || isS || isB || (isJ && fuOpType === BRUOpType.jirl))
  val src2_ren = (isR || isS || isB)

  // 寄存器读取
  io.regfile.src1.raddr := Mux(src1_ren, src1_raddr, 0.U)
  io.regfile.src2.raddr := Mux(src2_ren, src2_raddr, 0.U)

  // 发送寄存器信息给ControlUnit
  io.registerInfo.src1_raddr := src1_raddr
  io.registerInfo.src2_raddr := src2_raddr
  io.registerInfo.src1_ren   := src1_ren
  io.registerInfo.src2_ren   := src2_ren

  // 获取寄存器数据
  val src1_raw = io.regfile.src1.rdata
  val src2_raw = io.regfile.src2.rdata

  // 前递处理
  val src1_data = Mux(io.bypassData.src1_bypass, io.bypassData.src1_data, src1_raw)
  val src2_data = Mux(io.bypassData.src2_bypass, io.bypassData.src2_data, src2_raw)

  // 构建info
  val info = Wire(new Info())
  info.instr      := Mux(isN, Instructions.NOP, inst)
  info.reg_waddr  := reg_waddr
  info.src1_raddr := src1_raddr
  info.src2_raddr := src2_raddr
  info.op         := fuOpType
  info.reg_wen    := reg_wen && valid && !isN
  info.src1_ren   := src1_ren
  info.src2_ren   := src2_ren
  info.valid      := valid && !isN
  info.fusel      := fuType
  info.imm        := imm
  info.cheat      := fuOpType === ALUOpType.xor
  info.diffout    := DontCare

  // 选择正确的源操作数
  val src1_select_reg  = src1_ren
  val src1_select_zero = !src1_ren && is_lui
  val src1_select_pc   = !src1_ren && is_auipc

  val src1_data_final = Mux1H(
    Seq(
      src1_select_reg  -> src1_data,
      src1_select_zero -> 0.U,
      src1_select_pc   -> pc
    )
  )

  val src2_data_final = Mux(src2_ren, src2_data, imm)

  // io.branch := isJ && info.op =/= BRUOpType.jirl;
  // io.target := (pc.asSInt + imm.asSInt).asUInt;
  io.executeStage.data.pc                 := pc
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := src1_data_final
  io.executeStage.data.src_info.src2_data := src2_data_final

  // 功能单元选择
  io.islsu := fuType === FuType.lsu

}
