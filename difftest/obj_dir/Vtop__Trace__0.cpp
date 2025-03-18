// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgBit(oldp+0,((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))));
        bufp->chgQData(oldp+1,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc),64);
        bufp->chgQData(oldp+3,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst),64);
        bufp->chgBit(oldp+5,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
        bufp->chgQData(oldp+6,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc),64);
        bufp->chgCData(oldp+8,((0x1fU & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0xfU)))),5);
        bufp->chgQData(oldp+9,((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                 (((IData)(0x3fU) 
                                                   + 
                                                   (0x7ffU 
                                                    & VL_SHIFTL_III(11,11,32, 
                                                                    (0x1fU 
                                                                     & (IData)(
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))), 6U))) 
                                                  >> 5U)])) 
                                 << ((0U == (0x1fU 
                                             & VL_SHIFTL_III(11,11,32, 
                                                             (0x1fU 
                                                              & (IData)(
                                                                        (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                         >> 0xfU))), 6U)))
                                      ? 0x20U : ((IData)(0x40U) 
                                                 - 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0xfU))), 6U))))) 
                                | (((0U == (0x1fU & 
                                            VL_SHIFTL_III(11,11,32, 
                                                          (0x1fU 
                                                           & (IData)(
                                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                      >> 0xfU))), 6U)))
                                     ? 0ULL : ((QData)((IData)(
                                                               vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                               (((IData)(0x1fU) 
                                                                 + 
                                                                 (0x7ffU 
                                                                  & VL_SHIFTL_III(11,11,32, 
                                                                                (0x1fU 
                                                                                & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))), 6U))) 
                                                                >> 5U)])) 
                                               << ((IData)(0x20U) 
                                                   - 
                                                   (0x1fU 
                                                    & VL_SHIFTL_III(11,11,32, 
                                                                    (0x1fU 
                                                                     & (IData)(
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))), 6U))))) 
                                   | ((QData)((IData)(
                                                      vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                      (0x3fU 
                                                       & (VL_SHIFTL_III(11,11,32, 
                                                                        (0x1fU 
                                                                         & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))), 6U) 
                                                          >> 5U))])) 
                                      >> (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                                (0x1fU 
                                                                 & (IData)(
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0xfU))), 6U)))))),64);
        bufp->chgCData(oldp+11,((0x1fU & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 0x14U)))),5);
        bufp->chgQData(oldp+12,((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                  (((IData)(0x3fU) 
                                                    + 
                                                    (0x7ffU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     (0x1fU 
                                                                      & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U))), 6U))) 
                                                   >> 5U)])) 
                                  << ((0U == (0x1fU 
                                              & VL_SHIFTL_III(11,11,32, 
                                                              (0x1fU 
                                                               & (IData)(
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                          >> 0x14U))), 6U)))
                                       ? 0x20U : ((IData)(0x40U) 
                                                  - 
                                                  (0x1fU 
                                                   & VL_SHIFTL_III(11,11,32, 
                                                                   (0x1fU 
                                                                    & (IData)(
                                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                               >> 0x14U))), 6U))))) 
                                 | (((0U == (0x1fU 
                                             & VL_SHIFTL_III(11,11,32, 
                                                             (0x1fU 
                                                              & (IData)(
                                                                        (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                         >> 0x14U))), 6U)))
                                      ? 0ULL : ((QData)((IData)(
                                                                vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                                (((IData)(0x1fU) 
                                                                  + 
                                                                  (0x7ffU 
                                                                   & VL_SHIFTL_III(11,11,32, 
                                                                                (0x1fU 
                                                                                & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U))), 6U))) 
                                                                 >> 5U)])) 
                                                << 
                                                ((IData)(0x20U) 
                                                 - 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0x14U))), 6U))))) 
                                    | ((QData)((IData)(
                                                       vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                       (0x3fU 
                                                        & (VL_SHIFTL_III(11,11,32, 
                                                                         (0x1fU 
                                                                          & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U))), 6U) 
                                                           >> 5U))])) 
                                       >> (0x1fU & 
                                           VL_SHIFTL_III(11,11,32, 
                                                         (0x1fU 
                                                          & (IData)(
                                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                     >> 0x14U))), 6U)))))),64);
        bufp->chgCData(oldp+14,(((0x10U & ((IData)(
                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                    >> 3U)) 
                                           << 4U)) 
                                 | ((8U & ((IData)(
                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                    >> 0x1eU)) 
                                           << 3U)) 
                                    | (7U & (IData)(
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 0xcU)))))),5);
        bufp->chgCData(oldp+15,((0x1fU & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 7U)))),5);
        bufp->chgQData(oldp+16,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc),64);
        bufp->chgBit(oldp+18,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
        bufp->chgCData(oldp+19,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op),5);
        bufp->chgBit(oldp+20,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+21,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+22,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data),64);
        bufp->chgQData(oldp+24,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data),64);
        bufp->chgQData(oldp+26,(vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_memoryStage_data_rd_info_wdata),64);
        bufp->chgQData(oldp+28,((0x7fffffffffffffffULL 
                                 & ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data)) 
                                    << (0x1fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))))),63);
        bufp->chgIData(oldp+30,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__arithmeticShiftResult),32);
        bufp->chgCData(oldp+31,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state),2);
        bufp->chgQData(oldp+32,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc),64);
        bufp->chgBit(oldp+34,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
        bufp->chgBit(oldp+35,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+36,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+37,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata),64);
        bufp->chgBit(oldp+39,(vlSelfRef.top__DOT__core__DOT__core__DOT___writeBackUnit_io_regfile_wen));
        bufp->chgCData(oldp+40,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+41,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata),64);
        bufp->chgQData(oldp+43,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0),64);
        bufp->chgQData(oldp+45,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1),64);
        bufp->chgQData(oldp+47,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2),64);
        bufp->chgQData(oldp+49,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3),64);
        bufp->chgQData(oldp+51,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4),64);
        bufp->chgQData(oldp+53,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5),64);
        bufp->chgQData(oldp+55,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6),64);
        bufp->chgQData(oldp+57,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7),64);
        bufp->chgQData(oldp+59,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8),64);
        bufp->chgQData(oldp+61,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9),64);
        bufp->chgQData(oldp+63,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10),64);
        bufp->chgQData(oldp+65,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11),64);
        bufp->chgQData(oldp+67,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12),64);
        bufp->chgQData(oldp+69,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13),64);
        bufp->chgQData(oldp+71,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14),64);
        bufp->chgQData(oldp+73,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15),64);
        bufp->chgQData(oldp+75,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16),64);
        bufp->chgQData(oldp+77,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17),64);
        bufp->chgQData(oldp+79,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18),64);
        bufp->chgQData(oldp+81,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19),64);
        bufp->chgQData(oldp+83,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20),64);
        bufp->chgQData(oldp+85,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21),64);
        bufp->chgQData(oldp+87,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22),64);
        bufp->chgQData(oldp+89,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23),64);
        bufp->chgQData(oldp+91,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24),64);
        bufp->chgQData(oldp+93,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25),64);
        bufp->chgQData(oldp+95,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26),64);
        bufp->chgQData(oldp+97,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27),64);
        bufp->chgQData(oldp+99,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28),64);
        bufp->chgQData(oldp+101,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29),64);
        bufp->chgQData(oldp+103,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30),64);
        bufp->chgQData(oldp+105,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31),64);
        bufp->chgQData(oldp+107,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc),64);
        bufp->chgBit(oldp+109,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid));
        bufp->chgBit(oldp+110,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen));
    }
    bufp->chgBit(oldp+111,(vlSelfRef.clock));
    bufp->chgBit(oldp+112,(vlSelfRef.reset));
    bufp->chgBit(oldp+113,(vlSelfRef.mei));
    bufp->chgBit(oldp+114,(vlSelfRef.msi));
    bufp->chgBit(oldp+115,(vlSelfRef.mti));
    bufp->chgBit(oldp+116,(vlSelfRef.sei));
    bufp->chgBit(oldp+117,(vlSelfRef.inst_sram_en));
    bufp->chgCData(oldp+118,(vlSelfRef.inst_sram_wen),4);
    bufp->chgIData(oldp+119,(vlSelfRef.inst_sram_addr),32);
    bufp->chgIData(oldp+120,(vlSelfRef.inst_sram_wdata),32);
    bufp->chgIData(oldp+121,(vlSelfRef.inst_sram_rdata),32);
    bufp->chgBit(oldp+122,(vlSelfRef.data_sram_en));
    bufp->chgCData(oldp+123,(vlSelfRef.data_sram_wen),8);
    bufp->chgIData(oldp+124,(vlSelfRef.data_sram_addr),32);
    bufp->chgQData(oldp+125,(vlSelfRef.data_sram_wdata),64);
    bufp->chgQData(oldp+127,(vlSelfRef.data_sram_rdata),64);
    bufp->chgBit(oldp+129,(vlSelfRef.debug_commit));
    bufp->chgQData(oldp+130,(vlSelfRef.debug_pc),64);
    bufp->chgCData(oldp+132,(vlSelfRef.debug_rf_wnum),5);
    bufp->chgQData(oldp+133,(vlSelfRef.debug_rf_wdata),64);
    bufp->chgQData(oldp+135,((QData)((IData)(vlSelfRef.inst_sram_rdata))),64);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
