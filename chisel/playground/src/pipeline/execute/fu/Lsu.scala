package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Lsu extends Module {
  val io = IO(new Bundle {
    val info     = Input(new Info())
    val src_info = Input(new SrcInfo())
    val result   = Output(UInt(XLEN.W))
    val addr3    = Output(UInt(3.W))
    val dataSram = new DataSram()
  })

  /*
dataSram is a 64-bit ram so datasram.wen has 8 bit to represent the 8 bits' write signals.
generate tmp_datasram for me , for example, if the instruction is lb:

tmp_datasram_wen := LSUOpType.lb[1:0] <<datasram.addr[2:0]

tmp_datasram_wen := LSUOpType.sh[1:0] <<datasram.addr[2:0] ... like this

in some case like the datasram.addr[0] = 1 and the command type is double word might incurs that we write 8 bytes which is not in the same sram unit, you can ignore it

TODO: add unaligned exception
   */

  // io.dataSram.addr := io.src_info.src1_data + io.info.imm
  io.dataSram.addr := LookupTree(
    LSUOpType.isStore(io.info.op),
    Seq(
      true.B  -> (io.src_info.src1_data.asSInt + SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0),
      false.B -> (io.src_info.src1_data.asSInt + SignedExtend(io.info.imm(11, 0), XLEN).asSInt)(31, 0)
    )
  )
  io.addr3 := io.dataSram.addr(2, 0)
  val count = 1.U << (io.info.op(1, 0)) // 要写几个字节
  val bits  = (1.U << count) - 1.U      // 生成一个字节个数的全 1 串

  val tmpwen = ZeroExtend((bits << (io.dataSram.addr(2, 0).asUInt)), 8)

  io.dataSram.en  := !reset.asBool
  io.dataSram.wen := tmpwen & Fill(8, io.info.valid && (io.info.fusel === FuType.lsu) && LSUOpType.isStore(io.info.op))
  io.dataSram.wdata := LookupTree(
    io.info.op,
    Seq(
      LSUOpType.sb -> Fill(8, io.src_info.src2_data(7, 0)),  // Store Byte: replicate the lowest byte 8 times
      LSUOpType.sh -> Fill(4, io.src_info.src2_data(15, 0)), // Store Halfword: replicate the lowest 2 bytes 4 times
      LSUOpType.sw -> Fill(2, io.src_info.src2_data(31, 0))  // Store Word: replicate the lowest 4 bytes 2 times
    )
  )
  io.result := 0.U // data sram takes 2 period so now we cannot have the read result
}
