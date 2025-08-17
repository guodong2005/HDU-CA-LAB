package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val icache_resp = Flipped(Valid(new InstPacket))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(new ICacheReq)
    val canStart    = Output(Bool())
  })

  val pc        = RegInit(PC_INIT)
  val state     = RegInit(0.U(2.W))
  val sIdle     = 0.U
  val sWaitMiss = 1.U // 只等待miss的响应

  val ifid_reg     = RegInit(0.U.asTypeOf(new IfIdData()))
  val pending_req  = RegInit(false.B) // 标记是否有pending的miss请求
  val pending_addr = RegInit(0.U(XLEN.W)) // 保存pending请求的地址

  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid
  val instIdx     = pc(ICACHE_OFFSET_WIDTH - 1, 2)

  val branch = io.signal.branchControl.branch
  val target = io.signal.branchControl.target

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := canStart

  // 默认输出
  io.icache_req.bits.addr := pc
  io.icache_req.valid     := false.B
  io.decodeStage.data     := 0.U.asTypeOf(new IfIdData())

  // 指令提取逻辑
  def extractInst(data: UInt, pc: UInt): UInt = {
    val idx = pc(ICACHE_OFFSET_WIDTH - 1, 2)
    MuxLookup(idx, 0.U)(
      Seq(
        0.U -> data(31, 0),
        1.U -> data(63, 32),
        2.U -> data(95, 64),
        3.U -> data(127, 96),
        4.U -> data(159, 128),
        5.U -> data(191, 160),
        6.U -> data(223, 192),
        7.U -> data(255, 224)
      )
    )
  }

  // 分支处理：清理所有状态
  when(branch) {
    pc             := target
    state          := sIdle
    ifid_reg.valid := false.B
    pending_req    := false.B
    pending_addr   := 0.U
  }.otherwise {
    switch(state) {
      is(sIdle) {
        // 处理缓存的指令
        when(ifid_reg.valid && decodeReady) {
          io.decodeStage.data := ifid_reg
          ifid_reg.valid      := false.B
          pc                  := ifid_reg.pc + 4.U
        }.elsewhen(canStart && !stall) {
          // 发送新的icache请求
          io.icache_req.valid     := true.B
          io.icache_req.bits.addr := pc

          when(io.icache_req.ready) {
            pending_req  := true.B
            pending_addr := pc // 保存请求地址
            // 不改变状态，等待同周期或下周期的响应
          }
        }

        // 处理icache响应（可能是同周期的hit响应）
        when(io.icache_resp.valid && pending_req) {
          val addr_match = io.icache_resp.bits.addr === pending_addr
          when(addr_match) {
            val inst = extractInst(io.icache_resp.bits.data, pending_addr)
            pending_req := false.B

            when(decodeReady) {
              // 直接发送到decode阶段
              io.decodeStage.data.inst  := inst
              io.decodeStage.data.pc    := pending_addr
              io.decodeStage.data.valid := true.B
              pc                        := pending_addr + 4.U
            }.otherwise {
              // 缓存指令
              ifid_reg.inst  := inst
              ifid_reg.pc    := pending_addr
              ifid_reg.valid := true.B
              pc             := pending_addr + 4.U
            }
          }
          // 地址不匹配时忽略响应，继续等待
        }
      }

      is(sWaitMiss) {
        // 等待miss响应
        when(io.icache_resp.valid && pending_req) {
          val addr_match = io.icache_resp.bits.addr === pending_addr
          when(addr_match) {
            val inst = extractInst(io.icache_resp.bits.data, pending_addr)
            pending_req := false.B
            state       := sIdle

            when(decodeReady) {
              io.decodeStage.data.inst  := inst
              io.decodeStage.data.pc    := pending_addr
              io.decodeStage.data.valid := true.B
              pc                        := pending_addr + 4.U
            }.otherwise {
              ifid_reg.inst  := inst
              ifid_reg.pc    := pending_addr
              ifid_reg.valid := true.B
              pc             := pending_addr + 4.U
            }
          }
          // 地址不匹配时继续等待正确的响应
        }
      }
    }

    // 如果发送了请求但本周期没有响应，说明是miss，进入等待状态
    when(io.icache_req.valid && io.icache_req.ready && !io.icache_resp.valid && state === sIdle) {
      state := sWaitMiss
    }
  }

  // 分支时立即发送新地址请求
  when(branch) {
    io.icache_req.bits.addr := target
    io.icache_req.valid     := true.B
    when(io.icache_req.ready) {
      pending_req  := true.B
      pending_addr := target
    }
  }
}
