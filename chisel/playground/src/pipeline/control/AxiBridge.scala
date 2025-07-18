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
class awRequest extends Bundle {
  val valid = Bool()
  val size  = UInt(3.W)
  val addr  = UInt(32.W)
}
class wRequest extends Bundle {
  val valid = Bool()
  val strb  = UInt(4.W)
  val data  = UInt(32.W)
}

/**
 * Axibridge acts as an intermediary between two cache modules (dcache and icache) and an external AXI memory bus. It arbitrates AR (read address) requests from both caches and forwards them on the external bus. When the AXI slave returns read data, the bridge demultiplexes the response to the
 * proper cache based on a source tag encoded in the lowest bit of the AXI id.
 */
class Axibridge extends Module {
  val io = IO(new Bundle {
    val axi         = new AXI()
    val dcacheInput = Flipped(new AXI())
    val icacheInput = Flipped(new AXI())
    val cache_resp  = Output(UInt((FETCH_WIDTH * 32).W))
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

  when(io.dcacheInput.ar.valid && !regDcacheReq.valid) {
    regDcacheReq.valid := true.B
    regDcacheReq.addr  := io.dcacheInput.ar.bits.addr
    regDcacheReq.size  := io.dcacheInput.ar.bits.size
    regDcacheReq.id    := io.dcacheInput.ar.bits.id
  }
  when(io.icacheInput.ar.valid && !regIcacheReq.valid) {
    regIcacheReq.valid := true.B
    regIcacheReq.addr  := io.icacheInput.ar.bits.addr
    regIcacheReq.size  := io.icacheInput.ar.bits.size
    regIcacheReq.id    := io.icacheInput.ar.bits.id
  }

  val DcacheReq = Wire(new readRequest)
  val IcacheReq = Wire(new readRequest)

  DcacheReq.valid := Mux(regDcacheReq.valid, regDcacheReq.valid, io.dcacheInput.ar.valid)
  DcacheReq.addr  := Mux(regDcacheReq.valid, regDcacheReq.addr, io.dcacheInput.ar.bits.addr)
  DcacheReq.id    := Mux(regDcacheReq.valid, regDcacheReq.id, io.dcacheInput.ar.bits.id)
  DcacheReq.size  := Mux(regDcacheReq.valid, regDcacheReq.size, io.dcacheInput.ar.bits.size)

  IcacheReq.valid := Mux(regIcacheReq.valid, regIcacheReq.valid, io.icacheInput.ar.valid)
  IcacheReq.addr  := Mux(regIcacheReq.valid, regIcacheReq.addr, io.icacheInput.ar.bits.addr)
  IcacheReq.id    := Mux(regIcacheReq.valid, regIcacheReq.id, io.icacheInput.ar.bits.id)
  IcacheReq.size  := Mux(regIcacheReq.valid, regIcacheReq.size, io.icacheInput.ar.bits.size)

  // ------------------------------------------------------------
  // Arbitration for the external AXI AR channel.
  // ------------------------------------------------------------
  val selValid = Mux(DcacheReq.valid, true.B, IcacheReq.valid)
  val selAddr  = Mux(DcacheReq.valid, DcacheReq.addr, IcacheReq.addr)
  val selSize  = Mux(DcacheReq.valid, DcacheReq.size, IcacheReq.size)
  val selLen   = Mux(DcacheReq.valid, 0.U, (FETCH_WIDTH - 1).U)
  val selId    = Mux(DcacheReq.valid, Cat(DcacheReq.id(3, 1), 1.U(1.W)), Cat(IcacheReq.id(3, 1), 0.U(1.W)))

  io.axi.ar.valid     := selValid
  io.axi.ar.bits.addr := selAddr
  io.axi.ar.bits.size := selSize
  io.axi.ar.bits.len  := selLen
  io.axi.ar.bits.id   := selId

  when(io.axi.ar.valid && io.axi.ar.ready) {
    when(DcacheReq.valid) {
      regDcacheReq.valid := false.B
    }.otherwise {
      regIcacheReq.valid := false.B
    }
  }

  // ------------------------------------------------------------
  // Handle the AXI R (read data) channel.
  // ------------------------------------------------------------
  io.axi.r.ready := true.B
  val r_sel = io.axi.r.bits.id(0)

  val icacheDataBuffer  = RegInit(VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W))))
  val icacheBeatCounter = RegInit(0.U(log2Ceil(FETCH_WIDTH).W))
  val icacheReceiving   = RegInit(false.B)

  when(io.axi.r.valid && io.axi.r.ready) {
    when(!r_sel) {
      icacheDataBuffer(icacheBeatCounter) := io.axi.r.bits.data
      icacheBeatCounter                   := icacheBeatCounter + 1.U
      icacheReceiving                     := true.B

      when(io.axi.r.bits.last) {
        icacheReceiving   := false.B
        icacheBeatCounter := 0.U
      }
    }.otherwise {
      io.dcacheInput.r.valid     := true.B
      io.dcacheInput.r.bits.data := io.axi.r.bits.data
    }
  }

  io.icacheInput.r.valid     := !icacheReceiving && (icacheBeatCounter === 0.U)
  io.icacheInput.r.bits.data := DontCare // optional

  io.cache_resp := icacheDataBuffer.asUInt
  printf(p"cache_resp = 0x${Hexadecimal(io.cache_resp)}\n")

  // ------------------------------------------------------------
  // Drive AR ready back to the caches.
  // ------------------------------------------------------------
  io.dcacheInput.ar.ready := true.B
  io.icacheInput.ar.ready := true.B

  // ------------------------------------------------------------
  // Write Handshake for dcache write request.
  // ------------------------------------------------------------
  val regDcacheAw = RegInit(0.U.asTypeOf(io.dcacheInput.aw.bits))
  val aw_hold     = RegInit(false.B)
  when(io.dcacheInput.aw.valid && !aw_hold) {
    regDcacheAw := io.dcacheInput.aw.bits
    aw_hold     := true.B
  }
  when(io.axi.aw.ready && io.axi.aw.valid) {
    aw_hold := false.B
  }

  val DcacheAw = Wire(new awRequest)
  DcacheAw.valid          := Mux(aw_hold, aw_hold, io.dcacheInput.aw.valid)
  DcacheAw.addr           := Mux(aw_hold, regDcacheAw.addr, io.dcacheInput.aw.bits.addr)
  DcacheAw.size           := Mux(aw_hold, regDcacheAw.size, io.dcacheInput.aw.bits.size)
  io.axi.aw.valid         := DcacheAw.valid
  io.axi.aw.bits.addr     := DcacheAw.addr
  io.axi.aw.bits.size     := DcacheAw.size
  io.dcacheInput.aw.ready := io.axi.aw.ready

  val regDcacheW = RegInit(0.U.asTypeOf(io.dcacheInput.w.bits))
  val w_hold     = RegInit(false.B)
  when(io.dcacheInput.w.valid && !w_hold) {
    regDcacheW := io.dcacheInput.w.bits
    w_hold     := true.B
  }
  when(io.axi.w.ready && io.axi.w.valid) {
    w_hold := false.B
  }

  val DcacheW = Wire(new wRequest)
  DcacheW.valid      := Mux(w_hold, w_hold, io.dcacheInput.w.valid)
  DcacheW.strb       := Mux(w_hold, regDcacheW.strb, io.dcacheInput.w.bits.strb)
  DcacheW.data       := Mux(w_hold, regDcacheW.data, io.dcacheInput.w.bits.data)
  io.axi.w.valid     := DcacheW.valid
  io.axi.w.bits.data := DcacheW.data
  io.axi.w.bits.strb := DcacheW.strb

  io.dcacheInput.w.ready := io.axi.w.ready

  io.dcacheInput.b.bits  := io.axi.b.bits
  io.dcacheInput.b.valid := io.axi.b.valid
  io.axi.b.ready         := io.dcacheInput.b.ready
}
