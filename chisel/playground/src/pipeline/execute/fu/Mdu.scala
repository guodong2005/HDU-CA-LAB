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
      when(io.src_info.src2_data === 0.U) {
        io.result := (-1).S.asUInt // Divide-by-zero: return -1 for signed division
      }.elsewhen(io.src_info.src1_data.asSInt === Int.MinValue.S && io.src_info.src2_data.asSInt === -1.S) {
        io.result := Int.MinValue.U // Overflow: return Int.MinValue
      }.otherwise {
        io.result := (io.src_info.src1_data.asSInt / io.src_info.src2_data.asSInt).asUInt
      }
    }
    is(MDUOpType.divu) {
      io.result := Mux(io.src_info.src2_data === 0.U, ((1L << XLEN) - 1).U, io.src_info.src1_data / io.src_info.src2_data)
    }
    is(MDUOpType.rem) {
      when(io.src_info.src2_data === 0.U) {
        io.result := io.src_info.src1_data // Divide-by-zero: return dividend for signed remainder
      }.elsewhen(io.src_info.src1_data.asSInt === Int.MinValue.S && io.src_info.src2_data.asSInt === -1.S) {
        io.result := 0.U // Overflow: remainder is 0
      }.otherwise {
        io.result := (io.src_info.src1_data.asSInt % io.src_info.src2_data.asSInt).asUInt
      }
    }
    is(MDUOpType.remu) {
      io.result := Mux(io.src_info.src2_data === 0.U, io.src_info.src1_data, io.src_info.src1_data % io.src_info.src2_data)
    }

    // Word-Type Operations (32-bit, sign-extended to 64-bit)
    is(MDUOpType.mulw) {
      val mulResult = (io.src_info.src1_data(31, 0) * io.src_info.src2_data(31, 0)).asUInt
      io.result := SignedExtend(mulResult, XLEN) // Use SignedExtend to extend to XLEN
    }
    is(MDUOpType.divw) {
      when(io.src_info.src2_data(31, 0) === 0.U) {
        io.result := (-1).S.asUInt // Divide-by-zero: return -1 for signed division
      }.elsewhen(io.src_info.src1_data(31, 0).asSInt === Int.MinValue.S && io.src_info.src2_data(31, 0).asSInt === -1.S) {
        io.result := Int.MinValue.U // Overflow: return Int.MinValue
      }.otherwise {
        val divResult = (io.src_info.src1_data(31, 0).asSInt / io.src_info.src2_data(31, 0).asSInt).asUInt
        io.result := SignedExtend(divResult, XLEN) // Use SignedExtend to extend to XLEN
      }
    }
    is(MDUOpType.divuw) {
      val divResult = Mux(io.src_info.src2_data(31, 0) === 0.U, ((1L << 32) - 1).U, io.src_info.src1_data(31, 0) / io.src_info.src2_data(31, 0)).asUInt
      io.result := SignedExtend(divResult, XLEN) // Use SignedExtend to extend to XLEN
    }
    is(MDUOpType.remw) {
      when(io.src_info.src2_data(31, 0) === 0.U) {
        io.result := io.src_info.src1_data(31, 0) // Divide-by-zero: return dividend for signed remainder
      }.elsewhen(io.src_info.src1_data(31, 0).asSInt === Int.MinValue.S && io.src_info.src2_data(31, 0).asSInt === -1.S) {
        io.result := 0.U // Overflow: remainder is 0
      }.otherwise {
        val remResult = (io.src_info.src1_data(31, 0).asSInt % io.src_info.src2_data(31, 0).asSInt).asUInt
        io.result := SignedExtend(remResult, XLEN) // Use SignedExtend to extend to XLEN
      }
    }
    is(MDUOpType.remuw) {
      val remResult = Mux(io.src_info.src2_data(31, 0) === 0.U, io.src_info.src1_data(31, 0), io.src_info.src1_data(31, 0) % io.src_info.src2_data(31, 0)).asUInt
      io.result := SignedExtend(remResult, XLEN) // Use SignedExtend to extend to XLEN
    }
  }
}
