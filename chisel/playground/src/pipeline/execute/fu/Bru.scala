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
    val target   = Output(SInt(XLEN.W))
  })
  val info = io.info
  val pc   = io.pc
  io.result := DontCare
  io.target:= 0.U
  io.branch := 0.U
  printf(p"instr: ${Hexadecimal(info.instr)}, imm: ${Hexadecimal(info.imm)}\n")

  switch(info.op) {
  // JAL (Jump and Link)
  is(BRUOpType.jal) {
    io.branch := info.valid && (info.fusel === FuType.bru)
    io.target := pc + info.imm // Target address = PC + immediate offset
    io.result := pc + 4.U      // Return address (PC + 4)
  }

  // JALR (Jump and Link Register)
  is(BRUOpType.jalr) {
    io.branch := info.valid && (info.fusel === FuType.bru)
    io.target := (io.src_info.src1_data + info.imm) & (~1.U(XLEN.W)) // Target with alignment
    io.result := pc + 4.U                                           // Return address (PC + 4)
  }

  // BEQ (Branch if Equal)
  is(BRUOpType.beq) {
    io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data === io.src_info.src2_data)
    io.target := pc + info.imm // Target address for branch
    io.result := 0.U           // No return address needed
  }

  // BNE (Branch if Not Equal)
  is(BRUOpType.bne) {
    io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data =/= io.src_info.src2_data)
    io.target := pc + info.imm
    io.result := 0.U
  }

  // BLT (Branch if Less Than)
  is(BRUOpType.blt) {
    io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data.asSInt < io.src_info.src2_data.asSInt)
    io.target := pc + info.imm
    io.result := 0.U
  }

  // BGE (Branch if Greater Than or Equal)
  is(BRUOpType.bge) {
    io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data.asSInt >= io.src_info.src2_data.asSInt)
    io.target := pc + info.imm
    io.result := 0.U
  }

  // BLTU (Branch if Less Than Unsigned)
  is(BRUOpType.bltu) {
    io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data < io.src_info.src2_data)
    io.target := pc + info.imm
    io.result := 0.U
  }

  // BGEU (Branch if Greater Than or Equal Unsigned)
  is(BRUOpType.bgeu) {
    io.branch := info.valid && (info.fusel === FuType.bru) && (io.src_info.src1_data >= io.src_info.src2_data)
    io.target := pc + info.imm
    io.result := 0.U
  }
}

}
