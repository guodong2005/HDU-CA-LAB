package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._

/** A simple read request bundle used inside the AXI‑bridge. */
class readRequest extends Bundle {
  val valid = Bool()
  val id    = UInt(4.W)
  val addr  = UInt(32.W)
  val size  = UInt(3.W)
}

/**
 * Axibridge acts as an intermediary between two cache modules (dcache and icache) and an external AXI memory bus. It arbitrates AR (read address) requests from both caches and forwards them on the external bus. When the AXI slave returns read data, the bridge demultiplexes the response to the
 * proper cache based on a source tag encoded in the lowest bit of the AXI id.
 */
class Axibridge extends Module {
  val io = IO(new Bundle {
    // External AXI interface.
    val axi = new AXI()
    // Read-side interfaces from the caches.
    val dcacheInput = Flipped(new AXI())
    val icacheInput = Flipped(new AXI())
  })

  dontTouch(io.dcacheInput)
  io.axi         := DontCare
  io.dcacheInput := DontCare
  io.icacheInput := DontCare
  // ------------------------------------------------------------
  // Latch incoming AR requests from caches.
  // ------------------------------------------------------------
  val regDcacheReq = RegInit(0.U.asTypeOf(new readRequest))
  val regIcacheReq = RegInit(0.U.asTypeOf(new readRequest))

  // When a cache asserts its AR valid, capture its request.
  when(io.dcacheInput.ar.valid) {
    regDcacheReq.valid := true.B
    regDcacheReq.addr  := io.dcacheInput.ar.bits.addr
    regDcacheReq.size  := io.dcacheInput.ar.bits.size
    regDcacheReq.id    := io.dcacheInput.ar.bits.id
  }
  when(io.icacheInput.ar.valid) {
    regIcacheReq.valid := true.B
    regIcacheReq.addr  := io.icacheInput.ar.bits.addr
    regIcacheReq.size  := io.icacheInput.ar.bits.size
    regIcacheReq.id    := io.icacheInput.ar.bits.id
  }

  // ------------------------------------------------------------
  // Arbitration for the external AXI AR channel.
  // Priority: if dcache has a pending request, choose it; otherwise, pick icache.
  // ------------------------------------------------------------
  val selValid = Mux(regDcacheReq.valid, true.B, regIcacheReq.valid)
  val selAddr  = Mux(regDcacheReq.valid, regDcacheReq.addr, regIcacheReq.addr)
  val selSize  = Mux(regDcacheReq.valid, regDcacheReq.size, regIcacheReq.size)
  // Encode the cache source in the lowest bit:
  // For dcache, force LSB = 1; for icache, force LSB = 0.
  // Upper 3 bits come from the original request’s id.
  val selId = Mux(regDcacheReq.valid, Cat(regDcacheReq.id(3, 1), 1.U(1.W)), Cat(regIcacheReq.id(3, 1), 0.U(1.W)))

  // Drive the external AXI AR port.
  io.axi.ar.valid     := selValid
  io.axi.ar.bits.addr := selAddr
  io.axi.ar.bits.size := selSize
  io.axi.ar.bits.id   := selId

  // When the external AR handshake completes, clear the appropriate request.
  when(io.axi.ar.valid && io.axi.ar.ready) {
    when(regDcacheReq.valid) {
      regDcacheReq.valid := false.B
    }.otherwise {
      regIcacheReq.valid := false.B
    }
  }

  // ------------------------------------------------------------
  // Handle the AXI R (read data) channel.
  // ------------------------------------------------------------
  // Always ready to accept read data.
  io.axi.r.ready := true.B

  // Demultiplex the response back to the appropriate cache.
  // We assume that the slave echoes the AXI id (with our tag in LSB) with the read response.
  val r_sel = io.axi.r.bits.id(0) // If r_sel is 1: dcache; if 0: icache

  // Pipeline the valid signals by one cycle; initialize with false.
  io.icacheInput.r.valid     := RegNext((!r_sel) && io.axi.r.valid, init = false.B)
  io.icacheInput.r.bits.data := io.axi.r.bits.data
  // If there are other fields (like id, last, etc.) you could forward them similarly.

  io.dcacheInput.r.valid     := RegNext((r_sel) && io.axi.r.valid, init = false.B)
  io.dcacheInput.r.bits.data := io.axi.r.bits.data

  // ------------------------------------------------------------
  // Drive AR ready back to the caches.
  // In this simple scheme, we assume the caches can always present a new request,
  // so we tie their AR ready to true.
  // ------------------------------------------------------------
  io.dcacheInput.ar.ready := true.B
  io.icacheInput.ar.ready := true.B

  // ------------------------------------------------------------
  // Write Handshake for dcache write request.
  // We assume that only dcache issues write transactions.
  // ------------------------------------------------------------

  // Write Address Channel (AW)
  val regDcacheAw = RegInit(0.U.asTypeOf(io.dcacheInput.aw.bits))
  val aw_hold     = RegInit(false.B)
  when(io.dcacheInput.aw.valid) {
    regDcacheAw := io.dcacheInput.aw.bits
    aw_hold     := true.B
  }.elsewhen(io.axi.aw.ready && aw_hold) {
    aw_hold := false.B
  }
  io.axi.aw.valid         := aw_hold
  io.axi.aw.bits.addr     := regDcacheAw.addr
  io.axi.aw.bits.size     := regDcacheAw.size
  io.dcacheInput.aw.ready := io.axi.aw.ready

  // Write Data Channel (W)
  val regDcacheW = RegInit(0.U.asTypeOf(io.dcacheInput.w.bits))
  val w_hold     = RegInit(false.B)
  when(io.dcacheInput.w.valid) {
    regDcacheW := io.dcacheInput.w.bits
    w_hold     := true.B
  }.elsewhen(io.axi.w.ready && w_hold) {
    w_hold := false.B
  }
  io.axi.w.valid         := w_hold
  io.axi.w.bits.data     := regDcacheW.data
  io.dcacheInput.w.ready := io.axi.w.ready

  // Write Response Channel (B)
  // Forward the write response from the external interface back to the dcache.
  io.dcacheInput.b.bits  := io.axi.b.bits
  io.dcacheInput.b.valid := io.axi.b.valid
  // For simplicity, we assume this bridge is always ready to accept a B-channel response.
  io.axi.b.ready := true.B
}
