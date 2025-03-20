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
  val iszero = Mux(io.src_info.src2_data === 0.U, 1.U, 0.U)
  val neg1_64 = (-1).S(64.W)
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
      val result   = Mux(iszero === 1.U, SignedExtend(1.U, XLEN).asSInt, (io.src_info.src1_data.asSInt / io.src_info.src2_data.asSInt)) // Signed Division
      val overflow = io.src_info.src2_data.asSInt === -1.S && io.src_info.src1_data === SignedExtend(1.U, XLEN)
      io.result := Mux(overflow === true.B, SignedExtend(1.U, XLEN).asSInt, result).asUInt
    }
    is(MDUOpType.divu) {
      val result = Mux(iszero === 1.U, SignedExtend(1.U, XLEN), (io.src_info.src1_data / io.src_info.src2_data)) // Unsigned Division
      io.result := result
    }
    is(MDUOpType.rem) {
      io.result := Mux(iszero === 1.U, io.src_info.src1_data.asUInt, (io.src_info.src1_data.asSInt % io.src_info.src2_data.asSInt).asUInt) // Signed Remainder
    }
    is(MDUOpType.remu) {
      io.result := Mux(iszero === 1.U, io.src_info.src2_data, io.src_info.src1_data % io.src_info.src2_data) // Unsigned Remainder
    }

    // Word-Type Operations (32-bit, sign-extended to 64-bit)
    is(MDUOpType.mulw) {
      val mulResult = (io.src_info.src1_data(31, 0) * io.src_info.src2_data(31, 0))(31, 0).asUInt
      io.result := SignedExtend(mulResult, XLEN) // Use SignedExtend to extend to XLEN
    }
    is(MDUOpType.divw) {
      val divtmp                = io.src_info.src1_data(31, 0).asSInt / io.src_info.src2_data(31, 0).asSInt
      val divResult             = Mux(iszero === 1.U, neg1_64, divtmp.asSInt)(31,0)
      val overflow              = io.src_info.src2_data.asSInt === neg1_64.asSInt && io.src_info.src1_data === SignedExtend(1.U, 32)
      io.result := Mux(overflow === 1.U, SignedExtend(1.U, XLEN), SignedExtend(divResult.asUInt, XLEN))

    }
    is(MDUOpType.divuw) {
      val divtmp    = (io.src_info.src1_data(31, 0) / io.src_info.src2_data(31, 0)).asSInt
      val divResult = Mux(iszero === 1.U, neg1_64, divtmp)(31,0)
      io.result := SignedExtend(divResult.asUInt, XLEN) // Use SignedExtend to extend to XLEN
    }
    is(MDUOpType.remw) {

      val divtmp    = (io.src_info.src1_data(31, 0).asSInt % io.src_info.src2_data(31, 0).asSInt)(31,0)
      val remResult = Mux(iszero === 1.U, io.src_info.src1_data.asUInt, SignedExtend(divtmp.asUInt,XLEN))
    //  printf(p"res width: ${remResult.getWidth},sign bit : ${remResult(31)}\n") // comment this line will get a wrong answer ??
      io.result := remResult.asUInt // Use SignedExtend to extend to XLEN
  printf(p"divtmp: ${(remResult.getWidth)}, width: ${Hexadecimal(io.result)},iszero : ${iszero}\n")
    }
   is(MDUOpType.remuw) {
  // Extracting the relevant bits for the remainder operation
  val src1 = io.src_info.src1_data(31, 0).asUInt // 32-bit source 1
  val src2 = io.src_info.src2_data(31, 0).asUInt // 32-bit source 2

  // Calculate the remainder, ensuring proper usage
  val divtmp = WireDefault(0.U(32.W)) // Explicitly define divtmp as a 32-bit wire
  when(iszero === 0.U) {              // Handle divide-by-zero scenario
    divtmp := src1 % src2             // Perform unsigned modulus operation
  }

  // Result handling with Mux
  val remResult = Mux(iszero === 1.U, io.src_info.src1_data.asUInt, SignedExtend(divtmp(31,0),XLEN)) // Select between src1 (if zero) or divtmp
  io.result := remResult       // Extend the result to XLEN

  // Debugging can still be added, but it's optional now
  // printf(p"src1 : ${Decimal(src1)}, src2: ${Decimal(src2)}\n")
} 
  }
}
