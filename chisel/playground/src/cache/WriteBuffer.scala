package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

class WriteBufferEntry extends Bundle {
  val req = new DCacheReq
  val age = UInt(log2Ceil(16).W) // 用于跟踪写入顺序，假设最多16个pending操作
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

    // 用于跟踪已发送但未完成的store操作
    val dcacheResp = Flipped(Valid(new Bundle {
      val addr    = UInt(XLEN.W)
      val success = Bool()
    }))
  })

  val buffer = Reg(Vec(depth, new WriteBufferEntry))
  val valids = RegInit(VecInit(Seq.fill(depth)(false.B)))

  // 用于跟踪已发送但未完成的store操作
  val inFlightBuffer = Reg(Vec(depth, new WriteBufferEntry))
  val inFlightValids = RegInit(VecInit(Seq.fill(depth)(false.B)))

  // 全局age计数器，用于跟踪操作的顺序
  val globalAge = RegInit(0.U(log2Ceil(16).W))

  val validVecUInt = VecInit(valids.map(_.asBool))
  val inverted     = validVecUInt.map(x => ~x)
  val enqIdx       = PriorityEncoder(inverted)
  val deqIdx       = PriorityEncoder(validVecUInt)

  // In-flight buffer管理
  val inFlightValidVecUInt = VecInit(inFlightValids.map(_.asBool))
  val inFlightInverted     = inFlightValidVecUInt.map(x => ~x)
  val inFlightEnqIdx       = PriorityEncoder(inFlightInverted)

  io.enq.ready := valids.count(_ === true.B) < depth.U
  io.deq.valid := valids.reduce(_ || _)
  io.deq.bits  := buffer(deqIdx).req

  when(io.enq.fire) {
    buffer(enqIdx).req := io.enq.bits
    buffer(enqIdx).age := globalAge
    valids(enqIdx)     := true.B
    globalAge          := globalAge + 1.U
  }

  when(io.deq.fire) {
    // 当store被发送到DCache时，将其移动到in-flight buffer
    when(inFlightValids.count(_ === true.B) < depth.U) {
      inFlightBuffer(inFlightEnqIdx) := buffer(deqIdx)
      inFlightValids(inFlightEnqIdx) := true.B
    }
    valids(deqIdx) := false.B
  }

  // 处理DCache响应，从in-flight buffer中移除已完成的操作
  when(io.dcacheResp.valid && io.dcacheResp.bits.success) {
    for (i <- 0 until depth) {
      when(inFlightValids(i) && inFlightBuffer(i).req.addr === io.dcacheResp.bits.addr) {
        inFlightValids(i) := false.B
      }
    }
  }

  when(io.flush) {
    for (i <- 0 until depth) {
      valids(i)         := false.B
      inFlightValids(i) := false.B
    }
  }

  // 增强的bypass逻辑：考虑buffer中的和in-flight的store操作
  // 1. 检查buffer中的匹配
  val bufferHits = VecInit(buffer.zip(valids).map { case (entry, v) =>
    v && io.bypassEnable && entry.req.write && (entry.req.addr === io.bypassAddr)
  })

  // 2. 检查in-flight buffer中的匹配
  val inFlightHits = VecInit(inFlightBuffer.zip(inFlightValids).map { case (entry, v) =>
    v && io.bypassEnable && entry.req.write && (entry.req.addr === io.bypassAddr)
  })

  // 3. 找到最新的匹配项（具有最大age值）
  val allEntries = buffer ++ inFlightBuffer
  val allValids  = valids ++ inFlightValids
  val allHits    = bufferHits ++ inFlightHits

  // 计算每个匹配项的age，未匹配的设为0
  val ages = VecInit(allEntries.zip(allHits).map { case (entry, hit) =>
    Mux(hit, entry.age, 0.U)
  })

  // 找到最大age值
  val maxAge = ages.reduce((a, b) => Mux(a > b, a, b))

  // 确定哪个entry具有最大age
  val newestHits = VecInit(ages.zip(allHits).map { case (age, hit) =>
    hit && (age === maxAge)
  })

  io.bypassHit  := allHits.reduce(_ || _)
  io.bypassData := Mux1H(newestHits, allEntries.map(_.req.wdata))
}
