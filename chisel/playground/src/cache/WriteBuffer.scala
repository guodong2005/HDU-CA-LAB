package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class WriteBufferEntry extends Bundle {
  val req = new DCacheReq
}

class WriteBuffer(depth: Int = 8) extends Module {
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

  // ============= 添加 isExtAddr 函数 =============
  def isExtAddr(addr: UInt): Bool = addr(31, 22) === "h201".U(10.W) // 0x80400000>>22 = 0x201
  // ================================================

  // ============= 修复：写合并逻辑需要检查valid =============
  val addrMatches = VecInit(
    (0 until depth).map(i =>
      valids(i) && // 必须检查entry是否valid
        buffer(i).req.write &&
        (buffer(i).req.addr === io.enq.bits.addr)
    )
  )
  val hasMatch = addrMatches.reduce(_ || _)
  val matchIdx = PriorityEncoder(addrMatches)
  // ========================================================

  // 队列管理
  val validVecUInt = VecInit(valids.map(_.asBool))
  val inverted     = validVecUInt.map(x => ~x)
  val enqIdx       = PriorityEncoder(inverted)
  val deqIdx       = PriorityEncoder(validVecUInt)
  val hasSpace     = valids.count(_ === true.B) < depth.U

  // 入队条件：要么有匹配可以合并，要么有空间分配新entry
  io.enq.ready := hasMatch || hasSpace
  io.deq.valid := valids.reduce(_ || _)
  io.deq.bits  := buffer(deqIdx).req

  // ============= 修复：入队逻辑 =============
  when(io.enq.fire && io.enq.bits.write) {
    when(hasMatch) {
      // 写合并：更新现有entry的数据和掩码
      buffer(matchIdx).req.wdata := io.enq.bits.wdata
      buffer(matchIdx).req.wstrb := io.enq.bits.wstrb | buffer(matchIdx).req.wstrb // 合并掩码
      // 修复：matchIdx对应的entry已经是valid的，不需要再设置
      // valids(enqIdx) := true.B  // ❌ 错误！
      // 或者明确写出：valids(matchIdx) := true.B（虽然已经是true了）
    }.otherwise {
      // 新分配：使用空闲slot
      buffer(enqIdx).req := io.enq.bits
      valids(enqIdx)     := true.B
    }
  }
  // =======================================

  // 出队逻辑
  when(io.deq.fire) {
    valids(deqIdx) := false.B
  }

  // ============= 修复：Bypass逻辑也需要检查valid =============
  val bypassMatches = VecInit(
    (0 until depth).map(i =>
      io.bypassEnable &&
        valids(i) && // 必须检查entry是否valid
        buffer(i).req.write &&
        (buffer(i).req.addr === io.bypassAddr) &&
        isExtAddr(buffer(i).req.addr) // 只有满足isExtAddr才进行前递
    )
  )
  io.bypassHit  := bypassMatches.reduce(_ || _)
  io.bypassData := Mux1H(bypassMatches, buffer.map(_.req.wdata))
  // ===========================================================

  // Flush逻辑
  when(io.flush) {
    valids.foreach(_ := false.B)
  }

  // 调试信息
  when(io.enq.fire && hasMatch) {
    printf(
      p"[WriteBuffer] Write coalescing: addr=0x${Hexadecimal(io.enq.bits.addr)}, " +
        p"old_data=0x${Hexadecimal(buffer(matchIdx).req.wdata)}, " +
        p"new_data=0x${Hexadecimal(io.enq.bits.wdata)}\n"
    )
  }

  when(io.bypassHit) {
    printf(
      p"[WriteBuffer] Bypass hit: addr=0x${Hexadecimal(io.bypassAddr)}, " +
        p"data=0x${Hexadecimal(io.bypassData)}\n"
    )
  }

  // 调试信号
  dontTouch(valids)
  dontTouch(hasMatch)
  dontTouch(hasSpace)
}
