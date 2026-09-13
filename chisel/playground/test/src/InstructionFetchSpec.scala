package cpu

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

class InstructionFetchSpec extends AnyFlatSpec with ChiselScalatestTester {
  behavior of "InstructionFetch"

  it should "hold a fetched instruction until ID accepts it" in {
    test(new InstructionFetch) { dut =>
      dut.io.out.ready.poke(false.B)
      dut.io.redirect.valid.poke(false.B)
      dut.io.axi.r.valid.poke(false.B)
      dut.io.axi.ar.ready.poke(true.B)
      dut.io.axi.aw.ready.poke(false.B)
      dut.io.axi.w.ready.poke(false.B)
      dut.io.axi.b.valid.poke(false.B)
      dut.reset.poke(true.B)
      dut.clock.step()
      dut.reset.poke(false.B)

      dut.io.axi.ar.valid.expect(true.B)
      dut.clock.step()
      dut.io.axi.ar.valid.expect(false.B)
      dut.io.axi.r.valid.poke(true.B)
      dut.io.axi.r.bits.data.poke("h12345678".U)
      dut.io.axi.r.bits.id.poke(0.U)
      dut.io.axi.r.bits.resp.poke(0.U)
      dut.io.axi.r.bits.last.poke(true.B)
      dut.io.axi.r.ready.expect(true.B)
      dut.clock.step()
      dut.io.axi.r.valid.poke(false.B)

      dut.io.out.valid.expect(true.B)
      dut.io.out.bits.pc.expect("h80000000".U)
      dut.io.out.bits.instr.expect("h12345678".U)
      dut.clock.step()
      dut.io.out.valid.expect(true.B)

      dut.io.out.ready.poke(true.B)
      dut.clock.step()
      dut.io.out.valid.expect(false.B)
      dut.io.axi.ar.valid.expect(true.B)
    }
  }

  it should "discard a pending response on redirect" in {
    test(new InstructionFetch) { dut =>
      dut.io.out.ready.poke(false.B)
      dut.io.redirect.valid.poke(false.B)
      dut.io.axi.ar.ready.poke(true.B)
      dut.io.axi.r.valid.poke(false.B)
      dut.io.axi.aw.ready.poke(false.B)
      dut.io.axi.w.ready.poke(false.B)
      dut.io.axi.b.valid.poke(false.B)
      dut.reset.poke(true.B)
      dut.clock.step()
      dut.reset.poke(false.B)
      dut.clock.step()

      dut.io.axi.r.valid.poke(true.B)
      dut.io.axi.r.bits.data.poke("h00000013".U)
      dut.io.axi.r.bits.id.poke(0.U)
      dut.io.axi.r.bits.resp.poke(0.U)
      dut.io.axi.r.bits.last.poke(true.B)
      dut.clock.step()
      dut.io.axi.r.valid.poke(false.B)
      dut.io.out.valid.expect(true.B)

      dut.io.redirect.valid.poke(true.B)
      dut.io.redirect.bits.poke("h80000100".U)
      dut.clock.step()
      dut.io.redirect.valid.poke(false.B)
      dut.io.out.valid.expect(false.B)
      dut.io.axi.ar.valid.expect(true.B)
      dut.io.axi.ar.bits.addr.expect("h80000100".U)
    }
  }
}
