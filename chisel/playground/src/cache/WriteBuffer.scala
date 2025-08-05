package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class WriteBufferEntry extends Bundle {
  val req = new DCacheReq
}

class WriteBuffer(depth: Int = 4, bypassCycles: Int = 4) extends Module {
  val io = IO(new Bundle {
    val enq          = Flipped(Decoupled(new DCacheReq))
    val deq          = Decoupled(new DCacheReq)
    val flush        = Input(Bool())
    val bypassAddr   = Input(UInt(XLEN.W))
    val bypassEnable = Input(Bool())
    val bypassHit    = Output(Bool())
    val bypassData   = Output(UInt(XLEN.W))
  })

  val buffer = Reg(Vec(depth, new WriteBufferEntry))
  val valids = RegInit(VecInit(Seq.fill(depth)(false.B)))

  // 添加 bypass 计数器，用于跟踪已发送但仍可前递的数据
  val bypassCounters = RegInit(VecInit(Seq.fill(depth)(0.U(log2Ceil(bypassCycles + 1).W))))
  val bypassable     = VecInit(bypassCounters.map(_ > 0.U))

  val validVecUInt = VecInit(valids.map(_.asBool))
  val inverted     = validVecUInt.map(x => ~x)
  val enqIdx       = PriorityEncoder(inverted)
  val deqIdx       = PriorityEncoder(validVecUInt)

  io.enq.ready := valids.count(_ === true.B) < depth.U
  io.deq.valid := valids.reduce(_ || _)
  io.deq.bits  := buffer(deqIdx).req

  // Enqueue 逻辑
  when(io.enq.fire) {
    buffer(enqIdx).req := io.enq.bits
    valids(enqIdx)     := true.B
    // 只有写请求才需要 bypass
    when(io.enq.bits.write) {
      bypassCounters(enqIdx) := bypassCycles.U
    }.otherwise {
      bypassCounters(enqIdx) := 0.U
    }
  }

  // Dequeue 逻辑
  when(io.deq.fire) {
    valids(deqIdx) := false.B
    // 保持 bypass 计数器，让数据仍可前递
    // bypassCounters(deqIdx) 保持不变
  }

  // Flush 逻辑
  when(io.flush) {
    for (i <- 0 until depth) {
      valids(i)         := false.B
      bypassCounters(i) := 0.U
    }
  }

  // 更新 bypass 计数器
  for (i <- 0 until depth) {
    when(!io.flush && bypassCounters(i) > 0.U) {
      // 如果该位置没有新的写入，则递减计数器
      when(!(io.enq.fire && enqIdx === i.U)) {
        bypassCounters(i) := bypassCounters(i) - 1.U
      }
    }
  }

  // 增强的 bypass 逻辑：检查所有可前递的数据（包括已发送的）
  val hits = VecInit(buffer.zip(bypassable).map { case (entry, canBypass) =>
    canBypass && io.bypassEnable && entry.req.write && (entry.req.addr === io.bypassAddr)
  })

  io.bypassHit  := hits.reduce(_ || _)
  io.bypassData := Mux1H(hits, buffer.map(_.req.wdata))

  // 可选：添加调试信号
  // val debug_valid_count = PopCount(valids)
  // val debug_bypass_count = PopCount(bypassable)
}
