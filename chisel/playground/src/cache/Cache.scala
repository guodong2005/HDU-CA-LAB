package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

/**
  * ICache module rewritten with an AXI‑protocol style interface for the fetch unit.
  *
  * The fetch interface now follows an AXI‑like handshake:
  *   - fetch_req: { valid (input), addr (input), ready (output) }
  *   - fetch_rsp: { valid (output), data (output), addr (output) }
  *
  * Internally the module implements a simple two‐state FSM: • sIdle: ICache is idle and fetch_req.ready is high. If fetch_req.valid is high then the module drives an AR transaction on the AXI bus. • sWait: ICache awaits the read data from the AXI slave. During this state fetch_req.ready is false.
  *
  * When the AR handshake completes (i.e. the slave asserts axi.ar.ready), the ICache latches the request address and enters sWait. Once the read data arrives (axi.r.valid), the fetch response is produced and the FSM returns to idle.
  */
class InstPacket extends Bundle {
  val data = Vec(FETCH_WIDTH, UInt(XLEN.W))
  val addr = UInt(XLEN.W)
}

class ICacheReq extends Bundle {
  val addr = UInt(32.W)
}
class ICacheResp extends Bundle {
  val data = UInt((FETCH_WIDTH * 32).W)
}
class DecoupledICacheReq extends Bundle {
  val valid = Bool()
  val bits  = new ICacheReq()
}
class ICacheDebugIO extends Bundle {
  val state          = Output(Bool())
  val hit_cache      = Output(Bool())
  val cache_we       = Output(Bool())
  val cache_read_tag = Output(UInt(ICACHE_TAG_WIDTH.W))
  val icache_req     = new DecoupledICacheReq()
}

class ICacheIO extends Bundle {
  val icache_req   = Flipped(Decoupled(new ICacheReq))
  val icache_resp  = Valid(new InstPacket)
  val io_read_req  = Decoupled(new ICacheReq)
  val io_read_resp = Flipped(Decoupled(new ICacheResp))
  val icache_debug = new ICacheDebugIO
}

class ICache extends Module {
  val io = IO(new ICacheIO)

  val sIDLE :: sWAIT_RESP :: Nil = Enum(2)
  val state                      = RegInit(sIDLE)
  val req_valid_hold             = RegInit(false.B)

  val saved_req   = RegInit(0.U.asTypeOf(new DecoupledICacheReq))
  val cache_valid = RegInit(VecInit(Seq.fill(ICACHE_DEPTH)(false.B)))
  val cache_tag   = SyncReadMem(ICACHE_DEPTH, UInt(ICACHE_TAG_WIDTH.W))
  val cache_data  = Seq.fill(FETCH_WIDTH)(SyncReadMem(ICACHE_DEPTH, UInt(32.W)))

  val current_req_valid = saved_req.valid
  val current_req_bits  = saved_req.bits

  val index = current_req_bits.addr(ICACHE_OFFSET_WIDTH + ICACHE_INDEX_WIDTH - 1, ICACHE_OFFSET_WIDTH)
  val tag   = current_req_bits.addr(31, 32 - ICACHE_TAG_WIDTH)

  val read_data       = io.io_read_resp.bits.data.asTypeOf(Vec(FETCH_WIDTH, UInt(32.W)))
  val cache_read_tag  = cache_tag.read(index)
  val cache_read_data = VecInit(cache_data.map(_.read(index)))
  val hit_cache       = cache_read_tag === tag && cache_valid(index) && !io.icache_req.valid

  val cache_we         = WireInit(false.B)
  val cache_valid_we   = WireInit(false.B)
  val cache_write_tag  = tag
  val cache_write_data = read_data

  // 默认信号赋值
  io.icache_req.ready      := (state === sIDLE && !saved_req.valid)
  io.icache_resp.valid     := false.B
  io.icache_resp.bits.data := DontCare
  // 返回的是 raw 的 addr 而不是对齐后的 addr.
  io.icache_resp.bits.addr := current_req_bits.addr

  io.io_read_req.valid     := false.B
  io.io_read_req.bits.addr := Cat(current_req_bits.addr(31, ICACHE_OFFSET_WIDTH), 0.U(ICACHE_OFFSET_WIDTH.W))
  io.io_read_resp.ready    := true.B

  // 🧠 请求寄存器控制逻辑：
  // ✅ 保存请求
  when(io.icache_req.valid) {
    saved_req.valid := true.B
    saved_req.bits  := io.icache_req.bits
  }

  // ✅ 清空请求（ready 代表可以接受新请求）
  when(io.icache_resp.valid) {
    saved_req.valid := false.B
    saved_req.bits  := 0.U.asTypeOf(new ICacheReq())
  }
  when(saved_req.valid) {
    io.icache_req.ready := false.B
  }

  switch(state) {
    is(sIDLE) {
      when(current_req_valid && hit_cache) {
        io.icache_resp.valid     := true.B
        io.icache_resp.bits.data := cache_read_data
      }.elsewhen(current_req_valid && !hit_cache) {
        io.io_read_req.valid := true.B
        when(io.io_read_req.ready) {
          req_valid_hold := true.B
          state          := sWAIT_RESP
        }.otherwise {}
      }
    }

    is(sWAIT_RESP) {
      when(io.io_read_resp.valid) {
        io.icache_resp.valid     := true.B
        io.icache_resp.bits.data := read_data
        io.icache_resp.bits.addr := current_req_bits.addr

        cache_we       := true.B
        cache_valid_we := true.B
        req_valid_hold := false.B
        state          := sIDLE
      }.otherwise {}
    }
  }

  when(cache_we) {
    cache_tag.write(index, cache_write_tag)
    cache_data.zip(cache_write_data).foreach { case (mem, data) => mem.write(index, data) }
  }

  when(cache_valid_we) {
    cache_valid(index) := true.B
  }

  // 🐞 debug
  dontTouch(io.icache_debug)
  io.icache_debug.state          := state === sWAIT_RESP
  io.icache_debug.hit_cache      := hit_cache
  io.icache_debug.cache_we       := cache_we
  io.icache_debug.cache_read_tag := cache_read_tag
  io.icache_debug.icache_req     := saved_req
}

class DCache extends Module {
  val io = IO(new Bundle {
    // CPU–side interface.
    val req  = Flipped(Decoupled(new DCacheReq))
    val resp = Decoupled(new DCacheResp)

    // AXI interface – acting as master.
    val axi = new AXI()
  })

  io.axi            := DontCare
  io.axi.ar.valid   := false.B
  io.axi.ar.bits.id := 1.U

  io.axi.aw.valid   := false.B
  io.axi.aw.bits.id := 1.U

  io.axi.w.valid   := false.B
  io.axi.w.bits.id := 1.U

  io.axi.r.ready := true.B
  io.axi.b.ready := true.B

  val sIdle :: sReadReq :: sReadWait :: sWrite :: sWriteResp :: Nil = Enum(5)
  val state                                                         = RegInit(sIdle)

  // Latch the incoming CPU request.
  val reqReg    = Reg(new DCacheReq)
  val reqStored = RegInit(false.B)
  when(io.req.valid && !reqStored) {
    reqStored := true.B
    reqReg    := io.req.bits
  }

  val req = Wire(Decoupled(new DCacheReq))

  req.valid := Mux(reqStored, reqStored, io.req.valid)
  req.bits  := Mux(reqStored, reqReg, io.req.bits)
  req.ready := DontCare
  // The CPU request interface is ready when idle.
  io.req.ready := (state === sIdle)

  // Default CPU response assignments.
  io.resp.valid       := false.B
  io.resp.bits.rdata  := 0.U
  io.axi.ar.bits.size := req.bits.size

  // ------------------------------------------------------------
  // Write Sub-FSM (active only in global state sWrite).
  // ------------------------------------------------------------
  // Enumerate the sub-states:
  //   wIdle:      Neither AW nor W handshake has occurred.
  //   wAWDone:    AW handshake has completed; waiting for W handshake.
  //   wWDone:     W handshake has completed; waiting for AW handshake.
  //   wComplete:  Both AW and W handshakes have completed.
  val wIdle :: wAWDone :: wWDone :: wComplete :: Nil = Enum(4)
  val writeSubState                                  = RegInit(wIdle)

  // ------------------------------------------------------------
  // Global FSM Implementation
  // ------------------------------------------------------------
  io.axi.aw.bits.addr := req.bits.addr
  io.axi.aw.bits.size := 2.U
  io.axi.aw.bits.id   := 0.U

  // Set up W channel signals.
  io.axi.w.bits.data  := req.bits.wdata
  io.axi.w.bits.strb  := req.bits.wstrb // For a full 32-bit write.
  io.axi.ar.bits.addr := req.bits.addr

  io.axi.b.ready := false.B // write response may be very fast
  switch(state) {
    is(sIdle) {
      // When a CPU request arrives, latch it.
      when(io.req.valid) {
        when(io.req.bits.write) {
          state         := sWrite // Begin a write transaction.
          writeSubState := wIdle // Initialize the write sub-FSM.
        }.otherwise {
          state := sReadReq // Begin a read transaction.
        }
      }
    }
    is(sReadReq) {
      // Issue the AXI AR transaction (read address).
      io.axi.ar.valid := true.B
      when(io.axi.ar.ready) {
        state := sReadWait
      }
    }
    is(sReadWait) {
      // Wait for the AXI R channel to return the read data.
      when(io.axi.r.valid) {
        io.resp.valid      := true.B
        io.resp.bits.rdata := io.axi.r.bits.data
        when(io.resp.ready) {
          reqStored := false.B
          state     := sIdle
        }
      }
    }
    is(sWrite) {
      // In the write state, a sub-FSM manages the handshakes on both AW and W channels.
      // Set up AW channel signals.

      // Sub-FSM implementation:
      switch(writeSubState) {
        is(wIdle) {
          // In this state, drive valid on both AW and W channels.
          io.axi.aw.valid := true.B
          io.axi.w.valid  := true.B
          when(io.axi.aw.ready && io.axi.w.ready) {
            // Both handshakes succeed in the same cycle.
            writeSubState := wComplete
          }.elsewhen(io.axi.aw.ready && !io.axi.w.ready) {
            // AW handshake occurs first; wait for W handshake.
            writeSubState := wAWDone
          }.elsewhen(!io.axi.aw.ready && io.axi.w.ready) {
            // W handshake occurs first; wait for AW handshake.
            writeSubState := wWDone
          }
        }
        is(wAWDone) {
          // AW handshake is done. Stop driving AW while continuing to drive W.
          io.axi.aw.valid := false.B
          io.axi.w.valid  := true.B
          when(io.axi.w.ready) {
            writeSubState := wComplete
          }
        }
        is(wWDone) {
          // W handshake is done. Stop driving W while continuing to drive AW.
          io.axi.aw.valid := true.B
          io.axi.w.valid  := false.B
          when(io.axi.aw.ready) {
            writeSubState := wComplete
          }
        }
        is(wComplete) {
          // Both handshakes are complete: deassert valid signals.
          io.axi.aw.valid := false.B
          io.axi.w.valid  := false.B
          // Transition the global FSM to wait for the write response (B channel).
          state := sWriteResp
          // Reset sub-FSM for future write transactions.
          writeSubState  := wIdle
          io.axi.b.ready := true.B
        }
      }
    }
    is(sWriteResp) {
      // Wait for the write response on the AXI B channel.
      when(io.axi.b.valid) {
        io.resp.valid      := true.B
        io.resp.bits.rdata := 0.U // For store operations, a dummy data response.
        when(io.resp.ready) {
          reqStored      := false.B
          state          := sIdle
          io.axi.b.ready := false.B // Acknowledge the write response.
        }
      }
    }
  }
}
