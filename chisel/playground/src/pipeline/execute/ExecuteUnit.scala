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
    val dcache = new Bundle {
      val req  = (Decoupled(new DCacheReq))
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  val fu = Module(new Fu())

  fu.io.dcache <> io.dcache
  fu.io.data.pc       := io.executeStage.data.pc
  fu.io.data.info     := io.executeStage.data.info
  fu.io.data.src_info := io.executeStage.data.src_info

  io.ready                         := fu.io.data.ready
  io.memoryStage.data.pc           := io.executeStage.data.pc
  io.memoryStage.data.info         := io.executeStage.data.info
  io.memoryStage.data.info.valid   := fu.io.data.valid
  io.memoryStage.data.info.diffout := fu.io.data.diffout
  io.memoryStage.data.src_info     := io.executeStage.data.src_info
  io.memoryStage.data.rd_info      := fu.io.data.rd_info
}
