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
      val target   = UInt(XLEN.W)
    }

    val dataSram = new DataSram()
  })

  val alu = Module(new Alu())
  val mdu = Module(new Mdu())
  val lsu = Module(new Lsu())
  val bru = Module(new Bru())

  alu.io.info     := io.data.info
  alu.io.src_info := io.data.src_info

  mdu.io.info     := io.data.info
  mdu.io.src_info := io.data.src_info

  lsu.io.dataSram <> io.dataSram // same as := ? Answer :no, but I should have a deeper understanding !
  lsu.io.info     := io.data.info
  lsu.io.src_info := io.data.src_info

  bru.io.info     := io.data.info
  bru.io.src_info := io.data.src_info
  bru.io.pc       := io.data.pc

  val result = LookupTree(
    io.data.info.fusel,
    Seq(
      FuType.alu -> alu.io.result,
      FuType.mdu -> mdu.io.result,
      FuType.bru -> bru.io.result
      // FuType.lsu -> lsu.io.result
    )
  )
  io.data.rd_info.wdata := result 

  io.data.branch := bru.io.branch
  io.data.target := bru.io.target

  io.data.rd_info.addr3 := lsu.io.addr3
}
