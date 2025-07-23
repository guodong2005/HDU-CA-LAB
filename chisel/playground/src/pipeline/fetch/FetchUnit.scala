package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._
class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(new ICacheReq)
    val icache_resp = Flipped(Valid(new InstPacket))
  })

  // -----------------------------
  // 状态定义
  // -----------------------------
  val sIdle :: sRequest :: sWaitResp :: Nil = Enum(3)
  val state                                 = RegInit(sIdle)

  // -----------------------------
  // 控制寄存器
  // -----------------------------
  val pc          = RegInit(PC_INIT)
  val reqPC       = RegInit(PC_INIT)
  val ifid_reg    = RegInit(0.U.asTypeOf(new IfIdData()))
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  // -----------------------------
  // 输出默认值
  // -----------------------------
  io.icache_req.valid     := false.B
  io.icache_req.bits.addr := reqPC
  io.decodeStage.data     := 0.U.asTypeOf(new IfIdData())

  // -----------------------------
  // 状态切换逻辑
  // -----------------------------
  switch(state) {
    is(sIdle) {
      when(io.branch) {
        pc    := io.target
        reqPC := io.target
      }.otherwise {
        reqPC := pc
      }

      when(!stall) {
        io.icache_req.valid := true.B
        when(io.icache_req.ready) {
          state := sWaitResp
        }.otherwise {
          state := sRequest
        }
      }
    }

    is(sRequest) {
      io.icache_req.valid := true.B
      when(io.icache_req.ready) {
        state := sWaitResp
      }
    }

    is(sWaitResp) {
      val reqLineAddr = reqPC & ~((1 << ICACHE_OFFSET_WIDTH) - 1).U
      val instIdx     = reqPC(ICACHE_OFFSET_WIDTH - 1, 2)
      val inst        = io.icache_resp.bits.data(instIdx)

      when(io.icache_resp.valid && io.icache_resp.bits.addr === reqPC) {
        when(decodeReady) {
          io.decodeStage.data.inst  := inst
          io.decodeStage.data.pc    := reqPC
          io.decodeStage.data.valid := true.B
          pc                        := reqPC + 4.U
        }.otherwise {
          ifid_reg.inst  := inst
          ifid_reg.pc    := reqPC
          ifid_reg.valid := true.B
        }
        state := sIdle
      }
    }
  }

  // -----------------------------
  // Pipeline 回填
  // -----------------------------
  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    pc                  := ifid_reg.pc + 4.U
  }
}
