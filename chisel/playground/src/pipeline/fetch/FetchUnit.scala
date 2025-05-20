package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._
import cpu.defines.Instructions.NOP

// Keep these definitions for the fetch answer interface.
class FetchAnswer extends Bundle {
  val data  = UInt(XLEN.W)
  val pc    = UInt(XLEN.W)
  val valid = Bool()
}

/**
 * The FetchUnit sends out an address request to the I‑cache using an AXI‑like (ready/valid) channel. Here we use Chisel’s Decoupled interface so that:
 *   - io.fetchrequest.bits carries the requested (read) address,
 *   - io.fetchrequest.valid indicates a valid request from the fetch unit,
 *   - io.fetchrequest.ready is driven by the I‑cache (slave) when it is ready to accept the request.
 *
 * In response the I‑cache returns a read answer over the fetchanswer channel. When the answer’s valid flag is high and its PC matches the latched request address, the fetch unit forwards the instruction (together with its associated PC) to the decode stage.
 *
 * While waiting for the read response, the fetch unit is in state sWait. A fetched instruction may be buffered if the decode stage is not yet ready (controlled by io.signal.fetchUnitSignal.allow_to_go). Also, branch signals (branch plus the target address) are used to compute the next PC.
 */
class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val fetchanswer = Input(new FetchAnswer())
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    // The fetch request channel uses a ready/valid handshake (AXI‑like).
    val fetchrequest = Decoupled(UInt(XLEN.W))
  })

  // -------------------------------------------------------------------------
  // Program Counter (PC) management.
  // -------------------------------------------------------------------------
  // Initialize PC to 0. We want it to become PC_INIT once reset is over.
  val pc = RegInit(0.U(XLEN.W))
  // Generate a canStart flag so that we don't issue any fetch request while still in reset.
  // (The RegNext ensures that canStart becomes a registered version of !reset.)
  val canStart = RegNext(!reset.asBool) && (!reset.asBool)

  // When canStart becomes true and we haven't started (pc is still 0), update the pc to PC_INIT.
  when(canStart && (pc === 0.U)) {
    pc := PC_INIT
  }

  // -------------------------------------------------------------------------
  // FSM for the fetch request handshake.
  // -------------------------------------------------------------------------
  // Two states:
  //  • sIdle:  The fetch unit is ready to send a new request.
  //  • sWait:  A request has been sent. The unit waits for an answer.
  val sIdle :: sWait :: Nil = Enum(2)
  val state                 = RegInit(sIdle)

  // This register latches the PC value for which a fetch request was sent.
  val reqPC = Reg(UInt(XLEN.W))

  // -------------------------------------------------------------------------
  // Buffer for a fetched instruction waiting to be forwarded to decode.
  // If the decode stage is not ready, we store the result here.
  // (Assume IfIdData has fields: inst, pc, and valid.)
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  // -------------------------------------------------------------------------
  // Determine if the pipeline is stalled.
  // In our design we do not issue a new fetch request if:
  //   1. The decode stage is not ready to accept a new instruction, or
  //   2. There is already a buffered instruction (ifid_reg.valid is true).
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  // -------------------------------------------------------------------------
  // Drive the fetch request (AXI AR channel).
  // A new fetch request is issued (with the current pc) only when:
  //   - The fetch unit is in the idle state (sIdle),
  //   - Not stalled, and
  //   - canStart is true (ensuring that we have come out of reset).
  io.fetchrequest.valid := (state === sIdle) && !stall && RegNext(canStart)
  io.fetchrequest.bits  := pc

  // -------------------------------------------------------------------------
  // Default assignment for the decode stage output.
  // (It will be updated when a fetched instruction is forwarded.)
  io.decodeStage.data := 0.U.asTypeOf(new IfIdData())

  // -------------------------------------------------------------------------
  // FSM Implementation.
  // -------------------------------------------------------------------------
  switch(state) {
    is(sIdle) {
      // In the idle state, when the fetch request handshake occurs,
      // latch the current PC into reqPC and transition to sWait to await the read response.
      when(canStart === false.B) {
        state := sIdle
      }.elsewhen(io.fetchrequest.valid && io.fetchrequest.ready) {
        reqPC := pc
        state := sWait
      }
    }
    is(sWait) {
      // In the wait state, the unit awaits a fetch answer whose pc matches the latched reqPC.
      val answerMatches = (io.fetchanswer.pc === reqPC)
      when(io.fetchanswer.valid && answerMatches) {
        when(decodeReady) {
          // If the decode stage is ready, forward the fetched instruction immediately.
          io.decodeStage.data.inst  := io.fetchanswer.data
          io.decodeStage.data.pc    := reqPC
          io.decodeStage.data.valid := true.B
          // Update the PC: if a branch is signaled, use the branch target; otherwise, increment by 4.
          pc    := Mux(io.branch, io.target, reqPC + 4.U)
          state := sIdle
        }.otherwise {
          // If the decode stage is not ready, buffer the fetched instruction.
          ifid_reg.inst  := io.fetchanswer.data
          ifid_reg.pc    := reqPC
          ifid_reg.valid := true.B
          // Remain in sWait; the PC and state are not updated until the buffered instruction is consumed.
        }
      }
    }
  }

  // -------------------------------------------------------------------------
  // If a buffered instruction exists and the decode stage is ready, forward it.
  // This helps quickly drain the buffer once decode is ready.
  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    // Update the PC after forwarding; use the buffered instruction’s pc.
    pc    := Mux(io.branch, io.target, ifid_reg.pc + 4.U)
    state := sIdle
  }
}
