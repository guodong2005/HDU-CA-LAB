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
    vlSelfRef.data_sram_en = 0U;
    vlSelfRef.data_sram_addr = 0U;
    vlSelfRef.data_sram_wdata = 0ULL;
    vlSelfRef.data_sram_wen = 0U;
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
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___addResult_T_2;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___addResult_T_2 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___subResult_T_2;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___subResult_T_2 = 0;
    // Body
    vlSelfRef.inst_sram_en = (1U & (~ (IData)(vlSelfRef.reset)));
    vlSelfRef.inst_sram_addr = ((IData)(4U) + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc));
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T 
        = ((IData)(4U) + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc));
    vlSelfRef.debug_pc = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
    vlSelfRef.debug_rf_wnum = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
    vlSelfRef.debug_rf_wdata = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
    vlSelfRef.top__DOT__core__DOT__core__DOT___writeBackUnit_io_regfile_wen 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen) 
           & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___addResult_T_2 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data) 
           + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___subResult_T_2 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data) 
           - (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__arithmeticShiftResult 
        = VL_SHIFTRS_III(32,32,5, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data), 
                         (0x1fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[1U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[2U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[3U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[4U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[5U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[6U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[7U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[8U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[9U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xaU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xbU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xcU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xdU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xeU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0xfU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x10U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x11U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x12U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x13U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x14U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x15U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x16U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x17U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x18U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x19U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1aU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1bU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1cU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1dU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1eU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x1fU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x20U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x21U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x22U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x23U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x24U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x25U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x26U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x27U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x28U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x29U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x2aU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x2bU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x2cU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x2dU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x2eU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x2fU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x30U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x31U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x32U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x33U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x34U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x35U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x36U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x37U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x38U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x39U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x3aU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x3bU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x3cU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x3dU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x3eU] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31);
    vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[0x3fU] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31 
                   >> 0x20U));
    vlSelfRef.debug_commit = vlSelfRef.top__DOT__core__DOT__core__DOT___writeBackUnit_io_regfile_wen;
    vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_memoryStage_data_rd_info_wdata 
        = ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
            ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
               + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
            : ((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                   - vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                : ((7U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                    ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                       & vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                    : ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                        ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                           | vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                        : ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                            ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                               ^ vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                            : ((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                ? (QData)((IData)(VL_LTS_IQQ(64, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                : ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                    ? (QData)((IData)(
                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                       < vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                    : ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                        ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                           << (0x3fU 
                                               & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                        : ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                            ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                               >> (0x3fU 
                                                   & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                            : ((0xdU 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                ? VL_SHIFTRS_QQI(64,64,6, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, 
                                                                 (0x3fU 
                                                                  & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                                : (
                                                   (0x10U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? 
                                                   (((QData)((IData)(
                                                                     (- (IData)(
                                                                                (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___addResult_T_2 
                                                                                >> 0x1fU))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___addResult_T_2)))
                                                    : 
                                                   ((0x18U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? 
                                                    (((QData)((IData)(
                                                                      (- (IData)(
                                                                                (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___subResult_T_2 
                                                                                >> 0x1fU))))) 
                                                      << 0x20U) 
                                                     | (QData)((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___subResult_T_2)))
                                                     : 
                                                    ((0x11U 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                      ? 
                                                     (((QData)((IData)(
                                                                       (- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (0xffffffffULL 
                                                                                & (((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data)) 
                                                                                << 
                                                                                (0x1fU 
                                                                                & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))) 
                                                                                >> 0x1fU)))))))) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(
                                                                        ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data) 
                                                                         << 
                                                                         (0x1fU 
                                                                          & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))))))
                                                      : 
                                                     ((0x15U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                       ? (QData)((IData)(
                                                                         ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data) 
                                                                          >> 
                                                                          (0x1fU 
                                                                           & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))))
                                                       : 
                                                      ((0x1dU 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                        ? 
                                                       (((QData)((IData)(
                                                                         (- (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__arithmeticShiftResult 
                                                                                >> 0x1fU))))) 
                                                         << 0x20U) 
                                                        | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__arithmeticShiftResult)))
                                                        : 0ULL)))))))))))))));
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
    vlSelf->data_sram_wen = VL_RAND_RESET_I(8);
    vlSelf->data_sram_addr = VL_RAND_RESET_I(32);
    vlSelf->data_sram_wdata = VL_RAND_RESET_Q(64);
    vlSelf->data_sram_rdata = VL_RAND_RESET_Q(64);
    vlSelf->debug_commit = VL_RAND_RESET_I(1);
    vlSelf->debug_pc = VL_RAND_RESET_Q(64);
    vlSelf->debug_rf_wnum = VL_RAND_RESET_I(5);
    vlSelf->debug_rf_wdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT___writeBackUnit_io_regfile_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT___executeUnit_io_memoryStage_data_rd_info_wdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31 = VL_RAND_RESET_Q(64);
    VL_RAND_RESET_W(2048, vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT___GEN);
    vlSelf->top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__arithmeticShiftResult = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata = VL_RAND_RESET_Q(64);
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
