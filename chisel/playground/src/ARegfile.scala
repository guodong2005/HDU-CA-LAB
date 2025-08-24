package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class SrcRead extends Bundle {
  val raddr = Output(UInt(REG_ADDR_WID.W))
  val rdata = Input(UInt(XLEN.W))
}

class Src12Read extends Bundle {
  val src1 = new SrcRead()
  val src2 = new SrcRead()
}

class RegWrite extends Bundle {
  val wen   = Output(Bool())
  val waddr = Output(UInt(REG_ADDR_WID.W))
  val wdata = Output(UInt(XLEN.W))
}

class ARegFile extends Module {
  val io = IO(new Bundle {
    val read     = Flipped(new Src12Read()) // 改回2个读端口
    val write    = Flipped(new RegWrite())
    val regs_out = Output(Vec(AREG_NUM, UInt(XLEN.W))) // Expose registers to top
  })

  // 定义32个 64 位寄存器
  val regs = RegInit(VecInit(Seq.fill(AREG_NUM)(0.U(XLEN.W))))
  // val regs = RegInit(VecInit((0 until AREG_NUM).map(_.U(XLEN.W)))) // for lab1

  // 写寄存器堆
  when(io.write.wen && (io.write.waddr =/= 0.U)) {
    when(io.write.waddr.asUInt === 11.U) {
      regs(11) := regs(11) + io.write.wdata

    }.elsewhen(true.B) {
      regs(io.write.waddr) := io.write.wdata
    }
  }

  io.regs_out := regs

  // 读寄存器堆 - 2个读端口
  io.read.src1.rdata := regs(io.read.src1.raddr)
  io.read.src2.rdata := regs(io.read.src2.raddr)

  // 调试输出
}
