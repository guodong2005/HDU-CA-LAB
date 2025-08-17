package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig
import scala.collection.generic.IdleSignalling

class Fu extends Module with HasInstrType {
  val io = IO(new Bundle {
    val data = new Bundle {
      val pc       = Input(UInt(XLEN.W))
      val info     = Input(new Info())
      val src_info = Input(new SrcInfo())
      val rd_info  = Output(new RdInfo())
      val diffout  = Output(new DiffOut())
      val ready    = Output(Bool())
      val valid    = Output(Bool())
      val branch   = Output(Bool())
      val target   = Output(UInt(XLEN.W))
    }
    val dcache = new Bundle {
      val req  = Decoupled(new DCacheReq)
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })

  // 功能单元
  val alu = Module(new Alu())
  val mdu = Module(new Mdu())
  val lsu = Module(new Lsu())
  val bru = Module(new Bru())

  // LSU 和 DCache 连接
  lsu.io.dcache <> io.dcache

  // 信息传递
  alu.io.info     := io.data.info
  alu.io.src_info := io.data.src_info

  mdu.io.info     := io.data.info
  mdu.io.src_info := io.data.src_info

  lsu.io.info     := io.data.info
  lsu.io.src_info := io.data.src_info

  bru.io.info     := io.data.info
  bru.io.src_info := io.data.src_info
  bru.io.pc       := io.data.pc

  // 寄存器记录 info 和 fusel 类型
  val fuselReg = RegInit(0.U.asTypeOf(new Info()))
  when(io.data.info.valid) {
    fuselReg := io.data.info
  }
  val fusel = Mux(io.data.info.valid, io.data.info.fusel, fuselReg.fusel)

  // 有效信号和结果选择
  val valid = LookupTree(
    fusel,
    Seq(
      FuType.alu -> alu.io.valid,
      FuType.mdu -> mdu.io.valid,
      FuType.bru -> bru.io.valid,
      FuType.lsu -> lsu.io.valid
    )
  )

  val result = LookupTree(
    fusel,
    Seq(
      FuType.alu -> alu.io.result,
      FuType.mdu -> mdu.io.result,
      FuType.bru -> bru.io.result,
      FuType.lsu -> lsu.io.result
    )
  )

  // Ready信号选择 - 现在MDU和LSU都可能不ready
  val ready = LookupTree(
    fusel,
    Seq(
      FuType.alu -> true.B,       // ALU总是ready
      FuType.mdu -> mdu.io.ready, // MDU现在有ready信号
      FuType.bru -> true.B,       // BRU总是ready
      FuType.lsu -> lsu.io.ready  // LSU可能不ready
    )
  )

  // 输出赋值
  io.data.branch        := bru.io.branch
  io.data.target        := bru.io.target
  io.data.rd_info.wdata := result
  io.data.diffout       := lsu.io.diffout
  io.data.valid         := Mux(io.data.info.valid, valid, false.B)
  io.data.ready         := ready // 简化ready逻辑，统一处理
}
