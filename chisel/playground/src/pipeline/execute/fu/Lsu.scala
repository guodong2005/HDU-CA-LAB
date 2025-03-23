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
  io.dataSram.en    := false.B
  io.dataSram.addr  := DontCare
  io.dataSram.wen   := 0.U
   */
  /*
dataSram is a 64-bit ram so datasram.wen has 8 bit to represent the 8 bits' write signals.
generate tmp_datasram for me , for example, if the instruction is lb:

tmp_datasram_wen := LSUOpType.lb[1:0] <<datasram.addr[2:0]

tmp_datasram_wen := LSUOpType.sh[1:0] <<datasram.addr[2:0] ... like this

in some case like the datasram.addr[0] = 1 and the command type is double word might incurs that we write 8 bytes which is not in the same sram unit, you can ignore it

TODO: add unaligned exception
   */
  io.dataSram.addr := io.src_info.src1_data + io.info.imm
  val tmpwen = ZeroExtend(((io.info.op(1, 0).asUInt) << (io.dataSram.addr(2, 0).asUInt)),8)
  // printf("tmpwen : ${tmpwen}.io.info.op,io.src_info.src2_data\n")
  printf(p"tmpwen: ${Binary(ZeroExtend(tmpwen,8))}, io.info.op: ${io.info.op}, io.src_info.src2_data: ${Hexadecimal(io.src_info.src2_data)}\n")

  // io.dataSram.wen := tmpwen &&
  io.dataSram.en   := !reset.asBool
  io.dataSram.wen  := tmpwen & Fill(8, io.info.valid && (io.info.fusel === FuType.lsu) && LSUOpType.isStore(io.info.op))
  io.dataSram.wdata := LookupTree(
    io.info.op,
    Seq(
      LSUOpType.sb -> Fill(8, io.src_info.src2_data(7, 0)),  // Store Byte: replicate the lowest byte 8 times
      LSUOpType.sh -> Fill(4, io.src_info.src2_data(15, 0)), // Store Halfword: replicate the lowest 2 bytes 4 times
      LSUOpType.sw -> Fill(2, io.src_info.src2_data(31, 0)), // Store Word: replicate the lowest 4 bytes 2 times
      LSUOpType.sd -> io.src_info.src2_data                  // Store Doubleword: directly use src2_data for 8 bytes
    )
  )
  io.result := 0.U // data sram takes 2 period so now we cannot have the read result
  io.addr3  := io.dataSram.addr(2, 0)

  /*
  switch(io.info.op) {
    // LSU Operations
    is(LSUOpType.lb) {
      io.result := SignedExtend(Memory.read(io.src_info.src1_data + io.src_info.src2_data, 8), XLEN) // Load Byte (signed)
    }
    is(LSUOpType.lbu) {
      io.result := ZeroExtend(Memory.read(io.src_info.src1_data + io.src_info.src2_data, 8), XLEN) // Load Byte Unsigned
    }
    is(LSUOpType.lh) {
      io.result := SignedExtend(Memory.read(io.src_info.src1_data + io.src_info.src2_data, 16), XLEN) // Load Halfword (signed)
    }
    is(LSUOpType.lhu) {
      io.result := ZeroExtend(Memory.read(io.src_info.src1_data + io.src_info.src2_data, 16), XLEN) // Load Halfword Unsigned
    }
    is(LSUOpType.lw) {
      io.result := SignedExtend(Memory.read(io.src_info.src1_data + io.src_info.src2_data, 32), XLEN) // Load Word (signed)
    }
    is(LSUOpType.ld) {
      io.result := Memory.read(io.src_info.src1_data + io.src_info.src2_data, XLEN) // Load Doubleword (for RV64, no sign extension needed)
    }
    is(LSUOpType.sb) {
      Memory.write(io.src_info.src1_data + io.src_info.src2_data, io.src_info.src3_data(7, 0), 8) // Store Byte
    }
    is(LSUOpType.sh) {
      Memory.write(io.src_info.src1_data + io.src_info.src2_data, io.src_info.src3_data(15, 0), 16) // Store Halfword
    }
    is(LSUOpType.sw) {
      Memory.write(io.src_info.src1_data + io.src_info.src2_data, io.src_info.src3_data(31, 0), 32) // Store Word
    }
    is(LSUOpType.sd) {
      Memory.write(io.src_info.src1_data + io.src_info.src2_data, io.src_info.src3_data, XLEN) // Store Doubleword (for RV64)
    }
  }
   */

}
