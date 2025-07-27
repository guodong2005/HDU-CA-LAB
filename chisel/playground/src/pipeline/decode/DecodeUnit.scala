package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class DecodeUnit extends Module with HasInstrType {
  val io = IO(new Bundle {
    // 输入
    val decodeStage = Flipped(new FetchUnitDecodeUnit())
    val regfile     = new Src12Read()

    // 新增：来自ControlUnit的前递数据
    val bypassData = Input(new Bundle {
      val src1_bypass = Bool() // src1是否需要前递
      val src2_bypass = Bool() // src2是否需要前递
      val src1_data   = UInt(XLEN.W) // src1前递的数据
      val src2_data   = UInt(XLEN.W) // src2前递的数据
    })

    // 输出
    val executeStage = Output(new DecodeUnitExecuteUnit())
    val islsu        = Output(Bool())
    val branch       = Output(Bool())
    val target       = Output(UInt(XLEN.W))
  })

  val decoder = Module(new Decoder())
  decoder.io.in.inst := io.decodeStage.data.inst

  val pc     = io.decodeStage.data.pc
  val info   = Wire(new Info())
  val is_lui = decoder.io.out.info.instr(31, 25) === "b0001010".U // is lu12i
  val inst   = decoder.io.out.info.instr

  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)

  val imm = LookupTree(
    instrType,
    Seq(
      // inst24 代表 I 指令是否要符号拓展 0 -> s, 1 -> u
      InstrI -> Mux(inst(24), ZeroExtend(inst(21, 10), XLEN), SignedExtend(inst(21, 10), XLEN)),
      InstrS -> SignedExtend(inst(21, 10), XLEN),
      InstrB -> SignedExtend(Cat(inst(25, 10), 0.U(2.W)), XLEN), // 没有压缩指令
      InstrU -> SignedExtend(Cat(inst(24, 5), 0.U(12.W)), XLEN),
      InstrJ -> SignedExtend(
        Cat(Cat(Mux(fuOpType === BRUOpType.jirl, 0.U, inst(9, 0)), inst(25, 10)), 0.U(2.W)),
        XLEN
      ) // 没有压缩指令
    )
  )

  info       := decoder.io.out.info
  info.valid := io.decodeStage.data.valid
  info.imm   := imm

  io.regfile.src1.raddr := decoder.io.out.info.src1_raddr
  io.regfile.src2.raddr := decoder.io.out.info.src2_raddr

  // ========== 前递逻辑 ==========

  // 使用ControlUnit提供的前递信号和数据
  // 重写src1_data的取值逻辑
  val src1_data_raw   = Mux(info.src1_ren, io.regfile.src1.rdata, Mux(is_lui, 0.U, pc))
  val src1_data_final = Mux(io.bypassData.src1_bypass, io.bypassData.src1_data, src1_data_raw)

  // 重写src2_data的取值逻辑
  val src2_data_raw   = Mux(info.src2_ren, io.regfile.src2.rdata, imm)
  val src2_data_final = Mux(io.bypassData.src2_bypass, io.bypassData.src2_data, src2_data_raw)

  // 输出到executeStage
  io.executeStage.data.pc                 := pc
  io.executeStage.data.info               := info
  io.executeStage.data.src_info.src1_data := src1_data_final
  io.executeStage.data.src_info.src2_data := src2_data_final

  io.islsu := decoder.io.out.info.fusel === FuType.lsu

  // BRU也需要使用前递后的数据
  val bru = Module(new MiniBru())
  bru.io.info               := info
  bru.io.pc                 := pc
  bru.io.src_info.src1_data := src1_data_final // 使用前递后的数据
  bru.io.src_info.src2_data := src2_data_final // 使用前递后的数据

  io.target := bru.io.target
  io.branch := Mux(bru.io.valid, bru.io.branch, false.B)
}
