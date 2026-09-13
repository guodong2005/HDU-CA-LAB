package cpu

import chisel3._
import chisel3.util._

/** Six independent Cube engines. Launches are assigned oldest-ready first. */
class CubeCluster(val engineCount: Int = 6) extends Module {
  require(engineCount > 0)
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

  val engines = Seq.fill(engineCount)(Module(new CubeCore(elementCycles = 32)))
  val ready = VecInit(engines.map(_.io.launchReady))
  val selected = PriorityEncoderOH(ready)

  io.launchReady := ready.asUInt.orR
  io.busy := engines.map(_.io.busy).reduce(_ || _)
  io.done := engines.map(_.io.done).reduce(_ || _)

  for ((engine, i) <- engines.zipWithIndex) {
    engine.io.launch := io.launch && selected(i)
    engine.io.A := io.A
    engine.io.B := io.B
    engine.io.CIn := io.CIn
  }

  // The current teaching interface has no result index. Preserve the first
  // engine's stable result port; integration does not consume Cube results.
  io.COut := engines.head.io.COut
}
