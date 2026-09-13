package cpu

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

class AxiCacheSpec extends AnyFlatSpec with ChiselScalatestTester {
  behavior of "AxiCache"

  private def defaults(dut: AxiCache): Unit = {
    dut.io.cpu.ar.valid.poke(false.B)
    dut.io.cpu.aw.valid.poke(false.B)
    dut.io.cpu.w.valid.poke(false.B)
    dut.io.cpu.r.ready.poke(false.B)
    dut.io.cpu.b.ready.poke(false.B)
    dut.io.mem.ar.ready.poke(false.B)
    dut.io.mem.r.valid.poke(false.B)
    dut.io.mem.r.bits.id.poke(0.U)
    dut.io.mem.r.bits.data.poke(0.U)
    dut.io.mem.r.bits.resp.poke(0.U)
    dut.io.mem.r.bits.last.poke(true.B)
    dut.io.mem.aw.ready.poke(false.B)
    dut.io.mem.w.ready.poke(false.B)
    dut.io.mem.b.valid.poke(false.B)
    dut.io.mem.b.bits.id.poke(0.U)
    dut.io.mem.b.bits.resp.poke(0.U)
  }

  it should "issue one miss request and serve the next access from the hit" in {
    test(new AxiCache(4)) { dut =>
      defaults(dut)
      dut.reset.poke(true.B); dut.clock.step(); dut.reset.poke(false.B)

      dut.io.cpu.ar.bits.addr.poke("h80000100".U)
      dut.io.cpu.ar.bits.id.poke(2.U)
      dut.io.cpu.ar.valid.poke(true.B)
      dut.io.cpu.ar.ready.expect(true.B)
      dut.clock.step()
      dut.io.cpu.ar.valid.poke(false.B)

      dut.io.mem.ar.ready.poke(false.B)
      dut.io.mem.ar.valid.expect(true.B)
      dut.clock.step(2)
      dut.io.mem.ar.valid.expect(true.B)

      dut.io.mem.ar.ready.poke(true.B)
      dut.io.mem.ar.valid.expect(true.B)
      dut.clock.step()
      dut.io.mem.ar.valid.expect(false.B)

      dut.io.mem.r.bits.data.poke("h12345678".U)
      dut.io.mem.r.bits.id.poke(2.U)
      dut.io.mem.r.valid.poke(true.B)
      dut.io.mem.r.ready.expect(true.B)
      dut.clock.step()
      dut.io.mem.r.valid.poke(false.B)

      dut.io.cpu.r.ready.poke(true.B)
      dut.io.cpu.r.valid.expect(true.B)
      dut.io.cpu.r.bits.data.expect("h12345678".U)
      dut.clock.step()

      dut.io.cpu.ar.bits.addr.poke("h80000100".U)
      dut.io.cpu.ar.valid.poke(true.B)
      dut.clock.step()
      dut.io.cpu.ar.valid.poke(false.B)
      dut.io.mem.ar.valid.expect(false.B)
      dut.io.cpu.r.valid.expect(true.B)
    }
  }

  it should "hold AW and W until each downstream handshake completes" in {
    test(new AxiCache(4)) { dut =>
      defaults(dut)
      dut.reset.poke(true.B); dut.clock.step(); dut.reset.poke(false.B)

      dut.io.cpu.aw.bits.addr.poke("h80000200".U)
      dut.io.cpu.aw.bits.id.poke(1.U)
      dut.io.cpu.aw.valid.poke(true.B)
      dut.io.cpu.aw.ready.expect(true.B)
      dut.clock.step()
      dut.io.cpu.aw.valid.poke(false.B)

      dut.io.mem.aw.ready.poke(false.B)
      dut.io.mem.aw.valid.expect(true.B)
      dut.clock.step(2)
      dut.io.mem.aw.valid.expect(true.B)

      dut.io.mem.aw.ready.poke(true.B)
      dut.clock.step()
      dut.io.mem.w.ready.poke(false.B)
      dut.io.cpu.w.bits.data.poke("hdeadbeef".U)
      dut.io.cpu.w.bits.strb.poke("hf".U)
      dut.io.cpu.w.bits.id.poke(1.U)
      dut.io.cpu.w.bits.last.poke(true.B)
      dut.io.cpu.w.valid.poke(true.B)
      dut.io.cpu.w.ready.expect(false.B)
      dut.io.mem.w.valid.expect(true.B)
      dut.clock.step()
      dut.io.cpu.w.ready.expect(false.B)

      dut.io.mem.w.ready.poke(true.B)
      dut.io.cpu.w.ready.expect(true.B)
      dut.clock.step()
      dut.io.cpu.w.valid.poke(false.B)
      dut.io.mem.b.valid.poke(true.B)
      dut.io.mem.b.bits.id.poke(1.U)
      dut.io.mem.b.bits.resp.poke(0.U)
      dut.io.cpu.b.ready.poke(true.B)
      dut.io.cpu.b.valid.expect(true.B)
      dut.clock.step()
      dut.io.cpu.b.valid.expect(false.B)
    }
  }

  it should "accept only the write side when AR and AW arrive together" in {
    test(new AxiCache(4)) { dut =>
      defaults(dut)
      dut.reset.poke(true.B); dut.clock.step(); dut.reset.poke(false.B)
      dut.io.cpu.ar.bits.addr.poke("h80000300".U)
      dut.io.cpu.ar.bits.id.poke(2.U)
      dut.io.cpu.ar.valid.poke(true.B)
      dut.io.cpu.aw.bits.addr.poke("h80000400".U)
      dut.io.cpu.aw.bits.id.poke(1.U)
      dut.io.cpu.aw.valid.poke(true.B)
      dut.io.cpu.aw.ready.expect(true.B)
      dut.io.cpu.ar.ready.expect(false.B)
      dut.clock.step()
      dut.io.cpu.aw.valid.poke(false.B)
      dut.io.cpu.ar.valid.poke(false.B)

      dut.io.mem.aw.ready.poke(true.B)
      dut.io.mem.aw.valid.expect(true.B)
      dut.clock.step()
      dut.io.mem.w.ready.poke(true.B)
      dut.io.cpu.w.bits.data.poke("habcdef01".U)
      dut.io.cpu.w.bits.strb.poke("hf".U)
      dut.io.cpu.w.bits.id.poke(1.U)
      dut.io.cpu.w.bits.last.poke(true.B)
      dut.io.cpu.w.valid.poke(true.B)
      dut.clock.step()
      dut.io.cpu.w.valid.poke(false.B)
      dut.io.mem.b.bits.id.poke(1.U)
      dut.io.mem.b.bits.resp.poke(2.U)
      dut.io.mem.b.valid.poke(true.B)
      dut.io.cpu.b.ready.poke(true.B)
      dut.io.cpu.b.valid.expect(true.B)
      dut.io.cpu.b.bits.resp.expect(2.U)
      dut.clock.step()
    }
  }

  it should "forward read errors and avoid filling the line" in {
    test(new AxiCache(4)) { dut =>
      defaults(dut)
      dut.reset.poke(true.B); dut.clock.step(); dut.reset.poke(false.B)
      dut.io.cpu.ar.bits.addr.poke("h80000500".U)
      dut.io.cpu.ar.bits.id.poke(2.U)
      dut.io.cpu.ar.valid.poke(true.B)
      dut.clock.step()
      dut.io.cpu.ar.valid.poke(false.B)
      dut.io.mem.ar.ready.poke(true.B)
      dut.clock.step()
      dut.io.mem.r.bits.id.poke(2.U)
      dut.io.mem.r.bits.data.poke("hdeadbeef".U)
      dut.io.mem.r.bits.resp.poke(2.U)
      dut.io.mem.r.bits.last.poke(true.B)
      dut.io.mem.r.valid.poke(true.B)
      dut.clock.step()
      dut.io.mem.r.valid.poke(false.B)
      dut.io.cpu.r.valid.expect(true.B)
      dut.io.cpu.r.bits.id.expect(2.U)
      dut.io.cpu.r.bits.resp.expect(2.U)
      dut.io.cpu.r.bits.last.expect(true.B)
      dut.io.cpu.r.ready.poke(true.B)
      dut.clock.step()

      dut.io.cpu.ar.bits.addr.poke("h80000500".U)
      dut.io.cpu.ar.valid.poke(true.B)
      dut.clock.step()
      dut.io.cpu.ar.valid.poke(false.B)
      dut.io.mem.ar.valid.expect(true.B)
    }
  }
}
