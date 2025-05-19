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
class ICache extends Module {
  val io = IO(new Bundle {
    // AXI interface remains the same
    val axi = new AXI()

    // Fetch request: master (fetch unit) issues a read request using valid/addr;
    // ICache drives ready to indicate acceptance.
    val fetch_req = new Bundle {
      val valid = Input(Bool())
      val addr  = Input(UInt(XLEN.W))
      val ready = Output(Bool())
    }

    // Fetch response: ICache forwards AXI‑R data along with the associated address that was latched.
    val fetch_rsp = new Bundle {
      val valid = Output(Bool())
      val data  = Output(UInt(XLEN.W)) // Adjust the width as needed.
      val addr  = Output(UInt(XLEN.W))
    }
  })

  // Default assignments for the AXI AR channel.
  io.axi.ar.bits.size := 2.U
  io.axi.ar.bits.addr := 0.U
  io.axi.ar.valid     := false.B

  // The AXI R channel: assume our module is always ready to accept read data.
  io.axi.r.ready := true.B

  // FSM for the read transaction.
  // sIdle: ICache can accept a new fetch request.
  // sWait: ICache is waiting for read data from the AXI slave.
  val sIdle :: sWait :: Nil = Enum(2)
  val state                 = RegInit(sIdle)

  // Latch address for which a transaction was issued.
  val latchedAddr = RegInit(0.U(XLEN.W))

  // ---- Fetch Unit interface assignments ---- //
  // The ICache’s ready signal on the fetch request is asserted only in the idle state.
  io.fetch_req.ready := (state === sIdle)

  // Default assignments for the fetch response.
  // It becomes valid only when in sWait state and AXI read data is available.
  io.fetch_rsp.valid := false.B
  io.fetch_rsp.data  := io.axi.r.bits.data // Forward data from the AXI interface.
  io.fetch_rsp.addr  := latchedAddr        // Return the latched fetch address.

  // ---- FSM Implementation ---- //
  switch(state) {
    is(sIdle) {
      // When the fetch unit issues a valid request,
      // drive an AXI AR transaction.
      when(io.fetch_req.valid) {
        io.axi.ar.valid     := true.B
        io.axi.ar.bits.addr := io.fetch_req.addr
        // If the AXI slave is ready (handshake completes),
        // latch the address and transition to waiting for read data.
        when(io.axi.ar.ready) {
          latchedAddr := io.fetch_req.addr
          state       := sWait
        }
      }
    }
    is(sWait) {
      // In the waiting state, we do not drive the AR channel.
      io.axi.ar.valid := false.B
      // Once the read data arrives, produce the fetch response and return to idle.
      when(io.axi.r.valid) {
        io.fetch_rsp.valid := true.B
        state              := sIdle
      }
    }
  }
}
