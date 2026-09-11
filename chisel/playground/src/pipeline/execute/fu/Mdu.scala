package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

/** RV32M execution unit. */
class Mdu extends Module {
  val io = IO(new Bundle {
    val info = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result = Output(UInt(XLEN.W))
    val valid = Output(Bool())
    val ready = Output(Bool())
  })

  val active = io.info.valid && io.info.fusel === FuType.mdu
  val a = io.src_info.src1_data(31, 0)
  val b = io.src_info.src2_data(31, 0)
  val signedProduct = a.asSInt * b.asSInt
  val unsignedProduct = a * b

  io.result := 0.U
  switch(io.info.op) {
    is(MDUOpType.mul) { io.result := signedProduct(31, 0) }
    is(MDUOpType.mulh) { io.result := signedProduct(63, 32) }
    is(MDUOpType.mulhu) { io.result := unsignedProduct(63, 32) }
    is(MDUOpType.div) { io.result := Mux(b === 0.U, "hffffffff".U, (a.asSInt / b.asSInt).asUInt) }
    is(MDUOpType.divu) { io.result := Mux(b === 0.U, "hffffffff".U, a / b) }
    is(MDUOpType.rem) { io.result := Mux(b === 0.U, a, (a.asSInt % b.asSInt).asUInt) }
    is(MDUOpType.remu) { io.result := Mux(b === 0.U, a, a % b) }
  }
  io.valid := active
  io.ready := true.B
}
