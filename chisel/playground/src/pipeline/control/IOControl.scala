package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.pipeline._

class SramCtrlInfo extends Bundle {
  val addr = UInt(20.W)
  val be_n = UInt(4.W)
  val ce_n = Bool()
  val oe_n = Bool()
  val we_n = Bool()
}

class SramDataIO extends Bundle {
  val data_out = Output(UInt(32.W)) // 写入SRAM的数据
  val data_in  = Input(UInt(32.W)) // 从SRAM读取的数据
  val data_en  = Output(Bool()) // 数据输出使能（模拟三态门）
}

class SramCtrlIO extends Bundle {
  val data = new SramDataIO
  val ctrl = Output(new SramCtrlInfo)
}

class IoControlDebugIO extends Bundle {
  val base_state        = Output(UInt(12.W))
  val ext_state         = Output(UInt(12.W))
  val icache_read_base  = Output(Bool())
  val icache_read_ext   = Output(Bool())
  val dcache_read_base  = Output(Bool())
  val dcache_read_ext   = Output(Bool())
  val dcache_write_base = Output(Bool())
  val dcache_write_ext  = Output(Bool())
  val icache_read_addr  = Output(UInt(20.W))
  val dcache_read_addr  = Output(UInt(20.W))
  val dcache_write_addr = Output(UInt(20.W))
}

class RxDIO extends Bundle {
  val uart_ready = Input(Bool())
  val uart_clear = Output(Bool())
  val uart_data  = Input(UInt(8.W))
}

class TxDIO extends Bundle {
  val uart_start = Output(Bool())
  val uart_data  = Output(UInt(8.W))
  val uart_busy  = Input(Bool())
}

class UartBufferInfo extends Bundle {
  val data = UInt(8.W)
}

class IoControlIO extends Bundle {
  val icache_read_req  = Flipped(Decoupled(new ICacheReq))
  val icache_read_resp = Decoupled(new ICacheResp)
  val dcache_read_req  = Flipped(Decoupled(new DCacheReadReq))
  val dcache_read_resp = Decoupled(new DCacheResp)
  val dcache_write_req = Flipped(Decoupled(new DCacheWriteReq))
  val base_ram_ctrl    = new SramCtrlIO
  val ext_ram_ctrl     = new SramCtrlIO
  val rxd              = new RxDIO
  val txd              = new TxDIO
  val debug            = new IoControlDebugIO
}

class IoControl extends Module {
  def EndianConvert(data: UInt) = {
    // do nothing
    data
  }

  def leftRotate(i: UInt, n: Int): UInt = {
    val w = i.getWidth
    if (n > 0) {
      Cat(i(w - n - 1, 0), i(w - 1, w - n))
    } else {
      i
    }
  }

  val io = IO(new IoControlIO)

  // SRAM控制寄存器
  val base_ram_addr_r = RegInit(0.U(20.W))
  val base_ram_be_n_r = RegInit(0.U(4.W))
  val base_ram_ce_n_r = RegInit(true.B)
  val base_ram_oe_n_r = RegInit(true.B)
  val base_ram_we_n_r = RegInit(true.B)
  val base_ram_data_r = RegInit(0.U(32.W))

  val ext_ram_addr_r = RegInit(0.U(20.W))
  val ext_ram_be_n_r = RegInit(0.U(4.W))
  val ext_ram_ce_n_r = RegInit(true.B)
  val ext_ram_oe_n_r = RegInit(true.B)
  val ext_ram_we_n_r = RegInit(true.B)
  val ext_ram_data_r = RegInit(0.U(32.W))

  // 连接控制信号
  io.base_ram_ctrl.ctrl.addr := base_ram_addr_r
  io.base_ram_ctrl.ctrl.be_n := base_ram_be_n_r
  io.base_ram_ctrl.ctrl.ce_n := base_ram_ce_n_r
  io.base_ram_ctrl.ctrl.oe_n := base_ram_oe_n_r
  io.base_ram_ctrl.ctrl.we_n := base_ram_we_n_r

  io.ext_ram_ctrl.ctrl.addr := ext_ram_addr_r
  io.ext_ram_ctrl.ctrl.be_n := ext_ram_be_n_r
  io.ext_ram_ctrl.ctrl.ce_n := ext_ram_ce_n_r
  io.ext_ram_ctrl.ctrl.oe_n := ext_ram_oe_n_r
  io.ext_ram_ctrl.ctrl.we_n := ext_ram_we_n_r

  // 三态门控制：只有写使能时才驱动数据线
  io.base_ram_ctrl.data.data_out := base_ram_data_r
  io.base_ram_ctrl.data.data_en  := !base_ram_we_n_r

  io.ext_ram_ctrl.data.data_out := ext_ram_data_r
  io.ext_ram_ctrl.data.data_en  := !ext_ram_we_n_r

  // 状态机定义（使用独热码）
  val STAGE_WD = 12
  val stage_i  = RegInit(1.U(STAGE_WD.W))
  val stage_d  = RegInit(1.U(STAGE_WD.W))

  // 请求寄存器
  val ird_req_r = RegInit(false.B)
  val drd_req_r = RegInit(false.B)
  val dwr_req_r = RegInit(false.B)

  val ird_addr_r  = Reg(UInt(32.W))
  val drd_addr_r  = Reg(UInt(32.W))
  val dwr_addr_r  = Reg(UInt(32.W))
  val dwr_data_r  = Reg(UInt(32.W))
  val dwr_wstrb_r = Reg(UInt(4.W))

  // 偏移量寄存器
  val icache_offset = RegInit(0.U(4.W))

  // 响应数据
  val icacheline_new = RegInit(VecInit(Seq.fill(8)(0.U(32.W))))
  val ireload        = RegInit(false.B)
  val drd_data       = RegInit(0.U(32.W))
  val dreload        = RegInit(false.B)

  // 地址解析
  def isBaseAddr(addr:      UInt): Bool = addr(31, 22) === "b1000_0000_00".U(10.W)
  def isExtAddr(addr:       UInt): Bool = addr(31, 22) === "b1000_0000_01".U(10.W)
  def isUartDataAddr(addr:  UInt): Bool = addr === "hBFD003F8".U(32.W)
  def isUartStateAddr(addr: UInt): Bool = addr === "hBFD003FC".U(32.W)

  // Ready信号
  io.icache_read_req.ready := stage_i(0) && !ird_req_r && (
    (io.icache_read_req.valid && isBaseAddr(io.icache_read_req.bits.addr)) ||
      (io.icache_read_req.valid && isExtAddr(io.icache_read_req.bits.addr)) ||
      (io.icache_read_req.valid && !isBaseAddr(io.icache_read_req.bits.addr) && !isExtAddr(
        io.icache_read_req.bits.addr
      ))
  )

  io.dcache_read_req.ready := stage_d(0) && !drd_req_r && !dwr_req_r && (
    (io.dcache_read_req.valid && isBaseAddr(io.dcache_read_req.bits.addr)) ||
      (io.dcache_read_req.valid && isExtAddr(io.dcache_read_req.bits.addr)) ||
      (io.dcache_read_req.valid && (isUartDataAddr(io.dcache_read_req.bits.addr) || isUartStateAddr(
        io.dcache_read_req.bits.addr
      ))) ||
      (io.dcache_read_req.valid && !isBaseAddr(io.dcache_read_req.bits.addr) && !isExtAddr(
        io.dcache_read_req.bits.addr
      ) &&
        !isUartDataAddr(io.dcache_read_req.bits.addr) && !isUartStateAddr(io.dcache_read_req.bits.addr))
  )

  io.dcache_write_req.ready := stage_d(0) && !drd_req_r && !dwr_req_r && (
    (io.dcache_write_req.valid && isBaseAddr(io.dcache_write_req.bits.addr)) ||
      (io.dcache_write_req.valid && isExtAddr(io.dcache_write_req.bits.addr)) ||
      (io.dcache_write_req.valid && isUartDataAddr(io.dcache_write_req.bits.addr) && !io.txd.uart_busy) ||
      (io.dcache_write_req.valid && !isBaseAddr(io.dcache_write_req.bits.addr) && !isExtAddr(
        io.dcache_write_req.bits.addr
      ) &&
        !isUartDataAddr(io.dcache_write_req.bits.addr))
  )

  // 响应信号
  io.icache_read_resp.valid     := ireload
  io.icache_read_resp.bits.data := icacheline_new.asUInt
  io.dcache_read_resp.valid     := dreload
  io.dcache_read_resp.bits.data := drd_data

  // 清除响应
  when(io.icache_read_resp.fire) {
    ireload := false.B
  }
  when(io.dcache_read_resp.fire) {
    dreload := false.B
  }

  // Debug信号
  io.debug.base_state        := stage_i
  io.debug.ext_state         := stage_d
  io.debug.icache_read_base  := ird_req_r && isBaseAddr(ird_addr_r)
  io.debug.icache_read_ext   := ird_req_r && isExtAddr(ird_addr_r)
  io.debug.dcache_read_base  := drd_req_r && isBaseAddr(drd_addr_r)
  io.debug.dcache_read_ext   := drd_req_r && isExtAddr(drd_addr_r)
  io.debug.dcache_write_base := dwr_req_r && isBaseAddr(dwr_addr_r)
  io.debug.dcache_write_ext  := dwr_req_r && isExtAddr(dwr_addr_r)
  io.debug.icache_read_addr  := ird_addr_r(21, 2)
  io.debug.dcache_read_addr  := drd_addr_r(21, 2)
  io.debug.dcache_write_addr := dwr_addr_r(21, 2)

  // Base RAM状态机（处理icache）
  when(stage_i(0)) {
    ireload                  := false.B
    icacheline_new.foreach(_ := 0.U)
    ird_req_r                := io.icache_read_req.fire && isBaseAddr(io.icache_read_req.bits.addr)
    when(io.icache_read_req.fire && isBaseAddr(io.icache_read_req.bits.addr)) {
      ird_addr_r    := io.icache_read_req.bits.addr
      stage_i       := stage_i << 1
      icache_offset := 0.U
    }
  }.elsewhen(stage_i(1)) {
    base_ram_addr_r := ird_addr_r(21, 2) + icache_offset
    base_ram_be_n_r := 0.U
    base_ram_ce_n_r := false.B
    base_ram_oe_n_r := false.B
    base_ram_we_n_r := true.B
    base_ram_data_r := 0.U
    stage_i         := stage_i << 1
  }.elsewhen(stage_i(2)) {
    stage_i := stage_i << 1
  }.elsewhen(stage_i(3)) {
    icacheline_new(icache_offset) := EndianConvert(io.base_ram_ctrl.data.data_in)
    when(icache_offset === 7.U) {
      base_ram_addr_r := 0.U
      base_ram_be_n_r := 0.U
      base_ram_ce_n_r := true.B
      base_ram_oe_n_r := true.B
      base_ram_we_n_r := true.B
      base_ram_data_r := 0.U
      stage_i         := stage_i << 1
    }.otherwise {
      base_ram_addr_r := ird_addr_r(21, 2) + icache_offset + 1.U
      icache_offset   := icache_offset + 1.U
      stage_i         := stage_i >> 1
    }
  }.elsewhen(stage_i(4)) {
    stage_i := stage_i << 3
  }.elsewhen(stage_i(7)) {
    when(ird_req_r) {
      ireload := true.B
    }
    stage_i := 1.U
  }.otherwise {
    stage_i := 1.U
    ireload := false.B
  }

  // Ext RAM状态机（处理dcache）
  when(stage_d(0)) {
    dreload  := false.B
    drd_data := 0.U
    drd_req_r := io.dcache_read_req.fire && (isExtAddr(io.dcache_read_req.bits.addr) || isBaseAddr(
      io.dcache_read_req.bits.addr
    ))
    dwr_req_r := io.dcache_write_req.fire && (isExtAddr(io.dcache_write_req.bits.addr) || isBaseAddr(
      io.dcache_write_req.bits.addr
    ))

    when(io.dcache_read_req.fire) {
      drd_addr_r := io.dcache_read_req.bits.addr
    }
    when(io.dcache_write_req.fire) {
      dwr_addr_r  := io.dcache_write_req.bits.addr
      dwr_data_r  := io.dcache_write_req.bits.data
      dwr_wstrb_r := io.dcache_write_req.bits.byte_mask
    }

    when(
      (io.dcache_read_req.fire || io.dcache_write_req.fire) &&
        ((isExtAddr(io.dcache_read_req.bits.addr) || isExtAddr(io.dcache_write_req.bits.addr)) ||
          (isBaseAddr(io.dcache_read_req.bits.addr) || isBaseAddr(io.dcache_write_req.bits.addr)))
    ) {
      stage_d := stage_d << 1
    }
  }.elsewhen(stage_d(1)) {
    // 根据地址选择操作Base RAM还是Ext RAM
    val use_base = (drd_req_r && isBaseAddr(drd_addr_r)) || (dwr_req_r && isBaseAddr(dwr_addr_r))
    val use_ext  = (drd_req_r && isExtAddr(drd_addr_r)) || (dwr_req_r && isExtAddr(dwr_addr_r))

    when(use_ext) {
      ext_ram_addr_r := Mux(drd_req_r, drd_addr_r(21, 2), dwr_addr_r(21, 2))
      ext_ram_be_n_r := Mux(dwr_req_r, ~dwr_wstrb_r, 0.U)
      ext_ram_ce_n_r := false.B
      ext_ram_oe_n_r := !drd_req_r
      ext_ram_we_n_r := !dwr_req_r
      ext_ram_data_r := EndianConvert(dwr_data_r)
    }.elsewhen(use_base) {
      base_ram_addr_r := Mux(drd_req_r, drd_addr_r(21, 2), dwr_addr_r(21, 2))
      base_ram_be_n_r := Mux(dwr_req_r, ~dwr_wstrb_r, 0.U)
      base_ram_ce_n_r := false.B
      base_ram_oe_n_r := !drd_req_r
      base_ram_we_n_r := !dwr_req_r
      base_ram_data_r := EndianConvert(dwr_data_r)
    }
    stage_d := stage_d << 1
  }.elsewhen(stage_d(2)) {
    stage_d := stage_d << 1
  }.elsewhen(stage_d(3)) {
    val use_base = drd_req_r && isBaseAddr(drd_addr_r)
    val use_ext  = drd_req_r && isExtAddr(drd_addr_r)

    when(use_ext) {
      drd_data := EndianConvert(io.ext_ram_ctrl.data.data_in)
    }.elsewhen(use_base) {
      drd_data := EndianConvert(io.base_ram_ctrl.data.data_in)
    }

    when(drd_req_r || dwr_req_r) {
      dreload := true.B
    }

    // 清除控制信号
    when(isBaseAddr(drd_addr_r) || isBaseAddr(dwr_addr_r)) {
      base_ram_addr_r := 0.U
      base_ram_be_n_r := 0.U
      base_ram_ce_n_r := true.B
      base_ram_oe_n_r := true.B
      base_ram_we_n_r := true.B
      base_ram_data_r := 0.U
    }
    when(isExtAddr(drd_addr_r) || isExtAddr(dwr_addr_r)) {
      ext_ram_addr_r := 0.U
      ext_ram_be_n_r := 0.U
      ext_ram_ce_n_r := true.B
      ext_ram_oe_n_r := true.B
      ext_ram_we_n_r := true.B
      ext_ram_data_r := 0.U
    }

    stage_d := 1.U
  }.otherwise {
    stage_d := 1.U
    dreload := false.B
  }

  // 处理其他地址请求
  when(
    io.icache_read_req.fire && !isBaseAddr(io.icache_read_req.bits.addr) && !isExtAddr(io.icache_read_req.bits.addr)
  ) {
    icacheline_new.foreach(_ := 0.U)
    ireload                  := true.B
  }

  when(
    io.dcache_read_req.fire && !isBaseAddr(io.dcache_read_req.bits.addr) && !isExtAddr(io.dcache_read_req.bits.addr)
  ) {
    drd_data := 0.U
    dreload  := true.B
  }

  // UART部分
  val uart_buffer = Reg(Vec(UART_BUFFER_DEPTH, new UartBufferInfo))
  val uart_head   = RegInit(1.U(UART_BUFFER_DEPTH.W))
  val head_idx    = OHToUInt(uart_head)(log2Ceil(UART_BUFFER_DEPTH) - 1, 0).asUInt
  val uart_tail   = RegInit(1.U(UART_BUFFER_DEPTH.W))
  val tail_idx    = OHToUInt(uart_tail)(log2Ceil(UART_BUFFER_DEPTH) - 1, 0).asUInt
  val maybe_full  = RegInit(false.B)
  val uart_full   = uart_head === uart_tail && maybe_full
  val uart_empty  = uart_head === uart_tail && !maybe_full

  // UART接收
  when(io.rxd.uart_ready && !uart_full) {
    uart_buffer(tail_idx).data := io.rxd.uart_data
    uart_tail                  := leftRotate(uart_tail, 1)
    maybe_full                 := true.B
    io.rxd.uart_clear          := true.B
  }.otherwise {
    io.rxd.uart_clear := false.B
  }

  // UART读取
  when(io.dcache_read_req.fire && isUartDataAddr(io.dcache_read_req.bits.addr)) {
    when(!uart_empty) {
      drd_data   := Cat(0.U(24.W), uart_buffer(head_idx).data)
      uart_head  := leftRotate(uart_head, 1)
      maybe_full := false.B
    }.otherwise {
      drd_data := 0.U(32.W)
    }
    dreload := true.B
  }

  // UART状态读取
  when(io.dcache_read_req.fire && isUartStateAddr(io.dcache_read_req.bits.addr)) {
    drd_data := Cat(0.U(30.W), !uart_empty, !io.txd.uart_busy)
    dreload  := true.B
  }

  // UART写入
  val txd_start_reg = RegInit(false.B)
  io.txd.uart_start := txd_start_reg
  io.txd.uart_data  := io.dcache_write_req.bits.data(7, 0)

  when(io.dcache_write_req.fire && isUartDataAddr(io.dcache_write_req.bits.addr) && !io.txd.uart_busy) {
    txd_start_reg := true.B
  }.otherwise {
    txd_start_reg := false.B
  }

  // 复位
  when(reset.asBool) {
    stage_i       := 1.U
    stage_d       := 1.U
    ird_req_r     := false.B
    drd_req_r     := false.B
    dwr_req_r     := false.B
    icache_offset := 0.U
    ireload       := false.B
    dreload       := false.B
    uart_buffer.foreach(i => {
      i.data := 0.U
    })
  }
}
