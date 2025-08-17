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

  // 简化状态机：只需要 IDLE 和 WAIT_RESP
  val sIDLE :: sWAIT_RESP :: Nil = Enum(2)
  val state                      = RegInit(sIDLE)

  // 用寄存器实现 cache 存储（替代 SyncReadMem）
  val cache_valid   = RegInit(VecInit(Seq.fill(ICACHE_DEPTH)(false.B)))
  val cache_tag_reg = RegInit(VecInit(Seq.fill(ICACHE_DEPTH)(0.U(ICACHE_TAG_WIDTH.W))))
  val cache_data_reg = RegInit(
    VecInit(
      Seq.fill(ICACHE_DEPTH)(
        VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W)))
      )
    )
  )

  // 当前请求的地址解析
  val req_index = io.icache_req.bits.addr(ICACHE_OFFSET_WIDTH + ICACHE_INDEX_WIDTH - 1, ICACHE_OFFSET_WIDTH)
  val req_tag   = io.icache_req.bits.addr(31, 32 - ICACHE_TAG_WIDTH)

  // 组合逻辑实现单周期 hit 检测
  val hit_tag_match = cache_tag_reg(req_index) === req_tag
  val hit_valid     = cache_valid(req_index)
  val hit_cache     = hit_tag_match && hit_valid && io.icache_req.valid

  // 等待响应时的请求信息保存
  val waiting_req   = RegInit(0.U.asTypeOf(new ICacheReq()))
  val waiting_index = waiting_req.addr(ICACHE_OFFSET_WIDTH + ICACHE_INDEX_WIDTH - 1, ICACHE_OFFSET_WIDTH)
  val waiting_tag   = waiting_req.addr(31, 32 - ICACHE_TAG_WIDTH)

  // 默认输出
  io.icache_req.ready      := state === sIDLE
  io.icache_resp.valid     := false.B
  io.icache_resp.bits.data := DontCare
  io.icache_resp.bits.addr := DontCare
  io.io_read_req.valid     := false.B
  io.io_read_req.bits.addr := DontCare
  io.io_read_resp.ready    := true.B

  // 主状态机
  switch(state) {
    is(sIDLE) {
      when(io.icache_req.valid) {
        when(hit_cache) {
          // 单周期 cache hit
          io.icache_resp.valid     := true.B
          io.icache_resp.bits.data := cache_data_reg(req_index).asUInt
          io.icache_resp.bits.addr := io.icache_req.bits.addr
          // 保持在 sIDLE 状态，可以连续处理请求
        }.otherwise {
          // Cache miss：发起内存读取
          io.io_read_req.valid     := true.B
          io.io_read_req.bits.addr := Cat(io.icache_req.bits.addr(31, ICACHE_OFFSET_WIDTH), 0.U(ICACHE_OFFSET_WIDTH.W))

          when(io.io_read_req.ready) {
            // 保存当前请求信息
            waiting_req := io.icache_req.bits
            state       := sWAIT_RESP
          }
        }
      }
    }

    is(sWAIT_RESP) {
      when(io.io_read_resp.valid) {
        // 接收到内存响应
        val read_data = io.io_read_resp.bits.data.asTypeOf(Vec(FETCH_WIDTH, UInt(32.W)))

        // 响应给 CPU
        io.icache_resp.valid     := true.B
        io.icache_resp.bits.data := io.io_read_resp.bits.data
        io.icache_resp.bits.addr := waiting_req.addr

        // 更新 cache（寄存器写入，同步生效）
        cache_tag_reg(waiting_index)  := waiting_tag
        cache_data_reg(waiting_index) := read_data
        cache_valid(waiting_index)    := true.B

        // 返回 IDLE 状态
        state := sIDLE
      }
    }
  }

  // Debug 信号
  dontTouch(io.icache_debug)
  io.icache_debug.state          := state === sWAIT_RESP
  io.icache_debug.hit_cache      := hit_cache
  io.icache_debug.cache_we       := state === sWAIT_RESP && io.io_read_resp.valid
  io.icache_debug.cache_read_tag := cache_tag_reg(req_index)
  io.icache_debug.icache_req     := DontCare
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
