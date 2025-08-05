package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Bru extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val pc       = Input(UInt(XLEN.W))
    val src_info = Input(new SrcInfo())
    val valid    = Output(Bool())
    val result   = Output(UInt(XLEN.W))
    val branch   = Output(Bool())
    val target   = Output(UInt(XLEN.W))
  })

  io.valid := true.B && io.info.valid && (io.info.fusel === FuType.bru)

  val info = io.info
  val pc   = io.pc
  val imm  = info.imm.asSInt
  val src1 = io.src_info.src1_data
  val src2 = io.src_info.src2_data
  val op   = info.op

  // 并行计算所有可能的比较结果（从MiniBru复制）
  val eq  = src1 === src2
  val ne  = !eq
  val lt  = src1.asSInt < src2.asSInt
  val ge  = !lt
  val ltu = src1 < src2
  val geu = !ltu

  // 使用简单的Mux选择分支条件（从MiniBru复制）
  val takeBranch = MuxCase(
    false.B,
    Seq(
      (op === BRUOpType.beq)  -> eq,
      (op === BRUOpType.bne)  -> ne,
      (op === BRUOpType.blt)  -> lt,
      (op === BRUOpType.bge)  -> ge,
      (op === BRUOpType.bltu) -> ltu,
      (op === BRUOpType.bgeu) -> geu,
      (op === BRUOpType.b)    -> true.B,
      (op === BRUOpType.bl)   -> true.B,
      (op === BRUOpType.jirl) -> true.B
    )
  )

  // 并行计算所有可能的目标地址（从MiniBru复制）
  val branchTarget   = io.pc + info.imm
  val jumpTarget     = io.pc + info.imm
  val indirectTarget = src1 + info.imm

  // 选择正确的目标地址（从MiniBru复制）
  io.target := Mux(op === BRUOpType.jirl, indirectTarget, Mux(op === BRUOpType.b || op === BRUOpType.bl, jumpTarget, branchTarget))

  // 输出分支信号（从MiniBru复制）
  io.branch := takeBranch

  // Default output assignments
  io.result := DontCare

  // Debugging with printf
  // Instruction handling
  /*
  printf(p"its op: ${Binary(io.info.op)}\n");
  printf(p"its instr: ${Hexadecimal(io.info.instr)}\n");
  printf(p"its writeback: ${Hexadecimal(io.info.reg_wen)}\n");
   */

  switch(info.op) {
    // JAL (Jump and Link)
    is(BRUOpType.b) { // 不写回
      io.result := 0.U
      // printf("jal triggered\n");
    }
    is(BRUOpType.bl) {
      io.result := pc + 4.U
    }
    // JALR (Jump and Link Register)
    is(BRUOpType.jirl) {
      io.result := Mux(io.info.reg_waddr === 0.U, 0.U, pc + 4.U)
    }
    // BEQ (Branch if Equal)
    is(BRUOpType.beq) {
      io.result := 0.U // No return address needed
    }
    // BNE (Branch if Not Equal)
    is(BRUOpType.bne) {
      // printf(p"bne triggered: src1_data = ${Hexadecimal(io.src_info.src1_data)}, src2_data = ${Hexadecimal(io.src_info.src2_data)}, pc = ${Hexadecimal(pc)}\n")
      io.result := 0.U
    }
    // BLT (Branch if Less Than)
    is(BRUOpType.blt) {
      io.result := 0.U
    }
    // BGE (Branch if Greater Than or Equal)
    is(BRUOpType.bge) {
      io.result := 0.U
    }
    // BLTU (Branch if Less Than Unsigned)
    is(BRUOpType.bltu) {
      io.result := 0.U
    }
    // BGEU (Branch if Greater Than or Equal Unsigned)
    is(BRUOpType.bgeu) {
      io.result := 0.U
    }
  }
}
