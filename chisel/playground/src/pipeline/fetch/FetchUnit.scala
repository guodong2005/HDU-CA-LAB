package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.CpuConfig
import cpu.defines._
import cpu.defines.Instructions.NOP

// We keep these definitions for the fetch answer interface.
class FetchAnswer extends Bundle {
  val data  = UInt(XLEN.W)
  val pc    = UInt(XLEN.W)
  val valid = Bool()
}

/**
 * The FetchUnit sends out an address request to the I‑cache using an AXI‐like (ready/valid) channel. Here we use Chisel’s Decoupled interface so that:
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
    // Output to the decode stage (the decoded fetched instruction).
    // (For clarity, we assume that decodeStage.data is of type IfIdData.)
    val decodeStage = new FetchUnitDecodeUnit()
    // Read response coming from the I‑cache (AXI R channel).
    val fetchanswer = Input(new FetchAnswer())
    // Branch control: if branch is true then jump to “target” instead of PC+4.
    val branch = Input(Bool())
    val target = Input(UInt(XLEN.W))
    // Some external signal controlling whether the fetch unit (and later decode stage) is allowed to proceed.
    val signal = Input(new Signals())
    // AXI‑like fetch request (read address) channel.
    // The fetch unit (AXI master) drives valid and bits (the address),
    // and the I‑cache (AXI slave) drives ready.
    val fetchrequest = Flipped(Decoupled(UInt(XLEN.W)))
  })

  // -------------------------------------------------------------------------
  // Program Counter (PC) management.
  // -------------------------------------------------------------------------
  val pc = RegInit(0.U(XLEN.W))
  // We use a canStart flag so that on reset we do not update the PC until reset is gone.
  val canStart = RegNext(!reset.asBool) && (!reset.asBool)
  when(pc === 0.U) {
    when(!canStart) {
      pc := 0.U
    }.otherwise {
      pc := PC_INIT
    }
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
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))
  // The "valid" field in ifid_reg indicates that an instruction is buffered.
  // (We assume IfIdData has fields: inst, pc, and valid.)

  // -------------------------------------------------------------------------
  // Determine if the pipeline is stalled.
  // In our design we do not issue a new fetch request if:
  //   1. The decode stage is not ready to accept a new instruction, or
  //   2. There is already a buffered instruction (ifid_reg.valid is true).
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  // -------------------------------------------------------------------------
  // Drive the fetch request (AXI AR channel).
  // We issue a new fetch request (with the current pc) only when in sIdle and not stalled.
  io.fetchrequest.valid := (state === sIdle) && !stall
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
      // In idle state, if a fetch request handshake occurs then latch the current PC
      // and transition to sWait to await the read response.
      when(io.fetchrequest.valid && io.fetchrequest.ready) {
        reqPC := pc
        state := sWait
      }
    }
    is(sWait) {
      // In wait state, the unit awaits a fetch answer whose pc matches the latched reqPC.
      val answerMatches = (io.fetchanswer.pc === reqPC)
      when(io.fetchanswer.valid && answerMatches) {
        when(decodeReady) {
          // If the decode stage can accept an instruction, forward the fetched data immediately.
          io.decodeStage.data.inst  := io.fetchanswer.data
          io.decodeStage.data.pc    := reqPC
          io.decodeStage.data.valid := true.B
          // Update the PC: on a branch, use the target; otherwise, increment by 4.
          pc    := Mux(io.branch, io.target, reqPC + 4.U)
          state := sIdle
        }.otherwise {
          // Otherwise, buffer the fetched instruction until decode is ready.
          ifid_reg.inst  := io.fetchanswer.data
          ifid_reg.pc    := reqPC
          ifid_reg.valid := true.B
          // Remain in sWait; no PC update until the buffered instruction is consumed.
        }
      }
    }
  }

  // -------------------------------------------------------------------------
  // If a buffered instruction exists and the decode stage is now ready, forward it.
  // This works to quickly drain the buffer once decode is ready.
  when(ifid_reg.valid && decodeReady) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
    // Update the PC after forwarding; use the buffered instruction’s pc.
    pc    := Mux(io.branch, io.target, ifid_reg.pc + 4.U)
    state := sIdle
  }
}
