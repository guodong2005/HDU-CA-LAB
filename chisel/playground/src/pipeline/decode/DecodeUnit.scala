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

  // 第一级：并行解码指令类型
  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)

  // 并行提取所有字段
  val rd  = inst(4, 0)
  val rs1 = inst(9, 5)
  val rs2 = inst(14, 10)

  // 特殊指令检测
  val is_lui  = inst(31, 25) === "b0001010".U
  val is_jirl = fuOpType === BRUOpType.jirl
  val is_bl   = fuOpType === BRUOpType.bl
  val is_b    = fuOpType === BRUOpType.b

  // 并行计算所有可能的立即数格式
  val imm_i_signed   = SignedExtend(inst(21, 10), XLEN)
  val imm_i_unsigned = ZeroExtend(inst(21, 10), XLEN)
  val imm_s          = SignedExtend(inst(21, 10), XLEN)
  val imm_b          = SignedExtend(Cat(inst(25, 10), 0.U(2.W)), XLEN)
  val imm_u          = SignedExtend(Cat(inst(24, 5), 0.U(12.W)), XLEN)
  val imm_j = SignedExtend(
    Cat(Cat(Mux(is_jirl, 0.U, inst(9, 0)), inst(25, 10)), 0.U(2.W)),
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
      isI -> Mux(inst(24), imm_i_unsigned, imm_i_signed),
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
      isJ -> Mux(is_bl, 1.U, rd),
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
      isS -> rd, // store指令的rd字段实际是rs2
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
      isJ -> !is_b,
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
  info.instr      := Mux(isN, Instructions.NOP, inst)
  info.reg_waddr  := reg_waddr
  info.src1_raddr := src1_raddr
  info.src2_raddr := src2_raddr
  info.op         := op
  info.reg_wen    := reg_wen
  info.src1_ren   := src1_ren
  info.src2_ren   := src2_ren
  info.valid      := valid && !isN
  info.fusel      := fuType
  info.imm        := imm

  // 寄存器读取端口
  io.regfile.src1.raddr := src1_raddr
  io.regfile.src2.raddr := src2_raddr

  // 并行计算源操作数选择信号
  val src1_select_reg  = src1_ren
  val src1_select_zero = !src1_ren && is_lui
  val src1_select_pc   = !src1_ren && !is_lui

  val src2_select_reg = src2_ren
  val src2_select_imm = !src2_ren

  // 源操作数数据选择（不使用嵌套Mux）
  val src1_data_raw = Mux1H(
    Seq(
      src1_select_reg  -> io.regfile.src1.rdata,
      src1_select_zero -> 0.U,
      src1_select_pc   -> pc
    ))

  val src2_data_raw = Mux1H(
    Seq(
      src2_select_reg -> io.regfile.src2.rdata,
      src2_select_imm -> imm
    ))

  // 前递数据选择（单级Mux）
  val src1_data = Mux(io.bypassData.src1_bypass, io.bypassData.src1_data, src1_data_raw)
  val src2_data = Mux(io.bypassData.src2_bypass, io.bypassData.src2_data, src2_data_raw)

  // 输出到执行阶段
  io.executeStage.data.pc                 := pc
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := src1_data
  io.executeStage.data.src_info.src2_data := src2_data

  // 功能单元选择
  io.islsu := fuType === FuType.lsu

  // MiniBru实例化和连接
  val bru = Module(new MiniBru())
  bru.io.info               := info
  bru.io.pc                 := pc
  bru.io.src_info.src1_data := src1_data
  bru.io.src_info.src2_data := src2_data

  io.target := bru.io.target
  io.branch := bru.io.valid && bru.io.branch
}

// package cpu.pipeline

// import chisel3._
// import chisel3.util._
// import cpu.defines._
// import cpu.defines.Const._

// class DecodeUnit extends Module with HasInstrType {
//   val io = IO(new Bundle {
//     // 输入
//     val decodeStage = Flipped(new FetchUnitDecodeUnit())
//     val regfile     = new Src12Read()

//     // 新增：来自ControlUnit的前递数据
//     val bypassData = Input(new Bundle {
//       val src1_bypass = Bool() // src1是否需要前递
//       val src2_bypass = Bool() // src2是否需要前递
//       val src1_data   = UInt(XLEN.W) // src1前递的数据
//       val src2_data   = UInt(XLEN.W) // src2前递的数据
//     })

//     // 输出
//     val executeStage = Output(new DecodeUnitExecuteUnit())
//     val islsu        = Output(Bool())
//     val branch       = Output(Bool())
//     val target       = Output(UInt(XLEN.W))
//   })

//   val decoder = Module(new Decoder())
//   decoder.io.in.inst := io.decodeStage.data.inst

//   val pc     = io.decodeStage.data.pc
//   val info   = Wire(new Info())
//   val is_lui = decoder.io.out.info.instr(31, 25) === "b0001010".U // is lu12i
//   val inst   = decoder.io.out.info.instr

//   val instrType :: fuType :: fuOpType :: Nil =
//     ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)

//   val imm = LookupTree(
//     instrType,
//     Seq(
//       // inst24 代表 I 指令是否要符号拓展 0 -> s, 1 -> u
//       InstrI -> Mux(inst(24), ZeroExtend(inst(21, 10), XLEN), SignedExtend(inst(21, 10), XLEN)),
//       InstrS -> SignedExtend(inst(21, 10), XLEN),
//       InstrB -> SignedExtend(Cat(inst(25, 10), 0.U(2.W)), XLEN), // 没有压缩指令
//       InstrU -> SignedExtend(Cat(inst(24, 5), 0.U(12.W)), XLEN),
//       InstrJ -> SignedExtend(
//         Cat(Cat(Mux(fuOpType === BRUOpType.jirl, 0.U, inst(9, 0)), inst(25, 10)), 0.U(2.W)),
//         XLEN
//       ) // 没有压缩指令
//     )
//   )

//   info       := decoder.io.out.info
//   info.valid := io.decodeStage.data.valid
//   info.imm   := imm

//   io.regfile.src1.raddr := decoder.io.out.info.src1_raddr
//   io.regfile.src2.raddr := decoder.io.out.info.src2_raddr

//   // ========== 前递逻辑 ==========

//   // 使用ControlUnit提供的前递信号和数据
//   // 重写src1_data的取值逻辑
//   val src1_data_raw   = Mux(info.src1_ren, io.regfile.src1.rdata, Mux(is_lui, 0.U, pc))
//   val src1_data_final = Mux(io.bypassData.src1_bypass, io.bypassData.src1_data, src1_data_raw)

//   // 重写src2_data的取值逻辑
//   val src2_data_raw   = Mux(info.src2_ren, io.regfile.src2.rdata, imm)
//   val src2_data_final = Mux(io.bypassData.src2_bypass, io.bypassData.src2_data, src2_data_raw)

//   // 输出到executeStage
//   io.executeStage.data.pc                 := pc
//   io.executeStage.data.info               := info
//   io.executeStage.data.src_info.src1_data := src1_data_final
//   io.executeStage.data.src_info.src2_data := src2_data_final

//   io.islsu := decoder.io.out.info.fusel === FuType.lsu

//   // BRU也需要使用前递后的数据
//   val bru = Module(new MiniBru())
//   bru.io.info               := info
//   bru.io.pc                 := pc
//   bru.io.src_info.src1_data := src1_data_final // 使用前递后的数据
//   bru.io.src_info.src2_data := src2_data_final // 使用前递后的数据

//   io.target := bru.io.target
//   io.branch := Mux(bru.io.valid, bru.io.branch, false.B)
// }
