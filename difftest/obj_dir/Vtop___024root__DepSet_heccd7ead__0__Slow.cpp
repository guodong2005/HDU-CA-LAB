// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.inst_sram_wdata = 0U;
    vlSelfRef.inst_sram_wen = 0U;
    vlSelfRef.data_sram_en = 1U;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("core/top_sram_wrapper.v", 1, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf);
VL_ATTR_COLD void Vtop___024root____Vm_traceActivitySetAll(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
        Vtop___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT____VdfgRegularize_hbb470ff5_0_28;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT____VdfgRegularize_hbb470ff5_0_28 = 0;
    SData/*9:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_50;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_50 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_51;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_51 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_52;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_52 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_4;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_4 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_5;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_5 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_6;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_6 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_11;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_11 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_12;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_12 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__lsu__DOT____VdfgRegularize_h932ecef8_0_1;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__lsu__DOT____VdfgRegularize_h932ecef8_0_1 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4 = 0;
    CData/*2:0*/ __VdfgRegularize_hd87f99a1_1_0;
    __VdfgRegularize_hd87f99a1_1_0 = 0;
    CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_17;
    __VdfgRegularize_hd87f99a1_1_17 = 0;
    // Body
    vlSelfRef.inst_sram_en = (1U & (~ (IData)(vlSelfRef.reset)));
    vlSelfRef.debug_commit = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid;
    vlSelfRef.debug_rf_wnum = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
    vlSelfRef.debug_pc = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
    vlSelfRef.debug_rf_wdata = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
    vlSelfRef.data_sram_wdata = (((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                   ? ((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                       << 0x18U) | 
                                      ((0xff0000U & 
                                        (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                         << 0x10U)) 
                                       | ((0xff00U 
                                           & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                              << 8U)) 
                                          | (0xffU 
                                             & vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))))
                                   : 0U) | (((9U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                              ? ((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                  << 0x10U) 
                                                 | (0xffffU 
                                                    & vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))
                                              : 0U) 
                                            | ((0xaU 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data
                                                : 0U)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_3 
        = VL_DIV_III(32, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___result_T_6 
        = (0x1ffffffffULL & VL_DIVS_QQQ(33, (((QData)((IData)(
                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                               >> 0x1fU))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))), 
                                        (((QData)((IData)(
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                           >> 0x1fU))) 
                                          << 0x20U) 
                                         | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData 
        = (((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
             ? vlSelfRef.data_sram_rdata : 0U) | ((
                                                   (1U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                    ? 
                                                   VL_SHIFTR_III(32,32,32, vlSelfRef.data_sram_rdata, 8U)
                                                    : 0U) 
                                                  | (((2U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, vlSelfRef.data_sram_rdata, 0x10U)
                                                       : 0U) 
                                                     | ((3U 
                                                         == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                         ? 
                                                        VL_SHIFTR_III(32,32,32, vlSelfRef.data_sram_rdata, 0x18U)
                                                         : 0U))));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid) 
           & (3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel)));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_18 = VL_LTS_III(32, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_20 = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                 < vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0 
        = (((- (IData)((1U & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm) 
                              >> 0xbU)))) << 0xcU) 
           | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[1U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[2U] 
        = (IData)((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[3U] 
        = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2))) 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[4U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[5U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[6U] 
        = (IData)((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[7U] 
        = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6))) 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[8U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[9U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xaU] 
        = (IData)((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xbU] 
        = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10))) 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xcU] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xdU] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xeU] 
        = (IData)((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xfU] 
        = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14))) 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x10U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x11U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x12U] 
        = (IData)((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x13U] 
        = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18))) 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x14U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x15U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x16U] 
        = (IData)((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x17U] 
        = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22))) 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x18U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x19U] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1aU] 
        = (IData)((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1bU] 
        = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26))) 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1cU] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1dU] 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29;
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1eU] 
        = (IData)((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1fU] 
        = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30))) 
                   >> 0x20U));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_6 
        = ((0x29U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 0xfU)) | (0x22U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                             >> 0xfU)));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43 
        = ((0x380U & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 5U)) | (0x7fU & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_5 
        = ((0x20U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 0xfU)) | (0x2eU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                             >> 0xfU)));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_52 
        = ((0x38U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 0xfU)) | ((0x39U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                              >> 0xfU)) 
                                   | ((0x3aU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0xfU)) 
                                      | ((0x40U == 
                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                           >> 0xfU)) 
                                         | ((0x42U 
                                             == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0xfU)) 
                                            | ((0x41U 
                                                == 
                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0xfU)) 
                                               | (0x43U 
                                                  == 
                                                  (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                   >> 0xfU))))))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_12 
        = ((0xa0U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 0x16U)) | ((0xa8U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                               >> 0x16U)) 
                                    | ((0xa1U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 0x16U)) 
                                       | ((0xa9U == 
                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                            >> 0x16U)) 
                                          | (0xa2U 
                                             == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0x16U))))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_51 
        = ((0xa4U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 0x16U)) | ((0xa5U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                               >> 0x16U)) 
                                    | (0xa6U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0x16U))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_11 
        = ((0x16U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 0x1aU)) | ((0x17U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                               >> 0x1aU)) 
                                    | ((0x18U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 0x1aU)) 
                                       | ((0x19U == 
                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                            >> 0x1aU)) 
                                          | ((0x1aU 
                                              == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 0x1aU)) 
                                             | (0x1bU 
                                                == 
                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0x1aU)))))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_50 
        = ((0x14U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 0x1aU)) | ((0x15U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                               >> 0x1aU)) 
                                    | (0x13U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0x1aU))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_4 
        = ((0xaU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                     >> 0x19U)) | (0xeU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                            >> 0x19U)));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__lsu__DOT____VdfgRegularize_h932ecef8_0_1 
        = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
           + top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0);
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4 
        = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc 
           + top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0);
    if ((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3;
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    } else if ((0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3;
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    } else if ((0xbU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3;
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
               + (((- (IData)((1U & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm) 
                                     >> 0xbU)))) << 0xdU) 
                  | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm) 
                     << 1U)));
    } else if ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                  == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    } else if ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                  != vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    } else if ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_18));
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    } else if ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & VL_GTES_III(32, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    } else if ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_20));
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    } else if ((7U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid) 
               & ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel)) 
                  & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                     >= vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target = 0U;
    }
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT____VdfgRegularize_hbb470ff5_0_28 
        = ((0x29U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                      >> 0xfU)) | ((0x22U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                              >> 0xfU)) 
                                   | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_52)));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7 
        = ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_6) 
           | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_52));
    __VdfgRegularize_hd87f99a1_1_17 = ((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_12)) 
                                       & ((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_51)) 
                                          & ((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_11)) 
                                             & (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_50))));
    __VdfgRegularize_hd87f99a1_1_0 = ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_12)
                                       ? 4U : ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_51)
                                                ? 2U
                                                : ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_11)
                                                    ? 1U
                                                    : 
                                                   ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_50)
                                                     ? 7U
                                                     : 
                                                    (((0xf3U 
                                                       == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43)) 
                                                      | ((0x173U 
                                                          == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43)) 
                                                         | ((0x1f3U 
                                                             == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43)) 
                                                            | ((0x2f3U 
                                                                == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43)) 
                                                               | ((0x373U 
                                                                   == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43)) 
                                                                  | (0x3f3U 
                                                                     == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43))))))) 
                                                     << 2U)))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9 
        = ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_4) 
           | ((0xaU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                        >> 0x16U)) | (0x20U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                >> 0xfU))));
    vlSelfRef.data_sram_addr = (((8U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                  ? top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__lsu__DOT____VdfgRegularize_h932ecef8_0_1
                                  : 0U) | ((8U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                            ? 0U : top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__lsu__DOT____VdfgRegularize_h932ecef8_0_1));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_10 
        = ((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_4)) 
           & ((0xaU != (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                        >> 0x16U)) & ((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_5)) 
                                      & ((8U != (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0x16U)) 
                                         & ((0x24U 
                                             != (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0xfU)) 
                                            & ((9U 
                                                != 
                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0x16U)) 
                                               & ((0x25U 
                                                   != 
                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                    >> 0xfU)) 
                                                  & ((0xfU 
                                                      != 
                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                       >> 0x16U)) 
                                                     & ((0x2bU 
                                                         != 
                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                          >> 0xfU)) 
                                                        & ((0x89U 
                                                            != 
                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                             >> 0xfU)) 
                                                           & ((0x2fU 
                                                               != 
                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                >> 0xfU)) 
                                                              & ((0x91U 
                                                                  != 
                                                                  (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                   >> 0xfU)) 
                                                                 & ((0x30U 
                                                                     != 
                                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                      >> 0xfU)) 
                                                                    & ((0xeU 
                                                                        != 
                                                                        (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                         >> 0x16U)) 
                                                                       & ((0x2aU 
                                                                           != 
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0xfU)) 
                                                                          & ((0xdU 
                                                                              != 
                                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                               >> 0x16U)) 
                                                                             & ((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7)) 
                                                                                & (IData)(__VdfgRegularize_hd87f99a1_1_17))))))))))))))))));
    if (top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_4) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 6U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 6U;
    } else if ((0xaU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                         >> 0x16U))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 4U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 4U;
    } else if (top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_5) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 5U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 5U;
    } else if ((8U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                       >> 0x16U))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 4U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 4U;
    } else if ((0x24U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 5U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 5U;
    } else if ((9U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                       >> 0x16U))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 4U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 4U;
    } else if ((0x25U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 5U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 5U;
    } else if ((0xfU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                         >> 0x16U))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 4U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 4U;
    } else if ((0x2bU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 5U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 5U;
    } else if ((0x89U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 4U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 4U;
    } else if ((0x2fU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 5U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 5U;
    } else if ((0x91U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 4U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 4U;
    } else if ((0x30U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 5U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 5U;
    } else if ((0xeU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                         >> 0x16U))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 4U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 4U;
    } else if ((0x2aU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 5U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 5U;
    } else if ((0xdU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                         >> 0x16U))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = 4U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = 4U;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType 
            = ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT____VdfgRegularize_hbb470ff5_0_28)
                ? 5U : (IData)(__VdfgRegularize_hd87f99a1_1_0));
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType 
            = ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7)
                ? 5U : (IData)(__VdfgRegularize_hd87f99a1_1_0));
    }
    vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel 
        = (((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9) 
            | ((0x2eU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                          >> 0xfU)) | ((8U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                               >> 0x16U)) 
                                       | ((0x24U == 
                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                            >> 0xfU)) 
                                          | ((9U == 
                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                               >> 0x16U)) 
                                             | ((0x25U 
                                                 == 
                                                 (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 0xfU)) 
                                                | ((0xfU 
                                                    == 
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 0x16U)) 
                                                   | ((0x2bU 
                                                       == 
                                                       (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                        >> 0xfU)) 
                                                      | ((0x89U 
                                                          == 
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                           >> 0xfU)) 
                                                         | ((0x2fU 
                                                             == 
                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                              >> 0xfU)) 
                                                            | ((0x91U 
                                                                == 
                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                 >> 0xfU)) 
                                                               | ((0x30U 
                                                                   == 
                                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                    >> 0xfU)) 
                                                                  | ((0xeU 
                                                                      == 
                                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                       >> 0x16U)) 
                                                                     | ((0x2aU 
                                                                         == 
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                          >> 0xfU)) 
                                                                        | ((0xdU 
                                                                            == 
                                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                             >> 0x16U)) 
                                                                           | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_6))))))))))))))))
            ? 0U : ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_52)
                     ? 1U : (((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_12) 
                              | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_51))
                              ? 2U : (3U & (- (IData)(
                                                      ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_11) 
                                                       | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_50))))))));
    vlSelfRef.data_sram_wen = (0xfU & ((((0xffffU & 
                                          ((IData)(1U) 
                                           << (0xfU 
                                               & ((IData)(1U) 
                                                  << 
                                                  (3U 
                                                   & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op)))))) 
                                         - (IData)(1U)) 
                                        << (7U & vlSelfRef.data_sram_addr)) 
                                       & (- (IData)(
                                                    ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid) 
                                                     & ((2U 
                                                         == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel)) 
                                                        & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op) 
                                                           >> 3U)))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm 
        = (((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType))
             ? ((((0x1000000U & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)
                   ? 0U : (0xfffffU & (- (IData)((1U 
                                                  & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 0x15U)))))) 
                 << 0xcU) | (0xfffU & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                       >> 0xaU))) : 0U) 
           | (((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType))
                ? (((- (IData)((1U & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                      >> 0x15U)))) 
                    << 0xcU) | (0xfffU & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                          >> 0xaU)))
                : 0U) | (((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType))
                           ? (((- (IData)((1U & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0x19U)))) 
                               << 0x1cU) | (0xffffffcU 
                                            & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                               << 2U)))
                           : 0U) | (((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType))
                                      ? (0xfffff000U 
                                         & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)
                                      : 0U) | (((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_4)) 
                                                & ((0xaU 
                                                    != 
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 0x16U)) 
                                                   & ((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_5)) 
                                                      & ((8U 
                                                          != 
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                           >> 0x16U)) 
                                                         & ((0x24U 
                                                             != 
                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                              >> 0xfU)) 
                                                            & ((9U 
                                                                != 
                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                 >> 0x16U)) 
                                                               & ((0x25U 
                                                                   != 
                                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                    >> 0xfU)) 
                                                                  & ((0xfU 
                                                                      != 
                                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                       >> 0x16U)) 
                                                                     & ((0x2bU 
                                                                         != 
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                          >> 0xfU)) 
                                                                        & ((0x89U 
                                                                            != 
                                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                             >> 0xfU)) 
                                                                           & ((0x2fU 
                                                                               != 
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)) 
                                                                              & ((0x91U 
                                                                                != 
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)) 
                                                                                & ((0x30U 
                                                                                != 
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)) 
                                                                                & ((0xeU 
                                                                                != 
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x16U)) 
                                                                                & ((0x2aU 
                                                                                != 
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)) 
                                                                                & ((0xdU 
                                                                                != 
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x16U)) 
                                                                                & ((~ (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT____VdfgRegularize_hbb470ff5_0_28)) 
                                                                                & (IData)(__VdfgRegularize_hd87f99a1_1_17))))))))))))))))))
                                                ? (
                                                   ((- (IData)(
                                                               (1U 
                                                                & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                   >> 0x19U)))) 
                                                    << 0x12U) 
                                                   | (0x3fffcU 
                                                      & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                         >> 8U)))
                                                : 0U)))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_60 
        = ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
           | (6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_59 
        = ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
           | (4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58 
        = ((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
           | (1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)));
    vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_op 
        = ((1U & ((~ ((~ ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58) 
                          | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_10))) 
                      | (6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))) 
                  | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_59)))
            ? ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9)
                ? 0U : ((0x2eU == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                   >> 0xfU)) ? 9U : 
                        (((8U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                  >> 0x16U)) | (0x24U 
                                                == 
                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0xfU)))
                          ? 2U : (((9U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                           >> 0x16U)) 
                                   | (0x25U == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                >> 0xfU)))
                                   ? 3U : (((0xfU == 
                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                              >> 0x16U)) 
                                            | (0x2bU 
                                               == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                   >> 0xfU)))
                                            ? 4U : 
                                           (((0x89U 
                                              == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 0xfU)) 
                                             | (0x2fU 
                                                == 
                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0xfU)))
                                             ? 5U : 
                                            (((0x91U 
                                               == (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                   >> 0xfU)) 
                                              | (0x30U 
                                                 == 
                                                 (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 0xfU)))
                                              ? 6U : 
                                             (((0xeU 
                                                == 
                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                 >> 0x16U)) 
                                               | (0x2aU 
                                                  == 
                                                  (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                   >> 0xfU)))
                                               ? 7U
                                               : ((
                                                   (0xdU 
                                                    == 
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 0x16U)) 
                                                   | (0x29U 
                                                      == 
                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                       >> 0xfU)))
                                                   ? 8U
                                                   : 
                                                  ((0x22U 
                                                    == 
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 0xfU))
                                                    ? 1U
                                                    : 
                                                   ((0x38U 
                                                     == 
                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                      >> 0xfU))
                                                     ? 0U
                                                     : 
                                                    ((0x39U 
                                                      == 
                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                       >> 0xfU))
                                                      ? 1U
                                                      : 
                                                     ((0x3aU 
                                                       == 
                                                       (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                        >> 0xfU))
                                                       ? 3U
                                                       : 
                                                      ((0x40U 
                                                        == 
                                                        (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                         >> 0xfU))
                                                        ? 4U
                                                        : 
                                                       ((0x42U 
                                                         == 
                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                          >> 0xfU))
                                                         ? 5U
                                                         : 
                                                        ((0x41U 
                                                          == 
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                           >> 0xfU))
                                                          ? 6U
                                                          : 
                                                         ((0x43U 
                                                           == 
                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                            >> 0xfU))
                                                           ? 7U
                                                           : 
                                                          ((0xa0U 
                                                            == 
                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                             >> 0x16U))
                                                            ? 0U
                                                            : 
                                                           ((0xa8U 
                                                             == 
                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                              >> 0x16U))
                                                             ? 4U
                                                             : 
                                                            ((0xa1U 
                                                              == 
                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                               >> 0x16U))
                                                              ? 1U
                                                              : 
                                                             ((0xa9U 
                                                               == 
                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                >> 0x16U))
                                                               ? 5U
                                                               : 
                                                              ((0xa2U 
                                                                == 
                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                 >> 0x16U))
                                                                ? 2U
                                                                : 
                                                               ((0xa4U 
                                                                 == 
                                                                 (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                  >> 0x16U))
                                                                 ? 8U
                                                                 : 
                                                                ((0xa5U 
                                                                  == 
                                                                  (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                   >> 0x16U))
                                                                  ? 9U
                                                                  : 
                                                                 ((0xa6U 
                                                                   == 
                                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                    >> 0x16U))
                                                                   ? 0xaU
                                                                   : 
                                                                  ((0x16U 
                                                                    == 
                                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                     >> 0x1aU))
                                                                    ? 0U
                                                                    : 
                                                                   ((0x17U 
                                                                     == 
                                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                      >> 0x1aU))
                                                                     ? 1U
                                                                     : 
                                                                    ((0x18U 
                                                                      == 
                                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                       >> 0x1aU))
                                                                      ? 4U
                                                                      : 
                                                                     ((0x19U 
                                                                       == 
                                                                       (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                        >> 0x1aU))
                                                                       ? 5U
                                                                       : 
                                                                      ((0x1aU 
                                                                        == 
                                                                        (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                         >> 0x1aU))
                                                                        ? 6U
                                                                        : 
                                                                       ((0x1bU 
                                                                         == 
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                          >> 0x1aU))
                                                                         ? 7U
                                                                         : 
                                                                        ((0x14U 
                                                                          == 
                                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                           >> 0x1aU))
                                                                          ? 8U
                                                                          : 
                                                                         ((0x15U 
                                                                           == 
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0x1aU))
                                                                           ? 0xaU
                                                                           : 
                                                                          ((0x13U 
                                                                            == 
                                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                             >> 0x1aU))
                                                                            ? 0xbU
                                                                            : 
                                                                           ((0xf3U 
                                                                             == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43))
                                                                             ? 1U
                                                                             : 
                                                                            ((0x173U 
                                                                              == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43))
                                                                              ? 2U
                                                                              : 
                                                                             ((0x1f3U 
                                                                               == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43))
                                                                               ? 3U
                                                                               : 
                                                                              ((0x2f3U 
                                                                                == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43))
                                                                                ? 5U
                                                                                : 
                                                                               ((0x373U 
                                                                                == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43))
                                                                                 ? 6U
                                                                                 : 
                                                                                (7U 
                                                                                & (- (IData)(
                                                                                (0x3f3U 
                                                                                == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43))))))))))))))))))))))))))))))))))))))))))))
            : 0U);
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_59) 
           | ((6U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
              & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren 
        = ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
           | ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_60)) 
              & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr 
        = ((1U & ((~ ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58)) 
                      | (6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))) 
                  | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_59)))
            ? (0x1fU & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                        >> 5U)) : 0U);
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr 
        = ((1U & ((~ ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58)) 
                      | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_60))) 
                  | (5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
            ? (0x1fU & (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                        >> 0xaU)) : 0U);
    vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall 
        = (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen) 
            & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid) 
               & ((0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr)) 
                  & (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren) 
                      & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr) 
                         == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr))) 
                     | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren) 
                        & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr) 
                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr))))))) 
           | (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen) 
               & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid) 
                  & ((0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr)) 
                     & (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren) 
                         & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr) 
                            == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr))) 
                        | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren) 
                           & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr) 
                              == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr))))))) 
              | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen) 
                 & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid) 
                    & ((0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)) 
                       & (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren) 
                           & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr) 
                              == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr))) 
                          | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren) 
                             & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr) 
                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T_3 
        = (vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc 
           + (4U & ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall)) 
                    << 2U)));
    vlSelfRef.inst_sram_addr = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush)
                                 ? vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target
                                 : vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T_3);
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root____Vm_traceActivitySetAll(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root____Vm_traceActivitySetAll\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->mei = VL_RAND_RESET_I(1);
    vlSelf->msi = VL_RAND_RESET_I(1);
    vlSelf->mti = VL_RAND_RESET_I(1);
    vlSelf->sei = VL_RAND_RESET_I(1);
    vlSelf->inst_sram_en = VL_RAND_RESET_I(1);
    vlSelf->inst_sram_wen = VL_RAND_RESET_I(4);
    vlSelf->inst_sram_addr = VL_RAND_RESET_I(32);
    vlSelf->inst_sram_wdata = VL_RAND_RESET_I(32);
    vlSelf->inst_sram_rdata = VL_RAND_RESET_I(32);
    vlSelf->data_sram_en = VL_RAND_RESET_I(1);
    vlSelf->data_sram_wen = VL_RAND_RESET_I(4);
    vlSelf->data_sram_addr = VL_RAND_RESET_I(32);
    vlSelf->data_sram_wdata = VL_RAND_RESET_I(32);
    vlSelf->data_sram_rdata = VL_RAND_RESET_I(32);
    vlSelf->debug_commit = VL_RAND_RESET_I(1);
    vlSelf->debug_pc = VL_RAND_RESET_I(32);
    vlSelf->debug_rf_wnum = VL_RAND_RESET_I(5);
    vlSelf->debug_rf_wdata = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT___executeUnit_io_target = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_op = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T_3 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_59 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_60 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_10 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31 = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(1024, vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT___GEN);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm = VL_RAND_RESET_I(12);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__unnamedblk1__DOT___GEN = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___result_T_6 = VL_RAND_RESET_Q(33);
    vlSelf->top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_3 = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3 = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall = VL_RAND_RESET_I(1);
    vlSelf->__VdfgRegularize_hd87f99a1_1_18 = VL_RAND_RESET_I(1);
    vlSelf->__VdfgRegularize_hd87f99a1_1_20 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
