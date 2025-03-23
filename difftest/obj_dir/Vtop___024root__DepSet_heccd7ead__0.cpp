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
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT____VdfgRegularize_h56152d37_0_0 
        = (0xffU & (((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                      ? (IData)(vlSelfRef.data_sram_rdata)
                      : 0U) | (((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                 ? (IData)((vlSelfRef.data_sram_rdata 
                                            >> 8U))
                                 : 0U) | (((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                            ? (IData)(
                                                      (vlSelfRef.data_sram_rdata 
                                                       >> 0x10U))
                                            : 0U) | 
                                          (((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                             ? (IData)(
                                                       (vlSelfRef.data_sram_rdata 
                                                        >> 0x18U))
                                             : 0U) 
                                           | (((4U 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                ? (IData)(
                                                          (vlSelfRef.data_sram_rdata 
                                                           >> 0x20U))
                                                : 0U) 
                                              | (((5U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                   ? (IData)(
                                                             (vlSelfRef.data_sram_rdata 
                                                              >> 0x28U))
                                                   : 0U) 
                                                 | (((6U 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                      ? (IData)(
                                                                (vlSelfRef.data_sram_rdata 
                                                                 >> 0x30U))
                                                      : 0U) 
                                                    | ((7U 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                        ? (IData)(
                                                                  (vlSelfRef.data_sram_rdata 
                                                                   >> 0x38U))
                                                        : 0U)))))))));
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
    SData/*9:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN = 0;
    IData/*16:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1 = 0;
    SData/*15:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_3;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_3 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___addResult_T_2;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___addResult_T_2 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___subResult_T_2;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___subResult_T_2 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___arithmeticShiftResult_T_3;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___arithmeticShiftResult_T_3 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___mulResult_T_2;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___mulResult_T_2 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_5;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_5 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_6;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_6 = 0;
    QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_8;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_8 = 0;
    CData/*1:0*/ __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 0;
    VlWide<4>/*127:0*/ __Vtemp_25;
    VlWide<4>/*127:0*/ __Vtemp_26;
    VlWide<4>/*127:0*/ __Vtemp_27;
    VlWide<4>/*127:0*/ __Vtemp_28;
    VlWide<4>/*127:0*/ __Vtemp_29;
    VlWide<4>/*127:0*/ __Vtemp_30;
    VlWide<4>/*127:0*/ __Vtemp_31;
    VlWide<3>/*95:0*/ __Vtemp_33;
    VlWide<3>/*95:0*/ __Vtemp_34;
    VlWide<3>/*95:0*/ __Vtemp_35;
    VlWide<3>/*95:0*/ __Vtemp_38;
    VlWide<3>/*95:0*/ __Vtemp_39;
    VlWide<3>/*95:0*/ __Vtemp_40;
    // Body
    __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.reset)))))) {
        VL_FWRITEF_NX(0x80000002U,"tmpwen: %b, io.info.op: %2#, io.src_info.src2_data: %x\n",0,
                      8,(0xffU & ((3U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op)) 
                                  << (7U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data)))),
                      5,(IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op),
                      64,vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    }
    if (vlSelfRef.reset) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3 = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31 = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op = 0U;
        __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc = 0x7ffffffcULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst = 0ULL;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3 
            = (7U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data));
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
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
            = vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_src_info_src2_data;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
            = (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_63) 
                | ((6U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                   & (2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                ? (((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                    (((IData)(0x3fU) 
                                      + (0x7ffU & VL_SHIFTL_III(11,11,32, 
                                                                ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                                                                  ? 
                                                                 (0x1fU 
                                                                  & (IData)(
                                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                             >> 0xfU)))
                                                                  : 0U), 6U))) 
                                     >> 5U)])) << (
                                                   (0U 
                                                    == 
                                                    (0x1fU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                                                                       ? 
                                                                      (0x1fU 
                                                                       & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                       : 0U), 6U)))
                                                    ? 0x20U
                                                    : 
                                                   ((IData)(0x40U) 
                                                    - 
                                                    (0x1fU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                                                                       ? 
                                                                      (0x1fU 
                                                                       & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                       : 0U), 6U))))) 
                   | (((0U == (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                     ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                                                       ? 
                                                      (0x1fU 
                                                       & (IData)(
                                                                 (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                  >> 0xfU)))
                                                       : 0U), 6U)))
                        ? 0ULL : ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                  (((IData)(0x1fU) 
                                                    + 
                                                    (0x7ffU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                                                                       ? 
                                                                      (0x1fU 
                                                                       & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                       : 0U), 6U))) 
                                                   >> 5U)])) 
                                  << ((IData)(0x20U) 
                                      - (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                               ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                                                                 ? 
                                                                (0x1fU 
                                                                 & (IData)(
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0xfU)))
                                                                 : 0U), 6U))))) 
                      | ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                         (0x3fU & (
                                                   VL_SHIFTL_III(11,11,32, 
                                                                 ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                                                                   ? 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0xfU)))
                                                                   : 0U), 6U) 
                                                   >> 5U))])) 
                         >> (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                   ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                                                     ? 
                                                    (0x1fU 
                                                     & (IData)(
                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                >> 0xfU)))
                                                     : 0U), 6U)))))
                : ((0x37U == (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)))
                    ? 0ULL : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc));
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata 
            = ((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel))
                ? ((((4U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                      ? 0ULL : (0xffffffffffffffULL 
                                & (- (QData)((IData)(
                                                     ((2U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel)) 
                                                      & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT____VdfgRegularize_h56152d37_0_0) 
                                                         >> 7U))))))) 
                    << 8U) | (QData)((IData)(((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel))
                                               ? (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT____VdfgRegularize_h56152d37_0_0)
                                               : 0U))))
                : vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata);
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata 
            = (((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                 ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result
                 : 0ULL) | ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                             ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result
                             : 0ULL));
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr 
            = (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_reg_wen) 
                | (2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))
                ? (0x1fU & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                    >> 7U))) : 0U);
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel 
            = vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op 
            = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64)
                ? ((0x10U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___op_T_29)) 
                   | (0xfU & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___op_T_29) 
                              | ((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                  ? ((8U & ((IData)(
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 5U)) 
                                            << 3U)) 
                                     | (7U & (IData)(
                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                      >> 0xcU))))
                                  : 0U)))) : 0U);
        if ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 1U;
        } else if ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 2U;
        }
        if ((0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc 
                = (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T));
        }
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
            = (QData)((IData)(vlSelfRef.inst_sram_rdata));
    }
    vlSelfRef.debug_pc = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
    vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen));
    vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
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
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT____VdfgRegularize_h56152d37_0_0 
        = (0xffU & (((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                      ? (IData)(vlSelfRef.data_sram_rdata)
                      : 0U) | (((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                 ? (IData)((vlSelfRef.data_sram_rdata 
                                            >> 8U))
                                 : 0U) | (((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                            ? (IData)(
                                                      (vlSelfRef.data_sram_rdata 
                                                       >> 0x10U))
                                            : 0U) | 
                                          (((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                             ? (IData)(
                                                       (vlSelfRef.data_sram_rdata 
                                                        >> 0x18U))
                                             : 0U) 
                                           | (((4U 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                ? (IData)(
                                                          (vlSelfRef.data_sram_rdata 
                                                           >> 0x20U))
                                                : 0U) 
                                              | (((5U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                   ? (IData)(
                                                             (vlSelfRef.data_sram_rdata 
                                                              >> 0x28U))
                                                   : 0U) 
                                                 | (((6U 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                      ? (IData)(
                                                                (vlSelfRef.data_sram_rdata 
                                                                 >> 0x30U))
                                                      : 0U) 
                                                    | ((7U 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3))
                                                        ? (IData)(
                                                                  (vlSelfRef.data_sram_rdata 
                                                                   >> 0x38U))
                                                        : 0U)))))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0[0U] 
        = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data);
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0[1U] 
        = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                   >> 0x20U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0[2U] 
        = (IData)((- (QData)((IData)((1U & (IData)(
                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                    >> 0x3fU)))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0[3U] 
        = (IData)(((- (QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                     >> 0x3fU)))))) 
                   >> 0x20U));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_6 
        = ((0xffffffffffffffffULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data) 
           & (0xffffffff80000000ULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_8 
        = VL_DIV_QQQ(64, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data, vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    vlSelfRef.data_sram_addr = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data);
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen));
    vlSelfRef.debug_commit = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid;
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
    vlSelfRef.debug_rf_wnum = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
    vlSelfRef.debug_rf_wdata = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___addResult_T_2 
        = (vlSelfRef.data_sram_addr + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___subResult_T_2 
        = (vlSelfRef.data_sram_addr - (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT__logicalShiftResult 
        = (vlSelfRef.data_sram_addr >> (0x1fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___arithmeticShiftResult_T_3 
        = VL_SHIFTRS_III(32,32,5, vlSelfRef.data_sram_addr, 
                         (0x1fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___mulResult_T_2 
        = (vlSelfRef.data_sram_addr * (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_5 
        = VL_DIV_III(32, vlSelfRef.data_sram_addr, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__divtmp 
        = (0x1ffffffffULL & VL_DIVS_QQQ(33, (((QData)((IData)(
                                                              (1U 
                                                               & (IData)(
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                                          >> 0x1fU))))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.data_sram_addr))), 
                                        (((QData)((IData)(
                                                          (1U 
                                                           & (IData)(
                                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                                      >> 0x1fU))))) 
                                          << 0x20U) 
                                         | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))));
    if ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult_1 
            = vlSelfRef.data_sram_addr;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult 
            = vlSelfRef.data_sram_addr;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult_1 
            = (vlSelfRef.data_sram_addr - (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_5 
                                           * (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult 
            = (vlSelfRef.data_sram_addr - ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__divtmp) 
                                           * (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
    }
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_reg_wen));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (2U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state)));
    vlSelfRef.data_sram_wdata = (((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                   ? (((QData)((IData)(
                                                       (0xffU 
                                                        & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                       << 0x38U) | 
                                      (((QData)((IData)(
                                                        (0xffU 
                                                         & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                        << 0x30U) | 
                                       (((QData)((IData)(
                                                         (0xffU 
                                                          & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                         << 0x28U) 
                                        | (((QData)((IData)(
                                                            (0xffU 
                                                             & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                            << 0x20U) 
                                           | (((QData)((IData)(
                                                               (0xffU 
                                                                & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                               << 0x18U) 
                                              | (((QData)((IData)(
                                                                  (0xffU 
                                                                   & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                                  << 0x10U) 
                                                 | (((QData)((IData)(
                                                                     (0xffU 
                                                                      & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                                     << 8U) 
                                                    | (QData)((IData)(
                                                                      (0xffU 
                                                                       & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))))))))))
                                   : 0ULL) | (((9U 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                ? (
                                                   ((QData)((IData)(
                                                                    (0xffffU 
                                                                     & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                                    << 0x30U) 
                                                   | (((QData)((IData)(
                                                                       (0xffffU 
                                                                        & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                                       << 0x20U) 
                                                      | (((QData)((IData)(
                                                                          (0xffffU 
                                                                           & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                                          << 0x10U) 
                                                         | (QData)((IData)(
                                                                           (0xffffU 
                                                                            & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))))))
                                                : 0ULL) 
                                              | (((0xaU 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                   ? 
                                                  (((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                                   : 0ULL) 
                                                 | ((0xbU 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data
                                                     : 0ULL))));
    vlSelfRef.data_sram_wen = (0xffU & (((3U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op)) 
                                         << (7U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))) 
                                        & (- (IData)(
                                                     ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid) 
                                                      & ((2U 
                                                          == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel)) 
                                                         & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op) 
                                                            >> 3U)))))));
    __Vtemp_25[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    __Vtemp_25[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                              >> 0x20U));
    __Vtemp_25[2U] = (IData)((- (QData)((IData)((1U 
                                                 & (IData)(
                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                            >> 0x3fU)))))));
    __Vtemp_25[3U] = (IData)(((- (QData)((IData)((1U 
                                                  & (IData)(
                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                             >> 0x3fU)))))) 
                              >> 0x20U));
    VL_MUL_W(4, __Vtemp_26, vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0, __Vtemp_25);
    __Vtemp_27[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    __Vtemp_27[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                              >> 0x20U));
    __Vtemp_27[2U] = 0U;
    __Vtemp_27[3U] = 0U;
    VL_MUL_W(4, __Vtemp_28, vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0, __Vtemp_27);
    __Vtemp_29[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data);
    __Vtemp_29[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                              >> 0x20U));
    __Vtemp_29[2U] = 0U;
    __Vtemp_29[3U] = 0U;
    __Vtemp_30[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    __Vtemp_30[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                              >> 0x20U));
    __Vtemp_30[2U] = 0U;
    __Vtemp_30[3U] = 0U;
    VL_MUL_W(4, __Vtemp_31, __Vtemp_29, __Vtemp_30);
    __Vtemp_33[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data);
    __Vtemp_33[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                              >> 0x20U));
    __Vtemp_33[2U] = (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                    >> 0x3fU)));
    __Vtemp_34[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    __Vtemp_34[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                              >> 0x20U));
    __Vtemp_34[2U] = (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                    >> 0x3fU)));
    VL_DIVS_WWW(65, __Vtemp_35, __Vtemp_33, __Vtemp_34);
    __Vtemp_38[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data);
    __Vtemp_38[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                              >> 0x20U));
    __Vtemp_38[2U] = (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                    >> 0x3fU)));
    __Vtemp_39[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    __Vtemp_39[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                              >> 0x20U));
    __Vtemp_39[2U] = (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                    >> 0x3fU)));
    VL_DIVS_WWW(65, __Vtemp_40, __Vtemp_38, __Vtemp_39);
    if ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result 
            = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
               + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result 
            = (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
               * vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result 
            = ((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
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
                                                                                (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___addResult_T_2 
                                                                                >> 0x1fU))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___addResult_T_2)))
                                                    : 
                                                   ((0x18U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? 
                                                    (((QData)((IData)(
                                                                      (- (IData)(
                                                                                (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___subResult_T_2 
                                                                                >> 0x1fU))))) 
                                                      << 0x20U) 
                                                     | (QData)((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___subResult_T_2)))
                                                     : 
                                                    ((0x11U 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                      ? 
                                                     (((QData)((IData)(
                                                                       (- (IData)(
                                                                                (1U 
                                                                                & (IData)(
                                                                                (0xffffffffULL 
                                                                                & (((QData)((IData)(vlSelfRef.data_sram_addr)) 
                                                                                << 
                                                                                (0x1fU 
                                                                                & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))) 
                                                                                >> 0x1fU)))))))) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(
                                                                        (vlSelfRef.data_sram_addr 
                                                                         << 
                                                                         (0x1fU 
                                                                          & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))))))
                                                      : 
                                                     ((0x15U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                       ? 
                                                      (((QData)((IData)(
                                                                        (- (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT__logicalShiftResult 
                                                                                >> 0x1fU))))) 
                                                        << 0x20U) 
                                                       | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT__logicalShiftResult)))
                                                       : 
                                                      ((0x1dU 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                        ? 
                                                       (((QData)((IData)(
                                                                         (- (IData)(
                                                                                (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___arithmeticShiftResult_T_3 
                                                                                >> 0x1fU))))) 
                                                         << 0x20U) 
                                                        | (QData)((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT___arithmeticShiftResult_T_3)))
                                                        : 0ULL))))))))))))));
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result 
            = ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                ? (((QData)((IData)(__Vtemp_26[3U])) 
                    << 0x20U) | (QData)((IData)(__Vtemp_26[2U])))
                : ((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                    ? (((QData)((IData)(__Vtemp_28[3U])) 
                        << 0x20U) | (QData)((IData)(
                                                    __Vtemp_28[2U])))
                    : ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                        ? (((QData)((IData)(__Vtemp_31[3U])) 
                            << 0x20U) | (QData)((IData)(
                                                        __Vtemp_31[2U])))
                        : ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                            ? ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_6)
                                ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data
                                : ((0ULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                    ? 0xffffffffffffffffULL
                                    : (((QData)((IData)(
                                                        __Vtemp_35[1U])) 
                                        << 0x20U) | (QData)((IData)(
                                                                    __Vtemp_35[0U])))))
                            : ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                ? ((0ULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                    ? 0xffffffffffffffffULL
                                    : top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_8)
                                : ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                    ? ((0ULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                        ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data
                                        : (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                           - ((((QData)((IData)(
                                                                __Vtemp_40[1U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 __Vtemp_40[0U]))) 
                                              * vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                    : ((7U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                        ? ((0ULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                            ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data
                                            : (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                               - (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_8 
                                                  * vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))
                                        : ((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                            ? (((QData)((IData)(
                                                                (- (IData)(
                                                                           (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___mulResult_T_2 
                                                                            >> 0x1fU))))) 
                                                << 0x20U) 
                                               | (QData)((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___mulResult_T_2)))
                                            : ((0xcU 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                ? ((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_6)
                                                    ? 0xffffffffffffffffULL
                                                    : 
                                                   (((QData)((IData)(
                                                                     (- (IData)(
                                                                                (1U 
                                                                                & ((0U 
                                                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)) 
                                                                                | (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__divtmp 
                                                                                >> 0x1fU)))))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(
                                                                      ((0U 
                                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))
                                                                        ? 0xffffffffU
                                                                        : (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__divtmp))))))
                                                : (
                                                   (0xdU 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? 
                                                   (((QData)((IData)(
                                                                     (- (IData)(
                                                                                ((top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_5 
                                                                                >> 0x1fU) 
                                                                                | (0U 
                                                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(
                                                                      ((0U 
                                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))
                                                                        ? 0xffffffffU
                                                                        : top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_5))))
                                                    : 
                                                   ((0xeU 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? 
                                                    (((QData)((IData)(
                                                                      (- (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult 
                                                                                >> 0x1fU))))) 
                                                      << 0x20U) 
                                                     | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult)))
                                                     : 
                                                    ((0xfU 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                      ? 
                                                     (((QData)((IData)(
                                                                       (- (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult_1 
                                                                                >> 0x1fU))))) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult_1)))
                                                      : 0ULL))))))))))));
    }
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state 
        = __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    vlSelfRef.inst_sram_addr = ((IData)(4U) + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc));
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T 
        = ((IData)(4U) + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56 
        = ((0x17U == (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst))) 
           | (0x37U == (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN 
        = ((0x380U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                               >> 0xcU)) << 7U)) | 
           (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7 
        = ((3U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
           | ((0x203U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
              | ((0x83U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                 | ((0x283U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                    | (0x103U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57 
        = ((0x23U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
           | ((0xa3U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
              | (0x123U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3 
        = ((0xfc00U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                >> 0x1aU)) << 0xaU)) 
           | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1 
        = ((0x1fc00U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                 >> 0x19U)) << 0xaU)) 
           | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_3 
        = ((0x13U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
           | (0x33U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2 
        = ((0x3b3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
           | (0x8033U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58 
        = (((0x433U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
            | (0x4b3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)) 
           | ((0x533U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
              | ((0x5b3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                 | ((0x633U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                    | ((0x6b3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                       | ((0x733U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                          | (0x7b3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)))))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55 
        = ((0x43bU == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
           | ((0x63bU == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
              | ((0x6bbU == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                 | ((0x73bU == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                    | (0x7bbU == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType 
        = ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_3)
            ? 0U : (((0x93U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                     | (0xb3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                     ? 1U : (((0x113U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                              | (0x133U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                              ? 2U : (((0x193U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                       | (0x1b3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                       ? 3U : (((0x213U 
                                                 == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                | (0x233U 
                                                   == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                                ? 4U
                                                : (
                                                   ((0x293U 
                                                     == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                                    | (0x2b3U 
                                                       == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                                    ? 5U
                                                    : 
                                                   (((0x4293U 
                                                      == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                                     | (0x82b3U 
                                                        == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                                     ? 0xdU
                                                     : 
                                                    (((0x313U 
                                                       == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                      | (0x333U 
                                                         == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                                      ? 6U
                                                      : 
                                                     (((0x393U 
                                                        == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                       | (0x3b3U 
                                                          == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
                                                       ? 7U
                                                       : 
                                                      ((0x8033U 
                                                        == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                        ? 8U
                                                        : 
                                                       ((0x433U 
                                                         == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                         ? 0U
                                                         : 
                                                        ((0x4b3U 
                                                          == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                          ? 1U
                                                          : 
                                                         ((0x533U 
                                                           == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                           ? 2U
                                                           : 
                                                          ((0x5b3U 
                                                            == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                            ? 3U
                                                            : 
                                                           ((0x633U 
                                                             == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                             ? 4U
                                                             : 
                                                            ((0x6b3U 
                                                              == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                              ? 5U
                                                              : 
                                                             ((0x733U 
                                                               == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                               ? 6U
                                                               : 
                                                              ((0x7b3U 
                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                ? 7U
                                                                : 
                                                               ((3U 
                                                                 == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                 ? 0U
                                                                 : 
                                                                ((0x203U 
                                                                  == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                  ? 4U
                                                                  : 
                                                                 ((0x83U 
                                                                   == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                   ? 1U
                                                                   : 
                                                                  ((0x283U 
                                                                    == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                    ? 5U
                                                                    : 
                                                                   ((0x103U 
                                                                     == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                     ? 2U
                                                                     : 
                                                                    ((0x23U 
                                                                      == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                      ? 8U
                                                                      : 
                                                                     ((0xa3U 
                                                                       == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                       ? 9U
                                                                       : 
                                                                      ((0x123U 
                                                                        == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                        ? 0xaU
                                                                        : 
                                                                       ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56)
                                                                         ? 0U
                                                                         : 
                                                                        ((0x1bU 
                                                                          == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                          ? 0x10U
                                                                          : 
                                                                         ((0x9bU 
                                                                           == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                           ? 0x11U
                                                                           : 
                                                                          ((0x29bU 
                                                                            == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                            ? 0x15U
                                                                            : 
                                                                           ((0x829bU 
                                                                             == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                             ? 0x1dU
                                                                             : 
                                                                            ((0xbbU 
                                                                              == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                              ? 0x11U
                                                                              : 
                                                                             ((0x2bbU 
                                                                               == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                               ? 0x15U
                                                                               : 
                                                                              ((0x82bbU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                ? 0x1dU
                                                                                : 
                                                                               ((0x3bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0x10U
                                                                                 : 
                                                                                ((0x803bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0x18U
                                                                                 : 
                                                                                ((0x43bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 8U
                                                                                 : 
                                                                                ((0x63bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0xcU
                                                                                 : 
                                                                                ((0x6bbU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0xdU
                                                                                 : 
                                                                                ((0x73bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0xeU
                                                                                 : 
                                                                                ((0x7bbU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                                                 ? 0xfU
                                                                                 : 
                                                                                ((0x183U 
                                                                                == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                                 ? 3U
                                                                                 : 
                                                                                ((0x1a3U 
                                                                                == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                                 ? 0xbU
                                                                                 : 0U)))))))))))))))))))))))))))))))))))))))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel 
        = (((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_3) 
            | ((0x93U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
               | ((0xb3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                  | ((0x113U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                     | ((0x133U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                        | ((0x193U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                           | ((0x1b3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                              | ((0x213U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                 | ((0x233U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                    | ((0x293U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                       | ((0x2b3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                          | ((0x4293U 
                                              == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3)) 
                                             | ((0x82b3U 
                                                 == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                | ((0x313U 
                                                    == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                   | ((0x333U 
                                                       == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                      | ((0x393U 
                                                          == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                         | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2)))))))))))))))))
            ? 0U : ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58)
                     ? 1U : (((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7) 
                              | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57))
                              ? 2U : (((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56) 
                                       | ((0x1bU == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                          | ((0x9bU 
                                              == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                             | ((0x29bU 
                                                 == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                | ((0x829bU 
                                                    == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                   | ((0xbbU 
                                                       == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                      | ((0x2bbU 
                                                          == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                         | ((0x82bbU 
                                                             == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                            | ((0x3bU 
                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                               | (0x803bU 
                                                                  == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))))))))))
                                       ? 0U : ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55)
                                                ? 1U
                                                : (
                                                   ((0x183U 
                                                     == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                    | (0x1a3U 
                                                       == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))) 
                                                   << 1U))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType 
        = ((0x13U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
            ? 4U : ((0x33U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                     ? 5U : ((0x93U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3))
                              ? 4U : ((0xb3U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                       ? 5U : ((0x113U 
                                                == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                ? 4U
                                                : (
                                                   (0x133U 
                                                    == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                    ? 5U
                                                    : 
                                                   ((0x193U 
                                                     == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                     ? 4U
                                                     : 
                                                    ((0x1b3U 
                                                      == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                      ? 5U
                                                      : 
                                                     ((0x213U 
                                                       == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                       ? 4U
                                                       : 
                                                      ((0x233U 
                                                        == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                        ? 5U
                                                        : 
                                                       ((0x293U 
                                                         == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3))
                                                         ? 4U
                                                         : 
                                                        ((0x2b3U 
                                                          == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                          ? 5U
                                                          : 
                                                         ((0x4293U 
                                                           == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3))
                                                           ? 4U
                                                           : 
                                                          ((0x82b3U 
                                                            == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                            ? 5U
                                                            : 
                                                           ((0x313U 
                                                             == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                             ? 4U
                                                             : 
                                                            ((0x333U 
                                                              == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)
                                                              ? 5U
                                                              : 
                                                             ((0x393U 
                                                               == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                               ? 4U
                                                               : 
                                                              (((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_2) 
                                                                | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58))
                                                                ? 5U
                                                                : 
                                                               ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_7)
                                                                 ? 4U
                                                                 : 
                                                                ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_57)
                                                                  ? 2U
                                                                  : 
                                                                 ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56)
                                                                   ? 6U
                                                                   : 
                                                                  (((0x1bU 
                                                                     == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                                    | ((0x9bU 
                                                                        == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                       | ((0x29bU 
                                                                           == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                          | (0x829bU 
                                                                             == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))))
                                                                    ? 4U
                                                                    : 
                                                                   ((((0xbbU 
                                                                       == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                      | (0x2bbU 
                                                                         == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)) 
                                                                     | (((0x82bbU 
                                                                          == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                         | (0x3bU 
                                                                            == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1)) 
                                                                        | ((0x803bU 
                                                                            == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                           | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_55))))
                                                                     ? 5U
                                                                     : 
                                                                    ((0x183U 
                                                                      == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN))
                                                                      ? 4U
                                                                      : 
                                                                     ((0x1a3U 
                                                                       == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
                                                                      << 1U)))))))))))))))))))))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___op_T_29 
        = (((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
             ? ((((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel))
                   ? ((2U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                      >> 3U)) << 1U)) 
                      | (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                       >> 0x1eU))))
                   : (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                    >> 3U)))) << 3U) 
                | (7U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                 >> 0xcU)))) : 0U) 
           | ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
               ? ((((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel))
                     ? (1U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                      >> 5U))) : ((2U 
                                                   & ((IData)(
                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                               >> 3U)) 
                                                      << 1U)) 
                                                  | ((0xdU 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType)) 
                                                     | (0x1dU 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType))))) 
                   << 3U) | (7U & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                           >> 0xcU))))
               : 0U));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65 
        = ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
           | (6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_63 
        = ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
           | (4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)));
    vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_src_info_src2_data 
        = (((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
            | ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65)) 
               & (2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
            ? (((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                (((IData)(0x3fU) + 
                                  (0x7ffU & VL_SHIFTL_III(11,11,32, 
                                                          ((1U 
                                                            & ((~ 
                                                                ((2U 
                                                                  != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                                                 | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65))) 
                                                               | (5U 
                                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                                                            ? 
                                                           (0x1fU 
                                                            & (IData)(
                                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                       >> 0x14U)))
                                                            : 0U), 6U))) 
                                 >> 5U)])) << ((0U 
                                                == 
                                                (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, 
                                                                 ((1U 
                                                                   & ((~ 
                                                                       ((2U 
                                                                         != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                                                        | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65))) 
                                                                      | (5U 
                                                                         == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                                                                   ? 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0x14U)))
                                                                   : 0U), 6U)))
                                                ? 0x20U
                                                : ((IData)(0x40U) 
                                                   - 
                                                   (0x1fU 
                                                    & VL_SHIFTL_III(11,11,32, 
                                                                    ((1U 
                                                                      & ((~ 
                                                                          ((2U 
                                                                            != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                                                           | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65))) 
                                                                         | (5U 
                                                                            == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                                                                      ? 
                                                                     (0x1fU 
                                                                      & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U)))
                                                                      : 0U), 6U))))) 
               | (((0U == (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                 ((1U 
                                                   & ((~ 
                                                       ((2U 
                                                         != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                                        | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65))) 
                                                      | (5U 
                                                         == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                                                   ? 
                                                  (0x1fU 
                                                   & (IData)(
                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                              >> 0x14U)))
                                                   : 0U), 6U)))
                    ? 0ULL : ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                              (((IData)(0x1fU) 
                                                + (0x7ffU 
                                                   & VL_SHIFTL_III(11,11,32, 
                                                                   ((1U 
                                                                     & ((~ 
                                                                         ((2U 
                                                                           != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                                                          | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65))) 
                                                                        | (5U 
                                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                                                                     ? 
                                                                    (0x1fU 
                                                                     & (IData)(
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U)))
                                                                     : 0U), 6U))) 
                                               >> 5U)])) 
                              << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                         ((1U 
                                                           & ((~ 
                                                               ((2U 
                                                                 != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                                                | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65))) 
                                                              | (5U 
                                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                                                           ? 
                                                          (0x1fU 
                                                           & (IData)(
                                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                      >> 0x14U)))
                                                           : 0U), 6U))))) 
                  | ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                     (0x3fU & (VL_SHIFTL_III(11,11,32, 
                                                             ((1U 
                                                               & ((~ 
                                                                   ((2U 
                                                                     != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                                                    | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65))) 
                                                                  | (5U 
                                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                                                               ? 
                                                              (0x1fU 
                                                               & (IData)(
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                          >> 0x14U)))
                                                               : 0U), 6U) 
                                               >> 5U))])) 
                     >> (0x1fU & VL_SHIFTL_III(11,11,32, 
                                               ((1U 
                                                 & ((~ 
                                                     ((2U 
                                                       != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                                      | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_65))) 
                                                    | (5U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))
                                                 ? 
                                                (0x1fU 
                                                 & (IData)(
                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                            >> 0x14U)))
                                                 : 0U), 6U)))))
            : (((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                 ? (((- (QData)((IData)((1U & (IData)(
                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                       >> 0x1fU)))))) 
                     << 0xcU) | (QData)((IData)((0xfffU 
                                                 & (IData)(
                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                            >> 0x14U))))))
                 : 0ULL) | (((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                              ? (((- (QData)((IData)(
                                                     (1U 
                                                      & (IData)(
                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                 >> 0x1fU)))))) 
                                  << 0xcU) | (QData)((IData)(
                                                             ((0xfe0U 
                                                               & ((IData)(
                                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                           >> 0x19U)) 
                                                                  << 5U)) 
                                                              | (0x1fU 
                                                                 & (IData)(
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 7U)))))))
                              : 0ULL) | (((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                           ? (((- (QData)((IData)(
                                                                  (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0x1fU)))))) 
                                               << 0xcU) 
                                              | (QData)((IData)(
                                                                ((0x800U 
                                                                  & ((IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 7U)) 
                                                                     << 0xbU)) 
                                                                 | ((0x7e0U 
                                                                     & ((IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x19U)) 
                                                                        << 5U)) 
                                                                    | (0x1eU 
                                                                       & ((IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 8U)) 
                                                                          << 1U)))))))
                                           : 0ULL) 
                                         | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                             ? (((QData)((IData)(
                                                                 (- (IData)(
                                                                            (1U 
                                                                             & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x1fU))))))) 
                                                 << 0x20U) 
                                                | (QData)((IData)(
                                                                  ((IData)(
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0xcU)) 
                                                                   << 0xcU))))
                                             : 0ULL)))));
    vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_reg_wen 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_63) 
           | (6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_64 
        = (1U & ((~ ((2U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                     | (6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))) 
                 | (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_63)));
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
