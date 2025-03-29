// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+158,0,"mei",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+159,0,"msi",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+160,0,"mti",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+161,0,"sei",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+162,0,"inst_sram_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+163,0,"inst_sram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+164,0,"inst_sram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+165,0,"inst_sram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+166,0,"inst_sram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+167,0,"data_sram_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+168,0,"data_sram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+169,0,"data_sram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+170,0,"data_sram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+172,0,"data_sram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+174,0,"debug_commit",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+175,0,"debug_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+177,0,"debug_rf_wnum",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+178,0,"debug_rf_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("top", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+158,0,"mei",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+159,0,"msi",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+160,0,"mti",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+161,0,"sei",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+162,0,"inst_sram_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+163,0,"inst_sram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+164,0,"inst_sram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+165,0,"inst_sram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+166,0,"inst_sram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+167,0,"data_sram_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+168,0,"data_sram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+169,0,"data_sram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+170,0,"data_sram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+172,0,"data_sram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+174,0,"debug_commit",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+175,0,"debug_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+177,0,"debug_rf_wnum",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+178,0,"debug_rf_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("core", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+158,0,"io_ext_int_mei",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+160,0,"io_ext_int_mti",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+159,0,"io_ext_int_msi",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+162,0,"io_inst_sram_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+164,0,"io_inst_sram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+165,0,"io_inst_sram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+163,0,"io_inst_sram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+166,0,"io_inst_sram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+167,0,"io_data_sram_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+169,0,"io_data_sram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+170,0,"io_data_sram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+168,0,"io_data_sram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declQuad(c+172,0,"io_data_sram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+175,0,"io_debug_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+174,0,"io_debug_commit",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+177,0,"io_debug_rf_wnum",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+178,0,"io_debug_rf_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("core", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+162,0,"io_instSram_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+164,0,"io_instSram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+166,0,"io_instSram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+169,0,"io_dataSram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+170,0,"io_dataSram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+168,0,"io_dataSram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declQuad(c+172,0,"io_dataSram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+175,0,"io_debug_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+174,0,"io_debug_commit",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+177,0,"io_debug_rf_wnum",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+178,0,"io_debug_rf_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("controlUnit", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+1,0,"io_decodeInfo_src1_raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+2,0,"io_decodeInfo_src2_raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+3,0,"io_decodeInfo_src1_ren",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+4,0,"io_decodeInfo_src2_ren",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+5,0,"io_executeInfo_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"io_executeInfo_reg_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"io_executeInfo_reg_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+8,0,"io_memoryInfo_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"io_memoryInfo_reg_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+10,0,"io_memoryInfo_reg_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+11,0,"io_signals_fetchUnitSignal_allow_to_go",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"io_signals_fetchUnitSignal_do_flush",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+11,0,"io_signals_decodeUnitSignal_allow_to_go",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"io_signals_decodeUnitSignal_do_flush",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"io_branch",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("decodeStage", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+180,0,"io_fetchUnit_data_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+13,0,"io_fetchUnit_data_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+14,0,"io_fetchUnit_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+11,0,"io_controlSignal_fetchUnitSignal_allow_to_go",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"io_controlSignal_fetchUnitSignal_do_flush",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+16,0,"io_decodeUnit_data_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+18,0,"io_decodeUnit_data_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+19,0,"io_decodeUnit_data_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+16,0,"data_inst",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+18,0,"data_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+19,0,"data_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("decodeUnit", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declQuad(c+16,0,"io_decodeStage_data_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+18,0,"io_decodeStage_data_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+19,0,"io_decodeStage_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+1,0,"io_regfile_src1_raddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+21,0,"io_regfile_src1_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+2,0,"io_regfile_src2_raddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+23,0,"io_regfile_src2_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+19,0,"io_executeStage_data_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+18,0,"io_executeStage_data_info_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+1,0,"io_executeStage_data_info_src1_raddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+2,0,"io_executeStage_data_info_src2_raddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+25,0,"io_executeStage_data_info_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+26,0,"io_executeStage_data_info_reg_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+27,0,"io_executeStage_data_info_reg_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+28,0,"io_executeStage_data_info_imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+3,0,"io_executeStage_data_info_src1_ren",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+4,0,"io_executeStage_data_info_src2_ren",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+29,0,"io_executeStage_data_info_fusel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+30,0,"io_executeStage_data_src_info_src1_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+32,0,"io_executeStage_data_src_info_src2_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+34,0,"instrType",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declQuad(c+35,0,"imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("decoder", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declQuad(c+16,0,"io_in_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+16,0,"io_out_info_instr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+1,0,"io_out_info_src1_raddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+2,0,"io_out_info_src2_raddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+25,0,"io_out_info_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+26,0,"io_out_info_reg_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+27,0,"io_out_info_reg_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+3,0,"io_out_info_src1_ren",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+4,0,"io_out_info_src2_ren",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+29,0,"io_out_info_fusel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+34,0,"instrType",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+29,0,"fuType",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+37,0,"fuOpType",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("executeStage", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+19,0,"io_decodeUnit_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+18,0,"io_decodeUnit_data_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+25,0,"io_decodeUnit_data_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+26,0,"io_decodeUnit_data_info_reg_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+27,0,"io_decodeUnit_data_info_reg_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+28,0,"io_decodeUnit_data_info_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+29,0,"io_decodeUnit_data_info_fusel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+30,0,"io_decodeUnit_data_src_info_src1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+32,0,"io_decodeUnit_data_src_info_src2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+11,0,"io_controlSignal_decodeUnitSignal_allow_to_go",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"io_controlSignal_decodeUnitSignal_do_flush",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+38,0,"io_executeUnit_data_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+5,0,"io_executeUnit_data_info_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"io_executeUnit_data_info_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+6,0,"io_executeUnit_data_info_reg_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"io_executeUnit_data_info_reg_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+41,0,"io_executeUnit_data_info_imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+42,0,"io_executeUnit_data_info_fusel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+43,0,"io_executeUnit_data_src_info_src1_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+45,0,"io_executeUnit_data_src_info_src2_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+38,0,"data_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+5,0,"data_info_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"data_info_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+6,0,"data_info_reg_wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"data_info_reg_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+41,0,"data_info_imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+42,0,"data_info_fusel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+43,0,"data_src_info_src1_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+45,0,"data_src_info_src2_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("executeUnit", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declQuad(c+38,0,"io_executeStage_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+5,0,"io_executeStage_data_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"io_executeStage_data_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+6,0,"io_executeStage_data_info_reg_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"io_executeStage_data_info_reg_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+41,0,"io_executeStage_data_info_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+42,0,"io_executeStage_data_info_fusel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+43,0,"io_executeStage_data_src_info_src1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+45,0,"io_executeStage_data_src_info_src2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+38,0,"io_memoryStage_data_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+5,0,"io_memoryStage_data_info_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"io_memoryStage_data_info_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+6,0,"io_memoryStage_data_info_reg_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"io_memoryStage_data_info_reg_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+42,0,"io_memoryStage_data_info_fusel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+47,0,"io_memoryStage_data_rd_info_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+49,0,"io_memoryStage_data_rd_info_addr3",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+169,0,"io_dataSram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+170,0,"io_dataSram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+168,0,"io_dataSram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+12,0,"io_branch",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+50,0,"io_target",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("Fu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declQuad(c+38,0,"io_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+5,0,"io_data_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"io_data_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+41,0,"io_data_info_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+42,0,"io_data_info_fusel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+43,0,"io_data_src_info_src1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+45,0,"io_data_src_info_src2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+47,0,"io_data_rd_info_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+49,0,"io_data_rd_info_addr3",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+12,0,"io_data_branch",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+50,0,"io_data_target",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+169,0,"io_dataSram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+170,0,"io_dataSram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+168,0,"io_dataSram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->pushPrefix("alu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+40,0,"io_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+43,0,"io_src_info_src1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+45,0,"io_src_info_src2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+52,0,"io_result",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+54,0,"logicalShiftResult",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("bru", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+5,0,"io_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"io_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+41,0,"io_info_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+42,0,"io_info_fusel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+38,0,"io_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+43,0,"io_src_info_src1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+45,0,"io_src_info_src2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+55,0,"io_result",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+12,0,"io_branch",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+50,0,"io_target",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("lsu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+5,0,"io_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"io_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+42,0,"io_info_fusel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+43,0,"io_src_info_src1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+45,0,"io_src_info_src2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+49,0,"io_addr3",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+169,0,"io_dataSram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+170,0,"io_dataSram_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+168,0,"io_dataSram_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("mdu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+40,0,"io_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+43,0,"io_src_info_src1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+45,0,"io_src_info_src2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+57,0,"io_result",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+59,0,"iszero",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+60,0,"iszero32",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+61,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+65,0,"product_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+69,0,"quotient",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 64,0);
    tracep->declQuad(c+72,0,"divtmp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 32,0);
    tracep->declQuad(c+72,0,"quotient_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 32,0);
    tracep->declBus(c+74,0,"remResult",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+75,0,"remResult_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("fetchUnit", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+180,0,"io_decodeStage_data_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+13,0,"io_decodeStage_data_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+14,0,"io_decodeStage_data_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+162,0,"io_instSram_en",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+164,0,"io_instSram_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+166,0,"io_instSram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+12,0,"io_branch",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+50,0,"io_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+11,0,"io_signal_fetchUnitSignal_allow_to_go",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+76,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+14,0,"pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("memoryStage", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+38,0,"io_executeUnit_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+5,0,"io_executeUnit_data_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+40,0,"io_executeUnit_data_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+6,0,"io_executeUnit_data_info_reg_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"io_executeUnit_data_info_reg_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+42,0,"io_executeUnit_data_info_fusel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+47,0,"io_executeUnit_data_rd_info_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+49,0,"io_executeUnit_data_rd_info_addr3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declQuad(c+77,0,"io_memoryUnit_data_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+8,0,"io_memoryUnit_data_info_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+79,0,"io_memoryUnit_data_info_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+9,0,"io_memoryUnit_data_info_reg_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+10,0,"io_memoryUnit_data_info_reg_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+80,0,"io_memoryUnit_data_info_fusel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+81,0,"io_memoryUnit_data_rd_info_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+83,0,"io_memoryUnit_data_rd_info_addr3",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declQuad(c+77,0,"data_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+8,0,"data_info_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+79,0,"data_info_op",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+9,0,"data_info_reg_wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+10,0,"data_info_reg_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+80,0,"data_info_fusel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+81,0,"data_rd_info_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+83,0,"data_rd_info_addr3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->popPrefix();
    tracep->pushPrefix("memoryUnit", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declQuad(c+77,0,"io_memoryStage_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+8,0,"io_memoryStage_data_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+79,0,"io_memoryStage_data_info_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+9,0,"io_memoryStage_data_info_reg_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+10,0,"io_memoryStage_data_info_reg_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+80,0,"io_memoryStage_data_info_fusel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declQuad(c+81,0,"io_memoryStage_data_rd_info_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+83,0,"io_memoryStage_data_rd_info_addr3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declQuad(c+77,0,"io_writeBackStage_data_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+8,0,"io_writeBackStage_data_info_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"io_writeBackStage_data_info_reg_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+10,0,"io_writeBackStage_data_info_reg_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+182,0,"io_writeBackStage_data_rd_info_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+172,0,"io_dataSram_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+184,0,"memData",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("regfile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+1,0,"io_read_src1_raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+21,0,"io_read_src1_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+2,0,"io_read_src2_raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+23,0,"io_read_src2_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+84,0,"io_write_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+85,0,"io_write_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+86,0,"io_write_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+88,0,"regs_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+90,0,"regs_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+92,0,"regs_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+94,0,"regs_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+96,0,"regs_4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+98,0,"regs_5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+100,0,"regs_6",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+102,0,"regs_7",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+104,0,"regs_8",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+106,0,"regs_9",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+108,0,"regs_10",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+110,0,"regs_11",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+112,0,"regs_12",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+114,0,"regs_13",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+116,0,"regs_14",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+118,0,"regs_15",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+120,0,"regs_16",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+122,0,"regs_17",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+124,0,"regs_18",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+126,0,"regs_19",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+128,0,"regs_20",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+130,0,"regs_21",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+132,0,"regs_22",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+134,0,"regs_23",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+136,0,"regs_24",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+138,0,"regs_25",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+140,0,"regs_26",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+142,0,"regs_27",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+144,0,"regs_28",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+146,0,"regs_29",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+148,0,"regs_30",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+150,0,"regs_31",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("writeBackStage", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+156,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+157,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+77,0,"io_memoryUnit_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+8,0,"io_memoryUnit_data_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"io_memoryUnit_data_info_reg_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+10,0,"io_memoryUnit_data_info_reg_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+182,0,"io_memoryUnit_data_rd_info_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+152,0,"io_writeBackUnit_data_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+154,0,"io_writeBackUnit_data_info_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+155,0,"io_writeBackUnit_data_info_reg_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+85,0,"io_writeBackUnit_data_info_reg_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+86,0,"io_writeBackUnit_data_rd_info_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+152,0,"data_pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+154,0,"data_info_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+155,0,"data_info_reg_wen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+85,0,"data_info_reg_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+86,0,"data_rd_info_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("writeBackUnit", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declQuad(c+152,0,"io_writeBackStage_data_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+154,0,"io_writeBackStage_data_info_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+155,0,"io_writeBackStage_data_info_reg_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+85,0,"io_writeBackStage_data_info_reg_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+86,0,"io_writeBackStage_data_rd_info_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+84,0,"io_regfile_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+85,0,"io_regfile_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+86,0,"io_regfile_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+175,0,"io_debug_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+174,0,"io_debug_commit",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+177,0,"io_debug_rf_wnum",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declQuad(c+178,0,"io_debug_rf_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedFst* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtop___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vtop___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    VlWide<4>/*127:0*/ __Vtemp_1;
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_5;
    VlWide<3>/*95:0*/ __Vtemp_7;
    VlWide<3>/*95:0*/ __Vtemp_8;
    VlWide<3>/*95:0*/ __Vtemp_9;
    VlWide<3>/*95:0*/ __Vtemp_10;
    // Body
    bufp->fullCData(oldp+1,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr),5);
    bufp->fullCData(oldp+2,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr),5);
    bufp->fullBit(oldp+3,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren));
    bufp->fullBit(oldp+4,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren));
    bufp->fullBit(oldp+5,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
    bufp->fullBit(oldp+6,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen));
    bufp->fullCData(oldp+7,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr),5);
    bufp->fullBit(oldp+8,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
    bufp->fullBit(oldp+9,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen));
    bufp->fullCData(oldp+10,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr),5);
    bufp->fullBit(oldp+11,((1U & (~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT___pipeline_stall_T)))));
    bufp->fullBit(oldp+12,(vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush));
    bufp->fullBit(oldp+13,((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))));
    bufp->fullQData(oldp+14,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc),64);
    bufp->fullQData(oldp+16,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst),64);
    bufp->fullBit(oldp+18,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
    bufp->fullQData(oldp+19,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc),64);
    bufp->fullQData(oldp+21,((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                               (((IData)(0x3fU) 
                                                 + 
                                                 (0x7ffU 
                                                  & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))) 
                                                >> 5U)])) 
                               << ((0U == (0x1fU & 
                                           VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))
                                    ? 0x20U : ((IData)(0x40U) 
                                               - (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))))) 
                              | (((0U == (0x1fU & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))
                                   ? 0ULL : ((QData)((IData)(
                                                             vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                             (((IData)(0x1fU) 
                                                               + 
                                                               (0x7ffU 
                                                                & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))) 
                                                              >> 5U)])) 
                                             << ((IData)(0x20U) 
                                                 - 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))))) 
                                 | ((QData)((IData)(
                                                    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                    (0x3fU 
                                                     & (VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U) 
                                                        >> 5U))])) 
                                    >> (0x1fU & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))))),64);
    bufp->fullQData(oldp+23,((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                               (((IData)(0x3fU) 
                                                 + 
                                                 (0x7ffU 
                                                  & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))) 
                                                >> 5U)])) 
                               << ((0U == (0x1fU & 
                                           VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))
                                    ? 0x20U : ((IData)(0x40U) 
                                               - (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))))) 
                              | (((0U == (0x1fU & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))
                                   ? 0ULL : ((QData)((IData)(
                                                             vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                             (((IData)(0x1fU) 
                                                               + 
                                                               (0x7ffU 
                                                                & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))) 
                                                              >> 5U)])) 
                                             << ((IData)(0x20U) 
                                                 - 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))))) 
                                 | ((QData)((IData)(
                                                    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                    (0x3fU 
                                                     & (VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U) 
                                                        >> 5U))])) 
                                    >> (0x1fU & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))))),64);
    bufp->fullCData(oldp+25,(((1U & ((~ ((~ ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_74) 
                                             | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9))) 
                                         | (6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))) 
                                     | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_75)))
                               ? ((0x10U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___op_T_37)) 
                                  | (0xfU & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___op_T_37) 
                                             | (((1U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                  ? 
                                                 (7U 
                                                  & (IData)(
                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                             >> 0xcU)))
                                                  : 0U) 
                                                | (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9)
                                                     ? 
                                                    (8U 
                                                     | (7U 
                                                        & (IData)(
                                                                  (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                   >> 0xcU))))
                                                     : 0U) 
                                                   | ((2U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                       ? 
                                                      ((8U 
                                                        & ((IData)(
                                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                    >> 5U)) 
                                                           << 3U)) 
                                                       | (7U 
                                                          & (IData)(
                                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                     >> 0xcU))))
                                                       : 0U))))))
                               : 0U)),5);
    bufp->fullBit(oldp+26,(((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                            | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_76) 
                               | ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_74)) 
                                  & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9))))));
    bufp->fullCData(oldp+27,(((1U & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_75) 
                                     | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                        | ((~ ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9)) 
                                               | (1U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))) 
                                           | (2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))))
                               ? (0x1fU & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                   >> 7U)))
                               : 0U)),5);
    bufp->fullSData(oldp+28,((0xfffU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm))),12);
    bufp->fullCData(oldp+29,(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel),2);
    bufp->fullQData(oldp+30,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                               ? (((QData)((IData)(
                                                   vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                   (((IData)(0x3fU) 
                                                     + 
                                                     (0x7ffU 
                                                      & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))) 
                                                    >> 5U)])) 
                                   << ((0U == (0x1fU 
                                               & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))
                                        ? 0x20U : ((IData)(0x40U) 
                                                   - 
                                                   (0x1fU 
                                                    & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))))) 
                                  | (((0U == (0x1fU 
                                              & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))
                                       ? 0ULL : ((QData)((IData)(
                                                                 vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                                 (((IData)(0x1fU) 
                                                                   + 
                                                                   (0x7ffU 
                                                                    & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))) 
                                                                  >> 5U)])) 
                                                 << 
                                                 ((IData)(0x20U) 
                                                  - 
                                                  (0x1fU 
                                                   & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))))) 
                                     | ((QData)((IData)(
                                                        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                        (0x3fU 
                                                         & (VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U) 
                                                            >> 5U))])) 
                                        >> (0x1fU & 
                                            VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))))
                               : ((0x37U == (0x7fU 
                                             & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)))
                                   ? 0ULL : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc))),64);
    bufp->fullQData(oldp+32,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren)
                               ? (((QData)((IData)(
                                                   vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                   (((IData)(0x3fU) 
                                                     + 
                                                     (0x7ffU 
                                                      & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))) 
                                                    >> 5U)])) 
                                   << ((0U == (0x1fU 
                                               & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))
                                        ? 0x20U : ((IData)(0x40U) 
                                                   - 
                                                   (0x1fU 
                                                    & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))))) 
                                  | (((0U == (0x1fU 
                                              & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))
                                       ? 0ULL : ((QData)((IData)(
                                                                 vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                                 (((IData)(0x1fU) 
                                                                   + 
                                                                   (0x7ffU 
                                                                    & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))) 
                                                                  >> 5U)])) 
                                                 << 
                                                 ((IData)(0x20U) 
                                                  - 
                                                  (0x1fU 
                                                   & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))))) 
                                     | ((QData)((IData)(
                                                        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                        (0x3fU 
                                                         & (VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U) 
                                                            >> 5U))])) 
                                        >> (0x1fU & 
                                            VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))))
                               : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm)),64);
    bufp->fullCData(oldp+34,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType),3);
    bufp->fullQData(oldp+35,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm),64);
    bufp->fullCData(oldp+37,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType),5);
    bufp->fullQData(oldp+38,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc),64);
    bufp->fullCData(oldp+40,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op),5);
    bufp->fullSData(oldp+41,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm),12);
    bufp->fullCData(oldp+42,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel),2);
    bufp->fullQData(oldp+43,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data),64);
    bufp->fullQData(oldp+45,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data),64);
    bufp->fullQData(oldp+47,((((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result
                                : 0ULL) | (((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                             ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result
                                             : 0ULL) 
                                           | ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                               ? ((8U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                   ? 
                                                  (4ULL 
                                                   + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                                   : 
                                                  ((0xaU 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? 
                                                   (4ULL 
                                                    + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                                    : 0ULL))
                                               : 0ULL)))),64);
    bufp->fullCData(oldp+49,((7U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))),3);
    bufp->fullQData(oldp+50,(((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                               ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                               : ((0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                   ? (0xfffffffffffffffeULL 
                                      & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                         + vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0))
                                   : ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                       ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                       : ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                           ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                           : ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                               ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                               : ((5U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                   ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                                   : 
                                                  ((6U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                                     : 0ULL))))))))),64);
    bufp->fullQData(oldp+52,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result),64);
    bufp->fullIData(oldp+54,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT__logicalShiftResult),32);
    bufp->fullQData(oldp+55,(((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                               ? (4ULL + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                               : ((0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                   ? (4ULL + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                   : 0ULL))),64);
    bufp->fullQData(oldp+57,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result),64);
    bufp->fullBit(oldp+59,((0ULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
    bufp->fullBit(oldp+60,((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))));
    __Vtemp_1[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    __Vtemp_1[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                             >> 0x20U));
    __Vtemp_1[2U] = (IData)((- (QData)((IData)((1U 
                                                & (IData)(
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                           >> 0x3fU)))))));
    __Vtemp_1[3U] = (IData)(((- (QData)((IData)((1U 
                                                 & (IData)(
                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                            >> 0x3fU)))))) 
                             >> 0x20U));
    VL_MUL_W(4, __Vtemp_2, vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0, __Vtemp_1);
    bufp->fullWData(oldp+61,(__Vtemp_2),128);
    __Vtemp_3[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data);
    __Vtemp_3[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                             >> 0x20U));
    __Vtemp_3[2U] = 0U;
    __Vtemp_3[3U] = 0U;
    __Vtemp_4[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    __Vtemp_4[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                             >> 0x20U));
    __Vtemp_4[2U] = 0U;
    __Vtemp_4[3U] = 0U;
    VL_MUL_W(4, __Vtemp_5, __Vtemp_3, __Vtemp_4);
    bufp->fullWData(oldp+65,(__Vtemp_5),128);
    __Vtemp_7[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data);
    __Vtemp_7[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                             >> 0x20U));
    __Vtemp_7[2U] = (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                   >> 0x3fU)));
    __Vtemp_8[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    __Vtemp_8[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                             >> 0x20U));
    __Vtemp_8[2U] = (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                   >> 0x3fU)));
    VL_DIVS_WWW(65, __Vtemp_9, __Vtemp_7, __Vtemp_8);
    __Vtemp_10[0U] = __Vtemp_9[0U];
    __Vtemp_10[1U] = __Vtemp_9[1U];
    __Vtemp_10[2U] = (1U & __Vtemp_9[2U]);
    bufp->fullWData(oldp+69,(__Vtemp_10),65);
    bufp->fullQData(oldp+72,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__divtmp),33);
    bufp->fullIData(oldp+74,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult),32);
    bufp->fullIData(oldp+75,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult_1),32);
    bufp->fullCData(oldp+76,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state),2);
    bufp->fullQData(oldp+77,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc),64);
    bufp->fullCData(oldp+79,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op),5);
    bufp->fullCData(oldp+80,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel),2);
    bufp->fullQData(oldp+81,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata),64);
    bufp->fullCData(oldp+83,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3),3);
    bufp->fullBit(oldp+84,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen) 
                            & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid))));
    bufp->fullCData(oldp+85,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr),5);
    bufp->fullQData(oldp+86,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata),64);
    bufp->fullQData(oldp+88,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0),64);
    bufp->fullQData(oldp+90,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1),64);
    bufp->fullQData(oldp+92,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2),64);
    bufp->fullQData(oldp+94,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3),64);
    bufp->fullQData(oldp+96,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4),64);
    bufp->fullQData(oldp+98,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5),64);
    bufp->fullQData(oldp+100,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6),64);
    bufp->fullQData(oldp+102,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7),64);
    bufp->fullQData(oldp+104,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8),64);
    bufp->fullQData(oldp+106,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9),64);
    bufp->fullQData(oldp+108,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10),64);
    bufp->fullQData(oldp+110,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11),64);
    bufp->fullQData(oldp+112,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12),64);
    bufp->fullQData(oldp+114,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13),64);
    bufp->fullQData(oldp+116,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14),64);
    bufp->fullQData(oldp+118,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15),64);
    bufp->fullQData(oldp+120,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16),64);
    bufp->fullQData(oldp+122,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17),64);
    bufp->fullQData(oldp+124,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18),64);
    bufp->fullQData(oldp+126,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19),64);
    bufp->fullQData(oldp+128,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20),64);
    bufp->fullQData(oldp+130,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21),64);
    bufp->fullQData(oldp+132,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22),64);
    bufp->fullQData(oldp+134,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23),64);
    bufp->fullQData(oldp+136,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24),64);
    bufp->fullQData(oldp+138,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25),64);
    bufp->fullQData(oldp+140,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26),64);
    bufp->fullQData(oldp+142,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27),64);
    bufp->fullQData(oldp+144,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28),64);
    bufp->fullQData(oldp+146,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29),64);
    bufp->fullQData(oldp+148,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30),64);
    bufp->fullQData(oldp+150,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31),64);
    bufp->fullQData(oldp+152,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc),64);
    bufp->fullBit(oldp+154,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid));
    bufp->fullBit(oldp+155,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen));
    bufp->fullBit(oldp+156,(vlSelfRef.clock));
    bufp->fullBit(oldp+157,(vlSelfRef.reset));
    bufp->fullBit(oldp+158,(vlSelfRef.mei));
    bufp->fullBit(oldp+159,(vlSelfRef.msi));
    bufp->fullBit(oldp+160,(vlSelfRef.mti));
    bufp->fullBit(oldp+161,(vlSelfRef.sei));
    bufp->fullBit(oldp+162,(vlSelfRef.inst_sram_en));
    bufp->fullCData(oldp+163,(vlSelfRef.inst_sram_wen),4);
    bufp->fullIData(oldp+164,(vlSelfRef.inst_sram_addr),32);
    bufp->fullIData(oldp+165,(vlSelfRef.inst_sram_wdata),32);
    bufp->fullIData(oldp+166,(vlSelfRef.inst_sram_rdata),32);
    bufp->fullBit(oldp+167,(vlSelfRef.data_sram_en));
    bufp->fullCData(oldp+168,(vlSelfRef.data_sram_wen),8);
    bufp->fullIData(oldp+169,(vlSelfRef.data_sram_addr),32);
    bufp->fullQData(oldp+170,(vlSelfRef.data_sram_wdata),64);
    bufp->fullQData(oldp+172,(vlSelfRef.data_sram_rdata),64);
    bufp->fullBit(oldp+174,(vlSelfRef.debug_commit));
    bufp->fullQData(oldp+175,(vlSelfRef.debug_pc),64);
    bufp->fullCData(oldp+177,(vlSelfRef.debug_rf_wnum),5);
    bufp->fullQData(oldp+178,(vlSelfRef.debug_rf_wdata),64);
    bufp->fullQData(oldp+180,((QData)((IData)(vlSelfRef.inst_sram_rdata))),64);
    bufp->fullQData(oldp+182,(((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel))
                                ? (((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                     ? (((- (QData)((IData)(
                                                            (1U 
                                                             & (IData)(
                                                                       (vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData 
                                                                        >> 7U)))))) 
                                         << 8U) | (QData)((IData)(
                                                                  (0xffU 
                                                                   & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData)))))
                                     : 0ULL) | (((4U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                  ? (QData)((IData)(
                                                                    (0xffU 
                                                                     & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData))))
                                                  : 0ULL) 
                                                | (((1U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                     ? 
                                                    (((- (QData)((IData)(
                                                                         (1U 
                                                                          & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData 
                                                                                >> 0xfU)))))) 
                                                      << 0x10U) 
                                                     | (QData)((IData)(
                                                                       (0xffffU 
                                                                        & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData)))))
                                                     : 0ULL) 
                                                   | (((5U 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                        ? (QData)((IData)(
                                                                          (0xffffU 
                                                                           & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData))))
                                                        : 0ULL) 
                                                      | (((2U 
                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                           ? 
                                                          (((QData)((IData)(
                                                                            (- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData 
                                                                                >> 0x1fU))))))) 
                                                            << 0x20U) 
                                                           | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData)))
                                                           : 0ULL) 
                                                         | (((6U 
                                                              == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                              ? (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData))
                                                              : 0ULL) 
                                                            | ((3U 
                                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                                ? vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData
                                                                : 0ULL)))))))
                                : vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata)),64);
    bufp->fullQData(oldp+184,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData),64);
}
