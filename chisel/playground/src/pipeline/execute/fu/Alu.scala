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
    // Other 32-bit operations remain unchanged
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
  }

}
