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

  // 通过比较两个PC判断是否有pending请求
  val has_pending = wait_pc =/= req_pc

  // 指令缓冲
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  // 控制信号
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go

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

      // 发送新请求 - 只有在有空间存储响应时才发送
      when(canStart && (!ifid_reg.valid || decodeReady) && !io.branch) {
        io.icache_req.valid     := true.B
        io.icache_req.bits.addr := req_pc

        when(io.icache_req.ready) {
          req_pc := req_pc + 4.U // 更新下一个请求地址
          state  := sWAIT_RESP
        }
      }
    }

    is(sWAIT_RESP) {
      // 处理缓存的指令
      val ifid_consumed = ifid_reg.valid && decodeReady && !io.branch
      when(ifid_consumed) {
        io.decodeStage.data := ifid_reg
        ifid_reg.valid      := false.B
      }

      // 处理ICache响应 - 只有在有pending请求时才处理
      when(io.icache_resp.valid && has_pending) {
        val resp_addr  = io.icache_resp.bits.addr
        val addr_match = resp_addr === wait_pc

        when(addr_match) {
          // 地址匹配 - 处理响应的指令
          val inst = extractInst(io.icache_resp.bits.data, wait_pc)

          // 计算缓冲区是否可用
          val buffer_available = !ifid_reg.valid || ifid_consumed

          when(buffer_available && decodeReady && !ifid_consumed) {
            // 直接传递给decode阶段
            io.decodeStage.data.inst  := inst
            io.decodeStage.data.pc    := wait_pc
            io.decodeStage.data.valid := true.B
          }.elsewhen(buffer_available) {
            // 缓存指令
            ifid_reg.inst  := inst
            ifid_reg.pc    := wait_pc
            ifid_reg.valid := true.B
          }
          // 否则丢弃（不应该发生，因为我们控制了请求发送）

          // 更新wait_pc，表示已处理这个响应
          wait_pc := wait_pc + 4.U

          // 如果还有更多pending请求，继续等待
          // 否则尝试发送新请求或回到IDLE
          when(has_pending) {
            // 还有pending请求，保持在WAIT_RESP
          }.elsewhen(!io.branch && decodeReady && !ifid_consumed) {
            // 没有pending了，但可以立即发送新请求
            io.icache_req.valid     := true.B
            io.icache_req.bits.addr := req_pc

            when(io.icache_req.ready) {
              req_pc := req_pc + 4.U
              // 保持在sWAIT_RESP状态
            }.otherwise {
              state := sIDLE
            }
          }.otherwise {
            state := sIDLE
          }
        }
        // 地址不匹配的响应会被自动忽略（过期的响应）
      }

      // 如果没有pending请求但可以发送新的，尝试发送
      when(!has_pending && (!ifid_reg.valid || decodeReady) && !io.branch) {
        io.icache_req.valid     := true.B
        io.icache_req.bits.addr := req_pc

        when(io.icache_req.ready) {
          req_pc := req_pc + 4.U
        }.otherwise {
          // 没有新请求，回到IDLE
          state := sIDLE
        }
      }.elsewhen(!has_pending) {
        // 没有pending且不能发送新请求，回到IDLE
        state := sIDLE
      }
    }
  }

  // ========== 分支处理 ==========
  when(io.branch) {
    // 同步两个PC到目标地址
    wait_pc := io.target
    req_pc  := io.target

    // 清空流水线状态
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
  dontTouch(has_pending)
  dontTouch(wait_pc)
  dontTouch(req_pc)
}
