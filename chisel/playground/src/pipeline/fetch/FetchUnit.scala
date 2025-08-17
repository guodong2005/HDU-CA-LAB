package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val icache_resp = Flipped(Valid(new InstPacket))
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(new ICacheReq)
    val canStart    = Output(Bool())
  })

  // 简化状态定义
  val sIDLE :: sWAIT_RESP :: Nil = Enum(2)
  val state                      = RegInit(sIDLE)

  // PC管理 - 分离职责
  val wait_pc = RegInit(PC_INIT) // 正在等待响应的PC
  val req_pc  = RegInit(PC_INIT) // 下一个要请求的PC

  // 请求追踪
  val pending_valid = RegInit(false.B) // 是否有未完成的请求

  // 指令缓冲
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  // 控制信号
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val canSendReq  = !ifid_reg.valid || decodeReady // 可以发送新请求的条件

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := canStart && state === sIDLE

  // 指令提取辅助函数
  def extractInst(data: UInt, pc: UInt): UInt = {
    val instIdx = pc(ICACHE_OFFSET_WIDTH - 1, 2)
    MuxLookup(instIdx, 0.U)(
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

  // 默认输出
  io.icache_req.valid       := false.B
  io.icache_req.bits.addr   := req_pc
  io.decodeStage.data.valid := false.B
  io.decodeStage.data.inst  := DontCare
  io.decodeStage.data.pc    := DontCare

  // ========== 主状态机 ==========
  switch(state) {
    is(sIDLE) {
      // 处理缓存的指令
      when(ifid_reg.valid && decodeReady && !io.branch) {
        io.decodeStage.data := ifid_reg
        ifid_reg.valid      := false.B
      }

      // 发送新请求（只要条件允许就发送）
      when(canStart && canSendReq && !io.branch) {
        io.icache_req.valid     := true.B
        io.icache_req.bits.addr := req_pc

        when(io.icache_req.ready) {
          pending_valid := true.B
          wait_pc       := req_pc // 记录正在等待的地址
          req_pc        := req_pc + 4.U // 更新下一个请求地址
          state         := sWAIT_RESP
        }
      }
    }

    is(sWAIT_RESP) {
      // 首先处理缓存的指令（如果有的话）
      when(ifid_reg.valid && decodeReady && !io.branch) {
        io.decodeStage.data := ifid_reg
        ifid_reg.valid      := false.B
      }

      // 等待ICache响应
      when(io.icache_resp.valid && pending_valid) {
        val resp_addr  = io.icache_resp.bits.addr
        val addr_match = resp_addr === wait_pc

        when(addr_match) {
          // 地址匹配 - 处理响应的指令
          val inst = extractInst(io.icache_resp.bits.data, wait_pc)

          when(!ifid_reg.valid && decodeReady) {
            // 直接传递给decode阶段
            io.decodeStage.data.inst  := inst
            io.decodeStage.data.pc    := wait_pc
            io.decodeStage.data.valid := true.B
          }.otherwise {
            // 缓存指令（只有在缓冲区为空时才缓存）
            when(!ifid_reg.valid) {
              ifid_reg.inst  := inst
              ifid_reg.pc    := wait_pc
              ifid_reg.valid := true.B
            }
            // 如果缓冲区已满且decode not ready，指令会丢失
            // 这种情况应该通过canSendReq避免
          }

          pending_valid := false.B

          // 关键优化：立即尝试发送下一个请求
          // 条件：没有分支，且（缓冲区为空 或 decode ready）
          when(!io.branch && canSendReq) {
            io.icache_req.valid     := true.B
            io.icache_req.bits.addr := req_pc

            when(io.icache_req.ready) {
              pending_valid := true.B
              wait_pc       := req_pc // 更新等待地址
              req_pc        := req_pc + 4.U // 更新请求地址
              // 保持在sWAIT_RESP状态，实现连续流水线
            }.otherwise {
              state := sIDLE
            }
          }.otherwise {
            state := sIDLE
          }
        }.otherwise {
          // 地址不匹配 - 过期的响应
          pending_valid := false.B
          state         := sIDLE
        }
      }

      // 即使在等待响应时，如果没有pending请求，也可以发送新请求
      // 这处理了响应已经到达但还没处理的情况
      when(!pending_valid && canSendReq && !io.branch) {
        io.icache_req.valid     := true.B
        io.icache_req.bits.addr := req_pc

        when(io.icache_req.ready) {
          pending_valid := true.B
          wait_pc       := req_pc
          req_pc        := req_pc + 4.U
        }
      }
    }
  }

  // ========== 分支处理 ==========
  when(io.branch) {
    // 更新两个PC到目标地址
    wait_pc := io.target
    req_pc  := io.target

    // 清空流水线状态
    pending_valid  := false.B
    ifid_reg.valid := false.B

    // 强制回到IDLE状态
    state := sIDLE
  }

  // ========== 初始化处理 ==========
  when(canStart && req_pc === 0.U && !io.branch) {
    wait_pc := PC_INIT
    req_pc  := PC_INIT
  }

  // ========== Debug信号 ==========
  dontTouch(state)
  dontTouch(pending_valid)
  dontTouch(wait_pc)
  dontTouch(req_pc)
}
