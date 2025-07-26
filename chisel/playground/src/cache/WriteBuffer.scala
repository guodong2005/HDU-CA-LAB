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

  val buffer = Reg(Vec(depth, new WriteBufferEntry))
  val valids = RegInit(VecInit(Seq.fill(depth)(false.B)))

  val validVecUInt = VecInit(valids.map(_.asBool))
  val inverted     = validVecUInt.map(x => ~x)
  val enqIdx       = PriorityEncoder(inverted)
  val deqIdx       = PriorityEncoder(validVecUInt)

  io.enq.ready := valids.count(_ === true.B) < depth.U
  io.deq.valid := valids.reduce(_ || _)
  io.deq.bits  := buffer(deqIdx).req
  io.deq.ready := false.B // 由外部 LSU 控制是否真正发出

  when(io.enq.fire) {
    buffer(enqIdx).req := io.enq.bits
    valids(enqIdx)     := true.B
  }

  when(io.deq.fire) {
    valids(deqIdx) := false.B
  }

  when(io.flush) {
    for (i <- 0 until depth) {
      valids(i) := false.B
    }
  }

  // Bypass logic (仅查找匹配地址，不做合并)
  val hits = VecInit(buffer.zip(valids).map {
    case (entry, v) => v && io.bypassEnable && entry.req.write && (entry.req.addr === io.bypassAddr)
  })

  io.bypassHit  := hits.reduce(_ || _)
  io.bypassData := Mux1H(hits, buffer.map(_.req.wdata))
}
