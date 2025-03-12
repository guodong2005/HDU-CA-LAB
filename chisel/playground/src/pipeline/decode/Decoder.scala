package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class Decoder extends Module with HasInstrType {
  val io = IO(new Bundle {
    // inputs
    val in = Input(new Bundle {
      val inst = UInt(XLEN.W)
    })
    // outputs
    val out = Output(new Bundle {
      val info = new Info()
    })
  })
  val opcode = io.in.inst(6, 0)     
  when(opcode === "b0110011".U){
    val rd = io.in.inst(11, 7)       
    val funct3 = io.in.inst(14, 12)  
    val rs1 = io.in.inst(19, 15)     
    val rs2 = io.in.inst(24, 20)     
    val funct7 = io.in.inst(31, 25)  

    // Decode R-type instruction
    io.out.info.src1_raddr := rs1
    io.out.info.src2_raddr := rs2
    io.out.info.reg_wen := true.B  // unneccesary ?  
    io.out.info.reg_waddr := rd
  }

}
