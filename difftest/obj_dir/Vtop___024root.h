// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(mei,0,0);
    VL_IN8(msi,0,0);
    VL_IN8(mti,0,0);
    VL_IN8(sei,0,0);
    VL_OUT8(inst_sram_en,0,0);
    VL_OUT8(inst_sram_wen,3,0);
    VL_OUT8(data_sram_en,0,0);
    VL_OUT8(data_sram_wen,7,0);
    VL_OUT8(debug_commit,0,0);
    VL_OUT8(debug_rf_wnum,4,0);
    CData/*1:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_56;
    CData/*2:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType;
    CData/*1:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuType;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid;
    CData/*4:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr;
    CData/*1:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid;
    CData/*4:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr;
    CData/*0:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid;
    CData/*4:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
    CData/*0:0*/ __VactContinue;
    SData/*9:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN;
    SData/*15:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_3;
    VL_OUT(inst_sram_addr,31,0);
    VL_OUT(inst_sram_wdata,31,0);
    VL_IN(inst_sram_rdata,31,0);
    VL_OUT(data_sram_addr,31,0);
    IData/*31:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T;
    IData/*16:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_1;
    IData/*31:0*/ __VactIterCount;
    VL_OUT64(data_sram_wdata,63,0);
    VL_IN64(data_sram_rdata,63,0);
    VL_OUT64(debug_pc,63,0);
    VL_OUT64(debug_rf_wdata,63,0);
    QData/*63:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc;
    QData/*63:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst;
    QData/*63:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc;
    QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc;
    QData/*63:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc;
    QData/*63:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
    QData/*63:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
