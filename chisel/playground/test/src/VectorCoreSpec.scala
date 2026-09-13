package cpu

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

class VectorCoreSpec extends AnyFlatSpec with ChiselScalatestTester {
  private def pokeLanes(v: Vec[UInt], xs: Seq[Long]): Unit = xs.zipWithIndex.foreach { case (x, i) => v(i).poke(x.U) }
  private def readLanes(v: Vec[UInt]): Seq[BigInt] = (0 until 4).map(i => v(i).peek().litValue)

  it should "implement vector arithmetic, permute operations, and writable v0" in {
    test(new VectorCore) { dut =>
      dut.io.issue.valid.poke(false.B)
      dut.io.testWriteEnable.poke(true.B)
      dut.io.testWriteAddr.poke(0.U); pokeLanes(dut.io.testWriteData, Seq(1, 2, 3, 4)); dut.clock.step()
      dut.io.testWriteAddr.poke(1.U); pokeLanes(dut.io.testWriteData, Seq(0xffffffffL, 2, 3, 4)); dut.clock.step()
      dut.io.testWriteAddr.poke(2.U); pokeLanes(dut.io.testWriteData, Seq(5, 6, 7, 8)); dut.clock.step()
      dut.io.testWriteEnable.poke(false.B)

      def issue(vd: Int, op: Int, a: Int, b: Int, sh: Int = 0): Unit = {
        dut.io.vs1.poke(a.U); dut.io.vs2.poke(b.U); dut.io.shamt.poke(sh.U); dut.io.op.poke(op.U)
        dut.io.issue.bits.poke(vd.U); dut.io.issue.valid.poke(true.B)
        dut.io.issue.ready.expect(true.B); dut.clock.step(); dut.io.issue.valid.poke(false.B)
      }
      issue(3, 0, 1, 2)
      dut.io.testReadAddr.poke(3.U); assert(readLanes(dut.io.testReadData) == Seq(BigInt("4",16), 8, 10, 12))
      issue(4, 1, 1, 2)
      dut.io.testReadAddr.poke(4.U); assert(readLanes(dut.io.testReadData) == Seq(BigInt("fffffffb",16), 12, 21, 32))
      issue(5, 2, 1, 0, 2)
      dut.io.testReadAddr.poke(5.U); assert(readLanes(dut.io.testReadData) == Seq(0, 0, BigInt("ffffffff",16), 2))
      issue(6, 3, 1, 2)
      dut.io.testReadAddr.poke(6.U); assert(readLanes(dut.io.testReadData) == Seq(2, 3, 4, BigInt("ffffffff",16)))
    }
  }
}
