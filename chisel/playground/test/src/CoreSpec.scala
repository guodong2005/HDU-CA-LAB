package cpu

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

class CoreSpec extends AnyFlatSpec with ChiselScalatestTester {
  behavior of "Core"

  it should "retire RAW-dependent instructions once and drain EBREAK" in {
    test(new Core) { dut =>
      val program = Map(
        0x80000000L -> 0x00100093L, // addi x1, x0, 1
        0x80000004L -> 0x00208113L, // addi x2, x1, 2
        0x80000008L -> 0x001101b3L, // add x3, x2, x1
        0x8000000cL -> 0x00100073L  // ebreak
      )
      var pending: Option[Long] = None
      var commits = Vector.empty[(Long, Long)]
      for (_ <- 0 until 80 if !dut.io.halted.peek().litToBoolean) {
        dut.io.axi.ar.ready.poke(true.B)
        dut.io.axi.r.valid.poke(pending.isDefined.B)
        dut.io.axi.r.bits.id.poke(0.U)
        dut.io.axi.r.bits.data.poke(program.getOrElse(pending.getOrElse(0L), 0x00100073L).U)
        dut.io.axi.r.bits.resp.poke(0.U)
        dut.io.axi.r.bits.last.poke(true.B)
        dut.io.axi.aw.ready.poke(true.B)
        dut.io.axi.w.ready.poke(true.B)
        dut.io.axi.b.valid.poke(false.B)
        dut.io.axi.b.bits.id.poke(1.U)
        dut.io.axi.b.bits.resp.poke(0.U)

        val arFire = dut.io.axi.ar.valid.peek().litToBoolean
        val arAddr = dut.io.axi.ar.bits.addr.peek().litValue.toLong
        val rFire = dut.io.axi.r.valid.peek().litToBoolean && dut.io.axi.r.ready.peek().litToBoolean
        dut.clock.step()
        if (dut.io.debug_commit.peek().litToBoolean) {
          commits :+= (dut.io.debug_pc.peek().litValue.toLong, dut.io.debug_instr.peek().litValue.toLong)
        }
        if (arFire) pending = Some(arAddr)
        if (rFire) pending = None
      }
      dut.io.halted.expect(true.B)
      assert(commits == Vector(
        (0x80000000L, 0x00100093L),
        (0x80000004L, 0x00208113L),
        (0x80000008L, 0x001101b3L)
      ))
      assert(!commits.exists(_._2 == 0x00100073L))
      assert(commits.map(_._1) == commits.map(_._1).distinct)
      assert(commits.map(_._1) == Vector(0x80000000L, 0x80000004L, 0x80000008L))
      assert(!commits.exists(_._2 == 0x00100073L))
      assert(commits.lastOption.exists(_._1 == 0x80000008L))
    }
  }

  it should "execute SRAI with sign extension and reject malformed shifts" in {
    test(new Core) { dut =>
      val program = Map(
        0x80000000L -> 0xff000093L, // addi x1, x0, -16
        0x80000004L -> 0x4020d113L, // srai x2, x1, 2 -> -4
        0x80000008L -> 0x800000b7L, // lui x1, 0x80000 -> 0x80000000
        0x8000000cL -> 0x41f0d113L, // srai x2, x1, 31 -> 0xffffffff
        0x80000010L -> 0x00100073L
      )
      var pending: Option[Long] = None
      var writes = Vector.empty[(Long, Long)]
      for (_ <- 0 until 120 if !dut.io.halted.peek().litToBoolean) {
        dut.io.axi.ar.ready.poke(true.B)
        dut.io.axi.r.valid.poke(pending.isDefined.B)
        dut.io.axi.r.bits.id.poke(0.U)
        dut.io.axi.r.bits.data.poke(program.getOrElse(pending.getOrElse(0L), 0x00100073L).U)
        dut.io.axi.r.bits.resp.poke(0.U)
        dut.io.axi.r.bits.last.poke(true.B)
        dut.io.axi.aw.ready.poke(true.B); dut.io.axi.w.ready.poke(true.B)
        dut.io.axi.b.valid.poke(false.B); dut.io.axi.b.bits.id.poke(1.U); dut.io.axi.b.bits.resp.poke(0.U)
        val arFire = dut.io.axi.ar.valid.peek().litToBoolean
        val arAddr = dut.io.axi.ar.bits.addr.peek().litValue.toLong
        val rFire = dut.io.axi.r.valid.peek().litToBoolean && dut.io.axi.r.ready.peek().litToBoolean
        dut.clock.step()
        if (dut.io.debug_commit.peek().litToBoolean && dut.io.debug_wen.peek().litToBoolean)
          writes :+= ((dut.io.debug_rd.peek().litValue.toLong, dut.io.debug_wdata.peek().litValue.toLong & 0xffffffffL))
        if (arFire) pending = Some(arAddr)
        if (rFire) pending = None
      }
      dut.io.halted.expect(true.B)
      assert(writes.contains(2L -> 0xfffffffcL))
      assert(writes.count(_ == (2L -> 0xffffffffL)) == 1)
    }
  }
}
