package cpu

import chisel3._

/** Control information carried with an instruction through the pipeline. */
class ScalarControl extends Bundle {
  val regWrite = Bool()
  val memRead = Bool()
  val memWrite = Bool()
  val memToReg = Bool()
  val branch = Bool()
  val jump = Bool()
  val aluOp = UInt(4.W)
  val aluSrcImmediate = Bool()
  val loadSize = UInt(2.W)
  val loadSigned = Bool()
  val storeSize = UInt(2.W)
  val branchFunct3 = UInt(3.W)
  val writeLink = Bool()
  val writeUpperImmediate = Bool()
  val writePcRelative = Bool()
  val illegal = Bool()
  val isVector = Bool()
  val vectorOp = UInt(2.W)
  val isCubeLaunch = Bool()
  val isCubeWait = Bool()
  val customIllegal = Bool()
}

/** IF/ID boundary. */
class IfIdPayload extends Bundle {
  val valid = Bool()
  val pc = UInt(32.W)
  val instr = UInt(32.W)
}

/** ID/EX boundary. */
class IdExPayload extends Bundle {
  val valid = Bool()
  val pc = UInt(32.W)
  val instr = UInt(32.W)
  val rs1 = UInt(5.W)
  val rs2 = UInt(5.W)
  val rd = UInt(5.W)
  val rs1Data = UInt(32.W)
  val rs2Data = UInt(32.W)
  val immediate = UInt(32.W)
  val control = new ScalarControl
}

/** EX/MEM boundary. */
class ExMemPayload extends Bundle {
  val valid = Bool()
  val pc = UInt(32.W)
  val instr = UInt(32.W)
  val rd = UInt(5.W)
  val aluResult = UInt(32.W)
  val storeData = UInt(32.W)
  val branchTarget = UInt(32.W)
  val branchTaken = Bool()
  val control = new ScalarControl
}

/** MEM/WB boundary. */
class MemWbPayload extends Bundle {
  val valid = Bool()
  val pc = UInt(32.W)
  val instr = UInt(32.W)
  val rd = UInt(5.W)
  val aluResult = UInt(32.W)
  val loadData = UInt(32.W)
  val control = new ScalarControl
}