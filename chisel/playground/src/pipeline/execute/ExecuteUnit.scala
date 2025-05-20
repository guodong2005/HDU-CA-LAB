package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.CpuConfig
import cpu.defines._
import cpu.defines.Const._
import chisel3.util.experimental.BoringUtils

class ExecuteUnit extends Module {
  val io = IO(new Bundle {
    val executeStage = Input(new DecodeUnitExecuteUnit())
    val memoryStage  = Output(new ExecuteUnitMemoryUnit())
    val ready        = Output(Bool())
    val branch       = Output(Bool())
    val target       = Output(UInt(XLEN.W))
    val dcache = new Bundle {
      val req  = (Decoupled(new DCacheReq))
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  val fu = Module(new Fu()).io

  fu.dcache        <> io.dcache
  fu.data.pc       := io.executeStage.data.pc
  fu.data.info     := io.executeStage.data.info
  fu.data.src_info := io.executeStage.data.src_info

  io.branch                        := fu.data.branch
  io.target                        := fu.data.target
  io.ready                         := fu.data.ready
  io.memoryStage.data.pc           := fu.data.pc
  io.memoryStage.data.info         := fu.data.info
  io.memoryStage.data.info.diffout := fu.data.diffout
  io.memoryStage.data.src_info     := fu.data.src_info
  io.memoryStage.data.rd_info      := fu.data.rd_info;
}
