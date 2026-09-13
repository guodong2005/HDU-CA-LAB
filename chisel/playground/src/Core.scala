package cpu

import chisel3._
import chisel3.util._
import cpu.defines._

/** In-order scalar RV32IM pipeline.  AXI has one globally owned transaction. */
class Core extends Module {
  val io = IO(new Bundle {
    val axi = new AxiMaster
    val debug_commit = Output(Bool()); val debug_pc = Output(UInt(32.W)); val debug_instr = Output(UInt(32.W))
    val debug_rd = Output(UInt(5.W)); val debug_wdata = Output(UInt(32.W)); val debug_wen = Output(Bool()); val debug_illegal = Output(Bool())
    val halted = Output(Bool())
  })

  val regs = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))
  val pc = RegInit("h80000000".U(32.W))
  val ifid = RegInit(0.U.asTypeOf(new IfIdPayload))
  val idex = RegInit(0.U.asTypeOf(new IdExPayload))
  val exmem = RegInit(0.U.asTypeOf(new ExMemPayload))
  val memwb = RegInit(0.U.asTypeOf(new MemWbPayload))

  val fReq :: fWait :: mReadReq :: mReadWait :: mAw :: mW :: mB :: Nil = Enum(7)
  val owner = RegInit(fReq)
  val memAddr = Reg(UInt(32.W)); val memData = Reg(UInt(32.W)); val memStrb = Reg(UInt(4.W))
  val memRd = Reg(UInt(5.W)); val memPc = Reg(UInt(32.W)); val memInstr = Reg(UInt(32.W))
  val memSize = Reg(UInt(2.W)); val memSigned = Reg(Bool()); val memIsLoad = Reg(Bool())
  val draining = RegInit(false.B); val halted = RegInit(false.B); val illegalSeen = RegInit(false.B)

  def regRead(r: UInt): UInt = Mux(r === 0.U, 0.U, regs(r))
  val idOpcode = ifid.instr(6,0); val idFunct3 = ifid.instr(14,12); val idFunct7 = ifid.instr(31,25)
  val idRs1 = ifid.instr(19,15); val idRs2 = ifid.instr(24,20); val idRd = ifid.instr(11,7)
  val iimm = Cat(Fill(20, ifid.instr(31)), ifid.instr(31,20))
  val simm = Cat(Fill(20, ifid.instr(31)), ifid.instr(31,25), ifid.instr(11,7))
  val bimm = Cat(Fill(19, ifid.instr(31)), ifid.instr(31), ifid.instr(7), ifid.instr(30,25), ifid.instr(11,8), 0.U)
  val uimm = Cat(ifid.instr(31,12), 0.U(12.W))
  val jimm = Cat(Fill(11, ifid.instr(31)), ifid.instr(31), ifid.instr(19,12), ifid.instr(20), ifid.instr(30,21), 0.U)
  val idCtrl = WireDefault(0.U.asTypeOf(new ScalarControl))
  val idImm = WireDefault(0.U(32.W))
  val idKnownOpcode = idOpcode === "b0110111".U || idOpcode === "b0010111".U || idOpcode === "b0010011".U || idOpcode === "b0110011".U || idOpcode === "b0000011".U || idOpcode === "b0100011".U || idOpcode === "b1100011".U || idOpcode === "b1101111".U || idOpcode === "b1100111".U || idOpcode === "b0001111".U || idOpcode === "b1110011".U
  val idLegalFunct = Mux(idOpcode === "b0001111".U, idFunct3===0.U || idFunct3===1.U, Mux(idOpcode === "b1110011".U, ifid.instr === "h00100073".U, Mux(idOpcode === "b0010011".U, idFunct3 <= 7.U && (idFunct3 =/= 1.U || idFunct7 === 0.U) && (idFunct3 =/= 5.U || idFunct7 === 0.U || idFunct7 === 32.U), Mux(idOpcode === "b0110011".U, (idFunct7 === 0.U || idFunct7 === 32.U || idFunct7 === 1.U) && (idFunct7 =/= 1.U || idFunct3 <= 7.U), Mux(idOpcode === "b0000011".U, idFunct3===0.U||idFunct3===1.U||idFunct3===2.U||idFunct3===4.U||idFunct3===5.U, Mux(idOpcode === "b0100011".U, idFunct3<=2.U, Mux(idOpcode === "b1100011".U, idFunct3===0.U||idFunct3===1.U||idFunct3===4.U||idFunct3===5.U||idFunct3===6.U||idFunct3===7.U, Mux(idOpcode === "b1100111".U, idFunct3===0.U, true.B))))))))
  val idIllegal = ifid.valid && (!idKnownOpcode || !idLegalFunct)
  idCtrl.illegal := idIllegal
  val idUsesRs1 = idOpcode === "b0010011".U || idOpcode === "b0110011".U || idOpcode === "b0000011".U || idOpcode === "b0100011".U || idOpcode === "b1100011".U || idOpcode === "b1100111".U
  val idUsesRs2 = idOpcode === "b0110011".U || idOpcode === "b0100011".U || idOpcode === "b1100011".U
  switch(idOpcode) {
    is("b0110111".U) { idCtrl.regWrite:=true.B; idCtrl.writeUpperImmediate:=true.B; idImm:=uimm }
    is("b0010111".U) { idCtrl.regWrite:=true.B; idCtrl.writePcRelative:=true.B; idCtrl.aluSrcImmediate:=true.B; idImm:=uimm }
    is("b0010011".U) { idCtrl.regWrite:=true.B; idCtrl.aluSrcImmediate:=true.B; idImm:=iimm }
    is("b0110011".U) { idCtrl.regWrite:=true.B; idCtrl.aluOp:=Mux(idFunct7 === 1.U, 5.U, 4.U) }
    is("b0000011".U) { idCtrl.regWrite:=true.B; idCtrl.memRead:=true.B; idCtrl.memToReg:=true.B; idCtrl.aluSrcImmediate:=true.B; idCtrl.loadSize:=Mux(idFunct3===0.U||idFunct3===4.U,0.U,Mux(idFunct3===1.U||idFunct3===5.U,1.U,2.U)); idCtrl.loadSigned:=idFunct3=/=4.U&&idFunct3=/=5.U; idImm:=iimm }
    is("b0100011".U) { idCtrl.memWrite:=true.B; idCtrl.aluSrcImmediate:=true.B; idCtrl.storeSize:=Mux(idFunct3===0.U,0.U,Mux(idFunct3===1.U,1.U,2.U)); idImm:=simm }
    is("b1100011".U) { idCtrl.branch:=true.B; idCtrl.branchFunct3:=idFunct3; idImm:=bimm }
    is("b1101111".U) { idCtrl.regWrite:=true.B; idCtrl.jump:=true.B; idCtrl.writeLink:=true.B; idImm:=jimm }
    is("b1100111".U) { idCtrl.regWrite:=true.B; idCtrl.jump:=true.B; idCtrl.aluSrcImmediate:=true.B; idCtrl.writeLink:=true.B; idImm:=iimm }
  }
  val loadUse = ifid.valid && idex.valid && idex.control.memRead && idex.rd =/= 0.U && ((idUsesRs1 && idex.rd===idRs1) || (idUsesRs2 && idex.rd===idRs2))
  val hazardStall = loadUse
  val wbValue = Mux(memwb.control.memToReg, memwb.loadData, memwb.aluResult)
  val exRs1 = Mux(idex.rs1===0.U,0.U,Mux(exmem.valid && exmem.control.regWrite && !exmem.control.memRead && exmem.rd===idex.rs1,exmem.aluResult,Mux(memwb.valid&&memwb.control.regWrite&&memwb.rd===idex.rs1,Mux(memwb.control.memToReg,memwb.loadData,memwb.aluResult),idex.rs1Data)))
  val exRs2 = Mux(idex.rs2===0.U,0.U,Mux(exmem.valid && exmem.control.regWrite && !exmem.control.memRead && exmem.rd===idex.rs2,exmem.aluResult,Mux(memwb.valid&&memwb.control.regWrite&&memwb.rd===idex.rs2,Mux(memwb.control.memToReg,memwb.loadData,memwb.aluResult),idex.rs2Data)))
  val exOp2 = Mux(idex.control.aluSrcImmediate,idex.immediate,exRs2)
  val exResult = WireDefault(0.U(32.W))
  val absRs1 = Mux(exRs1(31), 0.U-exRs1, exRs1)
  val absRs2 = Mux(exRs2(31), 0.U-exRs2, exRs2)
  val signedDiv = Mux(exRs2===0.U,"hffffffff".U,Mux(exRs1==="h80000000".U&&exRs2==="hffffffff".U,"h80000000".U,Mux(exRs1(31)^exRs2(31),0.U-(absRs1/absRs2),absRs1/absRs2)))
  val mulUU = exRs1 * exRs2
  val mulAbs = absRs1 * absRs2
  val mulSS = Mux(exRs1(31)^exRs2(31), 0.U-mulAbs, mulAbs)
  val mulSU = Mux(exRs1(31), 0.U-(absRs1*exRs2), absRs1*exRs2)
  when(idex.control.memRead || idex.control.memWrite){exResult:=exRs1+idex.immediate}.elsewhen(idex.control.writeUpperImmediate){exResult:=idex.immediate}.elsewhen(idex.control.writePcRelative){exResult:=idex.pc+idex.immediate}.elsewhen(idex.control.jump){exResult:=idex.pc+4.U}.elsewhen(idex.control.aluOp===5.U){
    switch(idex.instr(14,12)){
      is(0.U){exResult:=mulUU(31,0)}
      is(1.U){exResult:=mulSS(63,32)}
      is(2.U){exResult:=mulSU(63,32)}
      is(3.U){exResult:=mulUU(63,32)}
      is(4.U){exResult:=signedDiv}
      is(5.U){exResult:=Mux(exRs2===0.U,"hffffffff".U,exRs1/exRs2)}
      is(6.U){exResult:=Mux(exRs2===0.U,exRs1,Mux(exRs1==="h80000000".U&&exRs2==="hffffffff".U,0.U,Mux(exRs1(31),0.U-((absRs1%absRs2)),absRs1%absRs2)))}
      is(7.U){exResult:=Mux(exRs2===0.U,exRs1,exRs1-(exRs1/exRs2)*exRs2)}
    }
  }.otherwise{
    switch(idex.instr(14,12)){is(0.U){exResult:=Mux(idex.instr(6,0)==="b0110011".U&&idex.instr(30),exRs1-exOp2,exRs1+exOp2)};is(1.U){exResult:=exRs1<<exOp2(4,0)};is(2.U){exResult:=(exRs1.asSInt<exOp2.asSInt).asUInt};is(3.U){exResult:=(exRs1<exOp2).asUInt};is(4.U){exResult:=exRs1^exOp2};is(5.U){exResult:=Mux(idex.instr(30),(exRs1.asSInt>>exOp2(4,0)).asUInt,exRs1>>exOp2(4,0))};is(6.U){exResult:=exRs1|exOp2};is(7.U){exResult:=exRs1&exOp2}}
  }

  val d1 = Mux(exmem.valid && exmem.control.regWrite && !exmem.control.memRead && exmem.rd =/= 0.U && exmem.rd === idRs1, exmem.aluResult,
    Mux(memwb.valid && memwb.control.regWrite && memwb.rd =/= 0.U && memwb.rd === idRs1, wbValue, regRead(idRs1)))
  val d2 = Mux(exmem.valid && exmem.control.regWrite && !exmem.control.memRead && exmem.rd =/= 0.U && exmem.rd === idRs2, exmem.aluResult,
    Mux(memwb.valid && memwb.control.regWrite && memwb.rd =/= 0.U && memwb.rd === idRs2, wbValue, regRead(idRs2)))
  val cond = MuxLookup(idex.instr(14,12), false.B)(Seq(0.U -> (exRs1===exRs2), 1.U -> (exRs1=/=exRs2), 4.U -> (exRs1.asSInt < exRs2.asSInt), 5.U -> (exRs1.asSInt >= exRs2.asSInt), 6.U -> (exRs1<exRs2), 7.U -> (exRs1>=exRs2)))
  val taken = idex.valid && (idex.control.jump || (idex.control.branch && cond))
  val target = Mux(idex.control.jump && idex.instr(6,0)==="b1100111".U,(exRs1+idex.immediate)&"hfffffffe".U,idex.pc+idex.immediate)
  val memoryBusy = owner =/= fReq || exmem.valid && (exmem.control.memRead||exmem.control.memWrite)
  val canPipe = !halted && !memoryBusy && !draining
  val launchMem = canPipe && idex.valid && (idex.control.memRead || idex.control.memWrite)

  io.axi.ar.valid := owner===mReadReq || (owner===fReq && canPipe && !launchMem && !taken); io.axi.ar.bits:=0.U.asTypeOf(new AxiAR); io.axi.ar.bits.addr:=Mux(owner===mReadReq,memAddr&"hfffffffc".U,pc); io.axi.ar.bits.id:=0.U; io.axi.ar.bits.size:=2.U
  io.axi.r.ready := owner===fWait || owner===mReadWait
  io.axi.aw.valid := owner===mAw; io.axi.aw.bits:=0.U.asTypeOf(new AxiAW); io.axi.aw.bits.addr:=memAddr&"hfffffffc".U; io.axi.aw.bits.id:=1.U; io.axi.aw.bits.size:=2.U
  io.axi.w.valid := owner===mW; io.axi.w.bits:=0.U.asTypeOf(new AxiW); io.axi.w.bits.data:=memData; io.axi.w.bits.strb:=memStrb; io.axi.w.bits.id:=1.U; io.axi.w.bits.last:=true.B
  io.axi.b.ready:=owner===mB
  io.debug_commit:=false.B; io.debug_pc:=0.U; io.debug_instr:=0.U; io.debug_rd:=0.U; io.debug_wdata:=0.U; io.debug_wen:=false.B; io.halted:=halted; io.debug_illegal:=illegalSeen

  when(memwb.valid){when(memwb.control.regWrite&&memwb.rd=/=0.U){regs(memwb.rd):=Mux(memwb.control.memToReg,memwb.loadData,memwb.aluResult)};io.debug_commit:=true.B;io.debug_pc:=memwb.pc;io.debug_instr:=memwb.instr;io.debug_rd:=memwb.rd;io.debug_wdata:=Mux(memwb.control.memToReg,memwb.loadData,memwb.aluResult);io.debug_wen:=memwb.control.regWrite&&memwb.rd=/=0.U}
  memwb.valid:=false.B
  when(owner===fReq&&io.axi.ar.fire){owner:=fWait}
  val fetchResponse = owner === fWait && io.axi.r.fire
  when(fetchResponse){when(io.axi.r.bits.id===0.U&&io.axi.r.bits.resp===0.U&&io.axi.r.bits.last){when(!draining){ifid.valid:=true.B;ifid.pc:=pc;ifid.instr:=io.axi.r.bits.data;pc:=pc+4.U}}.otherwise{illegalSeen:=true.B;draining:=true.B};owner:=fReq}
  when(owner===mReadReq&&io.axi.ar.fire){owner:=mReadWait}
  when(owner===mReadWait&&io.axi.r.fire){when(io.axi.r.bits.id===0.U&&io.axi.r.bits.resp===0.U&&io.axi.r.bits.last){val word=io.axi.r.bits.data;val byte=MuxLookup(memAddr(1,0),word(7,0))(Seq(1.U->word(15,8),2.U->word(23,16),3.U->word(31,24)));val half=Mux(memAddr(1),word(31,16),word(15,0));val v=Mux(memSize===0.U,Cat(Fill(24,byte(7)&&memSigned),byte),Mux(memSize===1.U,Cat(Fill(16,half(15)&&memSigned),half),word));memwb.valid:=true.B;memwb.pc:=memPc;memwb.instr:=memInstr;memwb.rd:=memRd;memwb.loadData:=v;memwb.control:=0.U.asTypeOf(new ScalarControl);memwb.control.regWrite:=memRd=/=0.U;memwb.control.memToReg:=true.B;exmem.valid:=false.B;owner:=fReq}.otherwise{illegalSeen:=true.B;draining:=true.B;owner:=fReq}}
  when(owner===mAw&&io.axi.aw.fire){owner:=mW}; when(owner===mW&&io.axi.w.fire){owner:=mB}; when(owner===mB&&io.axi.b.fire){when(io.axi.b.bits.id===1.U&&io.axi.b.bits.resp===0.U){memwb.valid:=true.B;memwb.pc:=memPc;memwb.instr:=memInstr;memwb.control:=0.U.asTypeOf(new ScalarControl);exmem.valid:=false.B}.otherwise{illegalSeen:=true.B;draining:=true.B};owner:=fReq}

  when(canPipe){
    when(exmem.valid && !exmem.control.memRead && !exmem.control.memWrite){
      memwb.valid:=true.B; memwb.pc:=exmem.pc; memwb.instr:=exmem.instr; memwb.rd:=exmem.rd
      memwb.aluResult:=exmem.aluResult; memwb.loadData:=0.U; memwb.control:=exmem.control
    }
    when(!idex.valid){exmem.valid:=false.B}
    when(launchMem){idex.valid:=false.B}.elsewhen(hazardStall){idex.valid:=false.B}.elsewhen(taken){pc:=target; ifid.valid:=false.B; idex.valid:=false.B}.otherwise{ idex.valid:=ifid.valid;idex.pc:=ifid.pc;idex.instr:=ifid.instr;idex.rs1:=idRs1;idex.rs2:=idRs2;idex.rd:=idRd;idex.rs1Data:=d1;idex.rs2Data:=d2;idex.immediate:=idImm;idex.control:=idCtrl; when(!fetchResponse){ifid.valid:=false.B} }
    when(idex.valid && !idex.control.illegal && idex.instr =/= "h00100073".U){exmem.valid:=true.B;exmem.pc:=idex.pc;exmem.instr:=idex.instr;exmem.rd:=idex.rd;exmem.aluResult:=exResult;exmem.storeData:=exRs2;exmem.control:=idex.control;when(idex.control.memRead||idex.control.memWrite){memAddr:=exResult;memData:=exRs2 << (exResult(1,0) * 8.U);memPc:=idex.pc;memInstr:=idex.instr;memRd:=idex.rd;memSize:=Mux(idex.control.memRead,idex.control.loadSize,idex.control.storeSize);memSigned:=idex.control.loadSigned;memStrb:=Mux(idex.control.storeSize===0.U,1.U<<exResult(1,0),Mux(idex.control.storeSize===1.U,3.U<<Cat(exResult(1),0.U),15.U));owner:=Mux(idex.control.memRead,mReadReq,mAw)}}
  }
  when(idex.valid&&idex.control.illegal){printf(p"ILLEGAL instruction ${Hexadecimal(idex.instr)} at ${Hexadecimal(idex.pc)}\n");illegalSeen:=true.B;pc:=idex.pc;draining:=true.B;idex.valid:=false.B;ifid.valid:=false.B}
  when(idex.valid&&idex.instr==="h00100073".U){pc:=idex.pc;draining:=true.B;idex.valid:=false.B; ifid.valid:=false.B}
  when(draining && exmem.valid && !exmem.control.memRead && !exmem.control.memWrite){memwb.valid:=true.B;memwb.pc:=exmem.pc;memwb.instr:=exmem.instr;memwb.rd:=exmem.rd;memwb.aluResult:=exmem.aluResult;memwb.loadData:=0.U;memwb.control:=exmem.control;exmem.valid:=false.B}
  when(draining && !exmem.valid && !memwb.valid && owner===fReq){halted:=true.B}
}
