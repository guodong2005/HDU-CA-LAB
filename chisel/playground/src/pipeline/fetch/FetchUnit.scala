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

  // State definitions
  val sIDLE :: sWAIT_HIT :: sWAIT_MISS :: Nil = Enum(3)
  val state                                   = RegInit(sIDLE)

  // PC管理
  val pc      = RegInit(PC_INIT) // 当前要取的PC
  val next_pc = RegInit(PC_INIT + 4.U) // 下一个要取的PC（用于流水线）

  // 请求追踪
  val pending_pc    = RegInit(0.U(XLEN.W)) // 等待响应的PC
  val pending_valid = RegInit(false.B) // 是否有未完成的请求

  // Miss tracking
  val miss_cycles   = RegInit(0.U(8.W)) // 用于检测cache miss（响应延迟）
  val miss_detected = RegInit(false.B) // 检测到cache miss

  // 指令缓冲
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  // 控制信号
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady && ifid_reg.valid

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := canStart && state === sIDLE

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
      }

      // 发送新请求
      when(canStart && !stall && !io.branch) {
        io.icache_req.valid     := true.B
        io.icache_req.bits.addr := pc

        when(io.icache_req.ready) {
          pending_pc    := pc
          pending_valid := true.B
          miss_cycles   := 0.U
          miss_detected := false.B
          state         := sWAIT_HIT

          // 预先更新PC（乐观假设会hit）
          pc      := next_pc
          next_pc := next_pc + 4.U
        }
      }
    }

    is(sWAIT_HIT) {
      // 等待ICache响应，检测是否hit
      when(io.icache_resp.valid) {
        // Cache hit - 快速处理
        val instIdx = pending_pc(ICACHE_OFFSET_WIDTH - 1, 2)
        val inst = MuxLookup(instIdx, 0.U)(
          Seq(
            0.U -> io.icache_resp.bits.data(31, 0),
            1.U -> io.icache_resp.bits.data(63, 32),
            2.U -> io.icache_resp.bits.data(95, 64),
            3.U -> io.icache_resp.bits.data(127, 96),
            4.U -> io.icache_resp.bits.data(159, 128),
            5.U -> io.icache_resp.bits.data(191, 160),
            6.U -> io.icache_resp.bits.data(223, 192),
            7.U -> io.icache_resp.bits.data(255, 224)
          )
        )

        when(decodeReady && !ifid_reg.valid) {
          // 直接传递
          io.decodeStage.data.inst  := inst
          io.decodeStage.data.pc    := pending_pc
          io.decodeStage.data.valid := true.B
        }.otherwise {
          // 缓存
          ifid_reg.inst  := inst
          ifid_reg.pc    := pending_pc
          ifid_reg.valid := true.B
        }

        pending_valid := false.B

        // 如果没有stall，可以继续发送下一个请求（流水线化）
        when(!stall && !io.branch) {
          io.icache_req.valid     := true.B
          io.icache_req.bits.addr := pc

          when(io.icache_req.ready) {
            pending_pc    := pc
            pending_valid := true.B
            miss_cycles   := 0.U
            pc            := next_pc
            next_pc       := next_pc + 4.U
            state         := sWAIT_HIT // 保持在WAIT_HIT状态（流水线）
          }.otherwise {
            state := sIDLE
          }
        }.otherwise {
          state := sIDLE
        }
      }.otherwise {
        // 检测cache miss（响应延迟超过阈值）
        miss_cycles := miss_cycles + 1.U
        when(miss_cycles > 1.U) { // 假设hit应该在2-3周期内响应
          miss_detected := true.B
          state         := sWAIT_MISS
        }
      }
    }

    is(sWAIT_MISS) {
      // Cache miss状态 - 等待内存响应，不发送新请求
      when(io.icache_resp.valid) {
        val instIdx = pending_pc(ICACHE_OFFSET_WIDTH - 1, 2)
        val inst = MuxLookup(instIdx, 0.U)(
          Seq(
            0.U -> io.icache_resp.bits.data(31, 0),
            1.U -> io.icache_resp.bits.data(63, 32),
            2.U -> io.icache_resp.bits.data(95, 64),
            3.U -> io.icache_resp.bits.data(127, 96),
            4.U -> io.icache_resp.bits.data(159, 128),
            5.U -> io.icache_resp.bits.data(191, 160),
            6.U -> io.icache_resp.bits.data(223, 192),
            7.U -> io.icache_resp.bits.data(255, 224)
          )
        )

        when(decodeReady && !ifid_reg.valid) {
          io.decodeStage.data.inst  := inst
          io.decodeStage.data.pc    := pending_pc
          io.decodeStage.data.valid := true.B
        }.otherwise {
          ifid_reg.inst  := inst
          ifid_reg.pc    := pending_pc
          ifid_reg.valid := true.B
        }

        pending_valid := false.B
        miss_detected := false.B
        state         := sIDLE
      }
    }
  }

  // ========== 分支处理 ==========
  when(io.branch) {
    // 立即更新PC
    pc      := io.target
    next_pc := io.target + 4.U

    // 清空流水线
    pending_valid  := false.B
    ifid_reg.valid := false.B
    miss_cycles    := 0.U
    miss_detected  := false.B

    // 如果在等待状态，回到IDLE
    state := sIDLE
  }

  // ========== 初始化处理 ==========
  when(canStart && pc === 0.U && !io.branch) {
    pc      := PC_INIT
    next_pc := PC_INIT + 4.U
  }

  // ========== Debug信号 ==========
  dontTouch(state)
  dontTouch(pending_pc)
  dontTouch(pending_valid)
  dontTouch(miss_detected)
  dontTouch(miss_cycles)
}
