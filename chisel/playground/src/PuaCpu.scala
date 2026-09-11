import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.pipeline._

/** RV32 top-level wrapper used by the Verilator regression harness. */
class core_top extends Module {
  val io = IO(new Bundle {
    val mei = Input(Bool()); val msi = Input(Bool()); val mti = Input(Bool()); val sei = Input(Bool())
    val inst_sram_en = Output(Bool()); val inst_sram_wen = Output(UInt(4.W)); val inst_sram_addr = Output(UInt(32.W)); val inst_sram_wdata = Output(UInt(32.W)); val inst_sram_rdata = Input(UInt(32.W))
    val data_sram_en = Output(Bool()); val data_sram_wen = Output(UInt(8.W)); val data_sram_addr = Output(UInt(32.W)); val data_sram_wdata = Output(UInt(64.W)); val data_sram_rdata = Input(UInt(64.W))
    val debug_commit = Output(UInt(4.W)); val debug_pc = Output(UInt(32.W)); val debug_rf_wnum = Output(UInt(5.W)); val debug_rf_wdata = Output(UInt(32.W))
  })

  val core = Module(new cpu.Core())
    core.io.base_ram_ctrl.data_in := io.inst_sram_rdata
    core.io.ext_ram_ctrl.data_in := io.data_sram_rdata(31, 0)
    core.io.rxd.uart_ready := false.B
    core.io.rxd.uart_data := 0.U
    core.io.txd.uart_busy := false.B

    io.inst_sram_en := !core.io.base_ram_ctrl.ctrl.ce_n
    io.inst_sram_wen := core.io.base_ram_ctrl.ctrl.be_n
    io.inst_sram_addr := "h80000000".U(32.W) | Cat(0.U(10.W), core.io.base_ram_ctrl.ctrl.addr, 0.U(2.W))
    io.inst_sram_wdata := core.io.base_ram_ctrl.ctrl.data_out
    io.data_sram_en := !core.io.ext_ram_ctrl.ctrl.ce_n
    io.data_sram_wen := Cat("b1111".U(4.W), core.io.ext_ram_ctrl.ctrl.be_n)
    io.data_sram_addr := "h80000000".U(32.W) | Cat(0.U(10.W), core.io.ext_ram_ctrl.ctrl.addr, 0.U(2.W))
    io.data_sram_wdata := Cat(0.U(32.W), core.io.ext_ram_ctrl.ctrl.data_out)

    io.debug_commit := Fill(4, core.io.diff.instrCommit.valid)
    io.debug_pc := core.io.diff.instrCommit.pc
    io.debug_rf_wnum := core.io.diff.instrCommit.wdest
  io.debug_rf_wdata := core.io.diff.instrCommit.wdata
}
