package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig

class Fu extends Module {
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

  io.dataSram.en    := false.B
  io.dataSram.addr  := DontCare
  io.dataSram.wdata := DontCare
  io.dataSram.wen   := 0.U

  alu.io.info     := io.data.info
  alu.io.src_info := io.data.src_info

  mdu.io.info := io.data.info
  mdu.io.src_info := io.data.src_info

  io.data.rd_info.wdata := Mux(io.data.info.fusel === 0.U,alu.io.result,mdu.io.result)
}
