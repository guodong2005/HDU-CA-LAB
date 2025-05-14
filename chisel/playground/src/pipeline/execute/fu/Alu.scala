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
    is(ALUOpType.add) { io.result := (io.src_info.src1_data + io.src_info.src2_data)(31, 0) } // ADD
    is(ALUOpType.sub) { io.result := (io.src_info.src1_data - io.src_info.src2_data)(31, 0) } // SUB
    is(ALUOpType.and) { io.result := (io.src_info.src1_data & io.src_info.src2_data)(31, 0) } // AND
    is(ALUOpType.or) { io.result := (io.src_info.src1_data | io.src_info.src2_data)(31, 0) } // OR
    is(ALUOpType.xor) { io.result := (io.src_info.src1_data ^ io.src_info.src2_data)(31, 0) } // XOR
    is(ALUOpType.slt) { io.result := (io.src_info.src1_data.asSInt < io.src_info.src2_data.asSInt) } // SLT (signed)
    is(ALUOpType.sltu) { io.result := (io.src_info.src1_data.asUInt < io.src_info.src2_data).asUInt } // SLTU (unsigned)
    is(ALUOpType.sll) { io.result := (io.src_info.src1_data << io.src_info.src2_data(4, 0))(31, 0) } // SLL
    is(ALUOpType.srl) { io.result := (io.src_info.src1_data >> io.src_info.src2_data(4, 0))(31, 0) } // SRL (logical right shift)
    is(ALUOpType.sra) { io.result := (io.src_info.src1_data.asSInt >> io.src_info.src2_data(4, 0)).asUInt(31, 0) } // SRA (arithmetic right shift)

  }

}
