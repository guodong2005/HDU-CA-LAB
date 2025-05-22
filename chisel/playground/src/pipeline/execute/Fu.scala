package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class Fu extends Module with HasInstrType {
  val io = IO(new Bundle {
    val data = new Bundle {
      val pc       = Input(UInt(XLEN.W))
      val info     = Input(new Info())
      val src_info = Input(new SrcInfo())
      val rd_info  = Output(new RdInfo())
      val branch   = Bool()
      val diffout  = Output(new DiffOut())
      val target   = UInt(XLEN.W)
      val ready    = Output(Bool())
      val valid    = Output(Bool())
    }
    val dcache = new Bundle {
      val req  = (Decoupled(new DCacheReq))
      val resp = Flipped(Decoupled(new DCacheResp))
    }
  })
  val dataReg = RegInit(0.U.asTypeOf(io.data))

  when(io.data.info.valid === true.B) {
    dataReg := io.data
  }


  val alu = Module(new Alu())
  val mdu = Module(new Mdu())
  val lsu = Module(new Lsu())
  val bru = Module(new Bru())

  lsu.io.dcache   <> io.dcache
  alu.io.info     := data.info
  alu.io.src_info := data.src_info

  mdu.io.info     := data.info
  mdu.io.src_info := data.src_info

  lsu.io.info     := data.info
  lsu.io.src_info := data.src_info

  bru.io.info     := data.info
  bru.io.src_info := data.src_info
  bru.io.pc       := data.pc

  val fuselReg = RegInit(0.U.asTypeOf(new Info()))
  when(io.data.info.valid) {
    fuselReg := io.data.info
  }
  val fusel = Mux(io.data.info.valid, io.data.info.fusel, fuselReg.fusel)
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
  when(io.data.info.valid === false.B) {
    io.data := dataReg
  }
  io.data.rd_info.wdata := result
  io.data.diffout       := lsu.io.diffout

  io.data.branch := bru.io.branch
  io.data.target := bru.io.target
  io.data.ready  := lsu.io.ready
  io.data.valid  := valid

}
