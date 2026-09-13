package cpu

import chisel3._
import chisel3.util._
import cpu.defines._

/**
  * Small unified direct-mapped write-through cache.
  * It is deliberately single-outstanding and single-beat: the CPU-side AXI
  * contract is preserved while hit responses are returned without external traffic.
  */
class AxiCache(val lines: Int = 4) extends Module {
  require(lines >= 2 && isPow2(lines))
  val io = IO(new Bundle { val cpu = Flipped(new AxiMaster); val mem = new AxiMaster })
  val indexBits = log2Ceil(lines)
  val valid = RegInit(VecInit(Seq.fill(lines)(false.B)))
  val tags = Reg(Vec(lines, UInt((32 - 2 - indexBits).W)))
  val data = Reg(Vec(lines, UInt(32.W)))
  val readPending = RegInit(false.B)

  val readAddr = Reg(UInt(32.W)); val readId = Reg(UInt(4.W)); val readIndex = Reg(UInt(indexBits.W)); val readTag = Reg(UInt((32 - 2 - indexBits).W))
  val hit = valid(readIndex) && tags(readIndex) === readTag
  val state = RegInit(0.U(3.W)); val sIdle :: sReadMiss :: sReadResp :: sWriteAw :: sWriteW :: sWriteB :: Nil = Enum(6)

  io.cpu.ar.ready := state === sIdle && !readPending
  io.cpu.r.valid := state === sReadResp
  io.cpu.r.bits := 0.U.asTypeOf(new AxiR)
  io.cpu.r.bits.id := readId; io.cpu.r.bits.data := data(readIndex); io.cpu.r.bits.last := true.B
  io.cpu.aw.ready := state === sIdle && io.mem.aw.ready
  io.cpu.w.ready := state === sIdle && io.mem.w.ready
  io.cpu.b.valid := io.mem.b.valid; io.cpu.b.bits := io.mem.b.bits
  io.mem.ar.valid := state === sReadMiss; io.mem.ar.bits := 0.U.asTypeOf(new AxiAR)
  io.mem.ar.bits.addr := readAddr; io.mem.ar.bits.id := readId; io.mem.ar.bits.size := 2.U
  io.mem.r.ready := state === sReadMiss
  io.mem.aw.valid := state === sIdle && io.cpu.aw.valid; io.mem.aw.bits := io.cpu.aw.bits
  io.mem.w.valid := state === sIdle && io.cpu.w.valid; io.mem.w.bits := io.cpu.w.bits
  io.mem.b.ready := io.cpu.b.ready

  when(reset.asBool) { state := sIdle; valid.foreach(_ := false.B); readPending := false.B }
  when(state === sIdle && io.cpu.ar.fire) {
    readAddr := io.cpu.ar.bits.addr; readId := io.cpu.ar.bits.id
    readIndex := io.cpu.ar.bits.addr(indexBits + 1, 2)
    readTag := io.cpu.ar.bits.addr(31, indexBits + 2)
    when(valid(io.cpu.ar.bits.addr(indexBits + 1, 2)) && tags(io.cpu.ar.bits.addr(indexBits + 1, 2)) === io.cpu.ar.bits.addr(31, indexBits + 2)) {
      state := sReadResp
    }.otherwise { state := sReadMiss }
  }
  when(state === sReadMiss && io.mem.ar.fire) { readPending := true.B }
  when(state === sReadMiss && io.mem.r.fire) {
    data(readIndex) := io.mem.r.bits.data; tags(readIndex) := readTag; valid(readIndex) := true.B; readPending := false.B; state := sReadResp
  }
  when(state === sReadResp && io.cpu.r.fire) { state := sIdle }
  when(io.cpu.aw.valid) {
    // The write data channel is independent from AW.  Until the cache holds
    // both channels together, invalidate all lines on every write address
    // handshake rather than risking a stale line after a later W handshake.
    valid.foreach(_ := false.B)

  }
  // Writes are direct write-through transactions.  The CPU issues AW before W;
  // keeping both channels transparent avoids introducing an additional coupled
  // write state machine into the cache.
}
