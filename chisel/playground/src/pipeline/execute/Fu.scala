package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class Fu extends Module with HasInstrType{
  val io = IO(new Bundle {
    val data = new Bundle {
      val pc       = Input(UInt(XLEN.W))
      val info     = Input(new Info())
      val src_info = Input(new SrcInfo())
      val rd_info  = Output(new RdInfo())
    }

    val dataSram = new DataSram()
  })

  val alu = Module(new Alu())
  val mdu = Module(new Mdu())
  val lsu = Module(new Lsu())

  io.dataSram.en    := false.B
  io.dataSram.addr  := DontCare
  io.dataSram.wdata := DontCare
  io.dataSram.wen   := 0.U

  alu.io.info     := io.data.info
  alu.io.src_info := io.data.src_info

  mdu.io.info := io.data.info
  mdu.io.src_info := io.data.src_info

  lsu.io.info := io.data.info
  lsu.io.src_info := io.data.src_info
  lsu.io.dataSram <> io.dataSram // same as := ? not, but I should have a deeper understanding !
  val result = LookupTree(
    io.data.info.fusel,
    Seq(
      FuType.alu -> alu.io.result,
      FuType.mdu -> mdu.io.result,
      FuType.lsu -> lsu.io.result
    )
  ) 
printf(p"info.fusel: ${io.data.info.fusel}, lsu.io.result: ${lsu.io.result}\n")

  io.data.rd_info.wdata := Mux(io.data.info.fusel === FuType.alu,alu.io.result,mdu.io.result) // lsu doesnt matter
  io.data.rd_info.addr3 := Mux(io.data.info.fusel === FuType.lsu,lsu.io.addr3,0.U)
}
