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

  val sIdle :: sWait :: Nil = Enum(2)
  val state                 = RegInit(sIdle)

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
  io.axi.ar.valid     := !req.bits.write
  io.axi.ar.bits.size := req.bits.size

  io.axi.aw.valid     := req.bits.write
  io.axi.aw.bits.addr := req.bits.addr
  io.axi.aw.bits.size := req.bits.size
  io.axi.aw.bits.id   := 0.U

  // Set up W channel signals.
  io.axi.w.valid      := req.bits.write
  io.axi.w.bits.data  := req.bits.wdata
  io.axi.w.bits.strb  := req.bits.wstrb // For a full 32-bit write.
  io.axi.ar.bits.addr := req.bits.addr

  io.axi.b.ready := false.B // write response may be very fast

  val cnt = RegInit(0.U)
  switch(state) {
    is(sIdle) {
      when(io.axi.ar.valid && io.axi.ar.ready) {
        io.axi.ar.valid := false.B
        reqStored       := false.B
        state           := sWait
      }
      when(io.axi.aw.valid && io.axi.aw.ready) {
        cnt   := cnt + 1.U
        state := sWait
      }
      when(io.axi.w.valid && io.axi.w.ready) {
        cnt   := cnt + 1.U
        state := sWait
      }
    }
  }

}
