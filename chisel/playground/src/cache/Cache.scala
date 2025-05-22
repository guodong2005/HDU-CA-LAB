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
  io.axi              := DontCare
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

  // ---- FSM Implementati7on ---- //
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
  when(io.req.valid) {}

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

  switch(state) {
    is(sIdle) {
      // When a CPU request arrives, latch it.
      when(io.req.valid) {
        reqReg    := io.req.bits
        reqStored := true.B
        when(io.req.bits.write) {
          state         := sWrite // Begin a write transaction.
          writeSubState := wIdle  // Initialize the write sub-FSM.
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
          writeSubState := wIdle
        }
      }
    }
    is(sWriteResp) {
      // Wait for the write response on the AXI B channel.
      when(io.axi.b.valid) {
        io.resp.valid      := true.B
        io.resp.bits.rdata := 0.U // For store operations, a dummy data response.
        when(io.resp.ready) {
          reqStored := false.B
          state     := sIdle
        }
      }
    }
  }
}
