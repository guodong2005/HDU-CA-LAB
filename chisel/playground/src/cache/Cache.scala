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
class ICache extends Module {
  val io = IO(new ICacheIO)

  val sIDLE :: sCHECK_HIT :: sWAIT_RESP :: Nil = Enum(3)
  val state                                    = RegInit(sIDLE)

  val saved_req   = RegInit(0.U.asTypeOf(new DecoupledICacheReq))
  val cache_valid = RegInit(VecInit(Seq.fill(ICACHE_DEPTH)(false.B)))
  val cache_tag   = SyncReadMem(ICACHE_DEPTH, UInt(ICACHE_TAG_WIDTH.W))
  val cache_data  = Seq.fill(FETCH_WIDTH)(SyncReadMem(ICACHE_DEPTH, UInt(32.W)))

  // ========== 优化1：请求路径寄存器切割 ==========
  // 将输入请求先打一拍，避免组合逻辑直接连到SRAM
  val req_valid_reg = RegNext(io.icache_req.valid && io.icache_req.ready, false.B)
  val req_addr_reg  = RegEnable(io.icache_req.bits.addr, 0.U, io.icache_req.valid && io.icache_req.ready)

  // 使用寄存器后的请求或saved_req
  val current_req_valid = saved_req.valid || req_valid_reg
  val current_req_addr  = Mux(saved_req.valid, saved_req.bits.addr, req_addr_reg)

  // ========== 优化2：地址解码提前一拍 ==========
  // 提前计算下一个周期可能需要的地址解码
  val next_addr = Mux(io.icache_req.valid && io.icache_req.ready, io.icache_req.bits.addr, current_req_addr)

  val next_index = next_addr(ICACHE_OFFSET_WIDTH + ICACHE_INDEX_WIDTH - 1, ICACHE_OFFSET_WIDTH)
  val next_tag   = next_addr(31, 32 - ICACHE_TAG_WIDTH)

  // 当前周期使用的地址（已经寄存过）
  val index         = RegNext(next_index)
  val tag           = RegNext(next_tag)
  val addr_for_resp = RegNext(next_addr)

  // ========== 优化3：SRAM读取优化 ==========
  // SRAM读取使用next_index，这样数据在下个周期就准备好了
  val cache_read_tag      = cache_tag.read(next_index)
  val cache_read_data_raw = VecInit(cache_data.map(_.read(next_index)))

  // 将SRAM输出再打一拍，与地址对齐
  val cache_read_tag_reg = RegNext(cache_read_tag)
  val cache_read_data    = RegNext(cache_read_data_raw)

  // ========== 优化4：命中判断寄存器化 ==========
  val tag_match   = cache_read_tag_reg === tag
  val valid_match = RegNext(cache_valid(next_index))
  val addr_stable = RegNext(current_req_valid)

  val hit_cache = tag_match && valid_match && addr_stable

  // 外部读取相关
  val read_data = io.io_read_resp.bits.data.asTypeOf(Vec(FETCH_WIDTH, UInt(32.W)))

  // Cache写使能
  val cache_we         = WireInit(false.B)
  val cache_valid_we   = WireInit(false.B)
  val cache_write_tag  = tag
  val cache_write_data = read_data

  // ========== 优化5：响应路径优化 ==========
  // 提前准备好响应数据
  val resp_valid_next = Wire(Bool())
  val resp_data_next  = Wire(UInt((FETCH_WIDTH * 32).W))

  resp_valid_next := false.B
  resp_data_next  := DontCare

  // 响应寄存器
  val resp_valid_reg = RegNext(resp_valid_next, false.B)
  val resp_data_reg  = RegNext(resp_data_next)
  val resp_addr_reg  = RegNext(addr_for_resp)

  // Default assignments
  io.icache_req.ready      := state === sIDLE && !saved_req.valid && !req_valid_reg
  io.icache_resp.valid     := resp_valid_reg
  io.icache_resp.bits.data := resp_data_reg
  io.icache_resp.bits.addr := resp_addr_reg

  io.io_read_req.valid     := false.B
  io.io_read_req.bits.addr := Cat(current_req_addr(31, ICACHE_OFFSET_WIDTH), 0.U(ICACHE_OFFSET_WIDTH.W))
  io.io_read_resp.ready    := true.B

  // ========== 请求保存逻辑 ==========
  when(req_valid_reg && !saved_req.valid && state =/= sIDLE) {
    saved_req.valid     := true.B
    saved_req.bits.addr := req_addr_reg
  }

  when(resp_valid_reg) {
    saved_req.valid := false.B
    saved_req.bits  := 0.U.asTypeOf(new ICacheReq())
  }

  // ========== 状态机（优化后） ==========
  switch(state) {
    is(sIDLE) {
      when(current_req_valid) {
        state := sCHECK_HIT
      }
    }

    is(sCHECK_HIT) {
      when(hit_cache) {
        resp_valid_next := true.B
        resp_data_next  := cache_read_data.asUInt
        state           := sIDLE
      }.otherwise {
        io.io_read_req.valid := true.B
        when(io.io_read_req.ready) {
          state := sWAIT_RESP
        }
      }
    }

    is(sWAIT_RESP) {
      when(io.io_read_resp.valid) {
        resp_valid_next := true.B
        resp_data_next  := read_data.asUInt
        cache_we        := true.B
        cache_valid_we  := true.B
        state           := sIDLE
      }
    }
  }

  // ========== Cache写入（使用原地址） ==========
  when(cache_we) {
    val write_index = current_req_addr(ICACHE_OFFSET_WIDTH + ICACHE_INDEX_WIDTH - 1, ICACHE_OFFSET_WIDTH)
    cache_tag.write(write_index, cache_write_tag)
    cache_data.zip(cache_write_data).foreach { case (mem, data) =>
      mem.write(write_index, data)
    }
  }

  when(cache_valid_we) {
    val write_index = current_req_addr(ICACHE_OFFSET_WIDTH + ICACHE_INDEX_WIDTH - 1, ICACHE_OFFSET_WIDTH)
    cache_valid(write_index) := true.B
  }

  // Debug
  dontTouch(io.icache_debug)
  io.icache_debug.state          := state === sWAIT_RESP
  io.icache_debug.hit_cache      := hit_cache
  io.icache_debug.cache_we       := cache_we
  io.icache_debug.cache_read_tag := cache_read_tag_reg
  io.icache_debug.icache_req     := saved_req
}
// class ICache extends Module {
//   val io = IO(new ICacheIO)

//   val sIDLE :: sCHECK_HIT :: sWAIT_RESP :: Nil = Enum(3)
//   val state                                    = RegInit(sIDLE)

//   val saved_req   = RegInit(0.U.asTypeOf(new DecoupledICacheReq))
//   val cache_valid = RegInit(VecInit(Seq.fill(ICACHE_DEPTH)(false.B)))
//   val cache_tag   = SyncReadMem(ICACHE_DEPTH, UInt(ICACHE_TAG_WIDTH.W))
//   val cache_data  = Seq.fill(FETCH_WIDTH)(SyncReadMem(ICACHE_DEPTH, UInt(32.W)))

//   val current_req_valid = Mux(saved_req.valid, saved_req.valid, io.icache_req.valid)
//   val current_req_bits  = Mux(saved_req.valid, saved_req.bits, io.icache_req.bits)

//   val index = current_req_bits.addr(ICACHE_OFFSET_WIDTH + ICACHE_INDEX_WIDTH - 1, ICACHE_OFFSET_WIDTH)
//   val tag   = current_req_bits.addr(31, 32 - ICACHE_TAG_WIDTH)

//   val read_data       = io.io_read_resp.bits.data.asTypeOf(Vec(FETCH_WIDTH, UInt(32.W)))
//   val cache_read_tag  = cache_tag.read(index)
//   val cache_read_data = VecInit(cache_data.map(_.read(index)))

//   val hit_cache = cache_read_tag === tag && cache_valid(index) &&
//     RegNext(current_req_bits.addr) === current_req_bits.addr

//   val cache_we         = WireInit(false.B)
//   val cache_valid_we   = WireInit(false.B)
//   val cache_write_tag  = tag
//   val cache_write_data = read_data

//   // Default assignments
//   io.icache_req.ready      := (state === sIDLE && !saved_req.valid)
//   io.icache_resp.valid     := false.B
//   io.icache_resp.bits.data := DontCare
//   io.icache_resp.bits.addr := current_req_bits.addr

//   io.io_read_req.valid     := false.B
//   io.io_read_req.bits.addr := Cat(current_req_bits.addr(31, ICACHE_OFFSET_WIDTH), 0.U(ICACHE_OFFSET_WIDTH.W))
//   io.io_read_resp.ready    := true.B

//   // Request register control
//   when(io.icache_req.valid && !saved_req.valid) {
//     saved_req.valid := true.B
//     saved_req.bits  := io.icache_req.bits
//   }

//   when(io.icache_resp.valid) {
//     saved_req.valid := false.B
//     saved_req.bits  := 0.U.asTypeOf(new ICacheReq())
//   }

//   when(saved_req.valid) {
//     io.icache_req.ready := false.B
//   }

//   // State machine
//   switch(state) {
//     is(sIDLE) {
//       when(current_req_valid) {
//         state := sCHECK_HIT
//       }
//     }

//     is(sCHECK_HIT) {
//       when(hit_cache) {
//         io.icache_resp.valid     := true.B
//         io.icache_resp.bits.data := cache_read_data.asUInt
//         state                    := sIDLE
//       }.otherwise {
//         io.io_read_req.valid := true.B
//         when(io.io_read_req.ready) {
//           state := sWAIT_RESP
//         }
//       }
//     }

//     is(sWAIT_RESP) {
//       when(io.io_read_resp.valid) {
//         io.icache_resp.valid     := true.B
//         io.icache_resp.bits.data := read_data.asUInt
//         io.icache_resp.bits.addr := current_req_bits.addr

//         cache_we       := true.B
//         cache_valid_we := true.B
//         state          := sIDLE
//       }
//     }
//   }

//   when(cache_we) {
//     cache_tag.write(index, cache_write_tag)
//     cache_data.zip(cache_write_data).foreach { case (mem, data) => mem.write(index, data) }
//   }

//   when(cache_valid_we) {
//     cache_valid(index) := true.B
//   }

//   // Debug
//   dontTouch(io.icache_debug)
//   io.icache_debug.state          := state === sWAIT_RESP
//   io.icache_debug.hit_cache      := hit_cache
//   io.icache_debug.cache_we       := cache_we
//   io.icache_debug.cache_read_tag := cache_read_tag
//   io.icache_debug.icache_req     := saved_req
// }

// // ============================================================================
// // DCache Module (Simplified)
// // ============================================================================

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
