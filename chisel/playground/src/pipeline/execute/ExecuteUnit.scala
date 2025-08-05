package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.CpuConfig
import cpu.defines._
import cpu.defines.Const._
import chisel3.util.experimental.BoringUtils

class ExecuteUnit extends Module {
  val io = IO(new Bundle {
    val executeStage   = Input(new DecodeUnitExecuteUnit())
    val writeBackStage = Output(new ExecuteUnitWriteBackUnit()) // 重命名：直接输出到WriteBack阶段
    val ready          = Output(Bool())
    val branch         = Output(Bool())
    val target         = Output(UInt(XLEN.W))
    val dcache = new Bundle {
      val req  = (Decoupled(new DCacheReq))
      val resp = Flipped(Decoupled(new DCacheResp))
    }
    val result = Output(UInt(XLEN.W))
  })

  val fu = Module(new Fu())
  fu.io.dcache        <> io.dcache
  fu.io.data.pc       := io.executeStage.data.pc
  fu.io.data.info     := io.executeStage.data.info
  fu.io.data.src_info := io.executeStage.data.src_info

  io.result := fu.io.data.rd_info.wdata
  io.ready  := fu.io.data.ready
  io.branch := io.branch
  io.target := io.target

  // 直接输出到WriteBack阶段，不再经过Memory阶段
  io.writeBackStage.data.pc           := io.executeStage.data.pc
  io.writeBackStage.data.info         := io.executeStage.data.info
  io.writeBackStage.data.info.valid   := fu.io.data.valid
  io.writeBackStage.data.info.diffout := fu.io.data.diffout
  io.writeBackStage.data.rd_info      := fu.io.data.rd_info
  // 注意：去掉了src_info的赋值，因为ExeWbData中没有src_info字段
}
