package cpu

import chisel3._
import chisel3.util._
import cpu.defines.Const

/** Combinational scalar decoder for the ID stage. */
class Decode extends Module {
  val io = IO(new Bundle {
    val valid = Input(Bool())
    val pc = Input(UInt(Const.Xlen.W))
    val instr = Input(UInt(Const.Xlen.W))
    val rs1Data = Input(UInt(Const.Xlen.W))
    val rs2Data = Input(UInt(Const.Xlen.W))
    val out = Output(new IdExPayload)
  })

  val opcode = io.instr(6, 0)
  val funct3 = io.instr(14, 12)
  val funct7 = io.instr(31, 25)
  val rs1 = io.instr(19, 15)
  val rs2 = io.instr(24, 20)
  val rd = io.instr(11, 7)

  val iImmediate = Cat(Fill(20, io.instr(31)), io.instr(31, 20))
  val sImmediate = Cat(Fill(20, io.instr(31)), io.instr(31, 25), io.instr(11, 7))
  val bImmediate = Cat(Fill(19, io.instr(31)), io.instr(31), io.instr(7), io.instr(30, 25), io.instr(11, 8), 0.U(1.W))
  val uImmediate = Cat(io.instr(31, 12), 0.U(12.W))
  val jImmediate = Cat(Fill(11, io.instr(31)), io.instr(31), io.instr(19, 12), io.instr(20), io.instr(30, 21), 0.U(1.W))

  val control = WireDefault(0.U.asTypeOf(new ScalarControl))
  val immediate = WireDefault(0.U(32.W))

  switch(opcode) {
    is("b0110111".U) { // LUI
      control.regWrite := true.B
      control.aluOp := 1.U
      control.writeUpperImmediate := true.B
      immediate := uImmediate
    }
    is("b0010111".U) { // AUIPC
      control.regWrite := true.B
      control.aluOp := 2.U
      control.aluSrcImmediate := true.B
      control.writePcRelative := true.B
      immediate := uImmediate
    }
    is("b0010011".U) { // immediate arithmetic
      control.regWrite := true.B
      control.aluOp := 3.U
      control.aluSrcImmediate := true.B
      immediate := iImmediate
    }
    is("b0110011".U) { // register arithmetic and M extension
      control.regWrite := true.B
      control.aluOp := Mux(funct7 === "b0000001".U, 5.U, 4.U)
    }
    is("b0000011".U) { // load
      control.regWrite := true.B
      control.memRead := true.B
      control.memToReg := true.B
      control.aluOp := 0.U
      control.aluSrcImmediate := true.B
      control.loadSize := Mux(funct3 === 0.U || funct3 === 4.U, 0.U, Mux(funct3 === 1.U || funct3 === 5.U, 1.U, 2.U))
      control.loadSigned := funct3 =/= 4.U && funct3 =/= 5.U
      immediate := iImmediate
    }
    is("b0100011".U) { // store
      control.memWrite := true.B
      control.aluOp := 0.U
      control.aluSrcImmediate := true.B
      control.storeSize := Mux(funct3 === 0.U, 0.U, Mux(funct3 === 1.U, 1.U, 2.U))
      immediate := sImmediate
    }
    is("b1100011".U) { // conditional branch
      control.branch := true.B
      control.aluOp := 6.U
      control.branchFunct3 := funct3
      immediate := bImmediate
    }
    is("b1101111".U) { // JAL
      control.regWrite := true.B
      control.jump := true.B
      control.aluOp := 7.U
      control.writeLink := true.B
      immediate := jImmediate
    }
    is("b1100111".U) { // JALR
      control.regWrite := true.B
      control.jump := true.B
      control.aluOp := 7.U
      control.aluSrcImmediate := true.B
      control.writeLink := true.B
      immediate := iImmediate
    }
  }

  io.out.valid := io.valid
  io.out.pc := io.pc
  io.out.instr := io.instr
  io.out.rs1 := rs1
  io.out.rs2 := rs2
  io.out.rd := rd
  io.out.rs1Data := io.rs1Data
  io.out.rs2Data := io.rs2Data
  io.out.immediate := immediate
  io.out.control := control
}
