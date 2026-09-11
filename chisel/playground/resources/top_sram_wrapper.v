// Compatibility wrapper for the RV32 Verilator harness.
module top(
    input clock, input reset,
    input mei, input msi, input mti, input sei,
    output inst_sram_en, output [3:0] inst_sram_wen,
    output [31:0] inst_sram_addr, output [31:0] inst_sram_wdata,
    input [31:0] inst_sram_rdata,
    output data_sram_en, output [7:0] data_sram_wen,
    output [31:0] data_sram_addr, output [63:0] data_sram_wdata,
    input [63:0] data_sram_rdata,
    output [3:0] debug_commit, output [31:0] debug_pc,
    output [4:0] debug_rf_wnum, output [31:0] debug_rf_wdata
);
  core_top core(
    .clock(clock), .reset(reset),
    .io_mei(mei), .io_msi(msi), .io_mti(mti), .io_sei(sei),
    .io_inst_sram_en(inst_sram_en), .io_inst_sram_wen(inst_sram_wen),
    .io_inst_sram_addr(inst_sram_addr), .io_inst_sram_wdata(inst_sram_wdata),
    .io_inst_sram_rdata(inst_sram_rdata),
    .io_data_sram_en(data_sram_en), .io_data_sram_wen(data_sram_wen),
    .io_data_sram_addr(data_sram_addr), .io_data_sram_wdata(data_sram_wdata),
    .io_data_sram_rdata(data_sram_rdata),
    .io_debug_commit(debug_commit), .io_debug_pc(debug_pc),
    .io_debug_rf_wnum(debug_rf_wnum), .io_debug_rf_wdata(debug_rf_wdata)
  );
endmodule
