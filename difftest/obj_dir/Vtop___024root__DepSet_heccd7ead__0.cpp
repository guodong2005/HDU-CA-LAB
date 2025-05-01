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
    CData/*1:0*/ __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 0;
    CData/*0:0*/ __Vdly__top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid;
    __Vdly__top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid = 0;
    // Body
    __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    __Vdly__top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid;
    __Vdly__top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush)) 
                                                   & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall)
                                                       ? (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid)
                                                       : 
                                                      (2U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state)))));
    if (vlSelfRef.reset) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc = 0U;
        vlSelfRef.debug_pc = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31 = 0U;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3 
            = (7U & vlSelfRef.data_sram_addr);
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc;
        vlSelfRef.debug_pc = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0 
            = (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen) 
                & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid)) 
               & (0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)));
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (~ (IData)((0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (7U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (9U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0xbU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0xcU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0xdU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0xeU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0xfU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x10U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x11U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x12U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x13U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x14U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x15U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x16U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x17U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x18U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x19U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1aU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1bU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1cU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1dU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1eU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
        if (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1fU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        }
    }
    vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen));
    vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
    if (vlSelfRef.reset) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata = 0U;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata 
            = ((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel))
                ? (((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                     ? (((- (IData)((1U & (vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData 
                                           >> 7U)))) 
                         << 8U) | (0xffU & vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData))
                     : 0U) | (((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                ? (0xffU & vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData)
                                : 0U) | (((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                           ? (((- (IData)(
                                                          (1U 
                                                           & (vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData 
                                                              >> 0xfU)))) 
                                               << 0x10U) 
                                              | (0xffffU 
                                                 & vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData))
                                           : 0U) | 
                                         (((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                            ? (0xffffU 
                                               & vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData)
                                            : 0U) | 
                                          (((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                             ? vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData
                                             : 0U) 
                                           | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                               ? vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData
                                               : 0U))))))
                : vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata);
    }
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
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen));
    vlSelfRef.debug_rf_wnum = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
    vlSelfRef.debug_commit = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid;
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
    if (vlSelfRef.reset) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst = 0U;
        __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc = 0x7ffffffcU;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata 
            = (((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                 ? ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                     ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                        + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                     : ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                         ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                            - vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                         : ((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                             ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                & vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                             : ((7U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                 ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                    | vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                 : ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                     ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                        ^ vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                     : ((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                         ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_18)
                                         : ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                             ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_20)
                                             : ((9U 
                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                 ? 
                                                VL_SHIFTL_III(32,32,6, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, 
                                                              (0x3fU 
                                                               & vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))
                                                 : 
                                                ((5U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                  ? 
                                                 VL_SHIFTR_III(32,32,6, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, 
                                                               (0x3fU 
                                                                & vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))
                                                  : 
                                                 ((6U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                   ? 
                                                  VL_SHIFTRS_III(32,32,6, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, 
                                                                 (0x3fU 
                                                                  & vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))
                                                   : 0U))))))))))
                 : 0U) | (((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                            ? ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                   * vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                : ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                    ? (IData)((((((QData)((IData)(
                                                                  (- (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                                              >> 0x1fU))))) 
                                                  << 0x20U) 
                                                 | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))) 
                                                * (
                                                   ((QData)((IData)(
                                                                    (- (IData)(
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                                                >> 0x1fU))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                               >> 0x20U))
                                    : ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                        ? (IData)((
                                                   ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data)) 
                                                    * (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))) 
                                                   >> 0x20U))
                                        : ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                            ? (((0xffffffffU 
                                                 == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data) 
                                                & (0x80000000U 
                                                   == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))
                                                ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data
                                                : (
                                                   (0U 
                                                    == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                    ? 0xffffffffU
                                                    : (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___result_T_6)))
                                            : ((5U 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                ? (
                                                   (0U 
                                                    == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                    ? 0xffffffffU
                                                    : vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_3)
                                                : (
                                                   (6U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? 
                                                   ((0U 
                                                     == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                     ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data
                                                     : 
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                     - 
                                                     ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___result_T_6) 
                                                      * vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? 
                                                    ((0U 
                                                      == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                      ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data
                                                      : 
                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                      - 
                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_3 
                                                       * vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                                     : 0U)))))))
                            : 0U) | ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                      ? ((0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                          ? ((IData)(4U) 
                                             + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                          : ((0xbU 
                                              == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                              ? ((IData)(4U) 
                                                 + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                              : 0U))
                                      : 0U)));
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__unnamedblk1__DOT___GEN 
            = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush) 
               | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall));
        if (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__unnamedblk1__DOT___GEN) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc = 0U;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op = 0U;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr = 0U;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm = 0U;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel = 0U;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data = 0U;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data = 0U;
        } else {
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op 
                = vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_op;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr 
                = ((1U & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_59) 
                          | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                             | ((~ ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_10)) 
                                    | (1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))) 
                                | (2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))))
                    ? (0x1fU & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)
                    : 0U);
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm 
                = (0xfffU & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm);
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel 
                = vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                    ? (((0U == (0x1fU & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U)))
                         ? 0U : (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                 (((IData)(0x1fU) + 
                                   (0x3ffU & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))) 
                                  >> 5U)] << ((IData)(0x20U) 
                                              - (0x1fU 
                                                 & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))))) 
                       | (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                          (0x1fU & (VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U) 
                                    >> 5U))] >> (0x1fU 
                                                 & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))))
                    : ((0x37U == (0x7fU & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst))
                        ? 0U : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc));
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren)
                    ? (((0U == (0x1fU & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U)))
                         ? 0U : (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                 (((IData)(0x1fU) + 
                                   (0x3ffU & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))) 
                                  >> 5U)] << ((IData)(0x20U) 
                                              - (0x1fU 
                                                 & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))))) 
                       | (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                          (0x1fU & (VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U) 
                                    >> 5U))] >> (0x1fU 
                                                 & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))))
                    : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm);
        }
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid 
            = ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__unnamedblk1__DOT___GEN)) 
               & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen 
            = ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__unnamedblk1__DOT___GEN)) 
               & ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                  | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_60) 
                     | ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58)) 
                        & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_10)))));
        if (vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc = 0U;
            vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall)))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc 
                = vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc;
            vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                = vlSelfRef.inst_sram_rdata;
        }
        if ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 1U;
        } else if ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 2U;
        }
        if ((0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc 
                = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush)
                    ? vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target
                    : vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T_3);
        }
    }
    vlSelfRef.debug_rf_wdata = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid 
        = __Vdly__top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid;
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
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0 
        = (((- (IData)((1U & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm) 
                              >> 0xbU)))) << 0xcU) 
           | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid) 
           & (3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel)));
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
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_18 = VL_LTS_III(32, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_20 = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                 < vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__lsu__DOT____VdfgRegularize_h932ecef8_0_1 
        = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
           + top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0);
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4 
        = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc 
           + top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0);
    vlSelfRef.data_sram_addr = (((8U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                  ? top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__lsu__DOT____VdfgRegularize_h932ecef8_0_1
                                  : 0U) | ((8U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                            ? 0U : top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__lsu__DOT____VdfgRegularize_h932ecef8_0_1));
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
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state 
        = __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    if ((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3;
    } else if ((0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3;
    } else if ((0xbU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
               + (((- (IData)((1U & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm) 
                                     >> 0xbU)))) << 0xdU) 
                  | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm) 
                     << 1U)));
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3;
    } else if ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                  == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    } else if ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                  != vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    } else if ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_18));
    } else if ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & VL_GTES_III(32, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    } else if ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3) 
               & (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_20));
    } else if ((7U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target 
            = top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_4;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush 
            = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid) 
               & ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel)) 
                  & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                     >= vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush = 0U;
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
