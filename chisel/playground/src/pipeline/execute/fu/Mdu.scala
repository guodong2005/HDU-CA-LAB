package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Mdu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
  })

  io.result := 0.U

  switch(io.info.op) {
    // Multiplication Operations
    is(MDUOpType.mul) { 
      io.result := io.src_info.src1_data * io.src_info.src2_data // 64-bit Multiply
    }
    is(MDUOpType.mulh) { 
      val product = (io.src_info.src1_data.asSInt * io.src_info.src2_data.asSInt).asSInt
      io.result := product(127, 64).asUInt // High 64 bits of signed multiplication
    }
    is(MDUOpType.mulhsu) { 
      val product = (io.src_info.src1_data.asSInt * io.src_info.src2_data).asSInt
      io.result := product(127, 64).asUInt // High 64 bits of signed-unsigned multiplication
    }
    is(MDUOpType.mulhu) { 
      val product = io.src_info.src1_data * io.src_info.src2_data
      io.result := product(127, 64) // High 64 bits of unsigned multiplication
    }

    // Division and Remainder Operations
    is(MDUOpType.div) { 
      io.result := (io.src_info.src1_data.asSInt / io.src_info.src2_data.asSInt).asUInt // Signed Division
    }
    is(MDUOpType.divu) { 
      io.result := io.src_info.src1_data / io.src_info.src2_data // Unsigned Division
    }
    is(MDUOpType.rem) { 
      io.result := (io.src_info.src1_data.asSInt % io.src_info.src2_data.asSInt).asUInt // Signed Remainder
    }
    is(MDUOpType.remu) { 
      io.result := io.src_info.src1_data % io.src_info.src2_data // Unsigned Remainder
    }

    // Word-Type Operations (32-bit, sign-extended to 64-bit)
    is(MDUOpType.mulw) {
      val mulResult = (io.src_info.src1_data(31, 0) * io.src_info.src2_data(31, 0)).asUInt
      io.result := SignedExtend(mulResult, XLEN) // Use SignedExtend to extend to XLEN
    }
    is(MDUOpType.divw) {
      val divResult = (io.src_info.src1_data(31, 0).asSInt / io.src_info.src2_data(31, 0).asSInt).asUInt
      io.result := SignedExtend(divResult, XLEN) // Use SignedExtend to extend to XLEN
    }
    is(MDUOpType.divuw) {
      val divResult = (io.src_info.src1_data(31, 0) / io.src_info.src2_data(31, 0)).asUInt
      io.result := SignedExtend(divResult, XLEN) // Use SignedExtend to extend to XLEN
    }
    is(MDUOpType.remw) {
      val remResult = (io.src_info.src1_data(31, 0).asSInt % io.src_info.src2_data(31, 0).asSInt).asUInt
      io.result := SignedExtend(remResult, XLEN) // Use SignedExtend to extend to XLEN
    }
    is(MDUOpType.remuw) {
      val remResult = (io.src_info.src1_data(31, 0) % io.src_info.src2_data(31, 0)).asUInt
      io.result := SignedExtend(remResult, XLEN) // Use SignedExtend to extend to XLEN
    }
  }
}
