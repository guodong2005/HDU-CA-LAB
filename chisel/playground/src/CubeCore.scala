package cpu

import chisel3._
import chisel3.util._

class CubeCore(val elementCycles: Int = 1) extends Module {
  require(elementCycles > 0)
  val io = IO(new Bundle {
    val launch = Input(Bool())
    val launchReady = Output(Bool())
    val busy = Output(Bool())
    val done = Output(Bool())
    val A = Input(Vec(4, Vec(4, SInt(16.W))))
    val B = Input(Vec(4, Vec(4, SInt(16.W))))
    val CIn = Input(Vec(4, Vec(4, SInt(32.W))))
    val COut = Output(Vec(4, Vec(4, SInt(32.W))))
  })

  val idle :: busyState :: doneState :: Nil = Enum(3)
  val state = RegInit(idle)
  val count = RegInit(0.U(4.W))
  val subCountWidth = math.max(1, log2Ceil(elementCycles))
  val subCount = RegInit(0.U(subCountWidth.W))
  val aReg = Reg(Vec(4, Vec(4, SInt(16.W))))
  val bReg = Reg(Vec(4, Vec(4, SInt(16.W))))
  val cReg = Reg(Vec(4, Vec(4, SInt(32.W))))
  val result = RegInit(VecInit(Seq.fill(4)(VecInit(Seq.fill(4)(0.S(32.W))))) )

  io.launchReady := state === idle
  io.busy := state === busyState
  io.done := state === doneState
  io.COut := result

  when (state === idle && io.launch) {
    aReg := io.A
    bReg := io.B
    cReg := io.CIn
    count := 0.U
    subCount := 0.U
    state := busyState
  }
  when (state === busyState) {
    val row = count(3, 2)
    val col = count(1, 0)
    val products = (0 until 4).map(k => aReg(row)(k) * bReg(k)(col))
    val sum = products.reduce((x, y) => x +& y) +& cReg(row)(col)
    result(row)(col) := sum(31, 0).asSInt
    if (elementCycles == 1) {
      when (count === 15.U) { state := doneState }
        .otherwise { count := count + 1.U }
    } else {
      when (subCount === (elementCycles - 1).U) {
        subCount := 0.U
        when (count === 15.U) { state := doneState }
          .otherwise { count := count + 1.U }
      }.otherwise {
        subCount := subCount + 1.U
      }
    }
  }
  when (state === doneState) { state := idle }
}
