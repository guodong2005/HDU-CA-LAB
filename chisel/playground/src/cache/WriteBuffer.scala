package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class WriteBufferEntry extends Bundle {
  val req       = new DCacheReq
  val timestamp = UInt(4.W) // 4位时间戳，支持16个时间点循环
}

class WriteBuffer(depth: Int = 4) extends Module {
  val io = IO(new Bundle {
    val enq          = Flipped(Decoupled(new DCacheReq))
    val deq          = Decoupled(new DCacheReq)
    val flush        = Input(Bool())
    val bypassAddr   = Input(UInt(XLEN.W))
    val bypassEnable = Input(Bool())
    val bypassHit    = Output(Bool())
    val bypassData   = Output(UInt(XLEN.W))
  })

  // 全局时间戳计数器（4位循环计数）
  val globalTimestamp = RegInit(0.U(4.W))

  // Buffer和valid标志
  val buffer = RegInit(VecInit(Seq.fill(depth)(0.U.asTypeOf(new WriteBufferEntry))))
  val valids = RegInit(VecInit(Seq.fill(depth)(false.B)))

  // 队列管理逻辑
  val validVecUInt = VecInit(valids.map(_.asBool))
  val inverted     = validVecUInt.map(x => ~x)
  val enqIdx       = PriorityEncoder(inverted)
  val deqIdx       = PriorityEncoder(validVecUInt)

  // 基本队列接口
  io.enq.ready := valids.count(_ === true.B) < depth.U
  io.deq.valid := valids.reduce(_ || _)
  io.deq.bits  := buffer(deqIdx).req

  // 入队逻辑 - 分配时间戳
  when(io.enq.fire) {
    buffer(enqIdx).req       := io.enq.bits
    buffer(enqIdx).timestamp := globalTimestamp
    valids(enqIdx)           := true.B
    globalTimestamp          := globalTimestamp + 1.U
  }

  // 出队逻辑
  when(io.deq.fire) {
    valids(deqIdx) := false.B
  }

  // 清空逻辑
  when(io.flush) {
    for (i <- 0 until depth) {
      valids(i) := false.B
      buffer(i) := 0.U.asTypeOf(new WriteBufferEntry)
    }
    globalTimestamp := 0.U
  }

  // 增强的Bypass逻辑 - 基于时间戳选择最新的匹配项
  val hits = VecInit(buffer.zip(valids).map {
    case (entry, v) =>
      v && io.bypassEnable && entry.req.write && (entry.req.addr === io.bypassAddr)
  })

  // 找到所有匹配项中时间戳最新的那个
  // 使用4位并行比较器找到最新时间戳
  val hitTimestamps = VecInit(buffer.zip(hits).map {
    case (entry, hit) => Mux(hit, entry.timestamp, 0.U)
  })

  // 并行查找最新时间戳
  val newestTimestamp = hitTimestamps.reduce((a, b) => {
    // 考虑4位时间戳的循环特性
    val diff     = a - b
    val aIsNewer = diff(3) === 0.B && diff =/= 0.U // 简化的时间戳比较
    Mux(aIsNewer, a, b)
  })

  // 生成最终的选择信号
  val finalHits = VecInit(buffer.zip(hits).map {
    case (entry, hit) => hit && (entry.timestamp === newestTimestamp)
  })

  io.bypassHit  := hits.reduce(_ || _)
  io.bypassData := Mux1H(finalHits, buffer.map(_.req.wdata))

  // 调试信息（可选）
  // when(io.bypassEnable && io.bypassHit) {
  //   printf(p"[WriteBuffer] Bypass hit: addr=0x${Hexadecimal(io.bypassAddr)}, " +
  //          p"newest_timestamp=${newestTimestamp}, data=0x${Hexadecimal(io.bypassData)}\n")
  // }
}
