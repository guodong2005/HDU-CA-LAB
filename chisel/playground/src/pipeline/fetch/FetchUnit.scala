package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._
import cpu.defines.Instructions.NOP

class FetchAnswer extends Bundle {
  val data  = UInt(XLEN.W)
  val pc    = UInt(XLEN.W)
  val valid = Bool()
}
class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(UInt(XLEN.W))                    // 请求地址发给 icache
    val icache_resp = Flipped(Valid(UInt((FETCH_WIDTH * 32).W))) // icache 返回的数据
  })

  // 初始化 PC 和启动控制
  val pc       = RegInit(0.U(XLEN.W))
  val canStart = RegNext(!reset.asBool) && (!reset.asBool)

  when(canStart && pc === 0.U) {
    pc := PC_INIT
  }

  // 状态机定义
  val sIdle :: sWaitCache :: Nil = Enum(2)
  val state                      = RegInit(sIdle)
  val reqPC                      = Reg(UInt(XLEN.W))
  val ifid_reg                   = RegInit(0.U.asTypeOf(new IfIdData()))

  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  // 默认输出
  io.decodeStage.data := 0.U.asTypeOf(new IfIdData())
  io.icache_req.valid := false.B
  io.icache_req.bits  := pc

  // 分支跳转优先处理
  when(io.branch) {
    pc             := io.target
    state          := sIdle
    ifid_reg.valid := false.B
  }

  // 主状态机逻辑
  switch(state) {
    is(sIdle) {
      when(canStart && !stall) {
        io.icache_req.valid := true.B
        when(io.icache_req.valid && io.icache_req.ready) {
          reqPC := pc
          state := sWaitCache
        }
      }
    }

    is(sWaitCache) {
      when(io.icache_resp.valid) {
        val instrs = io.icache_resp.bits.asTypeOf(Vec(FETCH_WIDTH, UInt(32.W)))
        val inst   = instrs(0) // 取第一个指令（可扩展为多发射）

        when(decodeReady) {
          io.decodeStage.data.inst  := inst
          io.decodeStage.data.pc    := reqPC
          io.decodeStage.data.valid := true.B
          pc                        := reqPC + 4.U
          state                     := sIdle
        }.otherwise {
          ifid_reg.inst  := inst
          ifid_reg.pc    := reqPC
          ifid_reg.valid := true.B
        }
      }
    }
  }

  // 如果 decode 阶段准备好，输出寄存器中的数据
  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    pc                  := ifid_reg.pc + 4.U
    state               := sIdle
  }
}
