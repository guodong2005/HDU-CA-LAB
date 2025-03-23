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
    // Anonymous structures to workaround compiler member-count bugs
    struct {
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
        CData/*1:0*/ top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel;
        CData/*1:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid;
        CData/*2:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__fuOpType;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___op_T_37;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_74;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_75;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_76;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_9;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr;
        CData/*1:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_2;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr;
        CData/*1:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel;
        CData/*2:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
        CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_2;
        CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_4;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
        CData/*0:0*/ __VactContinue;
        VL_OUT(inst_sram_addr,31,0);
        VL_OUT(inst_sram_wdata,31,0);
        VL_IN(inst_sram_rdata,31,0);
        VL_OUT(data_sram_addr,31,0);
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T_3;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__alu__DOT__logicalShiftResult;
        VlWide<4>/*127:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___GEN_0;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__remResult_1;
        IData/*31:0*/ __VactIterCount;
        VL_OUT64(data_sram_wdata,63,0);
        VL_IN64(data_sram_rdata,63,0);
        VL_OUT64(debug_pc,63,0);
        VL_OUT64(debug_rf_wdata,63,0);
        QData/*63:0*/ top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_src_info_src2_data;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1;
    };
    struct {
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31;
        VlWide<64>/*2047:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT___GEN;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_instr;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___mdu_io_result;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT___alu_io_result;
        QData/*32:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT__divtmp;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__bru__DOT____VdfgRegularize_h773b8ade_0_3;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
        QData/*63:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        QData/*63:0*/ __VdfgRegularize_hd87f99a1_1_0;
        VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    };
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
