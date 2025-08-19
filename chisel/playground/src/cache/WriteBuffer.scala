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
    val enq   = Flipped(Decoupled(new DCacheReq))
    val deq   = Decoupled(new DCacheReq)
    val flush = Input(Bool())
  })

  // 使用 Chisel 内置的 Queue 模块实现真正的 FIFO
  val queue = Module(new Queue(new DCacheReq, depth))

  // 连接输入输出
  queue.io.enq <> io.enq
  io.deq <> queue.io.deq

  // flush 功能：清空队列
  when(io.flush) {
    queue.reset := true.B
  }
}
