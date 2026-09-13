package cpu

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

class CubeCoreSpec extends AnyFlatSpec with ChiselScalatestTester {
  private def pokeMatrix(m: Vec[Vec[SInt]], xs: Seq[Seq[Int]]): Unit =
    xs.zipWithIndex.foreach { case (row, i) => row.zipWithIndex.foreach { case (x, j) => m(i)(j).poke(x.S) } }

  it should "compute a snapped four by four MMA over sixteen cycles" in {
    test(new CubeCore) { dut =>
      val identity = Seq(Seq(1,0,0,0), Seq(0,1,0,0), Seq(0,0,1,0), Seq(0,0,0,1))
      val a = Seq(Seq(1,2,3,4), Seq(5,6,7,8), Seq(-1,2,-3,4), Seq(2,0,0,1))
      val zero = Seq.fill(4)(Seq.fill(4)(0))
      pokeMatrix(dut.io.A, a); pokeMatrix(dut.io.B, identity); pokeMatrix(dut.io.CIn, zero)
      dut.io.launch.poke(true.B); dut.io.launchReady.expect(true.B); dut.clock.step()
      dut.io.launchReady.expect(false.B); dut.io.busy.expect(true.B)
      pokeMatrix(dut.io.A, zero); pokeMatrix(dut.io.B, zero)
      dut.clock.step(16)
      dut.io.done.expect(true.B); dut.io.busy.expect(false.B)
      for (i <- 0 until 4; j <- 0 until 4) dut.io.COut(i)(j).expect(a(i)(j).S)
      dut.clock.step(); dut.io.done.expect(false.B); dut.io.launchReady.expect(true.B)
    }
  }
}
