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
        bufp->chgBit(oldp+15,(vlSelfRef.top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall));
        bufp->chgBit(oldp+16,((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state))));
        bufp->chgIData(oldp+17,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc),32);
        bufp->chgIData(oldp+18,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst),32);
        bufp->chgBit(oldp+19,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid));
        bufp->chgIData(oldp+20,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc),32);
        bufp->chgIData(oldp+21,((((0U == (0x1fU & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U)))
                                   ? 0U : (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                           (((IData)(0x1fU) 
                                             + (0x3ffU 
                                                & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))) 
                                            >> 5U)] 
                                           << ((IData)(0x20U) 
                                               - (0x1fU 
                                                  & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))))) 
                                 | (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                    (0x1fU & (VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U) 
                                              >> 5U))] 
                                    >> (0x1fU & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))))),32);
        bufp->chgIData(oldp+22,((((0U == (0x1fU & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U)))
                                   ? 0U : (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                           (((IData)(0x1fU) 
                                             + (0x3ffU 
                                                & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))) 
                                            >> 5U)] 
                                           << ((IData)(0x20U) 
                                               - (0x1fU 
                                                  & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))))) 
                                 | (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                    (0x1fU & (VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U) 
                                              >> 5U))] 
                                    >> (0x1fU & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))))),32);
        bufp->chgCData(oldp+23,(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_op),5);
        bufp->chgBit(oldp+24,(((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                               | ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_60) 
                                  | ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58)) 
                                     & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_10))))));
        bufp->chgCData(oldp+25,(((1U & ((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_59) 
                                        | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                           | ((~ ((~ (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_10)) 
                                                  | (1U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))) 
                                              | (2U 
                                                 == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType))))))
                                  ? (0x1fU & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst)
                                  : 0U)),5);
        bufp->chgSData(oldp+26,((0xfffU & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm)),12);
        bufp->chgCData(oldp+27,(vlSelfRef.top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel),2);
        bufp->chgIData(oldp+28,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren)
                                  ? (((0U == (0x1fU 
                                              & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U)))
                                       ? 0U : (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                               (((IData)(0x1fU) 
                                                 + 
                                                 (0x3ffU 
                                                  & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))) 
                                                >> 5U)] 
                                               << ((IData)(0x20U) 
                                                   - 
                                                   (0x1fU 
                                                    & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))))) 
                                     | (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                        (0x1fU & (VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U) 
                                                  >> 5U))] 
                                        >> (0x1fU & 
                                            VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr), 5U))))
                                  : ((0x37U == (0x7fU 
                                                & vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst))
                                      ? 0U : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc))),32);
        bufp->chgIData(oldp+29,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren)
                                  ? (((0U == (0x1fU 
                                              & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U)))
                                       ? 0U : (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                               (((IData)(0x1fU) 
                                                 + 
                                                 (0x3ffU 
                                                  & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))) 
                                                >> 5U)] 
                                               << ((IData)(0x20U) 
                                                   - 
                                                   (0x1fU 
                                                    & VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))))) 
                                     | (vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT___GEN[
                                        (0x1fU & (VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U) 
                                                  >> 5U))] 
                                        >> (0x1fU & 
                                            VL_SHIFTL_III(10,10,32, (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr), 5U))))
                                  : vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm)),32);
        bufp->chgCData(oldp+30,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType),3);
        bufp->chgIData(oldp+31,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm),32);
        bufp->chgCData(oldp+32,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType),3);
        bufp->chgIData(oldp+33,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc),32);
        bufp->chgCData(oldp+34,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op),5);
        bufp->chgSData(oldp+35,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm),12);
        bufp->chgCData(oldp+36,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel),2);
        bufp->chgIData(oldp+37,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data),32);
        bufp->chgIData(oldp+38,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data),32);
        bufp->chgIData(oldp+39,((((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                   ? ((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                       ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                          + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                       : ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                           ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                              - vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                           : ((8U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                               ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                  & vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                               : ((7U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                   ? 
                                                  (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                   | vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? 
                                                   (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                    ^ vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                    : 
                                                   ((2U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_18)
                                                     : 
                                                    ((3U 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                      ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_20)
                                                      : 
                                                     ((9U 
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
                                              ? ((0U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                  ? 
                                                 (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                  * vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                  : 
                                                 ((1U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                   ? (IData)(
                                                             (((((QData)((IData)(
                                                                                (- (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                                                >> 0x1fU))))) 
                                                                 << 0x20U) 
                                                                | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))) 
                                                               * 
                                                               (((QData)((IData)(
                                                                                (- (IData)(
                                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                                                >> 0x1fU))))) 
                                                                 << 0x20U) 
                                                                | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                                              >> 0x20U))
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? (IData)(
                                                              (((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data)) 
                                                                * (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))) 
                                                               >> 0x20U))
                                                    : 
                                                   ((4U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? 
                                                    (((0xffffffffU 
                                                       == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data) 
                                                      & (0x80000000U 
                                                         == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))
                                                      ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data
                                                      : 
                                                     ((0U 
                                                       == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                       ? 0xffffffffU
                                                       : (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___result_T_6)))
                                                     : 
                                                    ((5U 
                                                      == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                      ? 
                                                     ((0U 
                                                       == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                       ? 0xffffffffU
                                                       : vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_3)
                                                      : 
                                                     ((6U 
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
                                              : 0U) 
                                            | ((3U 
                                                == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel))
                                                ? (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? 
                                                   ((IData)(4U) 
                                                    + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                                    : 
                                                   ((0xbU 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                     ? 
                                                    ((IData)(4U) 
                                                     + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                                     : 0U))
                                                : 0U)))),32);
        bufp->chgIData(oldp+40,(vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_target),32);
        bufp->chgIData(oldp+41,(((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
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
                                              : ((4U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                  ? 
                                                 (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                  ^ vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                  : 
                                                 ((2U 
                                                   == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                   ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_18)
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                    ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_20)
                                                    : 
                                                   ((9U 
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
                                                       : 0U))))))))))),32);
        bufp->chgIData(oldp+42,(((0xaU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                  ? ((IData)(4U) + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                  : ((0xbU == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                      ? ((IData)(4U) 
                                         + vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc)
                                      : 0U))),32);
        bufp->chgIData(oldp+43,(((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                  ? (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                     * vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                  : ((1U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                      ? (IData)((((
                                                   ((QData)((IData)(
                                                                    (- (IData)(
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                                                >> 0x1fU))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))) 
                                                  * 
                                                  (((QData)((IData)(
                                                                    (- (IData)(
                                                                               (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                                                >> 0x1fU))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))) 
                                                 >> 0x20U))
                                      : ((3U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                          ? (IData)(
                                                    (((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data)) 
                                                      * (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))) 
                                                     >> 0x20U))
                                          : ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                              ? (((0xffffffffU 
                                                   == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data) 
                                                  & (0x80000000U 
                                                     == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))
                                                  ? vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data
                                                  : 
                                                 ((0U 
                                                   == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                   ? 0xffffffffU
                                                   : (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___result_T_6)))
                                              : ((5U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op))
                                                  ? 
                                                 ((0U 
                                                   == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)
                                                   ? 0xffffffffU
                                                   : vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_3)
                                                  : 
                                                 ((6U 
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
                                                    : 0U)))))))),32);
        bufp->chgBit(oldp+44,((0U == vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)));
        bufp->chgQData(oldp+45,(((((QData)((IData)(
                                                   (- (IData)(
                                                              (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data 
                                                               >> 0x1fU))))) 
                                   << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data))) 
                                 * (((QData)((IData)(
                                                     (- (IData)(
                                                                (vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data 
                                                                 >> 0x1fU))))) 
                                     << 0x20U) | (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))))),64);
        bufp->chgQData(oldp+47,(((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data)) 
                                 * (QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data)))),64);
        bufp->chgQData(oldp+49,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___result_T_6),33);
        bufp->chgCData(oldp+51,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state),2);
        bufp->chgIData(oldp+52,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc),32);
        bufp->chgCData(oldp+53,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op),5);
        bufp->chgCData(oldp+54,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel),2);
        bufp->chgIData(oldp+55,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata),32);
        bufp->chgCData(oldp+56,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3),3);
        bufp->chgBit(oldp+57,(((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen) 
                               & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid))));
        bufp->chgIData(oldp+58,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata),32);
        bufp->chgIData(oldp+59,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0),32);
        bufp->chgIData(oldp+60,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1),32);
        bufp->chgIData(oldp+61,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2),32);
        bufp->chgIData(oldp+62,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3),32);
        bufp->chgIData(oldp+63,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4),32);
        bufp->chgIData(oldp+64,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5),32);
        bufp->chgIData(oldp+65,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6),32);
        bufp->chgIData(oldp+66,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7),32);
        bufp->chgIData(oldp+67,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8),32);
        bufp->chgIData(oldp+68,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9),32);
        bufp->chgIData(oldp+69,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10),32);
        bufp->chgIData(oldp+70,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11),32);
        bufp->chgIData(oldp+71,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12),32);
        bufp->chgIData(oldp+72,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13),32);
        bufp->chgIData(oldp+73,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14),32);
        bufp->chgIData(oldp+74,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15),32);
        bufp->chgIData(oldp+75,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16),32);
        bufp->chgIData(oldp+76,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17),32);
        bufp->chgIData(oldp+77,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18),32);
        bufp->chgIData(oldp+78,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19),32);
        bufp->chgIData(oldp+79,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20),32);
        bufp->chgIData(oldp+80,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21),32);
        bufp->chgIData(oldp+81,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22),32);
        bufp->chgIData(oldp+82,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23),32);
        bufp->chgIData(oldp+83,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24),32);
        bufp->chgIData(oldp+84,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25),32);
        bufp->chgIData(oldp+85,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26),32);
        bufp->chgIData(oldp+86,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27),32);
        bufp->chgIData(oldp+87,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28),32);
        bufp->chgIData(oldp+88,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29),32);
        bufp->chgIData(oldp+89,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30),32);
        bufp->chgIData(oldp+90,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31),32);
        bufp->chgIData(oldp+91,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc),32);
    }
    bufp->chgBit(oldp+92,(vlSelfRef.clock));
    bufp->chgBit(oldp+93,(vlSelfRef.reset));
    bufp->chgBit(oldp+94,(vlSelfRef.mei));
    bufp->chgBit(oldp+95,(vlSelfRef.msi));
    bufp->chgBit(oldp+96,(vlSelfRef.mti));
    bufp->chgBit(oldp+97,(vlSelfRef.sei));
    bufp->chgBit(oldp+98,(vlSelfRef.inst_sram_en));
    bufp->chgCData(oldp+99,(vlSelfRef.inst_sram_wen),4);
    bufp->chgIData(oldp+100,(vlSelfRef.inst_sram_addr),32);
    bufp->chgIData(oldp+101,(vlSelfRef.inst_sram_wdata),32);
    bufp->chgIData(oldp+102,(vlSelfRef.inst_sram_rdata),32);
    bufp->chgBit(oldp+103,(vlSelfRef.data_sram_en));
    bufp->chgCData(oldp+104,(vlSelfRef.data_sram_wen),4);
    bufp->chgIData(oldp+105,(vlSelfRef.data_sram_addr),32);
    bufp->chgIData(oldp+106,(vlSelfRef.data_sram_wdata),32);
    bufp->chgIData(oldp+107,(vlSelfRef.data_sram_rdata),32);
    bufp->chgBit(oldp+108,(vlSelfRef.debug_commit));
    bufp->chgIData(oldp+109,(vlSelfRef.debug_pc),32);
    bufp->chgCData(oldp+110,(vlSelfRef.debug_rf_wnum),5);
    bufp->chgIData(oldp+111,(vlSelfRef.debug_rf_wdata),32);
    bufp->chgCData(oldp+112,((7U & vlSelfRef.data_sram_addr)),3);
    bufp->chgIData(oldp+113,(((2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel))
                               ? (((0U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                    ? (((- (IData)(
                                                   (1U 
                                                    & (vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData 
                                                       >> 7U)))) 
                                        << 8U) | (0xffU 
                                                  & vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData))
                                    : 0U) | (((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                               ? (0xffU 
                                                  & vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData)
                                               : 0U) 
                                             | (((1U 
                                                  == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                  ? 
                                                 (((- (IData)(
                                                              (1U 
                                                               & (vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData 
                                                                  >> 0xfU)))) 
                                                   << 0x10U) 
                                                  | (0xffffU 
                                                     & vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData))
                                                  : 0U) 
                                                | (((5U 
                                                     == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                     ? 
                                                    (0xffffU 
                                                     & vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData)
                                                     : 0U) 
                                                   | (((2U 
                                                        == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                        ? vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData
                                                        : 0U) 
                                                      | ((6U 
                                                          == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op))
                                                          ? vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData
                                                          : 0U))))))
                               : vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata)),32);
    bufp->chgIData(oldp+114,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData),32);
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
