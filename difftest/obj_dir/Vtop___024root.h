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
        VL_OUT8(data_sram_wen,3,0);
        VL_OUT8(debug_commit,0,0);
        VL_OUT8(debug_rf_wnum,4,0);
        CData/*0:0*/ top__DOT__core__DOT__core__DOT___controlUnit_io_signals_fetchUnitSignal_do_flush;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_op;
        CData/*1:0*/ top__DOT__core__DOT__core__DOT___decodeUnit_io_executeStage_data_info_fusel;
        CData/*1:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT__state;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_valid;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_raddr;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_raddr;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src1_ren;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT___decoder_io_out_info_src2_ren;
        CData/*2:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__instrType;
        CData/*2:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT__instrType;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_58;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_59;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT___GEN_60;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__decoder__DOT____VdfgRegularize_hb9908eda_0_10;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_valid;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_op;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_wen;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_reg_waddr;
        CData/*1:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_fusel;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__unnamedblk1__DOT___GEN;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_valid;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_op;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_wen;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_reg_waddr;
        CData/*1:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_info_fusel;
        CData/*2:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_addr3;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_valid;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_wen;
        CData/*4:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_info_reg_waddr;
        CData/*0:0*/ top__DOT__core__DOT__core__DOT__controlUnit__DOT__pipeline_stall;
        CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_18;
        CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_20;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
        CData/*0:0*/ __VactContinue;
        SData/*11:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_info_imm;
        VL_OUT(inst_sram_addr,31,0);
        VL_OUT(inst_sram_wdata,31,0);
        VL_IN(inst_sram_rdata,31,0);
        VL_OUT(data_sram_addr,31,0);
        VL_OUT(data_sram_wdata,31,0);
        VL_IN(data_sram_rdata,31,0);
        VL_OUT(debug_pc,31,0);
        VL_OUT(debug_rf_wdata,31,0);
        IData/*31:0*/ top__DOT__core__DOT__core__DOT___executeUnit_io_target;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT__pc;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__fetchUnit__DOT___io_instSram_addr_T_3;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_inst;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__decodeStage__DOT__data_pc;
    };
    struct {
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__decodeUnit__DOT__imm;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_0;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_1;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_2;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_3;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_4;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_5;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_6;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_7;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_8;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_9;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_10;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_11;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_12;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_13;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_14;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_15;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_16;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_17;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_18;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_19;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_20;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_21;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_22;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_23;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_24;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_25;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_26;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_27;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_28;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_29;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_30;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT__regs_31;
        VlWide<32>/*1023:0*/ top__DOT__core__DOT__core__DOT__regfile__DOT___GEN;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_pc;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src1_data;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeStage__DOT__data_src_info_src2_data;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT____VdfgRegularize_hde4b9769_0_3;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_pc;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__memoryStage__DOT__data_rd_info_wdata;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__memoryUnit__DOT__memData;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_pc;
        IData/*31:0*/ top__DOT__core__DOT__core__DOT__writeBackStage__DOT__data_rd_info_wdata;
        IData/*31:0*/ __VactIterCount;
        QData/*32:0*/ top__DOT__core__DOT__core__DOT__executeUnit__DOT__Fu__DOT__mdu__DOT___result_T_6;
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
