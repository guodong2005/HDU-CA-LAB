package cpu

import chisel3._
import chisel3.util._
import cpu.defines._

/**
  * Instruction-fetch stage for the classic in-order pipeline.
  * It permits one outstanding AXI read and holds the response until ID accepts it.
  */
class InstructionFetch extends Module {
  val io = IO(new Bundle {
    val axi = new AxiMaster
    val redirect = Flipped(Valid(UInt(32.W)))
    val out = Decoupled(new IfIdPayload)
  })

  val pc = RegInit(cpu.defines.Const.ResetPc.U(32.W))
  val requestPending = RegInit(false.B)
  val responseValid = RegInit(false.B)
  val responsePc = Reg(UInt(32.W))
  val responseInstr = Reg(UInt(32.W))

  io.axi.ar.valid := !requestPending && !responseValid
  io.axi.ar.bits := 0.U.asTypeOf(new AxiAR)
  io.axi.ar.bits.id := 0.U
  io.axi.ar.bits.addr := pc
  io.axi.ar.bits.len := 0.U
  io.axi.ar.bits.size := 2.U
  io.axi.ar.bits.burst := 1.U
  io.axi.ar.bits.prot := 0.U
  io.axi.r.ready := requestPending && !responseValid

  io.axi.aw.valid := false.B
  io.axi.aw.bits := 0.U.asTypeOf(new AxiAW)
  io.axi.w.valid := false.B
  io.axi.w.bits := 0.U.asTypeOf(new AxiW)
  io.axi.b.ready := false.B

  io.out.valid := responseValid
  io.out.bits.valid := responseValid
  io.out.bits.pc := responsePc
  io.out.bits.instr := responseInstr

  when(io.redirect.valid) {
    pc := io.redirect.bits
    requestPending := false.B
    responseValid := false.B
  }.otherwise {
    when(io.axi.ar.fire) {
      requestPending := true.B
    }
    when(io.axi.r.fire) {
      requestPending := false.B
      responseValid := true.B
      responsePc := pc
      responseInstr := io.axi.r.bits.data
    }
    when(io.out.fire) {
      responseValid := false.B
      pc := responsePc + 4.U
    }
  }
}
