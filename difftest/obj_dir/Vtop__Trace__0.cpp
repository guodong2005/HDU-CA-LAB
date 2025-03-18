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
        bufp->chgCData(oldp+14,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__Decoder__DOT__io_out_info_op_0),5);
        bufp->chgCData(oldp+15,((0x1fU & (IData)((vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                  >> 7U)))),5);
        bufp->chgCData(oldp+16,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__Decoder__DOT__unnamedblk1__DOT__instrType),3);
        bufp->chgQData(oldp+17,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc),64);
        bufp->chgBit(oldp+19,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
        bufp->chgCData(oldp+20,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op),5);
        bufp->chgBit(oldp+21,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+22,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+23,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data),64);
        bufp->chgQData(oldp+25,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data),64);
        bufp->chgQData(oldp+27,(vlSelfRef.top__DOT__core__DOT__core__DOT___executeUnit_io_memoryStage_data_rd_info_wdata),64);
        bufp->chgQData(oldp+29,((0x7fffffffffffffffULL 
                                 & ((QData)((IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data)) 
                                    << (0x1fU & (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data))))),63);
        bufp->chgIData(oldp+31,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__Alu__DOT__arithmeticShiftResult),32);
        bufp->chgCData(oldp+32,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state),2);
        bufp->chgQData(oldp+33,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc),64);
        bufp->chgBit(oldp+35,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
        bufp->chgBit(oldp+36,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen));
        bufp->chgCData(oldp+37,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+38,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata),64);
        bufp->chgBit(oldp+40,(vlSelfRef.top__DOT__core__DOT__core__DOT___writeBackUnit_io_regfile_wen));
        bufp->chgCData(oldp+41,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+42,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata),64);
        bufp->chgQData(oldp+44,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0),64);
        bufp->chgQData(oldp+46,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1),64);
        bufp->chgQData(oldp+48,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2),64);
        bufp->chgQData(oldp+50,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3),64);
        bufp->chgQData(oldp+52,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4),64);
        bufp->chgQData(oldp+54,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5),64);
        bufp->chgQData(oldp+56,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6),64);
        bufp->chgQData(oldp+58,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7),64);
        bufp->chgQData(oldp+60,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8),64);
        bufp->chgQData(oldp+62,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9),64);
        bufp->chgQData(oldp+64,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10),64);
        bufp->chgQData(oldp+66,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11),64);
        bufp->chgQData(oldp+68,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12),64);
        bufp->chgQData(oldp+70,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13),64);
        bufp->chgQData(oldp+72,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14),64);
        bufp->chgQData(oldp+74,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15),64);
        bufp->chgQData(oldp+76,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16),64);
        bufp->chgQData(oldp+78,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17),64);
        bufp->chgQData(oldp+80,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18),64);
        bufp->chgQData(oldp+82,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19),64);
        bufp->chgQData(oldp+84,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20),64);
        bufp->chgQData(oldp+86,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21),64);
        bufp->chgQData(oldp+88,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22),64);
        bufp->chgQData(oldp+90,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23),64);
        bufp->chgQData(oldp+92,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24),64);
        bufp->chgQData(oldp+94,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25),64);
        bufp->chgQData(oldp+96,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26),64);
        bufp->chgQData(oldp+98,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27),64);
        bufp->chgQData(oldp+100,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28),64);
        bufp->chgQData(oldp+102,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29),64);
        bufp->chgQData(oldp+104,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30),64);
        bufp->chgQData(oldp+106,(vlSelfRef.top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31),64);
        bufp->chgQData(oldp+108,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc),64);
        bufp->chgBit(oldp+110,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid));
        bufp->chgBit(oldp+111,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen));
    }
    bufp->chgBit(oldp+112,(vlSelfRef.clock));
    bufp->chgBit(oldp+113,(vlSelfRef.reset));
    bufp->chgBit(oldp+114,(vlSelfRef.mei));
    bufp->chgBit(oldp+115,(vlSelfRef.msi));
    bufp->chgBit(oldp+116,(vlSelfRef.mti));
    bufp->chgBit(oldp+117,(vlSelfRef.sei));
    bufp->chgBit(oldp+118,(vlSelfRef.inst_sram_en));
    bufp->chgCData(oldp+119,(vlSelfRef.inst_sram_wen),4);
    bufp->chgIData(oldp+120,(vlSelfRef.inst_sram_addr),32);
    bufp->chgIData(oldp+121,(vlSelfRef.inst_sram_wdata),32);
    bufp->chgIData(oldp+122,(vlSelfRef.inst_sram_rdata),32);
    bufp->chgBit(oldp+123,(vlSelfRef.data_sram_en));
    bufp->chgCData(oldp+124,(vlSelfRef.data_sram_wen),8);
    bufp->chgIData(oldp+125,(vlSelfRef.data_sram_addr),32);
    bufp->chgQData(oldp+126,(vlSelfRef.data_sram_wdata),64);
    bufp->chgQData(oldp+128,(vlSelfRef.data_sram_rdata),64);
    bufp->chgBit(oldp+130,(vlSelfRef.debug_commit));
    bufp->chgQData(oldp+131,(vlSelfRef.debug_pc),64);
    bufp->chgCData(oldp+133,(vlSelfRef.debug_rf_wnum),5);
    bufp->chgQData(oldp+134,(vlSelfRef.debug_rf_wdata),64);
    bufp->chgQData(oldp+136,((QData)((IData)(vlSelfRef.inst_sram_rdata))),64);
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
