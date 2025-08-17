package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

import chisel3._
import chisel3.util._

// ============================================================================
// Bundle Definitions
// ============================================================================

class ICacheReq extends Bundle {
  val addr = UInt(32.W)
}

class ICacheResp extends Bundle {
  val data = UInt((FETCH_WIDTH * 32).W)
}

class InstPacket extends Bundle {
  val data = UInt((FETCH_WIDTH * 32).W)
  val addr = UInt(32.W)
}

class DCacheReq extends Bundle {
  val addr  = UInt(32.W)
  val write = Bool()
  val wdata = UInt(32.W)
  val wstrb = UInt(4.W)
  val size  = UInt(3.W)
}

class DCacheReadReq extends Bundle {
  val addr = UInt(32.W)
}

class DCacheWriteReq extends Bundle {
  val addr      = UInt(32.W)
  val data      = UInt(32.W)
  val byte_mask = UInt(4.W)
}

class DCacheResp extends Bundle {
  val data = UInt(32.W)
}

// ============================================================================
// ICache Module (Simplified)
// ============================================================================

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
class ICacheNonBlocking extends Module {
  val io = IO(new ICacheIO)

  // State machine states
  val sIDLE :: sCHECK_HIT :: sWAIT_RESP :: Nil = Enum(3)
  val state                                    = RegInit(sIDLE)

  // Request pipeline registers
  val stage1_req = RegInit(0.U.asTypeOf(Valid(new ICacheReq))) // First stage request
  val stage2_req = RegInit(0.U.asTypeOf(Valid(new ICacheReq))) // Request being checked for hit

  // Cache storage
  val cache_valid = RegInit(VecInit(Seq.fill(ICACHE_DEPTH)(false.B)))
  val cache_tag   = SyncReadMem(ICACHE_DEPTH, UInt(ICACHE_TAG_WIDTH.W))
  val cache_data  = Seq.fill(FETCH_WIDTH)(SyncReadMem(ICACHE_DEPTH, UInt(32.W)))

  // Helper functions to extract fields from address
  def getIndex(addr: UInt): UInt =
    addr(ICACHE_OFFSET_WIDTH + ICACHE_INDEX_WIDTH - 1, ICACHE_OFFSET_WIDTH)

  def getTag(addr: UInt): UInt =
    addr(31, 32 - ICACHE_TAG_WIDTH)

  def getBlockAddr(addr: UInt): UInt =
    Cat(addr(31, ICACHE_OFFSET_WIDTH), 0.U(ICACHE_OFFSET_WIDTH.W))

  // Determine which address to read from memory
  val read_addr = Wire(UInt(32.W))
  read_addr := Mux(
    io.icache_req.valid && io.icache_req.ready && !stage1_req.valid,
    io.icache_req.bits.addr,
    Mux(stage1_req.valid, stage1_req.bits.addr, stage2_req.bits.addr)
  )

  val read_index = getIndex(read_addr)

  // Memory read ports - reading one cycle ahead
  val cache_read_tag  = cache_tag.read(read_index)
  val cache_read_data = VecInit(cache_data.map(_.read(read_index)))

  // Registers to hold read values for hit detection
  val reg_tag   = RegNext(cache_read_tag)
  val reg_data  = RegNext(cache_read_data)
  val reg_index = RegNext(read_index)

  // Hit detection logic for stage2
  val hit_valid       = stage2_req.valid && state === sCHECK_HIT
  val hit_tag_match   = getTag(stage2_req.bits.addr) === reg_tag
  val hit_cache_valid = cache_valid(getIndex(stage2_req.bits.addr))
  val hit_cache       = hit_valid && hit_tag_match && hit_cache_valid

  // Memory response data processing
  val mem_resp_data = io.io_read_resp.bits.data.asTypeOf(Vec(FETCH_WIDTH, UInt(32.W)))

  // Cache write control
  val cache_we          = WireInit(false.B)
  val cache_write_index = getIndex(stage2_req.bits.addr)
  val cache_write_tag   = getTag(stage2_req.bits.addr)
  val cache_write_data  = mem_resp_data

  // Track if we're waiting for memory response
  val mem_req_sent = RegInit(false.B)

  // ============================================================================
  // Output Interface Logic
  // ============================================================================

  // ICache request interface - always ready to accept
  io.icache_req.ready := true.B

  // ICache response interface
  io.icache_resp.valid     := false.B
  io.icache_resp.bits.addr := DontCare
  io.icache_resp.bits.data := DontCare

  // Memory request interface
  io.io_read_req.valid     := false.B
  io.io_read_req.bits.addr := getBlockAddr(stage2_req.bits.addr)

  // Memory response interface - ready when waiting for response
  io.io_read_resp.ready := state === sWAIT_RESP

  // ============================================================================
  // Pipeline Stage Management
  // ============================================================================

  // Accept new request into stage1
  val accept_new_req = io.icache_req.valid && io.icache_req.ready
  val stage1_to_stage2 = stage1_req.valid && (!stage2_req.valid ||
    (stage2_req.valid && (hit_cache ||
      (state === sWAIT_RESP && io.io_read_resp.valid && io.io_read_resp.ready))))
  val stage2_complete = stage2_req.valid && (hit_cache ||
    (state === sWAIT_RESP && io.io_read_resp.valid && io.io_read_resp.ready))

  // Stage 1 register update
  when(accept_new_req && !stage1_req.valid) {
    stage1_req.valid := true.B
    stage1_req.bits  := io.icache_req.bits
  }.elsewhen(stage1_to_stage2) {
    when(accept_new_req) {
      stage1_req.bits  := io.icache_req.bits
      stage1_req.valid := true.B
    }.otherwise {
      stage1_req.valid := false.B
    }
  }

  // Stage 2 register update
  when(stage1_to_stage2) {
    stage2_req := stage1_req
  }.elsewhen(stage2_complete) {
    stage2_req.valid := false.B
  }

  // ============================================================================
  // State Machine
  // ============================================================================

  switch(state) {
    is(sIDLE) {
      when(stage2_req.valid) {
        state := sCHECK_HIT
      }
    }

    is(sCHECK_HIT) {
      when(hit_cache) {
        // Cache hit - send response
        io.icache_resp.valid     := true.B
        io.icache_resp.bits.addr := stage2_req.bits.addr
        io.icache_resp.bits.data := reg_data.asUInt

        // Move to next request or idle
        when(stage1_req.valid) {
          state := sCHECK_HIT // Continue checking
        }.otherwise {
          state := sIDLE
        }
      }.elsewhen(stage2_req.valid) {
        // Cache miss - request from memory
        io.io_read_req.valid := true.B
        when(io.io_read_req.ready) {
          mem_req_sent := true.B
          state        := sWAIT_RESP
        }
      }.otherwise {
        // No valid request in stage2
        state := sIDLE
      }
    }

    is(sWAIT_RESP) {
      // Wait for memory response
      io.io_read_resp.ready := true.B

      when(io.io_read_resp.valid && io.io_read_resp.ready) {
        // Memory response received
        io.icache_resp.valid     := true.B
        io.icache_resp.bits.addr := stage2_req.bits.addr
        io.icache_resp.bits.data := io.io_read_resp.bits.data

        // Update cache
        cache_we     := true.B
        mem_req_sent := false.B

        // Move to next request or idle
        when(stage1_req.valid) {
          state := sCHECK_HIT
        }.otherwise {
          state := sIDLE
        }
      }
    }
  }

  // ============================================================================
  // Cache Write Logic
  // ============================================================================

  when(cache_we) {
    cache_tag.write(cache_write_index, cache_write_tag)
    cache_data.zipWithIndex.foreach {
      case (mem, i) =>
        mem.write(cache_write_index, cache_write_data(i))
    }
    cache_valid(cache_write_index) := true.B
  }

  // ============================================================================
  // Debug Interface
  // ============================================================================

  io.icache_debug.state            := state
  io.icache_debug.hit_cache        := hit_cache
  io.icache_debug.cache_we         := cache_we
  io.icache_debug.cache_read_tag   := reg_tag
  io.icache_debug.icache_req       := 0.U.asTypeOf(new DecoupledICacheReq)
  io.icache_debug.icache_req.valid := stage2_req.valid
  io.icache_debug.icache_req.bits  := stage2_req.bits
}

// ============================================================================
// DCache Module (Simplified)
// ============================================================================

class DCacheIO extends Bundle {
  // CPU-side interface
  val req  = Flipped(Decoupled(new DCacheReq))
  val resp = Decoupled(new DCacheResp)

  // IoControl interface
  val io_read_req  = Decoupled(new DCacheReadReq)
  val io_read_resp = Flipped(Decoupled(new DCacheResp))
  val io_write_req = Decoupled(new DCacheWriteReq)
}

class DCache extends Module {
  val io = IO(new DCacheIO)

  // State definitions
  val sIDLE :: sWAIT_READ_RESP :: sWAIT_WRITE_RESP :: Nil = Enum(3)
  val state                                               = RegInit(sIDLE)

  // Saved request register - 分开存储bits和valid
  val saved_req_valid = RegInit(false.B)
  val saved_req_bits  = Reg(new DCacheReq)

  // Current request selection
  val current_req_valid = Mux(saved_req_valid, saved_req_valid, io.req.valid)
  val current_req_bits  = Mux(saved_req_valid, saved_req_bits, io.req.bits)

  // Default assignments
  io.req.ready      := (state === sIDLE && !saved_req_valid)
  io.resp.valid     := false.B
  io.resp.bits.data := 0.U

  // IO read interface
  io.io_read_req.valid     := false.B
  io.io_read_req.bits.addr := current_req_bits.addr
  io.io_read_resp.ready    := true.B

  // IO write interface
  io.io_write_req.valid          := false.B
  io.io_write_req.bits.addr      := current_req_bits.addr
  io.io_write_req.bits.data      := current_req_bits.wdata
  io.io_write_req.bits.byte_mask := current_req_bits.wstrb

  // Request register control - 分开管理bits和valid
  when(io.req.valid && io.req.ready && !saved_req_valid) {
    saved_req_valid := true.B
    saved_req_bits  := io.req.bits
  }

  when(io.resp.valid && io.resp.ready) {
    saved_req_valid := false.B
    saved_req_bits  := 0.U.asTypeOf(new DCacheReq())
  }

  // State machine
  switch(state) {
    is(sIDLE) {
      when(current_req_valid) {
        when(current_req_bits.write) {
          // Write request
          io.io_write_req.valid := true.B
          when(io.io_write_req.ready) {
            state := sWAIT_WRITE_RESP
          }
        }.otherwise {
          // Read request
          io.io_read_req.valid := true.B
          when(io.io_read_req.ready) {
            state := sWAIT_READ_RESP
          }
        }
      }
    }

    is(sWAIT_READ_RESP) {
      when(io.io_read_resp.valid) {
        io.resp.valid     := true.B
        io.resp.bits.data := io.io_read_resp.bits.data
        when(io.resp.ready) {
          state := sIDLE
        }
      }
    }

    is(sWAIT_WRITE_RESP) {
      // For write, we can immediately respond or wait for write completion
      // Here we immediately respond for simplicity
      io.resp.valid     := true.B
      io.resp.bits.data := 0.U // Write response doesn't need data
      when(io.resp.ready) {
        state := sIDLE
      }
    }
  }
}
