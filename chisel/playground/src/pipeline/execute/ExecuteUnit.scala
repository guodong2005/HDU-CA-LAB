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

  val fu = Module(new Fu())

  val srcInfoReg = RegInit(0.U.asTypeOf(new SrcInfo()))
  val infoReg    = RegInit(0.U.asTypeOf(new Info()))
  val pcReg      = RegInit(0.U(XLEN.W))

  when(io.executeStage.data.info.valid) {
    srcInfoReg := io.executeStage.data.src_info
  }

  when(io.executeStage.data.info.valid) {
    infoReg       := io.executeStage.data.info
    infoReg.valid := true.B
  }
  when(io.executeStage.data.info.valid) {
    pcReg := io.executeStage.data.pc
  }
  /*
  val srcinfo = Mux(io.executeStage.data.info.valid, io.executeStage.data.src_info, srcInfoReg)
  val info    = Mux(io.executeStage.data.info.valid, io.executeStage.data.info, infoReg)
  val pc      = Mux(io.executeStage.data.info.valid, io.executeStage.data.pc, pcReg)
   */
  val srcinfo = Mux(infoReg.valid, srcInfoReg, io.executeStage.data.src_info)
  val info    = Mux(infoReg.valid, infoReg, io.executeStage.data.info)
  val pc      = Mux(infoReg.valid, pcReg, io.executeStage.data.pc)
  when(fu.io.data.valid === true.B) {
    fu.io.data.info.valid := false.B
    infoReg               := 0.U.asTypeOf(new Info())
  }

  fu.io.dcache        <> io.dcache
  fu.io.data.pc       := pc
  fu.io.data.info     := info
  fu.io.data.src_info := srcinfo

  io.branch                        := fu.io.data.branch
  io.target                        := fu.io.data.target
  io.ready                         := fu.io.data.ready
  io.memoryStage.data.pc           := pc
  io.memoryStage.data.info         := info
  io.memoryStage.data.info.valid   := fu.io.data.valid
  io.memoryStage.data.info.diffout := fu.io.data.diffout
  io.memoryStage.data.src_info     := srcinfo
  io.memoryStage.data.rd_info      := fu.io.data.rd_info
}
