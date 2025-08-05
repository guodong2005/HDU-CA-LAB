package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import firrtl.annotations.MemoryLoadFileType.Hex

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

  // Default output assignments
  io.result := DontCare
  io.target := 0.U
  io.branch := false.B

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
      io.branch := info.valid && (info.fusel === FuType.bru)
      io.target := (pc.asSInt + imm).asUInt
      io.result := 0.U
      // printf("jal triggered\n");
    }
    is(BRUOpType.bl) {
      io.branch := info.valid && (info.fusel === FuType.bru)
      io.target := (pc.asSInt + imm).asUInt
      io.result := pc + 4.U
    }

    // JALR (Jump and Link Register)
    is(BRUOpType.jirl) {
      io.branch := info.valid && (info.fusel === FuType.bru)
      io.result := pc + 4.U // Return address (PC + 4)
      io.target := (io.src_info.src1_data.asSInt + imm).asUInt;
    }

    // BEQ (Branch if Equal)
    is(BRUOpType.beq) {
      io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data === io.src_info.src2_data)
      io.target := (pc.asSInt + imm).asUInt // Signed addition for target
      io.result := 0.U                      // No return address needed
    }

    // BNE (Branch if Not Equal)
    is(BRUOpType.bne) {
      // printf(p"bne triggered: src1_data = ${Hexadecimal(io.src_info.src1_data)}, src2_data = ${Hexadecimal(io.src_info.src2_data)}, pc = ${Hexadecimal(pc)}\n")
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
