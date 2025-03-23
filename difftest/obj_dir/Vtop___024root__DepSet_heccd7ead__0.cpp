// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.inst_sram_en = (1U & (~ (IData)(vlSelfRef.reset)));
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_1;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_1 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2 = 0;
    CData/*1:0*/ __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 0;
    // Body
    __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.reset)))))) {
        VL_FWRITEF_NX(0x80000002U,"info.fusel: %1#, lsu.io.result:                    0\n",0,
                      2,vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel);
    }
    if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.reset)))))) {
        VL_FWRITEF_NX(0x80000002U,"current inst: 0x%x, instrType: %1#, fuType: %1#, fuOpType: %2#\n",0,
                      64,vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst,
                      3,(IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType),
                      2,vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuType,
                      5,(((0x13U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                          | (0x33U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                          ? 0U : (((0x93U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                   | (0xb3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                   ? 1U : (((0x113U 
                                             == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                            | (0x133U 
                                               == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                            ? 2U : 
                                           (((0x193U 
                                              == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                             | (0x1b3U 
                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                             ? 3U : 
                                            (((0x213U 
                                               == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                              | (0x233U 
                                                 == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                              ? 4U : 
                                             (((0x293U 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                               | (0x2b3U 
                                                  == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                               ? 5U
                                               : ((
                                                   (0x4293U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                                   | (0x82b3U 
                                                      == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                                   ? 0xdU
                                                   : 
                                                  (((0x313U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                    | (0x333U 
                                                       == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                                    ? 6U
                                                    : 
                                                   (((0x393U 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                     | (0x3b3U 
                                                        == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                                     ? 7U
                                                     : 
                                                    ((0x8033U 
                                                      == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                      ? 8U
                                                      : 
                                                     ((0x433U 
                                                       == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                       ? 0U
                                                       : 
                                                      ((0x4b3U 
                                                        == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                        ? 1U
                                                        : 
                                                       ((0x533U 
                                                         == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                         ? 2U
                                                         : 
                                                        ((0x5b3U 
                                                          == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                          ? 3U
                                                          : 
                                                         ((0x633U 
                                                           == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                           ? 4U
                                                           : 
                                                          ((0x6b3U 
                                                            == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                            ? 5U
                                                            : 
                                                           ((0x733U 
                                                             == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                             ? 6U
                                                             : 
                                                            ((0x7b3U 
                                                              == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                              ? 7U
                                                              : 
                                                             ((3U 
                                                               == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                               ? 0U
                                                               : 
                                                              ((0x203U 
                                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                ? 4U
                                                                : 
                                                               ((0x83U 
                                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                 ? 1U
                                                                 : 
                                                                ((0x283U 
                                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                  ? 5U
                                                                  : 
                                                                 ((0x103U 
                                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                   ? 2U
                                                                   : 
                                                                  ((0x23U 
                                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                    ? 8U
                                                                    : 
                                                                   ((0xa3U 
                                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                     ? 9U
                                                                     : 
                                                                    ((0x123U 
                                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                      ? 0xaU
                                                                      : 
                                                                     ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56)
                                                                       ? 0U
                                                                       : 
                                                                      ((0x1bU 
                                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                        ? 0x10U
                                                                        : 
                                                                       ((0x9bU 
                                                                         == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                         ? 0x11U
                                                                         : 
                                                                        ((0x29bU 
                                                                          == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                          ? 0x15U
                                                                          : 
                                                                         ((0x829bU 
                                                                           == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                           ? 0x1dU
                                                                           : 
                                                                          ((0xbbU 
                                                                            == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                            ? 0x11U
                                                                            : 
                                                                           ((0x2bbU 
                                                                             == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                             ? 0x15U
                                                                             : 
                                                                            ((0x82bbU 
                                                                              == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                              ? 0x1dU
                                                                              : 
                                                                             ((0x3bU 
                                                                               == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                               ? 0x10U
                                                                               : 
                                                                              ((0x803bU 
                                                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                ? 0x18U
                                                                                : 
                                                                               ((0x43bU 
                                                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 8U
                                                                                 : 
                                                                                ((0x63bU 
                                                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0xcU
                                                                                 : 
                                                                                ((0x6bbU 
                                                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0xdU
                                                                                 : 
                                                                                ((0x73bU 
                                                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0xeU
                                                                                 : 
                                                                                ((0x7bbU 
                                                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0xfU
                                                                                 : 
                                                                                ((0x183U 
                                                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                                 ? 3U
                                                                                 : 
                                                                                ((0x1a3U 
                                                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                                 ? 0xbU
                                                                                 : 0U))))))))))))))))))))))))))))))))))))))))))));
    }
    vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata = 0ULL;
    vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
    if (vlSelfRef.reset) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst = 0ULL;
        __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc = 0x7ffffffcULL;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuType;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr 
            = (((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                | ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                   | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                      | (2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))))
                ? (0x1fU & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                    >> 7U))) : 0U);
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
            = (QData)((IData)(vlSelfRef.inst_sram_rdata));
        if ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 1U;
        } else if ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 2U;
        }
        if ((0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc 
                = (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T));
        }
    }
    vlSelfRef.debug_rf_wdata = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
    vlSelfRef.debug_commit = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid;
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
    vlSelfRef.debug_pc = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
    vlSelfRef.debug_rf_wnum = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (2U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56 
        = ((0x17U == (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst))) 
           | (0x37U == (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN 
        = ((0x380U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                               >> 0xcU)) << 7U)) | 
           (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state 
        = __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57 
        = ((0x23U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
           | ((0xa3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
              | (0x123U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2 
        = ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
           | ((0x203U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
              | ((0x83U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                 | ((0x283U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                    | (0x103U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3 
        = ((0xfc00U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                >> 0x1aU)) << 0xaU)) 
           | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1 
        = ((0x1fc00U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                 >> 0x19U)) << 0xaU)) 
           | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN));
    vlSelfRef.inst_sram_addr = ((IData)(4U) + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc));
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T 
        = ((IData)(4U) + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55 
        = ((0x43bU == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
           | ((0x63bU == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
              | ((0x6bbU == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                 | ((0x73bU == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                    | (0x7bbU == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58 
        = ((0x433U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
           | ((0x4b3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
              | ((0x533U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                 | ((0x5b3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                    | ((0x633U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                       | ((0x6b3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                          | ((0x733U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                             | (0x7b3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))))))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_1 
        = ((0x3b3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
           | (0x8033U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType 
        = ((0x13U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
            ? 4U : ((0x33U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                     ? 5U : ((0x93U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3))
                              ? 4U : ((0xb3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                       ? 5U : ((0x113U 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                ? 4U
                                                : (
                                                   (0x133U 
                                                    == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                    ? 5U
                                                    : 
                                                   ((0x193U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                     ? 4U
                                                     : 
                                                    ((0x1b3U 
                                                      == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                      ? 5U
                                                      : 
                                                     ((0x213U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                       ? 4U
                                                       : 
                                                      ((0x233U 
                                                        == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                        ? 5U
                                                        : 
                                                       ((0x293U 
                                                         == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3))
                                                         ? 4U
                                                         : 
                                                        ((0x2b3U 
                                                          == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                          ? 5U
                                                          : 
                                                         ((0x4293U 
                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3))
                                                           ? 4U
                                                           : 
                                                          ((0x82b3U 
                                                            == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                            ? 5U
                                                            : 
                                                           ((0x313U 
                                                             == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                             ? 4U
                                                             : 
                                                            ((0x333U 
                                                              == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                              ? 5U
                                                              : 
                                                             ((0x393U 
                                                               == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                               ? 4U
                                                               : 
                                                              (((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_1) 
                                                                | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58))
                                                                ? 5U
                                                                : 
                                                               ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2)
                                                                 ? 4U
                                                                 : 
                                                                ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57)
                                                                  ? 2U
                                                                  : 
                                                                 ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56)
                                                                   ? 6U
                                                                   : 
                                                                  (((0x1bU 
                                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                                    | ((0x9bU 
                                                                        == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                       | ((0x29bU 
                                                                           == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                          | (0x829bU 
                                                                             == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))))
                                                                    ? 4U
                                                                    : 
                                                                   (((0xbbU 
                                                                      == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                     | ((0x2bbU 
                                                                         == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                        | ((0x82bbU 
                                                                            == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                           | ((0x3bU 
                                                                               == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                              | ((0x803bU 
                                                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                                | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55))))))
                                                                     ? 5U
                                                                     : 
                                                                    ((0x183U 
                                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                      ? 4U
                                                                      : 
                                                                     ((0x1a3U 
                                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                                      << 1U)))))))))))))))))))))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuType 
        = (((0x13U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
            | ((0x33U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
               | ((0x93U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                  | ((0xb3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                     | ((0x113U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                        | ((0x133U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                           | ((0x193U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                              | ((0x1b3U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                 | ((0x213U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                    | ((0x233U == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                       | ((0x293U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                          | ((0x2b3U 
                                              == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                             | ((0x4293U 
                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                                | ((0x82b3U 
                                                    == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                   | ((0x313U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                      | ((0x333U 
                                                          == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                         | ((0x393U 
                                                             == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                            | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_1))))))))))))))))))
            ? 0U : ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58)
                     ? 1U : (((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2) 
                              | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57))
                              ? 2U : (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56) 
                                       | ((0x1bU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                          | ((0x9bU 
                                              == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                             | ((0x29bU 
                                                 == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                | ((0x829bU 
                                                    == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                   | ((0xbbU 
                                                       == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                      | ((0x2bbU 
                                                          == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                         | ((0x82bbU 
                                                             == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                            | ((0x3bU 
                                                                == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                               | (0x803bU 
                                                                  == vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))))))))))
                                       ? 0U : ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55)
                                                ? 1U
                                                : (
                                                   ((0x183U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                    | (0x1a3U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))) 
                                                   << 1U))))));
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("core/top_sram_wrapper.v", 1, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("core/top_sram_wrapper.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("core/top_sram_wrapper.v", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clock & 0xfeU)))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY(((vlSelfRef.mei & 0xfeU)))) {
        Verilated::overWidthError("mei");}
    if (VL_UNLIKELY(((vlSelfRef.msi & 0xfeU)))) {
        Verilated::overWidthError("msi");}
    if (VL_UNLIKELY(((vlSelfRef.mti & 0xfeU)))) {
        Verilated::overWidthError("mti");}
    if (VL_UNLIKELY(((vlSelfRef.sei & 0xfeU)))) {
        Verilated::overWidthError("sei");}
}
#endif  // VL_DEBUG
