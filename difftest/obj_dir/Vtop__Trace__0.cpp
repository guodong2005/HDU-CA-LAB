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
    VlWide<3>/*95:0*/ __Vtemp_7;
    VlWide<3>/*95:0*/ __Vtemp_8;
    VlWide<3>/*95:0*/ __Vtemp_9;
    VlWide<3>/*95:0*/ __Vtemp_10;
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgCData(oldp+0,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr),5);
        bufp->chgCData(oldp+1,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr),5);
        bufp->chgBit(oldp+2,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren));
        bufp->chgBit(oldp+3,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren));
        bufp->chgBit(oldp+4,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
        bufp->chgBit(oldp+5,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+6,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr),5);
        bufp->chgBit(oldp+7,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
        bufp->chgBit(oldp+8,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+9,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr),5);
        bufp->chgBit(oldp+10,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid));
        bufp->chgBit(oldp+11,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+12,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr),5);
        bufp->chgBit(oldp+13,((1U & (~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall)))));
        bufp->chgBit(oldp+14,(vlSelfRef.top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush));
        bufp->chgBit(oldp+15,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen) 
                               & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid) 
                                  & ((0U != (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr)) 
                                     & (((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren) 
                                         & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr) 
                                            == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr))) 
                                        | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren) 
                                           & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr) 
                                              == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr)))))))));
        bufp->chgBit(oldp+16,(vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall));
        bufp->chgBit(oldp+17,((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))));
        bufp->chgQData(oldp+18,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc),64);
        bufp->chgQData(oldp+20,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst),64);
        bufp->chgBit(oldp+22,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
        bufp->chgQData(oldp+23,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc),64);
        bufp->chgQData(oldp+25,((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
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
                                           VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))))),64);
        bufp->chgQData(oldp+27,((((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
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
                                           VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))))),64);
        bufp->chgCData(oldp+29,(((1U & ((~ ((~ ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_74) 
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
        bufp->chgBit(oldp+30,(((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                               | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_76) 
                                  | ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_74)) 
                                     & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9))))));
        bufp->chgCData(oldp+31,(((1U & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_75) 
                                        | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                           | ((~ ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9)) 
                                                  | (1U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))) 
                                              | (2U 
                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))))
                                  ? (0x1fU & (IData)(
                                                     (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                      >> 7U)))
                                  : 0U)),5);
        bufp->chgSData(oldp+32,((0xfffU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm))),12);
        bufp->chgCData(oldp+33,(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel),2);
        bufp->chgQData(oldp+34,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                  ? (((QData)((IData)(
                                                      vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                      (((IData)(0x3fU) 
                                                        + 
                                                        (0x7ffU 
                                                         & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))) 
                                                       >> 5U)])) 
                                      << ((0U == (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))
                                           ? 0x20U : 
                                          ((IData)(0x40U) 
                                           - (0x1fU 
                                              & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))))) 
                                     | (((0U == (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))
                                          ? 0ULL : 
                                         ((QData)((IData)(
                                                          vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                          (((IData)(0x1fU) 
                                                            + 
                                                            (0x7ffU 
                                                             & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))) 
                                                           >> 5U)])) 
                                          << ((IData)(0x20U) 
                                              - (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U))))) 
                                        | ((QData)((IData)(
                                                           vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                           (0x3fU 
                                                            & (VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U) 
                                                               >> 5U))])) 
                                           >> (0x1fU 
                                               & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 6U)))))
                                  : ((0x37U == (0x7fU 
                                                & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)))
                                      ? 0ULL : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc))),64);
        bufp->chgQData(oldp+36,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren)
                                  ? (((QData)((IData)(
                                                      vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                      (((IData)(0x3fU) 
                                                        + 
                                                        (0x7ffU 
                                                         & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))) 
                                                       >> 5U)])) 
                                      << ((0U == (0x1fU 
                                                  & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))
                                           ? 0x20U : 
                                          ((IData)(0x40U) 
                                           - (0x1fU 
                                              & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))))) 
                                     | (((0U == (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))
                                          ? 0ULL : 
                                         ((QData)((IData)(
                                                          vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                          (((IData)(0x1fU) 
                                                            + 
                                                            (0x7ffU 
                                                             & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))) 
                                                           >> 5U)])) 
                                          << ((IData)(0x20U) 
                                              - (0x1fU 
                                                 & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U))))) 
                                        | ((QData)((IData)(
                                                           vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                                           (0x3fU 
                                                            & (VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U) 
                                                               >> 5U))])) 
                                           >> (0x1fU 
                                               & VL_SHIFTL_III(11,11,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 6U)))))
                                  : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm)),64);
        bufp->chgCData(oldp+38,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType),3);
        bufp->chgQData(oldp+39,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm),64);
        bufp->chgCData(oldp+41,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType),5);
        bufp->chgQData(oldp+42,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc),64);
        bufp->chgCData(oldp+44,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op),5);
        bufp->chgSData(oldp+45,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm),12);
        bufp->chgCData(oldp+46,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel),2);
        bufp->chgQData(oldp+47,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data),64);
        bufp->chgQData(oldp+49,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data),64);
        bufp->chgQData(oldp+51,((((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                   ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result
                                   : 0ULL) | (((1U 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                                ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result
                                                : 0ULL) 
                                              | ((3U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                                  ? 
                                                 ((8U 
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
        bufp->chgCData(oldp+53,((7U & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))),3);
        bufp->chgQData(oldp+54,(((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                  ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                  : ((0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                      ? (0xfffffffffffffffeULL 
                                         & (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                            + vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT___GEN_0))
                                      : ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                          ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                          : ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                              ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                              : ((4U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                  ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3
                                                  : 
                                                 ((5U 
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
        bufp->chgQData(oldp+56,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result),64);
        bufp->chgIData(oldp+58,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT__logicalShiftResult),32);
        bufp->chgQData(oldp+59,(((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                  ? (4ULL + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                  : ((0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                      ? (4ULL + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                      : 0ULL))),64);
        bufp->chgQData(oldp+61,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result),64);
        bufp->chgBit(oldp+63,((0ULL == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
        bufp->chgBit(oldp+64,((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))));
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
        VL_MUL_W(4, __Vtemp_2, vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0, __Vtemp_1);
        bufp->chgWData(oldp+65,(__Vtemp_2),128);
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
        bufp->chgWData(oldp+69,(__Vtemp_5),128);
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
        bufp->chgWData(oldp+73,(__Vtemp_10),65);
        bufp->chgQData(oldp+76,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__divtmp),33);
        bufp->chgIData(oldp+78,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult),32);
        bufp->chgIData(oldp+79,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult_1),32);
        bufp->chgCData(oldp+80,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state),2);
        bufp->chgQData(oldp+81,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc),64);
        bufp->chgCData(oldp+83,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op),5);
        bufp->chgCData(oldp+84,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel),2);
        bufp->chgQData(oldp+85,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata),64);
        bufp->chgCData(oldp+87,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3),3);
        bufp->chgBit(oldp+88,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen) 
                               & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid))));
        bufp->chgQData(oldp+89,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata),64);
        bufp->chgQData(oldp+91,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0),64);
        bufp->chgQData(oldp+93,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1),64);
        bufp->chgQData(oldp+95,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2),64);
        bufp->chgQData(oldp+97,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3),64);
        bufp->chgQData(oldp+99,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4),64);
        bufp->chgQData(oldp+101,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5),64);
        bufp->chgQData(oldp+103,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6),64);
        bufp->chgQData(oldp+105,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7),64);
        bufp->chgQData(oldp+107,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8),64);
        bufp->chgQData(oldp+109,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9),64);
        bufp->chgQData(oldp+111,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10),64);
        bufp->chgQData(oldp+113,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11),64);
        bufp->chgQData(oldp+115,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12),64);
        bufp->chgQData(oldp+117,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13),64);
        bufp->chgQData(oldp+119,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14),64);
        bufp->chgQData(oldp+121,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15),64);
        bufp->chgQData(oldp+123,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16),64);
        bufp->chgQData(oldp+125,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17),64);
        bufp->chgQData(oldp+127,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18),64);
        bufp->chgQData(oldp+129,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19),64);
        bufp->chgQData(oldp+131,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20),64);
        bufp->chgQData(oldp+133,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21),64);
        bufp->chgQData(oldp+135,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22),64);
        bufp->chgQData(oldp+137,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23),64);
        bufp->chgQData(oldp+139,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24),64);
        bufp->chgQData(oldp+141,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25),64);
        bufp->chgQData(oldp+143,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26),64);
        bufp->chgQData(oldp+145,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27),64);
        bufp->chgQData(oldp+147,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28),64);
        bufp->chgQData(oldp+149,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29),64);
        bufp->chgQData(oldp+151,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30),64);
        bufp->chgQData(oldp+153,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31),64);
        bufp->chgQData(oldp+155,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc),64);
    }
    bufp->chgBit(oldp+157,(vlSelfRef.clock));
    bufp->chgBit(oldp+158,(vlSelfRef.reset));
    bufp->chgBit(oldp+159,(vlSelfRef.mei));
    bufp->chgBit(oldp+160,(vlSelfRef.msi));
    bufp->chgBit(oldp+161,(vlSelfRef.mti));
    bufp->chgBit(oldp+162,(vlSelfRef.sei));
    bufp->chgBit(oldp+163,(vlSelfRef.inst_sram_en));
    bufp->chgCData(oldp+164,(vlSelfRef.inst_sram_wen),4);
    bufp->chgIData(oldp+165,(vlSelfRef.inst_sram_addr),32);
    bufp->chgIData(oldp+166,(vlSelfRef.inst_sram_wdata),32);
    bufp->chgIData(oldp+167,(vlSelfRef.inst_sram_rdata),32);
    bufp->chgBit(oldp+168,(vlSelfRef.data_sram_en));
    bufp->chgCData(oldp+169,(vlSelfRef.data_sram_wen),8);
    bufp->chgIData(oldp+170,(vlSelfRef.data_sram_addr),32);
    bufp->chgQData(oldp+171,(vlSelfRef.data_sram_wdata),64);
    bufp->chgQData(oldp+173,(vlSelfRef.data_sram_rdata),64);
    bufp->chgBit(oldp+175,(vlSelfRef.debug_commit));
    bufp->chgQData(oldp+176,(vlSelfRef.debug_pc),64);
    bufp->chgCData(oldp+178,(vlSelfRef.debug_rf_wnum),5);
    bufp->chgQData(oldp+179,(vlSelfRef.debug_rf_wdata),64);
    bufp->chgQData(oldp+181,((QData)((IData)(vlSelfRef.inst_sram_rdata))),64);
    bufp->chgQData(oldp+183,(((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel))
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
    bufp->chgQData(oldp+185,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData),64);
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
