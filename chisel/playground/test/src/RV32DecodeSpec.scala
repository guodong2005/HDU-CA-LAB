package cpu

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import cpu.defines._
import cpu.defines.Const._
import cpu.pipeline.Decoder

class RV32DecodeSpec extends AnyFlatSpec with ChiselScalatestTester {
  behavior of "RV32 decoder"

  private def encodeR(funct7: Int, rs2: Int, rs1: Int, funct3: Int, rd: Int): Int =
    (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | 0x33

  it should "decode standard R-type register fields" in {
    test(new Decoder) { dut =>
      dut.io.in.inst.poke(encodeR(0, 2, 1, 0, 3).U)
      dut.clock.step()
      dut.io.out.info.valid.expect(true.B)
      dut.io.out.info.reg_waddr.expect(3.U)
      dut.io.out.info.src1_raddr.expect(1.U)
      dut.io.out.info.src2_raddr.expect(2.U)
      dut.io.out.info.fusel.expect(FuType.alu)
    }
  }

  it should "decode an ADDI instruction" in {
    test(new Decoder) { dut =>
      val inst = (5 << 20) | (1 << 15) | (0 << 12) | (3 << 7) | 0x13
      dut.io.in.inst.poke(inst.U)
      dut.clock.step()
      dut.io.out.info.valid.expect(true.B)
      dut.io.out.info.reg_waddr.expect(3.U)
      dut.io.out.info.src1_raddr.expect(1.U)
      dut.io.out.info.src2_ren.expect(false.B)
    }
  }

  it should "decode branch source registers from rs1 and rs2" in {
    test(new Decoder) { dut =>
      val inst = (2 << 20) | (1 << 15) | (0 << 12) | 0x63
      dut.io.in.inst.poke(inst.U)
      dut.clock.step()
      dut.io.out.info.valid.expect(true.B)
      dut.io.out.info.src1_raddr.expect(1.U)
      dut.io.out.info.src2_raddr.expect(2.U)
      dut.io.out.info.reg_wen.expect(false.B)
    }
  }
}
