package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import firrtl.annotations.MemoryLoadFileType.Hex

class Mdu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
  })

  io.result := 0.U
  val iszero   = Mux(io.src_info.src2_data === 0.U, 1.U, 0.U)
  val iszero32 = Mux(io.src_info.src2_data(31, 0) === 0.U, 1.U, 0.U)
  val neg1_32  = (-1).S(32.W)
  switch(io.info.op) {
    // Multiplication Operations
    is(MDUOpType.mul) {
      io.result := io.src_info.src1_data * io.src_info.src2_data // 64-bit Multiply
    }
    is(MDUOpType.mulh) {
      val product = (io.src_info.src1_data.asSInt * io.src_info.src2_data.asSInt).asSInt
      io.result := product(63, 32).asUInt // High 64 bits of signed multiplication
    }
    is(MDUOpType.mulhu) {
      val product = io.src_info.src1_data * io.src_info.src2_data
      io.result := product(63, 32) // High 64 bits of unsigned multiplication
    }

    // Division and Remainder Operations
    is(MDUOpType.div) {
      val result   = Mux(iszero === 1.U, SignedExtend(1.U, XLEN).asSInt, (io.src_info.src1_data.asSInt / io.src_info.src2_data.asSInt)) // Signed Division
      val overflow = io.src_info.src2_data.asSInt === neg1_32 && io.src_info.src1_data.asSInt === -(1 << 31).S                          // why not SignedExtend(1.U, XLEN) ?
      io.result := Mux(overflow === true.B, io.src_info.src1_data, result.asUInt)
    }
    is(MDUOpType.divu) {
      val result = Mux(iszero === 1.U, SignedExtend(1.U, XLEN), (io.src_info.src1_data / io.src_info.src2_data)) // Unsigned Division
      io.result := result
    }
    is(MDUOpType.rem) {
      val src1 = io.src_info.src1_data.asSInt // 32-bit source 1
      val src2 = io.src_info.src2_data.asSInt // 32-bit source 2

      val quotient = src1 / src2
      val rem      = src1 - quotient * src2

      io.result := Mux(iszero === 1.U, io.src_info.src1_data, rem(31, 0)) // Signed Remainder
    }
    is(MDUOpType.remu) {
      val src1 = io.src_info.src1_data.asUInt // 32-bit source 1
      val src2 = io.src_info.src2_data.asUInt // 32-bit source 2

      val quotient = src1 / src2
      val rem      = src1 - quotient * src2
      io.result := Mux(iszero === 1.U, io.src_info.src1_data, rem(31, 0)) // Unsigned Remainder
    }

  }
}
