package cpu

import chisel3._
import chisel3.util._
import cpu.defines._

/**
  * Small RV32IM core with one architectural transaction at a time.
  * Every memory operation is held until its AXI response is accepted.
  * There are no implicit SRAM delays or shared valid flags.
  */
class Core extends Module {
  val io = IO(new Bundle {
    val axi = new AxiMaster
    val debug_commit = Output(Bool())
    val debug_pc = Output(UInt(32.W))
    val debug_instr = Output(UInt(32.W))
    val debug_rd = Output(UInt(5.W))
    val debug_wdata = Output(UInt(32.W))
    val debug_wen = Output(Bool())
    val halted = Output(Bool())
  })

  val regs = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))
  val pc = RegInit(0x80000000L.U(32.W))
  val instr = RegInit(0.U(32.W))
  val memAddr = Reg(UInt(32.W)); val memWdata = Reg(UInt(32.W)); val memStrb = Reg(UInt(4.W))
  val memRd = Reg(UInt(5.W)); val memLoadSigned = Reg(Bool()); val memLoadSize = Reg(UInt(2.W))
  val memIsLoad = Reg(Bool())
  val nextPc = Reg(UInt(32.W))
  val state = RegInit(0.U(4.W))
  val sFetch :: sFetchR :: sExec :: sLoadAr :: sLoadR :: sStoreAw :: sStoreW :: sStoreB :: sHalt :: Nil = Enum(9)
  val commitValid = RegInit(false.B); val commitPc = RegInit(0.U(32.W)); val commitInstr = RegInit(0.U(32.W))
  val commitRd = RegInit(0.U(5.W)); val commitData = RegInit(0.U(32.W)); val commitWen = RegInit(false.B)

  val rd = instr(11, 7); val rs1 = instr(19, 15); val rs2 = instr(24, 20)
  val r1 = Mux(rs1 === 0.U, 0.U, regs(rs1)); val r2 = Mux(rs2 === 0.U, 0.U, regs(rs2))
  val iimm = Cat(Fill(20, instr(31)), instr(31, 20))
  val simm = Cat(Fill(20, instr(31)), instr(31, 25), instr(11, 7))
  val bimm = Cat(Fill(19, instr(31)), instr(31), instr(7), instr(30, 25), instr(11, 8), 0.U(1.W))
  val uimm = Cat(instr(31, 12), 0.U(12.W))
  val jimm = Cat(Fill(11, instr(31)), instr(31), instr(19, 12), instr(20), instr(30, 21), 0.U(1.W))
  val opcode = instr(6, 0); val funct3 = instr(14, 12); val funct7 = instr(31, 25)
  val alu = WireDefault(0.U(32.W)); val branchTaken = WireDefault(false.B)
  val writeEnable = WireDefault(false.B); val writeData = WireDefault(0.U(32.W))
  val isLoad = opcode === "b0000011".U; val isStore = opcode === "b0100011".U

  switch(opcode) {
    is("b0110111".U) { alu := uimm; writeEnable := true.B; writeData := alu }
    is("b0010111".U) { alu := pc + uimm; writeEnable := true.B; writeData := alu }
    is("b0010011".U) {
      writeEnable := true.B
      switch(funct3) {
        is("b000".U) { writeData := r1 + iimm }
        is("b010".U) { writeData := (r1.asSInt < iimm.asSInt).asUInt }
        is("b011".U) { writeData := (r1 < iimm).asUInt }
        is("b100".U) { writeData := r1 ^ iimm }
        is("b110".U) { writeData := r1 | iimm }
        is("b111".U) { writeData := r1 & iimm }
        is("b001".U) { writeData := r1 << instr(24, 20) }
        is("b101".U) { writeData := Mux(instr(30), (r1.asSInt >> instr(24, 20)).asUInt, r1 >> instr(24, 20)) }
      }
    }
    is("b0110011".U) {
      writeEnable := true.B
      when(funct7 === "b0000001".U) {
        switch(funct3) {
          is("b000".U) { writeData := (r1 * r2)(31, 0) }
          is("b100".U) { writeData := Mux(r2 === 0.U, "hffffffff".U, (r1.asSInt / r2.asSInt).asUInt) }
          is("b110".U) { writeData := Mux(r2 === 0.U, r1, (r1.asSInt % r2.asSInt).asUInt) }
          is("b101".U) { writeData := Mux(r2 === 0.U, "hffffffff".U, r1 / r2) }
          is("b111".U) { writeData := Mux(r2 === 0.U, r1, r1 % r2) }
        }
      }.otherwise {
        switch(funct3) {
          is("b000".U) { writeData := Mux(instr(30), r1 - r2, r1 + r2) }
          is("b001".U) { writeData := r1 << r2(4, 0) }
          is("b010".U) { writeData := (r1.asSInt < r2.asSInt).asUInt }
          is("b011".U) { writeData := (r1 < r2).asUInt }
          is("b100".U) { writeData := r1 ^ r2 }
          is("b101".U) { writeData := Mux(instr(30), (r1.asSInt >> r2(4, 0)).asUInt, r1 >> r2(4, 0)) }
          is("b110".U) { writeData := r1 | r2 }
          is("b111".U) { writeData := r1 & r2 }
        }
      }
    }
    is("b1101111".U) { writeEnable := true.B; writeData := pc + 4.U; branchTaken := true.B }
    is("b1100111".U) { writeEnable := true.B; writeData := pc + 4.U; branchTaken := true.B }
    is("b1100011".U) {
      when(funct3 === 0.U) { branchTaken := r1 === r2 }
      when(funct3 === 1.U) { branchTaken := r1 =/= r2 }
      when(funct3 === 4.U) { branchTaken := r1.asSInt < r2.asSInt }
      when(funct3 === 5.U) { branchTaken := r1.asSInt >= r2.asSInt }
      when(funct3 === 6.U) { branchTaken := r1 < r2 }
      when(funct3 === 7.U) { branchTaken := r1 >= r2 }
    }
  }

  io.axi.ar.valid := state === sFetch || state === sLoadAr; io.axi.ar.bits := 0.U.asTypeOf(new AxiAR)
  io.axi.ar.bits.addr := Mux(state === sLoadAr, memAddr & "hfffffffc".U, pc); io.axi.ar.bits.id := 0.U; io.axi.ar.bits.size := 2.U; io.axi.ar.bits.prot := 0.U
  io.axi.r.ready := state === sFetchR || state === sLoadR
  io.axi.aw.valid := state === sStoreAw; io.axi.aw.bits := 0.U.asTypeOf(new AxiAW)
  io.axi.aw.bits.addr := memAddr & "hfffffffc".U; io.axi.aw.bits.id := 1.U; io.axi.aw.bits.size := 2.U
  io.axi.w.valid := state === sStoreW; io.axi.w.bits := 0.U.asTypeOf(new AxiW)
  io.axi.w.bits.data := memWdata; io.axi.w.bits.strb := memStrb; io.axi.w.bits.id := 1.U; io.axi.w.bits.last := true.B
  io.axi.b.ready := state === sStoreB
  io.debug_commit := commitValid; io.debug_pc := commitPc; io.debug_instr := commitInstr; io.debug_rd := commitRd; io.debug_wdata := commitData; io.debug_wen := commitWen
  io.halted := state === sHalt

  when(reset.asBool) { state := sFetch; pc := 0x80000000L.U; regs.foreach(_ := 0.U) }
  commitValid := false.B
  when(state === sFetch && io.axi.ar.fire) { state := sFetchR }
  when(state === sFetchR && io.axi.r.fire) { instr := io.axi.r.bits.data; state := sExec }
  when(state === sExec) {
    val fallthrough = pc + 4.U
    val target = Mux(opcode === "b1101111".U, pc + jimm, Mux(opcode === "b1100111".U, (r1 + iimm) & "hfffffffe".U, pc + bimm))
    val effective = r1 + Mux(isStore, simm, iimm)
    when(instr === "h00100073".U) { state := sHalt }.elsewhen(isLoad) {
   nextPc := fallthrough; memAddr := effective; memRd := rd; memLoadSigned := funct3 =/= 4.U && funct3 =/= 5.U; memLoadSize := Mux(funct3 === 0.U || funct3 === 4.U, 0.U, Mux(funct3 === 1.U || funct3 === 5.U, 1.U, 2.U)); memIsLoad := true.B; state := sLoadAr
    }.elsewhen(isStore) {
      memAddr := effective; memWdata := r2 << (effective(1, 0) * 8.U); memStrb := Mux(funct3 === 0.U, 1.U << effective(1, 0), Mux(funct3 === 1.U, 3.U << Cat(effective(1), 0.U(1.W)), 15.U)); state := sStoreAw
    }.otherwise {
      when(writeEnable && rd =/= 0.U) { regs(rd) := writeData; commitWen := true.B; commitRd := rd; commitData := writeData }
      .otherwise { commitWen := false.B; commitRd := 0.U; commitData := 0.U }
      commitValid := true.B; commitPc := pc; commitInstr := instr
      pc := Mux(branchTaken, target, fallthrough); state := sFetch
    }
  }
  when(state === sLoadAr && io.axi.ar.fire) { state := sLoadR }
  when(state === sLoadR && io.axi.r.fire) {
    val shift = memAddr(1, 0) * 8.U; val raw = io.axi.r.bits.data >> shift
    val narrowed = Mux(memLoadSize === 0.U, Cat(Fill(24, raw(7) && memLoadSigned), raw(7, 0)), Mux(memLoadSize === 1.U, Cat(Fill(16, raw(15) && memLoadSigned), raw(15, 0)), raw(31, 0)))
    when(memRd =/= 0.U) { regs(memRd) := narrowed }
    commitValid := true.B; commitPc := pc; commitInstr := instr; commitWen := memRd =/= 0.U; commitRd := memRd; commitData := narrowed; pc := nextPc; state := sFetch
  }
  when(state === sStoreAw && io.axi.aw.fire) { state := sStoreW }
  when(state === sStoreW && io.axi.w.fire) { state := sStoreB }
  when(state === sStoreB && io.axi.b.fire) { commitValid := true.B; commitPc := pc; commitInstr := instr; commitWen := false.B; commitRd := 0.U; commitData := 0.U; pc := pc + 4.U; state := sFetch }
}
