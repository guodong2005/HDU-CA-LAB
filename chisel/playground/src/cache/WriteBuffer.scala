package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class WriteBufferEntry extends Bundle {
  val req       = new DCacheReq
  val valid     = Bool() // entry是否有效（未被写出）
  val allocated = Bool() // entry是否被分配（用于bypass查找）
}

class WriteBuffer(depth: Int = 4, historyDepth: Int = 8) extends Module {
  val io = IO(new Bundle {
    val enq   = Flipped(Decoupled(new DCacheReq))
    val deq   = Decoupled(new DCacheReq)
    val flush = Input(Bool())

    // Bypass接口
    val bypassAddr   = Input(UInt(XLEN.W))
    val bypassEnable = Input(Bool())
    val bypassHit    = Output(Bool())
    val bypassData   = Output(UInt(XLEN.W))
  })

  // 主buffer，包含当前有效的和历史的entries
  val buffer = Reg(Vec(depth + historyDepth, new WriteBufferEntry))

  // 初始化
  val initEntry = Wire(new WriteBufferEntry)
  initEntry.req       := DontCare
  initEntry.valid     := false.B
  initEntry.allocated := false.B

  // 有效entries（未被写出的）
  val validEntries = buffer.map(e => e.valid && e.allocated)
  val validCount   = PopCount(validEntries)

  // 查找相同地址的store（只在有效entries中查找）
  val sameAddrHits = VecInit(buffer.zip(validEntries).map { case (entry, valid) =>
    valid && entry.req.write && (entry.req.addr === io.enq.bits.addr)
  })
  val hasSameAddr = sameAddrHits.reduce(_ || _)
  val sameAddrIdx = PriorityEncoder(sameAddrHits)

  // 查找空闲slot（优先使用未分配的slot）
  val freeSlots   = buffer.map(e => !e.allocated)
  val hasFreeSlot = freeSlots.reduce(_ || _)
  val freeSlotIdx = PriorityEncoder(freeSlots)

  // 如果没有完全空闲的slot，使用已经写出但还保留的slot
  val historySlots   = buffer.map(e => e.allocated && !e.valid)
  val hasHistorySlot = historySlots.reduce(_ || _)
  val historySlotIdx = PriorityEncoder(historySlots)

  // 选择要写入的位置
  val enqIdx = Mux(hasSameAddr, sameAddrIdx, Mux(hasFreeSlot, freeSlotIdx, Mux(hasHistorySlot, historySlotIdx, 0.U)))

  // 输入准备信号：如果有相同地址就合并，否则需要有空位
  io.enq.ready := hasSameAddr || (validCount < depth.U)

  // 输出选择（只从有效entries中选择）
  val deqIdx = PriorityEncoder(validEntries)
  io.deq.valid := validEntries.reduce(_ || _)
  io.deq.bits  := buffer(deqIdx).req

  // 写入逻辑
  when(io.enq.fire && io.enq.bits.write) {
    when(hasSameAddr) {
      // 合并：只更新数据和mask
      buffer(sameAddrIdx).req.wdata := io.enq.bits.wdata
      buffer(sameAddrIdx).req.wmask := io.enq.bits.wmask
      buffer(sameAddrIdx).req.size  := io.enq.bits.size
    }.otherwise {
      // 新分配
      buffer(enqIdx).req       := io.enq.bits
      buffer(enqIdx).valid     := true.B
      buffer(enqIdx).allocated := true.B
    }
  }

  // 写出逻辑：标记为invalid但保留allocated状态
  when(io.deq.fire) {
    buffer(deqIdx).valid := false.B
    // allocated保持为true，这样历史数据仍然可以被bypass
  }

  // 刷新逻辑
  when(io.flush) {
    buffer.foreach { entry =>
      entry.valid     := false.B
      entry.allocated := false.B
    }
  }

  // Bypass逻辑：查找所有allocated的entries（包括已经写出的）
  val bypassHits = VecInit(buffer.map { entry =>
    entry.allocated &&
    entry.req.write &&
    io.bypassEnable &&
    (entry.req.addr === io.bypassAddr)
  })

  // 优先选择最新的（最后写入的）entry
  val bypassHitVec = bypassHits.asUInt
  val bypassIdx    = PriorityEncoder(bypassHitVec.asBools.reverse.reverse)

  io.bypassHit  := bypassHits.reduce(_ || _)
  io.bypassData := buffer(bypassIdx).req.wdata

  // 可选：定期清理历史entries以防止资源耗尽
  val cleanupCounter = RegInit(0.U(16.W))
  cleanupCounter := cleanupCounter + 1.U

  when(cleanupCounter === 0.U) {
    // 每65536周期清理一次最老的历史entry
    val oldestHistoryIdx = PriorityEncoder(historySlots)
    when(hasHistorySlot) {
      buffer(oldestHistoryIdx).allocated := false.B
    }
  }
}
