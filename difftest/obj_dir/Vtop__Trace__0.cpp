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
        bufp->chgCData(oldp+8,((((5U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                 | ((4U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                    | ((6U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)) 
                                       | (2U == (IData)(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType)))))
                                 ? (0x1fU & (IData)(
                                                    (vlSelfRef.top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst 
                                                     >> 7U)))
                                 : 0U)),5);
        bufp->chgCData(oldp+9,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuType),2);
        bufp->chgCData(oldp+10,(vlSelfRef.top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType),3);
        bufp->chgQData(oldp+11,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc),64);
        bufp->chgBit(oldp+13,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid));
        bufp->chgCData(oldp+14,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr),5);
        bufp->chgCData(oldp+15,(vlSelfRef.top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel),2);
        bufp->chgCData(oldp+16,(vlSelfRef.top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state),2);
        bufp->chgQData(oldp+17,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc),64);
        bufp->chgBit(oldp+19,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid));
        bufp->chgCData(oldp+20,(vlSelfRef.top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+21,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc),64);
        bufp->chgBit(oldp+23,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid));
        bufp->chgCData(oldp+24,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr),5);
        bufp->chgQData(oldp+25,(vlSelfRef.top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata),64);
    }
    bufp->chgBit(oldp+27,(vlSelfRef.clock));
    bufp->chgBit(oldp+28,(vlSelfRef.reset));
    bufp->chgBit(oldp+29,(vlSelfRef.mei));
    bufp->chgBit(oldp+30,(vlSelfRef.msi));
    bufp->chgBit(oldp+31,(vlSelfRef.mti));
    bufp->chgBit(oldp+32,(vlSelfRef.sei));
    bufp->chgBit(oldp+33,(vlSelfRef.inst_sram_en));
    bufp->chgCData(oldp+34,(vlSelfRef.inst_sram_wen),4);
    bufp->chgIData(oldp+35,(vlSelfRef.inst_sram_addr),32);
    bufp->chgIData(oldp+36,(vlSelfRef.inst_sram_wdata),32);
    bufp->chgIData(oldp+37,(vlSelfRef.inst_sram_rdata),32);
    bufp->chgBit(oldp+38,(vlSelfRef.data_sram_en));
    bufp->chgCData(oldp+39,(vlSelfRef.data_sram_wen),8);
    bufp->chgIData(oldp+40,(vlSelfRef.data_sram_addr),32);
    bufp->chgQData(oldp+41,(vlSelfRef.data_sram_wdata),64);
    bufp->chgQData(oldp+43,(vlSelfRef.data_sram_rdata),64);
    bufp->chgBit(oldp+45,(vlSelfRef.debug_commit));
    bufp->chgQData(oldp+46,(vlSelfRef.debug_pc),64);
    bufp->chgCData(oldp+48,(vlSelfRef.debug_rf_wnum),5);
    bufp->chgQData(oldp+49,(vlSelfRef.debug_rf_wdata),64);
    bufp->chgQData(oldp+51,((QData)((IData)(vlSelfRef.inst_sram_rdata))),64);
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
