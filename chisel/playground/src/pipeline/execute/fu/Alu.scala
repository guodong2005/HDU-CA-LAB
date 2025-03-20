package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Alu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
  })

  io.result := 0.U

  switch(io.info.op) {
    // Other 64-bit operations remain unchanged
    is(ALUOpType.add) { io.result := io.src_info.src1_data + io.src_info.src2_data } // ADD
    is(ALUOpType.sub) { io.result := io.src_info.src1_data - io.src_info.src2_data } // SUB
    is(ALUOpType.and) { io.result := io.src_info.src1_data & io.src_info.src2_data } // AND
    is(ALUOpType.or) { io.result := io.src_info.src1_data | io.src_info.src2_data } // OR
    is(ALUOpType.xor) { io.result := io.src_info.src1_data ^ io.src_info.src2_data } // XOR
    is(ALUOpType.slt) { io.result := (io.src_info.src1_data.asSInt < io.src_info.src2_data.asSInt).asUInt } // SLT (signed)
    is(ALUOpType.sltu) { io.result := (io.src_info.src1_data < io.src_info.src2_data) } // SLTU (unsigned)
    is(ALUOpType.sll) { io.result := io.src_info.src1_data << io.src_info.src2_data(5, 0) } // SLL
    is(ALUOpType.srl) { io.result := io.src_info.src1_data >> io.src_info.src2_data(5, 0) } // SRL (logical right shift)
    is(ALUOpType.sra) { io.result := (io.src_info.src1_data.asSInt >> io.src_info.src2_data(5, 0)).asUInt } // SRA (arithmetic right shift)

    // Word-Type Operations (32-bit operations with sign-extension)
    is(ALUOpType.addw) {
      val addResult = (io.src_info.src1_data(31, 0) + io.src_info.src2_data(31, 0)).asSInt
      io.result := SignedExtend(addResult, XLEN) // Sign-extend result to XLEN
    }

    is(ALUOpType.subw) {
      val subResult = (io.src_info.src1_data(31, 0) - io.src_info.src2_data(31, 0)).asSInt
      io.result := SignedExtend(subResult, XLEN) // Sign-extend result to XLEN
    }

    is(ALUOpType.sllw) {
      val shiftResult = (io.src_info.src1_data(31, 0) << io.src_info.src2_data(4, 0)).asUInt // 32-bit so it is 4-0
      io.result := SignedExtend(shiftResult, XLEN) // Sign-extend result to XLEN
    }

    is(ALUOpType.srlw) {
      val logicalShiftResult = (io.src_info.src1_data(31, 0) >> io.src_info.src2_data(4, 0)).asUInt
      io.result := SignedExtend(logicalShiftResult, XLEN) // Sign-extend result to XLEN
    }

    is(ALUOpType.sraw) {
      val arithmeticShiftResult = (io.src_info.src1_data(31, 0).asSInt >> io.src_info.src2_data(4, 0)).asSInt
      io.result := SignedExtend(arithmeticShiftResult, XLEN) // Sign-extend result to XLEN
    }

  }

}
