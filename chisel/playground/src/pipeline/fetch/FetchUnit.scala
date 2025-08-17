package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

// ============================================================================
// Complete PrefetchUnit for Non-blocking ICache
// ============================================================================
class PrefetchUnit extends Module {
  val io = IO(new Bundle {
    // Interface with ICache
    val icache_req  = Decoupled(new ICacheReq)
    val icache_resp = Flipped(Valid(new InstPacket))

    // Interface with FetchUnit
    val fetch_ready = Input(Bool()) // FetchUnit ready to receive
    val fetch_resp  = Valid(new InstPacket) // Send instruction to FetchUnit

    // Control signals from ControlUnit
    val branch = Input(Bool()) // Branch redirect signal
    val target = Input(UInt(XLEN.W)) // Branch target address

    // Status outputs
    val prefetch_active   = Output(Bool()) // Indicates prefetch is active
    val outstanding_count = Output(UInt(2.W)) // Number of outstanding requests
  })

  // ============================================================================
  // State and Registers
  // ============================================================================

  // Track outstanding requests (up to 2)
  val outstanding_req1 = RegInit(0.U.asTypeOf(Valid(UInt(XLEN.W))))
  val outstanding_req2 = RegInit(0.U.asTypeOf(Valid(UInt(XLEN.W))))

  // PC management
  val prefetch_pc = RegInit(PC_INIT) // Next PC to prefetch
  val fetch_pc    = RegInit(PC_INIT) // PC that FetchUnit expects next
  val initialized = RegInit(false.B) // Track initialization

  // Instruction buffer for when FetchUnit is not ready
  val inst_buffer = RegInit(0.U.asTypeOf(Valid(new InstPacket)))

  // Statistics and control
  val consecutive_hits  = RegInit(0.U(4.W)) // Track consecutive cache hits
  val prefetch_distance = RegInit(1.U(2.W)) // How far ahead to prefetch

  // ============================================================================
  // Control Logic
  // ============================================================================

  // Outstanding request management
  val outstanding_count = outstanding_req1.valid.asUInt + outstanding_req2.valid.asUInt
  val can_issue_request = outstanding_count < 2.U
  val has_outstanding   = outstanding_req1.valid || outstanding_req2.valid

  // Check if an address is outstanding
  def isOutstanding(addr: UInt): Bool = {
    (outstanding_req1.valid && outstanding_req1.bits === addr) ||
    (outstanding_req2.valid && outstanding_req2.bits === addr)
  }

  // Prefetch control
  val should_prefetch = can_issue_request &&
    !inst_buffer.valid &&
    initialized &&
    !io.branch

  val prefetch_ahead = (prefetch_pc - fetch_pc) >> 2 // Number of instructions ahead
  val too_far_ahead  = prefetch_ahead >= 2.U

  // ============================================================================
  // Default Outputs
  // ============================================================================

  io.icache_req.valid     := false.B
  io.icache_req.bits.addr := prefetch_pc
  io.fetch_resp.valid     := false.B
  io.fetch_resp.bits      := DontCare
  io.prefetch_active      := has_outstanding || inst_buffer.valid
  io.outstanding_count    := outstanding_count

  // ============================================================================
  // Initialization
  // ============================================================================

  when(!initialized && !reset.asBool) {
    initialized := true.B
    prefetch_pc := PC_INIT
    fetch_pc    := PC_INIT
  }

  // ============================================================================
  // Branch Handling - Highest Priority
  // ============================================================================

  when(io.branch) {
    // Clear all outstanding requests and buffer
    outstanding_req1.valid := false.B
    outstanding_req2.valid := false.B
    inst_buffer.valid      := false.B

    // Reset PCs to branch target
    prefetch_pc := io.target
    fetch_pc    := io.target

    // Reset prefetch statistics
    consecutive_hits  := 0.U
    prefetch_distance := 1.U

    // Issue immediate request for branch target
    when(io.icache_req.ready) {
      io.icache_req.valid     := true.B
      io.icache_req.bits.addr := io.target

      // Track this request
      outstanding_req1.valid := true.B
      outstanding_req1.bits  := io.target

      // Prepare to prefetch next
      prefetch_pc := io.target + 4.U
    }
  }.otherwise {
    // ============================================================================
    // Normal Prefetch Operation
    // ============================================================================

    // Issue new prefetch request
    when(should_prefetch && !too_far_ahead && io.icache_req.ready) {
      io.icache_req.valid     := true.B
      io.icache_req.bits.addr := prefetch_pc

      // Add to outstanding requests
      when(!outstanding_req1.valid) {
        outstanding_req1.valid := true.B
        outstanding_req1.bits  := prefetch_pc
      }.elsewhen(!outstanding_req2.valid) {
        outstanding_req2.valid := true.B
        outstanding_req2.bits  := prefetch_pc
      }

      // Advance prefetch PC
      prefetch_pc := prefetch_pc + 4.U
    }

    // ============================================================================
    // Handle ICache Responses
    // ============================================================================

    when(io.icache_resp.valid) {
      val resp_addr      = io.icache_resp.bits.addr
      val is_expected    = resp_addr === fetch_pc
      val is_next        = resp_addr === (fetch_pc + 4.U)
      val is_outstanding = isOutstanding(resp_addr)

      when(is_outstanding) {
        // Clear the matching outstanding request
        when(outstanding_req1.valid && outstanding_req1.bits === resp_addr) {
          outstanding_req1.valid := false.B
        }
        when(outstanding_req2.valid && outstanding_req2.bits === resp_addr) {
          outstanding_req2.valid := false.B
        }

        // Update consecutive hit counter
        consecutive_hits := Mux(consecutive_hits < 15.U, consecutive_hits + 1.U, 15.U)

        // Process the response
        when(is_expected) {
          when(io.fetch_ready && !inst_buffer.valid) {
            // Direct forward to FetchUnit
            io.fetch_resp.valid := true.B
            io.fetch_resp.bits  := io.icache_resp.bits
            fetch_pc            := fetch_pc + 4.U
          }.otherwise {
            // Buffer the instruction
            inst_buffer.valid := true.B
            inst_buffer.bits  := io.icache_resp.bits
          }
        }.elsewhen(is_next && !inst_buffer.valid) {
          // Got next instruction early, buffer it
          inst_buffer.valid := true.B
          inst_buffer.bits  := io.icache_resp.bits
        }
        // Else: Response for wrong address (discard)
      }
    }

    // ============================================================================
    // Deliver Buffered Instruction
    // ============================================================================

    when(inst_buffer.valid && inst_buffer.bits.addr === fetch_pc && io.fetch_ready) {
      io.fetch_resp.valid := true.B
      io.fetch_resp.bits  := inst_buffer.bits
      inst_buffer.valid   := false.B
      fetch_pc            := fetch_pc + 4.U
    }

    // ============================================================================
    // Adaptive Prefetch Distance (Optional Enhancement)
    // ============================================================================

    // Increase prefetch distance on consecutive hits
    when(consecutive_hits >= 8.U && prefetch_distance < 2.U) {
      prefetch_distance := 2.U
    }.elsewhen(consecutive_hits < 4.U && prefetch_distance > 1.U) {
      prefetch_distance := 1.U
    }
  }
}

// ============================================================================
// Complete FetchUnit for Non-blocking System
// ============================================================================
class FetchUnit extends Module {
  val io = IO(new Bundle {
    // Interface with DecodeStage
    val decodeStage = new FetchUnitDecodeUnit()

    // Control signals from ControlUnit
    val signal = Input(new Signals())

    // Interface with PrefetchUnit
    val prefetch_resp = Flipped(Valid(new InstPacket))
    val fetch_ready   = Output(Bool())

    // Status outputs
    val canStart    = Output(Bool())
    val pc_out      = Output(UInt(XLEN.W)) // Current PC for debug
    val stall_count = Output(UInt(32.W)) // Performance counter
  })

  // ============================================================================
  // State and Registers
  // ============================================================================

  // PC management
  val pc       = RegInit(PC_INIT)
  val pc_valid = RegInit(false.B)

  // Instruction buffer for decode stage
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  // Performance counters
  val stall_count = RegInit(0.U(32.W))
  val inst_count  = RegInit(0.U(32.W))

  // ============================================================================
  // Control Signals
  // ============================================================================

  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid
  val branch      = io.signal.branchControl.branch
  val target      = io.signal.branchControl.target

  // ============================================================================
  // Output Signals
  // ============================================================================

  io.fetch_ready      := !stall && pc_valid
  io.decodeStage.data := 0.U.asTypeOf(new IfIdData())
  io.canStart         := pc_valid && !stall
  io.pc_out           := pc
  io.stall_count      := stall_count

  // ============================================================================
  // Initialization
  // ============================================================================

  when(!pc_valid && !reset.asBool) {
    pc       := PC_INIT
    pc_valid := true.B
  }

  // ============================================================================
  // Branch Handling
  // ============================================================================

  when(branch) {
    // Immediate PC update on branch
    pc       := target
    pc_valid := true.B

    // Clear any buffered instruction
    ifid_reg.valid := false.B

    // Don't increment stall counter on branch
  }.otherwise {
    // ============================================================================
    // Normal Instruction Processing
    // ============================================================================

    // Track stalls
    when(stall && pc_valid) {
      stall_count := stall_count + 1.U
    }

    // Process prefetched instruction
    when(io.prefetch_resp.valid && io.prefetch_resp.bits.addr === pc && pc_valid) {
      // Extract the correct instruction from cache line
      val inst_offset = pc(ICACHE_OFFSET_WIDTH - 1, 2)
      val cache_line  = io.prefetch_resp.bits.data

      val inst = MuxLookup(inst_offset, 0.U)(
        Seq(
          0.U -> cache_line(31, 0),
          1.U -> cache_line(63, 32),
          2.U -> cache_line(95, 64),
          3.U -> cache_line(127, 96),
          4.U -> cache_line(159, 128),
          5.U -> cache_line(191, 160),
          6.U -> cache_line(223, 192),
          7.U -> cache_line(255, 224)
        )
      )

      when(decodeReady && !ifid_reg.valid) {
        // Send directly to decode stage
        io.decodeStage.data.inst  := inst
        io.decodeStage.data.pc    := pc
        io.decodeStage.data.valid := true.B
        pc                        := pc + 4.U
        inst_count                := inst_count + 1.U
      }.elsewhen(!ifid_reg.valid) {
        // Buffer the instruction
        ifid_reg.inst  := inst
        ifid_reg.pc    := pc
        ifid_reg.valid := true.B
      }
      // Else: Already have buffered instruction, ignore this one
    }

    // ============================================================================
    // Handle Buffered Instruction
    // ============================================================================

    when(ifid_reg.valid && decodeReady) {
      // Send buffered instruction to decode
      io.decodeStage.data := ifid_reg
      ifid_reg.valid      := false.B
      pc                  := ifid_reg.pc + 4.U
      inst_count          := inst_count + 1.U
    }
  }

  // ============================================================================
  // Debug Assertions (Optional)
  // ============================================================================

  when(io.prefetch_resp.valid && io.prefetch_resp.bits.addr =/= pc && pc_valid) {
    // Got unexpected instruction address
    // This is normal after branch, but shouldn't happen otherwise
    assert(branch || !pc_valid, "Received unexpected instruction address")
  }
}
