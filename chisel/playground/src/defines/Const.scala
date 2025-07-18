package cpu.defines

import chisel3._
import chisel3.util._
import cpu.CpuConfig

trait CoreParameter {
  def cpuConfig = new CpuConfig
  val XLEN      = if (cpuConfig.isRV32) 32 else 64
  val VADDR_WID = if (cpuConfig.isRV32) 32 else 39
  val PADDR_WID = 32
}

trait Constants extends CoreParameter {
  // 全局
  val PC_INIT = "h1c000000".U(XLEN.W)

  val INT_WID = 12
  val EXC_WID = 16

  // inst rom
  val INST_WID = 32

  // GPR RegFile
  val AREG_NUM     = 32
  val REG_ADDR_WID = 5
  // do not change Icache const
  val FETCH_WIDTH         = 8
  val ICACHE_DEPTH        = 128
  val ICACHE_OFFSET_WIDTH = log2Up(FETCH_WIDTH * 4)
  val ICACHE_INST_WIDTH   = log2Up(FETCH_WIDTH)
  val ICACHE_INDEX_WIDTH  = log2Up(ICACHE_DEPTH)
  val ICACHE_TAG_WIDTH    = 32 - ICACHE_INDEX_WIDTH - ICACHE_OFFSET_WIDTH

  val FETCH_BUFFER_DEPTH = 17

  val COMMIT_WIDTH       = 2
  val ISSUE_WIDTH        = 2
  val WRITE_BUFFER_DEPTH = 4
  val LOAD_QUEUE_DEPTH   = 8
  val DISPATCH_WIDTH     = 5
  val SRAM_DELAY         = 1

  val ROB_DEPTH         = 16
  val ROB_IDX_WIDTH     = log2Up(ROB_DEPTH)
  val UART_BUFFER_DEPTH = 8
}

trait SRAMConst extends Constants {
  val SRAM_ADDR_WID      = PADDR_WID // 32
  val DATA_SRAM_DATA_WID = XLEN
  val DATA_SRAM_WEN_WID  = XLEN / 8
  val INST_SRAM_DATA_WID = INST_WID
  val INST_SRAM_WEN_WID  = INST_WID / 8
}
object Const extends Constants with SRAMConst

object Instructions extends HasInstrType with CoreParameter {
  // def NOP           = 0x00000013.U // riscv
  def NOP           = 0x02800000.U // loongarch
  val DecodeDefault = List(InstrN, FuType.alu, ALUOpType.add)
  def DecodeTable   = RVIInstr.table
}
