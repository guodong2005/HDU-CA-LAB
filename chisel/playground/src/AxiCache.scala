package cpu

import chisel3._
import chisel3.util._
import cpu.defines._

/** Four-line direct-mapped, write-through, single-beat cache. */
class AxiCache(val lines: Int = 4) extends Module {
  require(lines >= 2 && isPow2(lines))
  val io = IO(new Bundle { val cpu = Flipped(new AxiMaster); val mem = new AxiMaster })
  val indexBits = log2Ceil(lines)
  val tagBits = 32 - 2 - indexBits
  val valid = RegInit(VecInit(Seq.fill(lines)(false.B)))
  val tags = Reg(Vec(lines, UInt(tagBits.W)))
  val data = Reg(Vec(lines, UInt(32.W)))

  val sIdle :: sReadReq :: sReadWait :: sReadResp :: sWriteAw :: sWriteW :: sWriteB :: Nil = Enum(7)
  val state = RegInit(sIdle)
  val readAddr = Reg(UInt(32.W)); val readId = Reg(UInt(4.W))
  val readIndex = Reg(UInt(indexBits.W)); val readTag = Reg(UInt(tagBits.W))
  val readData = Reg(UInt(32.W)); val readRespId = Reg(UInt(4.W)); val readResp = Reg(UInt(2.W)); val readLast = Reg(Bool())
  val writeAddr = Reg(UInt(32.W)); val writeId = Reg(UInt(4.W))

  val cpuIndex = io.cpu.ar.bits.addr(indexBits + 1, 2)
  val cpuTag = io.cpu.ar.bits.addr(31, indexBits + 2)
  val hit = valid(cpuIndex) && tags(cpuIndex) === cpuTag

  // Write priority is explicit. At most one CPU request can handshake in idle.
  io.cpu.aw.ready := state === sIdle && io.cpu.aw.valid
  io.cpu.ar.ready := state === sIdle && !io.cpu.aw.valid

  io.cpu.r.valid := state === sReadResp
  io.cpu.r.bits := 0.U.asTypeOf(new AxiR)
  io.cpu.r.bits.id := readRespId
  io.cpu.r.bits.data := readData
  io.cpu.r.bits.resp := readResp
  io.cpu.r.bits.last := readLast

  io.cpu.w.ready := state === sWriteW && io.mem.w.ready
  io.cpu.b.valid := state === sWriteB && io.mem.b.valid
  io.cpu.b.bits := io.mem.b.bits

  io.mem.ar.valid := state === sReadReq
  io.mem.ar.bits := 0.U.asTypeOf(new AxiAR)
  io.mem.ar.bits.addr := readAddr & "hfffffffc".U
  io.mem.ar.bits.id := readId
  io.mem.ar.bits.len := 0.U
  io.mem.ar.bits.size := 2.U
  io.mem.ar.bits.burst := 1.U
  io.mem.ar.bits.prot := 0.U
  io.mem.r.ready := state === sReadWait

  io.mem.aw.valid := state === sWriteAw
  io.mem.aw.bits := 0.U.asTypeOf(new AxiAW)
  io.mem.aw.bits.addr := writeAddr & "hfffffffc".U
  io.mem.aw.bits.id := writeId
  io.mem.aw.bits.len := 0.U
  io.mem.aw.bits.size := 2.U
  io.mem.aw.bits.burst := 1.U
  io.mem.aw.bits.prot := 0.U

  io.mem.w.valid := state === sWriteW && io.cpu.w.valid
  io.mem.w.bits := io.cpu.w.bits
  io.mem.b.ready := state === sWriteB && io.cpu.b.ready

  when (state === sIdle && io.cpu.aw.fire) {
    writeAddr := io.cpu.aw.bits.addr
    writeId := io.cpu.aw.bits.id
    valid.foreach(_ := false.B)
    state := sWriteAw
  } .elsewhen (state === sIdle && io.cpu.ar.fire) {
    readAddr := io.cpu.ar.bits.addr
    readId := io.cpu.ar.bits.id
    readIndex := cpuIndex
    readTag := cpuTag
    readData := Mux(hit, data(cpuIndex), 0.U)
    readRespId := io.cpu.ar.bits.id
    readResp := 0.U
    readLast := true.B
    state := Mux(hit, sReadResp, sReadReq)
  }

  when (state === sReadReq && io.mem.ar.fire) {
    state := sReadWait
  }
  when (state === sReadWait && io.mem.r.fire) {
    readRespId := io.mem.r.bits.id
    readData := io.mem.r.bits.data
    readResp := io.mem.r.bits.resp
    readLast := io.mem.r.bits.last
    when (io.mem.r.bits.id === readId && io.mem.r.bits.resp === 0.U && io.mem.r.bits.last) {
      data(readIndex) := io.mem.r.bits.data
      tags(readIndex) := readTag
      valid(readIndex) := true.B
    }
    state := sReadResp
  }
  when (state === sReadResp && io.cpu.r.fire) {
    state := sIdle
  }

  when (state === sWriteAw && io.mem.aw.fire) {
    state := sWriteW
  }
  when (state === sWriteW && io.mem.w.fire) {
    state := sWriteB
  }
  when (state === sWriteB && io.mem.b.fire) {
    state := sIdle
  }
}
