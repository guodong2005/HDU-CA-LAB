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
  val decodeReady   = io.signal.fetchUnitSignal.allow_to_go
  val bufferStalled = ifid_reg.valid && !decodeReady // 缓冲区被阻塞
  val canAcceptInst = !ifid_reg.valid || decodeReady // 可以接受新指令

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

      // 发送新请求 - 只有在没有阻塞时才发送
      when(canStart && !bufferStalled && !io.branch) {
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
      val ifid_consumed = ifid_reg.valid && decodeReady && !io.branch
      when(ifid_consumed) {
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

          // 注意：要考虑同周期可能刚消费了缓冲指令
          val buffer_available = !ifid_reg.valid || ifid_consumed

          when(buffer_available && decodeReady && !ifid_consumed) {
            // 直接传递给decode阶段（只有在没有同时消费缓冲指令时）
            io.decodeStage.data.inst  := inst
            io.decodeStage.data.pc    := wait_pc
            io.decodeStage.data.valid := true.B
          }.elsewhen(buffer_available) {
            // 缓存指令
            ifid_reg.inst  := inst
            ifid_reg.pc    := wait_pc
            ifid_reg.valid := true.B
          }
          // 如果缓冲区不可用，指令会丢失 - 这不应该发生

          pending_valid := false.B

          // 决定是否继续发送请求
          // 关键：只有在没有阻塞时才发送新请求
          val nextBufferStalled = (buffer_available && !decodeReady && !ifid_consumed) ||
            (!buffer_available)

          when(!io.branch && !nextBufferStalled) {
            io.icache_req.valid     := true.B
            io.icache_req.bits.addr := req_pc

            when(io.icache_req.ready) {
              pending_valid := true.B
              wait_pc       := req_pc
              req_pc        := req_pc + 4.U
              // 保持在sWAIT_RESP状态
            }.otherwise {
              state := sIDLE
            }
          }.otherwise {
            state := sIDLE
          }
        }
        // 地址不匹配时不做任何事，继续等待正确的响应
      }

      // 没有pending请求时，检查是否可以发送新请求
      // 重要：只有在缓冲区不阻塞时才发送
      when(!pending_valid && !bufferStalled && !io.branch) {
        io.icache_req.valid     := true.B
        io.icache_req.bits.addr := req_pc

        when(io.icache_req.ready) {
          pending_valid := true.B
          wait_pc       := req_pc
          req_pc        := req_pc + 4.U
        }.otherwise {
          // 无法发送新请求，回到IDLE
          state := sIDLE
        }
      }.elsewhen(!pending_valid && bufferStalled) {
        // 缓冲区阻塞且没有pending，回到IDLE等待
        state := sIDLE
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
  dontTouch(bufferStalled)
}
