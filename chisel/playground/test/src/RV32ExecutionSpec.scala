package cpu

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec
import cpu.defines._
import cpu.defines.Const._
import cpu.pipeline.{Csr, Mdu}

class RV32ExecutionSpec extends AnyFlatSpec with ChiselScalatestTester {
  behavior of "RV32M execution unit"

  it should "execute multiply and divide operations" in {
    test(new Mdu) { dut =>
      dut.io.info.valid.poke(true.B); dut.io.info.fusel.poke(FuType.mdu); dut.io.info.op.poke(MDUOpType.mul)
      dut.io.src_info.src1_data.poke(6.U)
      dut.io.src_info.src2_data.poke(7.U)
      dut.io.result.expect(42.U)
      dut.io.valid.expect(true.B)
      dut.io.info.op.poke(MDUOpType.div)
      dut.io.result.expect(0.U)
      dut.io.src_info.src1_data.poke(43.U)
      dut.io.src_info.src2_data.poke(7.U)
      dut.io.result.expect(6.U)
    }
  }

  behavior of "RV CSR execution unit"

  it should "write and read mtvec even when rd is x0" in {
    test(new Csr) { dut =>
      dut.io.info.valid.poke(true.B)
      dut.io.info.fusel.poke(FuType.csr)
      dut.io.info.op.poke(CSROpType.write)
      dut.io.info.instr.poke((0x305 << 20).U)
      dut.io.info.reg_waddr.poke(0.U)
      dut.io.src_info.src1_data.poke("h80000000".U)
      dut.clock.step()
      dut.io.info.op.poke(CSROpType.set)
      dut.io.src_info.src1_data.poke(0.U)
      dut.io.result.expect("h80000000".U)
    }
  }
}
