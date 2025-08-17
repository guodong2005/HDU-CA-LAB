package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

class PrefetchUnit extends Module {
  val io = IO(new Bundle {
    // Interface with ICache
    val icache_req  = Decoupled(new ICacheReq)
    val icache_resp = Flipped(Valid(new InstPacket))

    // Interface with FetchUnit
    val fetch_ready = Input(Bool()) // FetchUnit is ready to receive instruction
    val fetch_resp  = Valid(new InstPacket) // Prefetched instruction to FetchUnit

    // Branch control signals (same source as FetchUnit)
    val branch = Input(Bool())
    val target = Input(UInt(XLEN.W))

    // Status signals
    val prefetch_stall = Output(Bool()) // Indicate prefetch is stalled
  })

  // Prefetch PC register - always ahead of fetch PC
  val prefetch_pc = RegInit(PC_INIT)

  // Track what PC the FetchUnit should be receiving
  val should_rcv_pc = RegInit(PC_INIT)

  // State machine for prefetch
  val state     = RegInit(0.U(2.W))
  val sIdle     = 0.U
  val sWaitResp = 1.U
  val sStalled  = 2.U

  // Buffer for prefetched instruction when FetchUnit is not ready
  val inst_buffer  = Reg(new InstPacket)
  val buffer_valid = RegInit(false.B)

  // Track if we're waiting for a specific address
  val waiting_for_addr = RegInit(0.U(XLEN.W))
  val waiting_valid    = RegInit(false.B)

  // Default outputs
  io.icache_req.valid     := false.B
  io.icache_req.bits.addr := prefetch_pc
  io.fetch_resp.valid     := false.B
  io.fetch_resp.bits      := DontCare
  io.prefetch_stall       := state === sStalled

  // Handle branch redirect - highest priority
  when(io.branch) {
    prefetch_pc   := io.target
    should_rcv_pc := io.target
    state         := sIdle
    buffer_valid  := false.B // Invalidate buffer on branch
    waiting_valid := false.B

    // Immediately send new request for branch target
    io.icache_req.valid     := true.B
    io.icache_req.bits.addr := io.target
    when(io.icache_req.ready) {
      waiting_for_addr := io.target
      waiting_valid    := true.B
      state            := sWaitResp
    }
  }.otherwise {
    // Check if we have a response from ICache
    when(io.icache_resp.valid) {
      val resp_matches = !waiting_valid || (io.icache_resp.bits.addr === waiting_for_addr)

      when(resp_matches) {
        waiting_valid := false.B

        // Check if this is the instruction FetchUnit is expecting
        val is_expected = io.icache_resp.bits.addr === should_rcv_pc

        when(is_expected && io.fetch_ready) {
          // Direct forward to FetchUnit
          io.fetch_resp.valid := true.B
          io.fetch_resp.bits  := io.icache_resp.bits
          should_rcv_pc       := should_rcv_pc + 4.U

          // Continue prefetching next instruction
          prefetch_pc := prefetch_pc + 4.U
          state       := sIdle
        }.elsewhen(is_expected && !io.fetch_ready) {
          // Buffer the instruction
          inst_buffer  := io.icache_resp.bits
          buffer_valid := true.B
          state        := sStalled
        }.otherwise {
          // Response for wrong address (shouldn't happen in normal flow)
          state := sIdle
        }
      }
    }

    // Handle buffered instruction
    when(buffer_valid && io.fetch_ready) {
      io.fetch_resp.valid := true.B
      io.fetch_resp.bits  := inst_buffer
      buffer_valid        := false.B
      should_rcv_pc       := should_rcv_pc + 4.U

      // Resume prefetching
      prefetch_pc := should_rcv_pc + 4.U
      state       := sIdle
    }

    // State machine for normal prefetch operation
    switch(state) {
      is(sIdle) {
        when(!buffer_valid && io.icache_req.ready) {
          // Send prefetch request
          io.icache_req.valid     := true.B
          io.icache_req.bits.addr := prefetch_pc

          waiting_for_addr := prefetch_pc
          waiting_valid    := true.B
          state            := sWaitResp
        }
      }

      is(sWaitResp) {
        // Waiting for ICache response
        // Response handling is done above
        when(
          io.icache_resp.valid && waiting_valid &&
            io.icache_resp.bits.addr === waiting_for_addr
        ) {
          // Response received, transition handled above
        }
      }

      is(sStalled) {
        // Stalled because FetchUnit is not ready
        // Buffer handling is done above
        when(!buffer_valid) {
          state := sIdle
        }
      }
    }
  }
}

// Modified FetchUnit to work with PrefetchUnit
class FetchUnitWithPrefetch extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val signal      = Input(new Signals())

    // Interface with PrefetchUnit
    val prefetch_resp = Flipped(Valid(new InstPacket))
    val fetch_ready   = Output(Bool())

    // Status
    val canStart = Output(Bool())
  })

  val pc       = RegInit(PC_INIT)
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  // Signal to PrefetchUnit that we're ready for new instruction
  io.fetch_ready := !stall

  // Default outputs
  io.decodeStage.data := 0.U.asTypeOf(new IfIdData())
  io.canStart         := !reset.asBool && !stall

  // Handle branch
  val branch = io.signal.branchControl.branch
  val target = io.signal.branchControl.target

  when(branch) {
    pc             := target
    ifid_reg.valid := false.B
  }.otherwise {
    // Process prefetched instruction
    when(io.prefetch_resp.valid && io.prefetch_resp.bits.addr === pc) {
      val instIdx = pc(ICACHE_OFFSET_WIDTH - 1, 2)
      val inst = MuxLookup(instIdx, 0.U)(
        Seq(
          0.U -> io.prefetch_resp.bits.data(31, 0),
          1.U -> io.prefetch_resp.bits.data(63, 32),
          2.U -> io.prefetch_resp.bits.data(95, 64),
          3.U -> io.prefetch_resp.bits.data(127, 96),
          4.U -> io.prefetch_resp.bits.data(159, 128),
          5.U -> io.prefetch_resp.bits.data(191, 160),
          6.U -> io.prefetch_resp.bits.data(223, 192),
          7.U -> io.prefetch_resp.bits.data(255, 224)
        )
      )

      when(decodeReady) {
        io.decodeStage.data.inst  := inst
        io.decodeStage.data.pc    := pc
        io.decodeStage.data.valid := true.B
        pc                        := pc + 4.U
      }.otherwise {
        ifid_reg.inst  := inst
        ifid_reg.pc    := pc
        ifid_reg.valid := true.B
      }
    }

    // Handle buffered instruction
    when(ifid_reg.valid && decodeReady) {
      io.decodeStage.data := ifid_reg
      ifid_reg.valid      := false.B
      pc                  := ifid_reg.pc + 4.U
    }
  }
}
