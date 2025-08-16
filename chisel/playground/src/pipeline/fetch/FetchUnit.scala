package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

// Branch Target Buffer Entry
class BTBEntry extends Bundle {
  val valid   = Bool()
  val tag     = UInt((XLEN - 10).W)
  val target  = UInt(XLEN.W)
  val counter = UInt(2.W) // 2-bit saturating counter
}

// BPU Feedback from Execute Stage
class BPUFeedback extends Bundle {
  val valid         = Bool()
  val pc            = UInt(XLEN.W)
  val actual_taken  = Bool()
  val actual_target = UInt(XLEN.W)
  val mispredicted  = Bool()
}

// BPU Prediction Result
class BPUPrediction extends Bundle {
  val predicted_taken  = Bool()
  val predicted_target = UInt(XLEN.W)
}

// Branch Prediction Unit
class Bpu extends Module {
  val io = IO(new Bundle {
    val pc_in      = Input(UInt(XLEN.W))
    val prediction = Output(new BPUPrediction())
    val feedback   = Input(new BPUFeedback())
    val flush_req  = Output(Bool())
  })

  val btb_size = 1024
  val btb      = RegInit(VecInit(Seq.fill(btb_size)(0.U.asTypeOf(new BTBEntry()))))

  // Extract index and tag from PC
  val pc_index = io.pc_in(9, 2)
  val pc_tag   = io.pc_in(XLEN - 1, 10)

  val btb_entry = btb(pc_index)

  // Prediction logic
  val hit             = btb_entry.valid && (btb_entry.tag === pc_tag)
  val predicted_taken = hit && (btb_entry.counter >= 2.U)

  io.prediction.predicted_taken  := predicted_taken
  io.prediction.predicted_target := Mux(hit, btb_entry.target, 0.U)

  // Feedback handling
  when(io.feedback.valid) {
    val fb_index = io.feedback.pc(9, 2)
    val fb_tag   = io.feedback.pc(XLEN - 1, 10)
    val fb_entry = btb(fb_index)

    when(fb_entry.valid && (fb_entry.tag === fb_tag)) {
      // Update existing entry
      when(io.feedback.actual_taken) {
        btb(fb_index).counter := Mux(fb_entry.counter === 3.U, 3.U, fb_entry.counter + 1.U)
        btb(fb_index).target  := io.feedback.actual_target
      }.otherwise {
        btb(fb_index).counter := Mux(fb_entry.counter === 0.U, 0.U, fb_entry.counter - 1.U)
      }
    }.otherwise {
      // Allocate new entry
      btb(fb_index).valid   := true.B
      btb(fb_index).tag     := fb_tag
      btb(fb_index).target  := io.feedback.actual_target
      btb(fb_index).counter := Mux(io.feedback.actual_taken, 2.U, 1.U)
    }
  }

  io.flush_req := io.feedback.valid && io.feedback.mispredicted
}

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage  = new FetchUnitDecodeUnit()
    val icache_resp  = Flipped(Valid(new InstPacket))
    val signal       = Input(new Signals())
    val icache_req   = Decoupled(new ICacheReq)
    val canStart     = Output(Bool())
    val bpu_feedback = Input(new BPUFeedback()) // 添加BPU反馈接口
  })

  // 添加BPU模块
  val bpu = Module(new Bpu())

  val pc          = RegInit(PC_INIT)
  val reqPC       = Reg(UInt(XLEN.W))
  val state       = RegInit(0.U(2.W)) // sIdle :: sWait
  val sIdle       = 0.U
  val sWait       = 1.U
  val ifid_reg    = RegInit(0.U.asTypeOf(new IfIdData()))
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid
  val alignedPC   = pc & ~((1 << ICACHE_OFFSET_WIDTH) - 1).U
  val instIdx     = pc(ICACHE_OFFSET_WIDTH - 1, 2)

  // 连接BPU
  bpu.io.pc_in    := pc
  bpu.io.feedback := io.bpu_feedback

  val branch = io.signal.branchControl.branch || bpu.io.flush_req // 添加BPU flush
  val target = Mux(
    bpu.io.flush_req,
    Mux(io.bpu_feedback.valid, io.bpu_feedback.actual_target, pc + 4.U),
    io.signal.branchControl.target
  )

  // ✅ 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := state === sIdle && !stall && RegNext(canStart)

  // ✅ 默认输出
  io.icache_req.bits.addr := pc
  io.icache_req.valid     := io.canStart
  io.decodeStage.data     := 0.U.asTypeOf(new IfIdData())

  // ========== 修复后的逻辑 ==========
  // 分支处理：统一的PC更新逻辑
  when(branch) {
    pc             := target
    state          := sIdle
    ifid_reg.valid := false.B // 清除缓存的指令
  }.otherwise {
    // 添加BPU预测的PC更新
    val next_pc = Mux(bpu.io.prediction.predicted_taken, bpu.io.prediction.predicted_target, pc + 4.U)

    switch(state) {
      is(sIdle) {
        when(canStart && pc === 0.U) {
          pc := PC_INIT
        }
        when(io.canStart && io.icache_req.ready) {
          reqPC := pc
          state := sWait
          // 使用BPU预测更新PC
          pc := next_pc
        }
      }
      is(sWait) {
        val respLineAddr = io.icache_resp.bits.addr
        val instIdx      = reqPC(ICACHE_OFFSET_WIDTH - 1, 2)
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
        val matchAddr = respLineAddr === (reqPC)
        when(io.icache_resp.valid && matchAddr) {
          when(decodeReady) {
            io.decodeStage.data.inst  := inst
            io.decodeStage.data.pc    := reqPC
            io.decodeStage.data.valid := true.B
            // 添加预测信息
            io.decodeStage.data.predicted_taken  := bpu.io.prediction.predicted_taken
            io.decodeStage.data.predicted_target := bpu.io.prediction.predicted_target
            state                                := sIdle
          }.otherwise {
            ifid_reg.inst  := inst
            ifid_reg.pc    := reqPC
            ifid_reg.valid := true.B
            // 添加预测信息到寄存器
            ifid_reg.predicted_taken  := bpu.io.prediction.predicted_taken
            ifid_reg.predicted_target := bpu.io.prediction.predicted_target
            state                     := sIdle // 回到idle状态，等待decode ready
          }
        }
      }
    }
    // 处理缓存的指令
    when(ifid_reg.valid && decodeReady) {
      io.decodeStage.data := ifid_reg
      ifid_reg.valid      := false.B
    }
  }

  // 分支时立即更新icache请求地址
  when(branch) {
    io.icache_req.bits.addr := target
    io.icache_req.valid     := true.B // 分支时立即发送新地址的请求
  }
}
