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
    SData/*9:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN = 0;
    IData/*16:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1 = 0;
    SData/*15:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3 = 0;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43;
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___addResult_T_2;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___addResult_T_2 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___subResult_T_2;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___subResult_T_2 = 0;
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___arithmeticShiftResult_T_3;
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___arithmeticShiftResult_T_3 = 0;
    CData/*1:0*/ __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 0;
    // Body
    __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state 
        = vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    if (vlSelfRef.reset) {
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data = 0ULL;
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
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc = 0ULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr = 0U;
        __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state = 0U;
        vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc = 0x7ffffffcULL;
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst = 0ULL;
    } else {
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc;
        if (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op 
                = (((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                     ? ((0x10U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                           >> 3U)) 
                                  << 4U)) | ((8U & 
                                              ((IData)(
                                                       (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                        >> 0x1eU)) 
                                               << 3U)) 
                                             | (7U 
                                                & (IData)(
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                           >> 0xcU)))))
                     : 0U) | ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                               ? ((0x10U & ((IData)(
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 3U)) 
                                            << 4U)) 
                                  | ((((0xdU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType)) 
                                       | (0x1dU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType))) 
                                      << 3U) | (7U 
                                                & (IData)(
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                           >> 0xcU)))))
                               : 0U));
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                = (((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                    (((IData)(0x3fU) 
                                      + (0x7ffU & VL_SHIFTL_III(11,11,32, 
                                                                (0x1fU 
                                                                 & ((5U 
                                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                     ? (IData)(
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                     : 
                                                                    ((4U 
                                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                      ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                      : 0U))), 6U))) 
                                     >> 5U)])) << (
                                                   (0U 
                                                    == 
                                                    (0x1fU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     (0x1fU 
                                                                      & ((5U 
                                                                          == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                          ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                          : 
                                                                         ((4U 
                                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                           ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                           : 0U))), 6U)))
                                                    ? 0x20U
                                                    : 
                                                   ((IData)(0x40U) 
                                                    - 
                                                    (0x1fU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     (0x1fU 
                                                                      & ((5U 
                                                                          == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                          ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                          : 
                                                                         ((4U 
                                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                           ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                           : 0U))), 6U))))) 
                   | (((0U == (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                     (0x1fU 
                                                      & ((5U 
                                                          == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                          ? (IData)(
                                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                     >> 0xfU))
                                                          : 
                                                         ((4U 
                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                           ? (IData)(
                                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                      >> 0xfU))
                                                           : 0U))), 6U)))
                        ? 0ULL : ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                  (((IData)(0x1fU) 
                                                    + 
                                                    (0x7ffU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     (0x1fU 
                                                                      & ((5U 
                                                                          == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                          ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                          : 
                                                                         ((4U 
                                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                           ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                           : 0U))), 6U))) 
                                                   >> 5U)])) 
                                  << ((IData)(0x20U) 
                                      - (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                               (0x1fU 
                                                                & ((5U 
                                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                    ? (IData)(
                                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                               >> 0xfU))
                                                                    : 
                                                                   ((4U 
                                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                     ? (IData)(
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                     : 0U))), 6U))))) 
                      | ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                         (0x3fU & (
                                                   VL_SHIFTL_III(11,11,32, 
                                                                 (0x1fU 
                                                                  & ((5U 
                                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                      ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                      : 
                                                                     ((4U 
                                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                       ? (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU))
                                                                       : 0U))), 6U) 
                                                   >> 5U))])) 
                         >> (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                   (0x1fU 
                                                    & ((5U 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                        ? (IData)(
                                                                  (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                   >> 0xfU))
                                                        : 
                                                       ((4U 
                                                         == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                         ? (IData)(
                                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                    >> 0xfU))
                                                         : 0U))), 6U)))));
        } else {
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op = 0U;
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                = ((0x37U == (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)))
                    ? 0ULL : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc);
        }
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
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata;
        vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr;
        vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata 
            = vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_memoryStage_data_rd_info_wdata;
        vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr;
        if ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))) {
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                = (((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                    (((IData)(0x3fU) 
                                      + (0x7ffU & VL_SHIFTL_III(11,11,32, 
                                                                ((5U 
                                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                  ? 
                                                                 (0x1fU 
                                                                  & (IData)(
                                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                             >> 0x14U)))
                                                                  : 0U), 6U))) 
                                     >> 5U)])) << (
                                                   (0U 
                                                    == 
                                                    (0x1fU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     ((5U 
                                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                       ? 
                                                                      (0x1fU 
                                                                       & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U)))
                                                                       : 0U), 6U)))
                                                    ? 0x20U
                                                    : 
                                                   ((IData)(0x40U) 
                                                    - 
                                                    (0x1fU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     ((5U 
                                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                       ? 
                                                                      (0x1fU 
                                                                       & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U)))
                                                                       : 0U), 6U))))) 
                   | (((0U == (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                     ((5U 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                       ? 
                                                      (0x1fU 
                                                       & (IData)(
                                                                 (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                  >> 0x14U)))
                                                       : 0U), 6U)))
                        ? 0ULL : ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                  (((IData)(0x1fU) 
                                                    + 
                                                    (0x7ffU 
                                                     & VL_SHIFTL_III(11,11,32, 
                                                                     ((5U 
                                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                       ? 
                                                                      (0x1fU 
                                                                       & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U)))
                                                                       : 0U), 6U))) 
                                                   >> 5U)])) 
                                  << ((IData)(0x20U) 
                                      - (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                               ((5U 
                                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                 ? 
                                                                (0x1fU 
                                                                 & (IData)(
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0x14U)))
                                                                 : 0U), 6U))))) 
                      | ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                         (0x3fU & (
                                                   VL_SHIFTL_III(11,11,32, 
                                                                 ((5U 
                                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                   ? 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0x14U)))
                                                                   : 0U), 6U) 
                                                   >> 5U))])) 
                         >> (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                   ((5U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                     ? 
                                                    (0x1fU 
                                                     & (IData)(
                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                >> 0x14U)))
                                                     : 0U), 6U)))));
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr 
                = (0x1fU & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                    >> 7U)));
        } else {
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                = (((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                     ? (((- (QData)((IData)((1U & (IData)(
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                           >> 0x1fU)))))) 
                         << 0xcU) | (QData)((IData)(
                                                    (0xfffU 
                                                     & (IData)(
                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                >> 0x14U))))))
                     : 0ULL) | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                 ? (((QData)((IData)(
                                                     (- (IData)(
                                                                (1U 
                                                                 & (IData)(
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0x1fU))))))) 
                                     << 0x20U) | (QData)((IData)(
                                                                 ((IData)(
                                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                           >> 0xcU)) 
                                                                  << 0xcU))))
                                 : 0ULL));
            vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr 
                = (0x1fU & ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                             ? (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                        >> 7U)) : (
                                                   (6U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                    ? (IData)(
                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                               >> 7U))
                                                    : 0U)));
        }
        vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc 
            = vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc;
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
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___addResult_T_2 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data) 
           + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___subResult_T_2 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data) 
           - (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__logicalShiftResult 
        = ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data) 
           >> (0x1fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
    top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___arithmeticShiftResult_T_3 
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
    vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen));
    vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
    vlSelfRef.debug_rf_wdata = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen));
    vlSelfRef.debug_commit = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid;
    vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
    vlSelfRef.debug_rf_wnum = vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
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
                                                       ? 
                                                      (((QData)((IData)(
                                                                        (- (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__logicalShiftResult 
                                                                                >> 0x1fU))))) 
                                                        << 0x20U) 
                                                       | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__logicalShiftResult)))
                                                       : 
                                                      ((0x1dU 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                        ? 
                                                       (((QData)((IData)(
                                                                         (- (IData)(
                                                                                (top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___arithmeticShiftResult_T_3 
                                                                                >> 0x1fU))))) 
                                                         << 0x20U) 
                                                        | (QData)((IData)(top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT___arithmeticShiftResult_T_3)))
                                                        : 0ULL)))))))))))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren) 
                                                   | (6U 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (2U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state)));
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state 
        = __Vdly__top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    vlSelfRef.inst_sram_addr = ((IData)(4U) + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc));
    vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T 
        = ((IData)(4U) + (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43 
        = ((0x17U == (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst))) 
           | (0x37U == (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst))));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN 
        = ((0x380U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                               >> 0xcU)) << 7U)) | 
           (0x7fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1 
        = ((0x1fc00U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                 >> 0x19U)) << 0xaU)) 
           | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN));
    top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3 
        = ((0xfc00U & ((IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                >> 0x1aU)) << 0xaU)) 
           | (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType 
        = (((0x13U == (IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN)) 
            | (0x33U == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))
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
                                                               ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43)
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
                                                                             (0xfU 
                                                                              & (- (IData)(
                                                                                (0x7bbU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))))))))))))))))))))))))))))))))))));
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
                                                              (((0x3b3U 
                                                                 == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                | ((0x8033U 
                                                                    == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                   | ((0x433U 
                                                                       == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                      | ((0x4b3U 
                                                                          == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                         | ((0x533U 
                                                                             == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                            | ((0x5b3U 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                               | ((0x633U 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                                | ((0x6b3U 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                                | ((0x733U 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                                | (0x7b3U 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))))))))))
                                                                ? 5U
                                                                : 
                                                               ((IData)(top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_43)
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
                                                                 (((0xbbU 
                                                                    == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                   | ((0x2bbU 
                                                                       == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                      | ((0x82bbU 
                                                                          == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                         | ((0x3bU 
                                                                             == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                            | ((0x803bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                               | ((0x43bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                                | ((0x63bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                                | ((0x6bbU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                                | ((0x73bU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1) 
                                                                                | (0x7bbU 
                                                                                == top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1))))))))))
                                                                   ? 5U
                                                                   : 0U)))))))))))))))))))));
    vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren 
        = ((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
           | (4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)));
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
