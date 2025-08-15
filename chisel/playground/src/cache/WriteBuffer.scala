package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class WriteBufferEntry extends Bundle {
  val req = new DCacheReq
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

  val buffer = RegInit(VecInit(Seq.fill(depth)(0.U.asTypeOf(new WriteBufferEntry))))
  val valids = RegInit(VecInit(Seq.fill(depth)(false.B)))

  // 写合并逻辑：检查是否有相同地址的valid entry
  val addrMatches = VecInit(
    (0 until depth).map(i =>
      valids(i) && buffer(i).req.write &&
        (buffer(i).req.addr === io.enq.bits.addr)
    )
  )

  val hasMatch = addrMatches.reduce(_ || _)
  val matchIdx = PriorityEncoder(addrMatches)

  // 队列管理
  val validVecUInt = VecInit(valids.map(_.asBool))
  val inverted     = validVecUInt.map(x => ~x)
  val enqIdx       = PriorityEncoder(inverted)
  val deqIdx       = PriorityEncoder(validVecUInt)

  val hasSpace = valids.count(_ === true.B) < depth.U

  // 入队条件：要么有匹配可以合并，要么有空间分配新entry
  io.enq.ready := hasMatch || hasSpace

  io.deq.valid := valids.reduce(_ || _)
  io.deq.bits  := buffer(deqIdx).req

  // 入队逻辑：写合并 or 新分配
  when(io.enq.fire && io.enq.bits.write) {
    when(hasMatch) {
      // 写合并：更新现有entry的数据和掩码
      buffer(matchIdx).req.wdata := io.enq.bits.wdata
      buffer(matchIdx).req.wmask := io.enq.bits.wmask
      // 保持地址和其他字段不变
    }.otherwise {
      // 新分配：使用空闲slot
      buffer(enqIdx).req := io.enq.bits
      valids(enqIdx)     := true.B
    }
  }

  // 对于非写请求，直接分配新entry（如果有空间）
  when(io.enq.fire && !io.enq.bits.write) {
    buffer(enqIdx).req := io.enq.bits
    valids(enqIdx)     := true.B
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
  }

  // 简化的Bypass逻辑：由于有写合并，每个地址最多只有一个entry
  val bypassMatches = VecInit(
    (0 until depth).map(i =>
      valids(i) && io.bypassEnable &&
        buffer(i).req.write &&
        (buffer(i).req.addr === io.bypassAddr)
    )
  )

  io.bypassHit  := bypassMatches.reduce(_ || _)
  io.bypassData := Mux1H(bypassMatches, buffer.map(_.req.wdata))

  // 调试信息
  when(io.enq.fire && hasMatch) {
    printf(
      p"[WriteBuffer] Write coalescing: addr=0x${Hexadecimal(io.enq.bits.addr)}, " +
        p"old_data=0x${Hexadecimal(buffer(matchIdx).req.wdata)}, " +
        p"new_data=0x${Hexadecimal(io.enq.bits.wdata)}\n"
    )
  }
}
