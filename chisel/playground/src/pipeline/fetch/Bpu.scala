/*
package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
class BpuInstPacket extends Bundle {
  val data         = Vec(FETCH_WIDTH, UInt(32.W))
  val addr         = UInt(32.W)
  val gh_backup    = UInt(4.W)
  val valid_mask   = Vec(FETCH_WIDTH, Bool())
  val delay_mask   = Vec(FETCH_WIDTH, Bool())
  val branch_mask  = Vec(FETCH_WIDTH, Bool())
  val predict_mask = Vec(FETCH_WIDTH, Bool())
  def init(): Unit = {
    data         := VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W)))
    addr         := 0.U(32.W)
    gh_backup    := 0.U(4.W)
    valid_mask   := VecInit(Seq.fill(FETCH_WIDTH)(false.B))
    delay_mask   := VecInit(Seq.fill(FETCH_WIDTH)(false.B))
    branch_mask  := VecInit(Seq.fill(FETCH_WIDTH)(false.B))
    predict_mask := VecInit(Seq.fill(FETCH_WIDTH)(false.B))
  }
}

class BranchPredictionInfo extends Bundle {
  val predict_addr = UInt(32.W)
  val is_taken     = Bool()
  val take_delay   = Bool()
}

class BranchInfo extends Bundle {
  val target_addr  = UInt(32.W)
  val inst_addr    = UInt(32.W)
  val gh_update    = UInt(4.W)
  val is_branch    = Bool()
  val is_taken     = Bool()
  val predict_miss = Bool()
  def init(): Unit = {
    target_addr  := 0.U(32.W)
    inst_addr    := 0.U(32.W)
    gh_update    := 0.U(4.W)
    is_branch    := false.B
    is_taken     := false.B
    predict_miss := false.B
  }
}

class BpuDebugIO extends Bundle {
  val branch_mask    = Output(UInt(FETCH_WIDTH.W))
  val fetched_mask   = Output(UInt(FETCH_WIDTH.W))
  val predict_branch = Output(UInt(FETCH_WIDTH.W))
  val predict_addr   = Output(UInt(32.W))
  val is_taken       = Output(Bool())
  val take_delay     = Output(Bool())
  val inst_packet    = Output(Vec(FETCH_WIDTH, UInt(32.W)))
}

class BpuIO extends Bundle {
  val inst_packet_i     = Flipped(Valid(new InstPacket))
  val resp_o            = Valid(new BranchPredictionInfo())
  val bpu_inst_packet_o = Decoupled(new BpuInstPacket)
  val branch_info_i     = Flipped(Valid(new BranchInfo))
  val is_delay          = Input(Bool())
  val need_flush        = Input(Bool())
  val bpu_debug         = new BpuDebugIO
}

class BPU extends Module {
  val io = IO(new BpuIO)

  val global_history = RegInit(0.U(4.W))
  val predictor      = RegInit(VecInit(Seq.fill(128)("b10".U(2.W))))

  val insts = io.inst_packet_i.bits.data
  val addr  = io.inst_packet_i.bits.addr

  val branch_mask = insts.map { inst =>
    val instrType :: fuType :: fuOpType :: Nil =
      ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)
    fuType === FuType.bru
  }

  val fetched_mask = VecInit(Seq.tabulate(FETCH_WIDTH) { i =>
    i.U(ICACHE_INST_WIDTH.W) === io.inst_packet_i.bits.addr(ICACHE_INST_WIDTH + 1, 2)
  })

  val need_predict = branch_mask.zip(fetched_mask).map(_ & _)

  val predictor_idx = need_predict.zipWithIndex.map {
    case (_, i) =>
      Cat(global_history, io.inst_packet_i.bits.addr(5), i.U(ICACHE_INST_WIDTH.W))
  }

  val predict_mask   = predictor_idx.map(idx => predictor(idx)(1))
  val predict_branch = need_predict.zip(predict_mask).map(_ & _)

  val is_taken  = VecInit(predict_branch).asUInt().orR()
  val inst_mask = PriorityEncoderOH(predict_branch)
  val inst_idx  = OHToUInt(inst_mask)
  val inst      = insts(inst_idx)

  val instrType :: fuType :: fuOpType :: Nil =
    ListLookup(inst, Instructions.DecodeDefault, Instructions.DecodeTable)

  val imm = LookupTree(
    instrType,
    Seq(
      InstrI -> Mux(inst(24), ZeroExtend(inst(21, 10), XLEN), SignedExtend(inst(21, 10), XLEN)),
      InstrS -> SignedExtend(inst(21, 10), XLEN),
      InstrB -> SignedExtend(Cat(inst(25, 10), 0.U(2.W)), XLEN),
      InstrU -> SignedExtend(Cat(inst(24, 5), 0.U(12.W)), XLEN),
      InstrJ -> SignedExtend(
        Cat(
          Cat(Mux(fuOpType === BRUOpType.jirl, 0.U, inst(9, 0)), inst(25, 10)),
          0.U(2.W)
        ),
        XLEN
      )
    )
  )

  val predict_addr = io.inst_packet_i.bits.addr + imm

  val valid_mask = VecInit(
    inst_mask
      .scanRight(~is_taken)(_ | _)
      .dropRight(1)
      .zip(fetched_mask)
      .map(_ & _)
  )

  val bpu_packet = RegInit(0.U.asTypeOf(new BpuInstPacket))
  val bpu_valid  = RegInit(false.B)

  when(io.bpu_inst_packet_o.ready) {
    bpu_packet.data         := insts
    bpu_packet.addr         := addr
    bpu_packet.gh_backup    := global_history
    bpu_packet.valid_mask   := valid_mask
    bpu_packet.branch_mask  := branch_mask
    bpu_packet.predict_mask := predict_branch
    bpu_packet.delay_mask   := VecInit(Seq.fill(FETCH_WIDTH)(false.B)) // LoongArch 无延迟槽
    bpu_valid               := io.inst_packet_i.valid
  }

  when(io.need_flush || reset.asBool()) {
    bpu_packet.init()
    bpu_valid := false.B
  }

  io.bpu_inst_packet_o.bits   := bpu_packet
  io.bpu_inst_packet_o.valid  := bpu_valid
  io.resp_o.bits.predict_addr := predict_addr
  io.resp_o.bits.is_taken     := is_taken
  io.resp_o.bits.take_delay   := false.B // 无延迟槽
  io.resp_o.valid             := io.inst_packet_i.valid

  // 分支信息反馈更新预测器
  val update_idx  = Cat(io.branch_info_i.bits.gh_update, io.branch_info_i.bits.inst_addr(5, 2))
  val target_pred = predictor(update_idx)

  when(io.branch_info_i.valid && io.branch_info_i.bits.is_branch) {
    predictor(update_idx) := MuxLookup(
      target_pred,
      target_pred,
      Seq(
        "b00".U -> Mux(io.branch_info_i.bits.is_taken, "b01".U, "b00".U),
        "b01".U -> Mux(io.branch_info_i.bits.is_taken, "b11".U, "b00".U),
        "b10".U -> Mux(io.branch_info_i.bits.is_taken, "b11".U, "b00".U),
        "b11".U -> Mux(io.branch_info_i.bits.is_taken, "b11".U, "b10".U)
      )
    )
  }

  global_history := Mux(
    io.branch_info_i.valid && io.branch_info_i.bits.predict_miss,
    io.branch_info_i.bits.gh_update,
    Cat(is_taken, global_history(3, 1))
  )

  // debug 信号
  io.bpu_debug.branch_mask    := VecInit(branch_mask).asUInt()
  io.bpu_debug.fetched_mask   := VecInit(fetched_mask).asUInt()
  io.bpu_debug.predict_branch := VecInit(predict_branch).asUInt()
  io.bpu_debug.predict_addr   := predict_addr
  io.bpu_debug.is_taken       := is_taken
  io.bpu_debug.take_delay     := false.B
  io.bpu_debug.inst_packet    := insts
}
 */
