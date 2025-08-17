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

  // 简化状态定义 - 只需要两个状态
  val sIDLE :: sWAIT_RESP :: Nil = Enum(2)
  val state                      = RegInit(sIDLE)

  // PC管理
  val pc      = RegInit(PC_INIT) // 当前要取的PC
  val next_pc = RegInit(PC_INIT + 4.U) // 下一个要取的PC

  // 请求追踪 - 只需要知道是否有未完成的请求
  val pending_valid = RegInit(false.B) // 是否有未完成的请求

  // 指令缓冲
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  // 控制信号
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady && ifid_reg.valid

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
  io.icache_req.bits.addr   := pc
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
        // 缓存的指令被消费，更新PC
        pc      := pc + 4.U
        next_pc := next_pc + 4.U
      }

      // 发送新请求（只有在没有stall且没有缓存指令时）
      when(canStart && !stall && !io.branch) {
        io.icache_req.valid     := true.B
        io.icache_req.bits.addr := pc

        when(io.icache_req.ready) {
          pending_valid := true.B
          state         := sWAIT_RESP
          // 注意：这里不预先更新PC，等指令真正被消费时再更新
        }
      }
    }

    is(sWAIT_RESP) {
      // 等待ICache响应
      when(io.icache_resp.valid && pending_valid) {
        // 检查响应地址是否匹配当前需要的PC
        // 这样可以自动过滤掉分支前的无效响应
        val resp_addr  = io.icache_resp.bits.addr
        val addr_match = resp_addr === pc

        when(addr_match) {
          // 地址匹配 - 处理我们需要的指令
          val inst = extractInst(io.icache_resp.bits.data, pc)

          when(decodeReady && !ifid_reg.valid) {
            // 直接传递给decode阶段，可以更新PC
            io.decodeStage.data.inst  := inst
            io.decodeStage.data.pc    := pc
            io.decodeStage.data.valid := true.B

            // 指令被消费，更新PC
            pc      := pc + 4.U
            next_pc := next_pc + 4.U

          }.otherwise {
            // decode阶段not ready，缓存指令，不更新PC
            ifid_reg.inst  := inst
            ifid_reg.pc    := pc
            ifid_reg.valid := true.B
          }

          pending_valid := false.B

          // 如果指令被直接消费且没有分支，继续流水线操作
          when(decodeReady && !ifid_reg.valid && !io.branch) {
            io.icache_req.valid     := true.B
            io.icache_req.bits.addr := pc

            when(io.icache_req.ready) {
              pending_valid := true.B
              // 保持在sWAIT_RESP状态继续流水线
            }.otherwise {
              state := sIDLE
            }
          }.otherwise {
            state := sIDLE
          }
        }.otherwise {
          // 地址不匹配 - 这是过期的响应（比如分支前的请求）
          // 忽略这个响应，继续等待或重新请求
          // 由于地址不匹配，说明这不是我们要的数据
          // 需要重新发送正确地址的请求
          pending_valid := false.B
          state         := sIDLE
        }
      }

      // 如果pending请求无效（可能被分支清除），回到IDLE
      when(!pending_valid) {
        state := sIDLE
      }
    }
  }

  // ========== 分支处理 ==========
  when(io.branch) {
    // 立即更新PC到目标地址
    pc      := io.target
    next_pc := io.target + 4.U

    // 清空流水线状态
    pending_valid  := false.B // 使之前的请求无效
    ifid_reg.valid := false.B

    // 强制回到IDLE状态重新开始
    state := sIDLE
  }

  // ========== 初始化处理 ==========
  when(canStart && pc === 0.U && !io.branch) {
    pc      := PC_INIT
    next_pc := PC_INIT + 4.U
  }

  // ========== Debug信号 ==========
  dontTouch(state)
  dontTouch(pending_valid)
}
