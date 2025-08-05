package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class Fu extends Module with HasInstrType {
  val io = IO(new Bundle {
    val data = new Bundle {
      val pc       = Input(UInt(XLEN.W))
      val info     = Input(new Info())
      val src_info = Input(new SrcInfo())
      val rd_info  = Output(new RdInfo())
      val diffout  = Output(new DiffOut())
      val ready    = Output(Bool())
      val valid    = Output(Bool())
    }
    val dcache = new Bundle {
      val req  = Decoupled(new DCacheReq)
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  // 功能单元
  val alu = Module(new Alu())
  val mdu = Module(new Mdu())
  val lsu = Module(new Lsu())
  val bru = Module(new Bru())

  // LSU 和 DCache 连接
  lsu.io.dcache <> io.dcache

  // ========== 优化1: 提前解码，使用独热编码 ==========
  val isAlu = io.data.info.fusel === FuType.alu
  val isMdu = io.data.info.fusel === FuType.mdu
  val isLsu = io.data.info.fusel === FuType.lsu
  val isBru = io.data.info.fusel === FuType.bru

  // 寄存器化的功能单元选择（独热编码）
  val fuselOneHotReg = RegInit(VecInit(Seq.fill(4)(false.B)))
  when(io.data.info.valid) {
    fuselOneHotReg := VecInit(isAlu, isMdu, isLsu, isBru)
  }

  // 当前周期使用的选择信号
  val useAlu = Mux(io.data.info.valid, isAlu, fuselOneHotReg(0))
  val useMdu = Mux(io.data.info.valid, isMdu, fuselOneHotReg(1))
  val useLsu = Mux(io.data.info.valid, isLsu, fuselOneHotReg(2))
  val useBru = Mux(io.data.info.valid, isBru, fuselOneHotReg(3))

  // ========== 优化2: 条件化的信息传递（节省功耗） ==========
  alu.io.info     := io.data.info
  alu.io.src_info := io.data.src_info

  mdu.io.info     := io.data.info
  mdu.io.src_info := io.data.src_info

  lsu.io.info     := io.data.info
  lsu.io.src_info := io.data.src_info

  bru.io.info     := io.data.info
  bru.io.src_info := io.data.src_info
  bru.io.pc       := io.data.pc

  // ========== 优化3: 并行化的结果选择 ==========
  // 使用独热编码直接选择，避免LookupTree的串行比较
  val results = Wire(Vec(4, UInt(XLEN.W)))
  results(0) := alu.io.result
  results(1) := mdu.io.result
  results(2) := lsu.io.result
  results(3) := bru.io.result

  val valids = Wire(Vec(4, Bool()))
  valids(0) := alu.io.valid
  valids(1) := mdu.io.valid
  valids(2) := lsu.io.valid
  valids(3) := bru.io.valid

  val readys = Wire(Vec(4, Bool()))
  readys(0) := true.B // ALU always ready
  readys(1) := mdu.io.ready
  readys(2) := lsu.io.ready
  readys(3) := true.B // BRU always ready

  // 使用独热编码进行选择（更快的并行选择）
  val selVec = VecInit(useAlu, useMdu, useLsu, useBru)
  val result = Mux1H(selVec, results)
  val valid  = Mux1H(selVec, valids)
  val ready  = Mux1H(selVec, readys)

  // ========== 优化4: 流水线寄存器（可选） ==========
  // 如果时序仍然紧张，可以在这里添加流水线寄存器
  // val resultReg = RegNext(result)
  // val validReg = RegNext(valid && io.data.info.valid)

  // 输出赋值
  io.data.rd_info.wdata := result
  io.data.diffout       := lsu.io.diffout
  io.data.valid         := valid && io.data.info.valid
  io.data.ready         := ready
}

// ========== 优化5: 预计算优化版本 ==========
class FuOptimizedPrecompute extends Module with HasInstrType {
  val io = IO(new Bundle {
    val data = new Bundle {
      val pc       = Input(UInt(XLEN.W))
      val info     = Input(new Info())
      val src_info = Input(new SrcInfo())
      val rd_info  = Output(new RdInfo())
      val diffout  = Output(new DiffOut())
      val ready    = Output(Bool())
      val valid    = Output(Bool())
    }
    val dcache = new Bundle {
      val req  = Decoupled(new DCacheReq)
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  // 功能单元
  val alu = Module(new Alu())
  val mdu = Module(new Mdu())
  val lsu = Module(new Lsu())
  val bru = Module(new Bru())

  // LSU 和 DCache 连接
  lsu.io.dcache <> io.dcache

  // 预计算所有功能单元的输入
  alu.io.info     := io.data.info
  alu.io.src_info := io.data.src_info

  mdu.io.info     := io.data.info
  mdu.io.src_info := io.data.src_info

  lsu.io.info     := io.data.info
  lsu.io.src_info := io.data.src_info

  bru.io.info     := io.data.info
  bru.io.src_info := io.data.src_info
  bru.io.pc       := io.data.pc

  // 使用寄存器缓存fusel以减少选择逻辑
  val fuselReg = RegEnable(io.data.info.fusel, io.data.info.valid)
  val fusel    = Mux(io.data.info.valid, io.data.info.fusel, fuselReg)

  // 预计算所有可能的输出
  val aluOutput = Wire(new Bundle {
    val result = UInt(XLEN.W)
    val valid  = Bool()
    val ready  = Bool()
  })
  aluOutput.result := alu.io.result
  aluOutput.valid  := alu.io.valid
  aluOutput.ready  := true.B

  val mduOutput = Wire(new Bundle {
    val result = UInt(XLEN.W)
    val valid  = Bool()
    val ready  = Bool()
  })
  mduOutput.result := mdu.io.result
  mduOutput.valid  := mdu.io.valid
  mduOutput.ready  := mdu.io.ready

  val lsuOutput = Wire(new Bundle {
    val result = UInt(XLEN.W)
    val valid  = Bool()
    val ready  = Bool()
  })
  lsuOutput.result := lsu.io.result
  lsuOutput.valid  := lsu.io.valid
  lsuOutput.ready  := lsu.io.ready

  val bruOutput = Wire(new Bundle {
    val result = UInt(XLEN.W)
    val valid  = Bool()
    val ready  = Bool()
  })
  bruOutput.result := bru.io.result
  bruOutput.valid  := bru.io.valid
  bruOutput.ready  := true.B

  // 使用简化的选择逻辑
  val output = MuxLookup(fusel, aluOutput)(
    Seq(
      FuType.alu -> aluOutput,
      FuType.mdu -> mduOutput,
      FuType.lsu -> lsuOutput,
      FuType.bru -> bruOutput
    ))

  // 输出赋值
  io.data.rd_info.wdata := output.result
  io.data.diffout       := lsu.io.diffout
  io.data.valid         := output.valid && io.data.info.valid
  io.data.ready         := output.ready
}

// ========== 优化6: 完全并行化版本（面积换速度） ==========
class FuFullyParallel extends Module with HasInstrType {
  val io = IO(new Bundle {
    val data = new Bundle {
      val pc       = Input(UInt(XLEN.W))
      val info     = Input(new Info())
      val src_info = Input(new SrcInfo())
      val rd_info  = Output(new RdInfo())
      val diffout  = Output(new DiffOut())
      val ready    = Output(Bool())
      val valid    = Output(Bool())
    }
    val dcache = new Bundle {
      val req  = Decoupled(new DCacheReq)
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  // 功能单元
  val alu = Module(new Alu())
  val mdu = Module(new Mdu())
  val lsu = Module(new Lsu())
  val bru = Module(new Bru())

  lsu.io.dcache <> io.dcache

  // 并行计算所有功能单元
  alu.io.info     := io.data.info
  alu.io.src_info := io.data.src_info

  mdu.io.info     := io.data.info
  mdu.io.src_info := io.data.src_info

  lsu.io.info     := io.data.info
  lsu.io.src_info := io.data.src_info

  bru.io.info     := io.data.info
  bru.io.src_info := io.data.src_info
  bru.io.pc       := io.data.pc

  // 提前一个周期预测fusel（激进优化）
  val fuselPredict     = RegNext(io.data.info.fusel)
  val isPredictCorrect = fuselPredict === io.data.info.fusel

  // 使用预测值进行早期选择
  val earlyResult = MuxCase(
    0.U,
    Seq(
      (fuselPredict === FuType.alu) -> alu.io.result,
      (fuselPredict === FuType.mdu) -> mdu.io.result,
      (fuselPredict === FuType.lsu) -> lsu.io.result,
      (fuselPredict === FuType.bru) -> bru.io.result
    )
  )

  // 正常路径选择
  val normalResult = MuxCase(
    0.U,
    Seq(
      (io.data.info.fusel === FuType.alu) -> alu.io.result,
      (io.data.info.fusel === FuType.mdu) -> mdu.io.result,
      (io.data.info.fusel === FuType.lsu) -> lsu.io.result,
      (io.data.info.fusel === FuType.bru) -> bru.io.result
    )
  )

  // 选择预测或正常结果
  val result = Mux(isPredictCorrect && io.data.info.valid, earlyResult, normalResult)

  // Valid和Ready信号的快速选择
  val valid = MuxCase(
    false.B,
    Seq(
      (io.data.info.fusel === FuType.alu) -> alu.io.valid,
      (io.data.info.fusel === FuType.mdu) -> mdu.io.valid,
      (io.data.info.fusel === FuType.lsu) -> lsu.io.valid,
      (io.data.info.fusel === FuType.bru) -> bru.io.valid
    )
  )

  val ready = MuxCase(
    true.B,
    Seq(
      (io.data.info.fusel === FuType.mdu) -> mdu.io.ready,
      (io.data.info.fusel === FuType.lsu) -> lsu.io.ready
    ))

  // 输出
  io.data.rd_info.wdata := result
  io.data.diffout       := lsu.io.diffout
  io.data.valid         := valid && io.data.info.valid
  io.data.ready         := ready
}
