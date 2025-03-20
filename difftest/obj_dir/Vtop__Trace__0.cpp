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
    VlWide<4>/*127:0*/ __Vtemp_1;
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_5;
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgBit(oldp+0,((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))));
        bufp->chgQData(oldp+1,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc),64);
        bufp->chgQData(oldp+3,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst),64);
        bufp->chgBit(oldp+5,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
        bufp->chgQData(oldp+6,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc),64);
        bufp->chgCData(oldp+8,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                 ? (0x1fU & (IData)(
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 0xfU)))
                                 : 0U)),5);
        bufp->chgQData(oldp+9,((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                 (((IData)(0x3fU) 
                                                   + 
                                                   (0x7ffU 
                                                    & VL_SHIFTL_III(11,11,32, 
                                                                    ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                      ? 
                                                                     (0x1fU 
                                                                      & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                      : 0U), 6U))) 
                                                  >> 5U)])) 
                                 << ((0U == (0x1fU 
                                             & VL_SHIFTL_III(11,11,32, 
                                                             ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                               ? 
                                                              (0x1fU 
                                                               & (IData)(
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                          >> 0xfU)))
                                                               : 0U), 6U)))
                                      ? 0x20U : ((IData)(0x40U) 
                                                 - 
                                                 (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, 
                                                                  ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                    ? 
                                                                   (0x1fU 
                                                                    & (IData)(
                                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                               >> 0xfU)))
                                                                    : 0U), 6U))))) 
                                | (((0U == (0x1fU & 
                                            VL_SHIFTL_III(11,11,32, 
                                                          ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                            ? 
                                                           (0x1fU 
                                                            & (IData)(
                                                                      (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                       >> 0xfU)))
                                                            : 0U), 6U)))
                                     ? 0ULL : ((QData)((IData)(
                                                               vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                               (((IData)(0x1fU) 
                                                                 + 
                                                                 (0x7ffU 
                                                                  & VL_SHIFTL_III(11,11,32, 
                                                                                ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                                 ? 
                                                                                (0x1fU 
                                                                                & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                                 : 0U), 6U))) 
                                                                >> 5U)])) 
                                               << ((IData)(0x20U) 
                                                   - 
                                                   (0x1fU 
                                                    & VL_SHIFTL_III(11,11,32, 
                                                                    ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                      ? 
                                                                     (0x1fU 
                                                                      & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                      : 0U), 6U))))) 
                                   | ((QData)((IData)(
                                                      vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                      (0x3fU 
                                                       & (VL_SHIFTL_III(11,11,32, 
                                                                        ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                          ? 
                                                                         (0x1fU 
                                                                          & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                          : 0U), 6U) 
                                                          >> 5U))])) 
                                      >> (0x1fU & VL_SHIFTL_III(11,11,32, 
                                                                ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                  ? 
                                                                 (0x1fU 
                                                                  & (IData)(
                                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                             >> 0xfU)))
                                                                  : 0U), 6U)))))),64);
        bufp->chgCData(oldp+11,(((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                  ? (0x1fU & (IData)(
                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                      >> 0x14U)))
                                  : 0U)),5);
        bufp->chgQData(oldp+12,((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                  (((IData)(0x3fU) 
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
                                  << ((0U == (0x1fU 
                                              & VL_SHIFTL_III(11,11,32, 
                                                              ((5U 
                                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                ? 
                                                               (0x1fU 
                                                                & (IData)(
                                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                           >> 0x14U)))
                                                                : 0U), 6U)))
                                       ? 0x20U : ((IData)(0x40U) 
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
                                 | (((0U == (0x1fU 
                                             & VL_SHIFTL_III(11,11,32, 
                                                             ((5U 
                                                               == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                               ? 
                                                              (0x1fU 
                                                               & (IData)(
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                          >> 0x14U)))
                                                               : 0U), 6U)))
                                      ? 0ULL : ((QData)((IData)(
                                                                vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
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
                                                << 
                                                ((IData)(0x20U) 
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
                                    | ((QData)((IData)(
                                                       vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                       (0x3fU 
                                                        & (VL_SHIFTL_III(11,11,32, 
                                                                         ((5U 
                                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                           ? 
                                                                          (0x1fU 
                                                                           & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U)))
                                                                           : 0U), 6U) 
                                                           >> 5U))])) 
                                       >> (0x1fU & 
                                           VL_SHIFTL_III(11,11,32, 
                                                         ((5U 
                                                           == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                           ? 
                                                          (0x1fU 
                                                           & (IData)(
                                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                      >> 0x14U)))
                                                           : 0U), 6U)))))),64);
        bufp->chgCData(oldp+14,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                  ? (((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                       ? ((((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel)
                                             ? (1U 
                                                & (IData)(
                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                           >> 3U)))
                                             : ((2U 
                                                 & ((IData)(
                                                            (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                             >> 3U)) 
                                                    << 1U)) 
                                                | (1U 
                                                   & (IData)(
                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                              >> 0x1eU))))) 
                                           << 3U) | 
                                          (7U & (IData)(
                                                        (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                         >> 0xcU))))
                                       : 0U) | ((4U 
                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                 ? 
                                                ((0x10U 
                                                  & ((IData)(
                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                              >> 3U)) 
                                                     << 4U)) 
                                                 | ((((0xdU 
                                                       == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType)) 
                                                      | (0x1dU 
                                                         == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType))) 
                                                     << 3U) 
                                                    | (7U 
                                                       & (IData)(
                                                                 (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                  >> 0xcU)))))
                                                 : 0U))
                                  : 0U)),5);
        bufp->chgBit(oldp+15,(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_reg_wen));
        bufp->chgCData(oldp+16,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_reg_wen)
                                  ? (0x1fU & (IData)(
                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                      >> 7U)))
                                  : 0U)),5);
        bufp->chgBit(oldp+17,(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel));
        bufp->chgQData(oldp+18,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                  ? (((QData)((IData)(
                                                      vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                      (((IData)(0x3fU) 
                                                        + 
                                                        (0x7ffU 
                                                         & VL_SHIFTL_III(11,11,32, 
                                                                         ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                           ? 
                                                                          (0x1fU 
                                                                           & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                           : 0U), 6U))) 
                                                       >> 5U)])) 
                                      << ((0U == (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, 
                                                                  ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                    ? 
                                                                   (0x1fU 
                                                                    & (IData)(
                                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                               >> 0xfU)))
                                                                    : 0U), 6U)))
                                           ? 0x20U : 
                                          ((IData)(0x40U) 
                                           - (0x1fU 
                                              & VL_SHIFTL_III(11,11,32, 
                                                              ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                ? 
                                                               (0x1fU 
                                                                & (IData)(
                                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                           >> 0xfU)))
                                                                : 0U), 6U))))) 
                                     | (((0U == (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, 
                                                                 ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                   ? 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0xfU)))
                                                                   : 0U), 6U)))
                                          ? 0ULL : 
                                         ((QData)((IData)(
                                                          vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                          (((IData)(0x1fU) 
                                                            + 
                                                            (0x7ffU 
                                                             & VL_SHIFTL_III(11,11,32, 
                                                                             ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                               ? 
                                                                              (0x1fU 
                                                                               & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                               : 0U), 6U))) 
                                                           >> 5U)])) 
                                          << ((IData)(0x20U) 
                                              - (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, 
                                                                 ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                   ? 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0xfU)))
                                                                   : 0U), 6U))))) 
                                        | ((QData)((IData)(
                                                           vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                           (0x3fU 
                                                            & (VL_SHIFTL_III(11,11,32, 
                                                                             ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                               ? 
                                                                              (0x1fU 
                                                                               & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0xfU)))
                                                                               : 0U), 6U) 
                                                               >> 5U))])) 
                                           >> (0x1fU 
                                               & VL_SHIFTL_III(11,11,32, 
                                                               ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                                                 ? 
                                                                (0x1fU 
                                                                 & (IData)(
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0xfU)))
                                                                 : 0U), 6U)))))
                                  : ((0x37U == (0x7fU 
                                                & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)))
                                      ? 0ULL : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc))),64);
        bufp->chgQData(oldp+20,(((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                  ? (((QData)((IData)(
                                                      vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                      (((IData)(0x3fU) 
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
                                      << ((0U == (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, 
                                                                  ((5U 
                                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                    ? 
                                                                   (0x1fU 
                                                                    & (IData)(
                                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                               >> 0x14U)))
                                                                    : 0U), 6U)))
                                           ? 0x20U : 
                                          ((IData)(0x40U) 
                                           - (0x1fU 
                                              & VL_SHIFTL_III(11,11,32, 
                                                              ((5U 
                                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                ? 
                                                               (0x1fU 
                                                                & (IData)(
                                                                          (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                           >> 0x14U)))
                                                                : 0U), 6U))))) 
                                     | (((0U == (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, 
                                                                 ((5U 
                                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                   ? 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0x14U)))
                                                                   : 0U), 6U)))
                                          ? 0ULL : 
                                         ((QData)((IData)(
                                                          vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
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
                                              - (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, 
                                                                 ((5U 
                                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                   ? 
                                                                  (0x1fU 
                                                                   & (IData)(
                                                                             (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                              >> 0x14U)))
                                                                   : 0U), 6U))))) 
                                        | ((QData)((IData)(
                                                           vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                           (0x3fU 
                                                            & (VL_SHIFTL_III(11,11,32, 
                                                                             ((5U 
                                                                               == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                               ? 
                                                                              (0x1fU 
                                                                               & (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                                >> 0x14U)))
                                                                               : 0U), 6U) 
                                                               >> 5U))])) 
                                           >> (0x1fU 
                                               & VL_SHIFTL_III(11,11,32, 
                                                               ((5U 
                                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                                 ? 
                                                                (0x1fU 
                                                                 & (IData)(
                                                                           (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                            >> 0x14U)))
                                                                 : 0U), 6U)))))
                                  : (((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                       ? (((- (QData)((IData)(
                                                              (1U 
                                                               & (IData)(
                                                                         (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                          >> 0x1fU)))))) 
                                           << 0xcU) 
                                          | (QData)((IData)(
                                                            (0xfffU 
                                                             & (IData)(
                                                                       (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                                        >> 0x14U))))))
                                       : 0ULL) | ((6U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))
                                                   ? 
                                                  (((QData)((IData)(
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
                                                   : 0ULL)))),64);
        bufp->chgCData(oldp+22,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType),3);
        bufp->chgBit(oldp+23,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren));
        bufp->chgBit(oldp+24,((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))));
        bufp->chgCData(oldp+25,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType),5);
        bufp->chgQData(oldp+26,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc),64);
        bufp->chgBit(oldp+28,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
        bufp->chgCData(oldp+29,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op),5);
        bufp->chgBit(oldp+30,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+31,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr),5);
        bufp->chgBit(oldp+32,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel));
        bufp->chgQData(oldp+33,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data),64);
        bufp->chgQData(oldp+35,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data),64);
        bufp->chgQData(oldp+37,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel)
                                  ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result
                                  : vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result)),64);
        bufp->chgQData(oldp+39,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result),64);
        bufp->chgIData(oldp+41,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT__logicalShiftResult),32);
        bufp->chgQData(oldp+42,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result),64);
        bufp->chgBit(oldp+44,((0ULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
        __Vtemp_1[0U] = (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data);
        __Vtemp_1[1U] = (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                 >> 0x20U));
        __Vtemp_1[2U] = (IData)((- (QData)((IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                               >> 0x3fU)))))));
        __Vtemp_1[3U] = (IData)(((- (QData)((IData)(
                                                    (1U 
                                                     & (IData)(
                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                                >> 0x3fU)))))) 
                                 >> 0x20U));
        VL_MUL_W(4, __Vtemp_2, vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_1, __Vtemp_1);
        bufp->chgWData(oldp+45,(__Vtemp_2),128);
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
        bufp->chgWData(oldp+49,(__Vtemp_5),128);
        bufp->chgQData(oldp+53,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__divtmp),33);
        bufp->chgCData(oldp+55,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state),2);
        bufp->chgQData(oldp+56,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc),64);
        bufp->chgBit(oldp+58,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
        bufp->chgBit(oldp+59,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+60,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+61,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata),64);
        bufp->chgBit(oldp+63,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen) 
                               & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid))));
        bufp->chgCData(oldp+64,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+65,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata),64);
        bufp->chgQData(oldp+67,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0),64);
        bufp->chgQData(oldp+69,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1),64);
        bufp->chgQData(oldp+71,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2),64);
        bufp->chgQData(oldp+73,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3),64);
        bufp->chgQData(oldp+75,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4),64);
        bufp->chgQData(oldp+77,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5),64);
        bufp->chgQData(oldp+79,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6),64);
        bufp->chgQData(oldp+81,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7),64);
        bufp->chgQData(oldp+83,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8),64);
        bufp->chgQData(oldp+85,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9),64);
        bufp->chgQData(oldp+87,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10),64);
        bufp->chgQData(oldp+89,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11),64);
        bufp->chgQData(oldp+91,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12),64);
        bufp->chgQData(oldp+93,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13),64);
        bufp->chgQData(oldp+95,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14),64);
        bufp->chgQData(oldp+97,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15),64);
        bufp->chgQData(oldp+99,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16),64);
        bufp->chgQData(oldp+101,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17),64);
        bufp->chgQData(oldp+103,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18),64);
        bufp->chgQData(oldp+105,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19),64);
        bufp->chgQData(oldp+107,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20),64);
        bufp->chgQData(oldp+109,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21),64);
        bufp->chgQData(oldp+111,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22),64);
        bufp->chgQData(oldp+113,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23),64);
        bufp->chgQData(oldp+115,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24),64);
        bufp->chgQData(oldp+117,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25),64);
        bufp->chgQData(oldp+119,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26),64);
        bufp->chgQData(oldp+121,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27),64);
        bufp->chgQData(oldp+123,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28),64);
        bufp->chgQData(oldp+125,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29),64);
        bufp->chgQData(oldp+127,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30),64);
        bufp->chgQData(oldp+129,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31),64);
        bufp->chgQData(oldp+131,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc),64);
        bufp->chgBit(oldp+133,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid));
        bufp->chgBit(oldp+134,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen));
    }
    bufp->chgBit(oldp+135,(vlSelfRef.clock));
    bufp->chgBit(oldp+136,(vlSelfRef.reset));
    bufp->chgBit(oldp+137,(vlSelfRef.mei));
    bufp->chgBit(oldp+138,(vlSelfRef.msi));
    bufp->chgBit(oldp+139,(vlSelfRef.mti));
    bufp->chgBit(oldp+140,(vlSelfRef.sei));
    bufp->chgBit(oldp+141,(vlSelfRef.inst_sram_en));
    bufp->chgCData(oldp+142,(vlSelfRef.inst_sram_wen),4);
    bufp->chgIData(oldp+143,(vlSelfRef.inst_sram_addr),32);
    bufp->chgIData(oldp+144,(vlSelfRef.inst_sram_wdata),32);
    bufp->chgIData(oldp+145,(vlSelfRef.inst_sram_rdata),32);
    bufp->chgBit(oldp+146,(vlSelfRef.data_sram_en));
    bufp->chgCData(oldp+147,(vlSelfRef.data_sram_wen),8);
    bufp->chgIData(oldp+148,(vlSelfRef.data_sram_addr),32);
    bufp->chgQData(oldp+149,(vlSelfRef.data_sram_wdata),64);
    bufp->chgQData(oldp+151,(vlSelfRef.data_sram_rdata),64);
    bufp->chgBit(oldp+153,(vlSelfRef.debug_commit));
    bufp->chgQData(oldp+154,(vlSelfRef.debug_pc),64);
    bufp->chgCData(oldp+156,(vlSelfRef.debug_rf_wnum),5);
    bufp->chgQData(oldp+157,(vlSelfRef.debug_rf_wdata),64);
    bufp->chgQData(oldp+159,((QData)((IData)(vlSelfRef.inst_sram_rdata))),64);
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
