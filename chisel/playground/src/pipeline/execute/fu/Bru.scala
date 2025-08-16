package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Bru extends Module {
  val io = IO(new Bundle {
    val info        = Input(new Info())
    val pc          = Input(UInt(XLEN.W))
    val src_info    = Input(new SrcInfo())
    val valid       = Output(Bool())
    val result      = Output(UInt(XLEN.W))
    val branch      = Output(Bool())
    val target      = Output(UInt(XLEN.W))
    val bpufeedback = Output(new BPUFeedback())
  })

  io.valid := true.B && io.info.valid && (io.info.fusel === FuType.bru)

  val info = io.info
  val pc   = io.pc
  val imm  = info.imm.asSInt

  // Default output assignments
  io.result := DontCare
  io.target := 0.U
  io.branch := false.B

  // BPU feedback signals
  val actual_taken    = Wire(Bool())
  val actual_target   = Wire(UInt(XLEN.W))
  val is_branch_instr = Wire(Bool())

  // Default values
  actual_taken    := false.B
  actual_target   := 0.U
  is_branch_instr := false.B

  // Instruction handling
  switch(info.op) {
    // JAL (Jump and Link) - unconditional jump, no writeback
    is(BRUOpType.b) {
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U

      // BPU feedback for unconditional branch
      actual_taken    := true.B
      actual_target   := (pc.asSInt + imm).asUInt
      is_branch_instr := true.B
    }

    // JAL (Jump and Link) - unconditional jump with writeback
    is(BRUOpType.bl) {
      io.target := (pc.asSInt + imm).asUInt
      io.result := pc + 4.U

      // BPU feedback for unconditional branch
      actual_taken    := true.B
      actual_target   := (pc.asSInt + imm).asUInt
      is_branch_instr := true.B
    }

    // JALR (Jump and Link Register)
    is(BRUOpType.jirl) {
      io.result := pc + 4.U // Return address (PC + 4)
      io.target := (io.src_info.src1_data.asSInt + imm).asUInt

      // BPU feedback for indirect jump
      actual_taken    := true.B
      actual_target   := (io.src_info.src1_data.asSInt + imm).asUInt
      is_branch_instr := true.B
    }

    // BEQ (Branch if Equal)
    is(BRUOpType.beq) {
      val branch_taken = io.src_info.src1_data === io.src_info.src2_data
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U

      // BPU feedback
      actual_taken    := branch_taken
      actual_target   := Mux(branch_taken, (pc.asSInt + imm).asUInt, pc + 4.U)
      is_branch_instr := true.B
    }

    // BNE (Branch if Not Equal)
    is(BRUOpType.bne) {
      val branch_taken = io.src_info.src1_data =/= io.src_info.src2_data
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U

      // BPU feedback
      actual_taken    := branch_taken
      actual_target   := Mux(branch_taken, (pc.asSInt + imm).asUInt, pc + 4.U)
      is_branch_instr := true.B
    }

    // BLT (Branch if Less Than)
    is(BRUOpType.blt) {
      val branch_taken = io.src_info.src1_data.asSInt < io.src_info.src2_data.asSInt
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U

      // BPU feedback
      actual_taken    := branch_taken
      actual_target   := Mux(branch_taken, (pc.asSInt + imm).asUInt, pc + 4.U)
      is_branch_instr := true.B
    }

    // BGE (Branch if Greater Than or Equal)
    is(BRUOpType.bge) {
      val branch_taken = io.src_info.src1_data.asSInt >= io.src_info.src2_data.asSInt
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U

      // BPU feedback
      actual_taken    := branch_taken
      actual_target   := Mux(branch_taken, (pc.asSInt + imm).asUInt, pc + 4.U)
      is_branch_instr := true.B
    }

    // BLTU (Branch if Less Than Unsigned)
    is(BRUOpType.bltu) {
      val branch_taken = io.src_info.src1_data < io.src_info.src2_data
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U

      // BPU feedback
      actual_taken    := branch_taken
      actual_target   := Mux(branch_taken, (pc.asSInt + imm).asUInt, pc + 4.U)
      is_branch_instr := true.B
    }

    // BGEU (Branch if Greater Than or Equal Unsigned)
    is(BRUOpType.bgeu) {
      val branch_taken = io.src_info.src1_data >= io.src_info.src2_data
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U

      // BPU feedback
      actual_taken    := branch_taken
      actual_target   := Mux(branch_taken, (pc.asSInt + imm).asUInt, pc + 4.U)
      is_branch_instr := true.B
    }
  }

  // Generate BPU feedback
  io.bpufeedback.valid         := io.valid && is_branch_instr
  io.bpufeedback.pc            := pc
  io.bpufeedback.actual_taken  := actual_taken
  io.bpufeedback.actual_target := actual_target

  // Determine if prediction was wrong
  val prediction_wrong = (io.info.bpu_pred.predicted_taken =/= actual_taken) ||
    (actual_taken && (io.info.bpu_pred.predicted_target =/= actual_target))
  io.bpufeedback.mispredicted := io.bpufeedback.valid && prediction_wrong

  // Branch signal should only be true when we need to redirect (misprediction)
  // If prediction was correct, pipeline already went in the right direction
  // This avoids unnecessary pipeline flushes when BPU prediction is correct
  io.branch := io.bpufeedback.mispredicted
}
