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
    val result   = Output(UInt(XLEN.W))
    val branch   = Output(Bool())
    val target   = Output(UInt(XLEN.W))
  })

  // Extract and rename inputs for clarity
  val info = io.info
  val pc   = io.pc
  // val imm  = io.src_info.src2_data.asSInt // Treat imm as SInt since it may be signed
  val imm = info.imm

  // Default output assignments
  io.result := DontCare
  io.target := 0.U
  io.branch := false.B

  // Debugging with printf
  printf(p"instr: ${Hexadecimal(info.instr)}, imm: ${Hexadecimal(imm)}\n")

  // Instruction handling
  switch(info.op) {
    // JAL (Jump and Link)
    is(BRUOpType.jal) {
      io.branch := info.valid && (info.fusel === FuType.bru)
      io.target := (pc.asSInt + imm).asUInt // Signed addition for target calculation
      io.result := pc + 4.U                // Return address (PC + 4)
    }

    // JALR (Jump and Link Register)
    is(BRUOpType.jalr) {
      io.branch := info.valid && (info.fusel === FuType.bru)
      io.target := ((io.src_info.src1_data.asSInt + imm) & (~1.S)).asUInt // Signed addition and alignment
      io.result := pc + 4.U                                             // Return address (PC + 4)
    }

    // BEQ (Branch if Equal)
    is(BRUOpType.beq) {
      io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data === io.src_info.src2_data)
      io.target := (pc.asSInt + imm).asUInt // Signed addition for target
      io.result := 0.U                      // No return address needed
    }

    // BNE (Branch if Not Equal)
    is(BRUOpType.bne) {
      io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data =/= io.src_info.src2_data)
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U
    }

    // BLT (Branch if Less Than)
    is(BRUOpType.blt) {
      io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data.asSInt < io.src_info.src2_data.asSInt)
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U
    }

    // BGE (Branch if Greater Than or Equal)
    is(BRUOpType.bge) {
      io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data.asSInt >= io.src_info.src2_data.asSInt)
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U
    }

    // BLTU (Branch if Less Than Unsigned)
    is(BRUOpType.bltu) {
      io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data < io.src_info.src2_data)
      io.target := (pc.asSInt + imm).asUInt // Unsigned comparison, target still uses signed addition
      io.result := 0.U
    }

    // BGEU (Branch if Greater Than or Equal Unsigned)
    is(BRUOpType.bgeu) {
      io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data >= io.src_info.src2_data)
      io.target := (pc.asSInt + imm).asUInt // Unsigned comparison, target still uses signed addition
      io.result := 0.U
    }
  }
}
