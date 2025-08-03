package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.pipeline._

class SramCtrlInfo extends Bundle {
  def idle(): Unit = {
    data_out := 0.U
    addr     := 0.U
    be_n     := "b1111".U
    ce_n     := true.B
    oe_n     := true.B
    we_n     := true.B
  }

  def read(rAddr: UInt): Unit = {
    data_out := 0.U
    addr     := rAddr
    be_n     := "b0000".U
    ce_n     := false.B
    oe_n     := false.B
    we_n     := true.B
  }

  def write(wAddr: UInt, wData: UInt, wBe_n: UInt): Unit = {
    data_out := wData
    addr     := wAddr
    be_n     := wBe_n
    ce_n     := false.B
    oe_n     := true.B
    we_n     := false.B
  }

  val data_out = UInt(32.W)
  val addr     = UInt(20.W)
  val be_n     = UInt(4.W)
  val ce_n     = Bool()
  val oe_n     = Bool()
  val we_n     = Bool()
}

class SramCtrlIO extends Bundle {
  val data_in = Input(UInt(32.W))
  val ctrl    = Output(new SramCtrlInfo)
}

class IoControlDebugIO extends Bundle {
  val base_state        = Output(UInt(3.W))
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

  val io            = IO(new IoControlIO)
  val base_ram_ctrl = Reg(new SramCtrlInfo)
  val ext_ram_ctrl  = Reg(new SramCtrlInfo)
  io.base_ram_ctrl.ctrl <> base_ram_ctrl
  io.ext_ram_ctrl.ctrl <> ext_ram_ctrl

  // 状态定义
  val sIDLE :: sREAD :: sWRITE :: Nil = Enum(3)
  val base_state                      = RegInit(sIDLE)
  val ext_state                       = RegInit(sIDLE)

  // 计数器和字索引
  val base_counter  = RegInit(0.U(4.W))
  val ext_counter   = RegInit(0.U(4.W))
  val base_word_idx = RegInit(0.U(log2Ceil(FETCH_WIDTH).W))
  val ext_word_idx  = RegInit(0.U(log2Ceil(FETCH_WIDTH).W))

  // 请求存储寄存器
  val icache_req_addr  = Reg(UInt(32.W))
  val icache_req_valid = RegInit(false.B)

  val dcache_read_req_addr  = Reg(UInt(32.W))
  val dcache_read_req_valid = RegInit(false.B)

  val dcache_write_req_addr      = Reg(UInt(32.W))
  val dcache_write_req_data      = Reg(UInt(32.W))
  val dcache_write_req_byte_mask = Reg(UInt(4.W))
  val dcache_write_req_valid     = RegInit(false.B)

  // 响应缓冲
  val icache_buffer     = RegInit(VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W))))
  val icache_data_valid = RegInit(false.B)
  val dcache_buffer     = RegInit(0.U(32.W))
  val dcache_data_valid = RegInit(false.B)

  // 地址类型判断函数
  def isBaseAddr(addr:      UInt): Bool = addr(31, 22) === "b1000_0000_00".U(10.W)
  def isExtAddr(addr:       UInt): Bool = addr(31, 22) === "b1000_0000_01".U(10.W)
  def isUartDataAddr(addr:  UInt): Bool = addr === "hBFD003F8".U(32.W)
  def isUartStateAddr(addr: UInt): Bool = addr === "hBFD003FC".U(32.W)

  // 解析存储的请求地址类型
  val icache_read_base  = icache_req_valid && isBaseAddr(icache_req_addr)
  val icache_read_ext   = icache_req_valid && isExtAddr(icache_req_addr)
  val icache_read_other = icache_req_valid && !isBaseAddr(icache_req_addr) && !isExtAddr(icache_req_addr)

  val dcache_read_base       = dcache_read_req_valid && isBaseAddr(dcache_read_req_addr)
  val dcache_read_ext        = dcache_read_req_valid && isExtAddr(dcache_read_req_addr)
  val dcache_read_uart       = dcache_read_req_valid && isUartDataAddr(dcache_read_req_addr)
  val dcache_read_uart_state = dcache_read_req_valid && isUartStateAddr(dcache_read_req_addr)
  val dcache_read_other = dcache_read_req_valid && !isBaseAddr(dcache_read_req_addr) &&
    !isExtAddr(dcache_read_req_addr) && !isUartDataAddr(dcache_read_req_addr) &&
    !isUartStateAddr(dcache_read_req_addr)

  val dcache_write_base = dcache_write_req_valid && isBaseAddr(dcache_write_req_addr)
  val dcache_write_ext  = dcache_write_req_valid && isExtAddr(dcache_write_req_addr)
  val dcache_write_uart = dcache_write_req_valid && isUartDataAddr(dcache_write_req_addr)
  val dcache_write_other = dcache_write_req_valid && !isBaseAddr(dcache_write_req_addr) &&
    !isExtAddr(dcache_write_req_addr) && !isUartDataAddr(dcache_write_req_addr)

  // Ready信号 - 基于请求寄存器状态和目标内存状态
  io.icache_read_req.ready := !icache_req_valid && (
    (io.icache_read_req.valid && isBaseAddr(io.icache_read_req.bits.addr) && base_state === sIDLE) ||
      (io.icache_read_req.valid && isExtAddr(io.icache_read_req.bits.addr) && ext_state === sIDLE) ||
      (io.icache_read_req.valid && !isBaseAddr(io.icache_read_req.bits.addr) && !isExtAddr(
        io.icache_read_req.bits.addr
      ))
  )

  io.dcache_read_req.ready := !dcache_read_req_valid && (
    (io.dcache_read_req.valid && isBaseAddr(io.dcache_read_req.bits.addr) && base_state === sIDLE) ||
      (io.dcache_read_req.valid && isExtAddr(io.dcache_read_req.bits.addr) && ext_state === sIDLE) ||
      (io.dcache_read_req.valid && (isUartDataAddr(io.dcache_read_req.bits.addr) || isUartStateAddr(
        io.dcache_read_req.bits.addr
      ))) ||
      (io.dcache_read_req.valid && !isBaseAddr(io.dcache_read_req.bits.addr) && !isExtAddr(
        io.dcache_read_req.bits.addr
      ) &&
        !isUartDataAddr(io.dcache_read_req.bits.addr) && !isUartStateAddr(io.dcache_read_req.bits.addr))
  )

  io.dcache_write_req.ready := !dcache_write_req_valid && (
    (io.dcache_write_req.valid && isBaseAddr(io.dcache_write_req.bits.addr) && base_state === sIDLE) ||
      (io.dcache_write_req.valid && isExtAddr(io.dcache_write_req.bits.addr) && ext_state === sIDLE) ||
      (io.dcache_write_req.valid && isUartDataAddr(io.dcache_write_req.bits.addr) && !io.txd.uart_busy) ||
      (io.dcache_write_req.valid && !isBaseAddr(io.dcache_write_req.bits.addr) && !isExtAddr(
        io.dcache_write_req.bits.addr
      ) &&
        !isUartDataAddr(io.dcache_write_req.bits.addr))
  )

  // 捕获请求信息（握手成功时）
  when(io.icache_read_req.fire) {
    icache_req_addr  := io.icache_read_req.bits.addr
    icache_req_valid := true.B
  }

  when(io.dcache_read_req.fire) {
    dcache_read_req_addr  := io.dcache_read_req.bits.addr
    dcache_read_req_valid := true.B
  }

  when(io.dcache_write_req.fire) {
    dcache_write_req_addr      := io.dcache_write_req.bits.addr
    dcache_write_req_data      := io.dcache_write_req.bits.data
    dcache_write_req_byte_mask := io.dcache_write_req.bits.byte_mask
    dcache_write_req_valid     := true.B
  }

  // 响应信号
  io.icache_read_resp.valid     := icache_data_valid
  io.icache_read_resp.bits.data := icache_buffer.asUInt
  io.dcache_read_resp.valid     := dcache_data_valid
  io.dcache_read_resp.bits.data := dcache_buffer

  // 清除响应valid信号
  when(io.icache_read_resp.fire) {
    icache_data_valid := false.B
  }
  when(io.dcache_read_resp.fire) {
    dcache_data_valid := false.B
  }

  // 处理其他地址的请求（立即响应0）
  when(icache_read_other) {
    icache_buffer     := VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W)))
    icache_data_valid := true.B
    icache_req_valid  := false.B
  }

  when(dcache_read_other) {
    dcache_buffer         := 0.U(32.W)
    dcache_data_valid     := true.B
    dcache_read_req_valid := false.B
  }

  when(dcache_write_other) {
    dcache_write_req_valid := false.B
  }

  // Debug信号
  io.debug.base_state        := base_state
  io.debug.icache_read_base  := icache_read_base
  io.debug.icache_read_ext   := icache_read_ext
  io.debug.dcache_read_base  := dcache_read_base
  io.debug.dcache_read_ext   := dcache_read_ext
  io.debug.dcache_write_base := dcache_write_base
  io.debug.dcache_write_ext  := dcache_write_ext
  io.debug.icache_read_addr  := icache_req_addr(21, 2)
  io.debug.dcache_read_addr  := dcache_read_req_addr(21, 2)
  io.debug.dcache_write_addr := dcache_write_req_addr(21, 2)

  // Base RAM状态机
  switch(base_state) {
    is(sIDLE) {
      // 写优先级最高
      when(dcache_write_base) {
        base_state   := sWRITE
        base_counter := 0.U
        base_ram_ctrl.write(
          dcache_write_req_addr(21, 2),
          EndianConvert(dcache_write_req_data),
          dcache_write_req_byte_mask.do_unary_~
        )
      }.elsewhen(dcache_read_base) {
        base_state   := sREAD
        base_counter := 0.U
        base_ram_ctrl.read(dcache_read_req_addr(21, 2))
      }.elsewhen(icache_read_base) {
        base_state    := sREAD
        base_counter  := 0.U
        base_word_idx := 0.U
        base_ram_ctrl.read(icache_req_addr(21, 2))
      }
    }

    is(sREAD) {
      when(base_counter < SRAM_DELAY.U) {
        base_counter := base_counter + 1.U
      }.otherwise {
        // 判断是icache还是dcache的读请求
        when(icache_read_base) {
          // icache读取多个字
          icache_buffer(base_word_idx) := EndianConvert(io.base_ram_ctrl.data_in)

          when(base_word_idx === (FETCH_WIDTH - 1).U) {
            base_ram_ctrl.idle()
            icache_data_valid := true.B
            icache_req_valid  := false.B // 清除请求
            base_state        := sIDLE
            base_counter      := 0.U // 重置计数器
          }.otherwise {
            base_ram_ctrl.read(base_ram_ctrl.addr + 1.U)
            base_counter  := 0.U // 重置计数器，重新等待SRAM_DELAY
            base_word_idx := base_word_idx + 1.U
          }
        }.otherwise {
          // dcache读取单个字
          dcache_buffer         := EndianConvert(io.base_ram_ctrl.data_in)
          dcache_data_valid     := true.B
          dcache_read_req_valid := false.B // 清除请求
          base_ram_ctrl.idle()
          base_state   := sIDLE
          base_counter := 0.U // 重置计数器
        }
      }
    }

    is(sWRITE) {
      when(base_counter < SRAM_DELAY.U) {
        base_counter := base_counter + 1.U
      }.otherwise {
        base_ram_ctrl.idle()
        dcache_write_req_valid := false.B // 清除请求
        base_state             := sIDLE
        base_counter           := 0.U // 重置计数器
      }
    }
  }

  // Ext RAM状态机（与Base RAM类似）
  switch(ext_state) {
    is(sIDLE) {
      when(dcache_write_ext) {
        ext_state   := sWRITE
        ext_counter := 0.U
        ext_ram_ctrl.write(
          dcache_write_req_addr(21, 2),
          EndianConvert(dcache_write_req_data),
          dcache_write_req_byte_mask.do_unary_~
        )
      }.elsewhen(dcache_read_ext) {
        ext_state   := sREAD
        ext_counter := 0.U
        ext_ram_ctrl.read(dcache_read_req_addr(21, 2))
      }.elsewhen(icache_read_ext) {
        ext_state    := sREAD
        ext_counter  := 0.U
        ext_word_idx := 0.U
        ext_ram_ctrl.read(icache_req_addr(21, 2))
      }
    }

    is(sREAD) {
      when(ext_counter < SRAM_DELAY.U) {
        ext_counter := ext_counter + 1.U
      }.otherwise {
        when(icache_read_ext) {
          icache_buffer(ext_word_idx) := EndianConvert(io.ext_ram_ctrl.data_in)

          when(ext_word_idx === (FETCH_WIDTH - 1).U) {
            ext_ram_ctrl.idle()
            icache_data_valid := true.B
            icache_req_valid  := false.B
            ext_state         := sIDLE
            ext_counter       := 0.U // 重置计数器
          }.otherwise {
            ext_ram_ctrl.read(ext_ram_ctrl.addr + 1.U)
            ext_counter  := 0.U // 重置计数器，重新等待SRAM_DELAY
            ext_word_idx := ext_word_idx + 1.U
          }
        }.otherwise {
          dcache_buffer         := EndianConvert(io.ext_ram_ctrl.data_in)
          dcache_data_valid     := true.B
          dcache_read_req_valid := false.B
          ext_ram_ctrl.idle()
          ext_state   := sIDLE
          ext_counter := 0.U // 重置计数器
        }
      }
    }

    is(sWRITE) {
      when(ext_counter < SRAM_DELAY.U) {
        ext_counter := ext_counter + 1.U
      }.otherwise {
        ext_ram_ctrl.idle()
        dcache_write_req_valid := false.B
        ext_state              := sIDLE
        ext_counter            := 0.U // 重置计数器
      }
    }
  }

  // UART缓冲区
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

  // UART读取处理
  when(dcache_read_uart) {
    when(!uart_empty) {
      dcache_buffer := Cat(0.U(24.W), uart_buffer(head_idx).data)
      uart_head     := leftRotate(uart_head, 1)
      maybe_full    := false.B
    }.otherwise {
      dcache_buffer := 0.U(32.W)
    }
    dcache_data_valid     := true.B
    dcache_read_req_valid := false.B
  }

  // UART状态读取
  when(dcache_read_uart_state) {
    dcache_buffer         := Cat(0.U(30.W), !uart_empty, !io.txd.uart_busy)
    dcache_data_valid     := true.B
    dcache_read_req_valid := false.B
  }

  // UART写入
  val txd_start_reg = RegInit(false.B)
  io.txd.uart_start := txd_start_reg
  io.txd.uart_data  := dcache_write_req_data(7, 0)

  when(dcache_write_uart && !io.txd.uart_busy) {
    txd_start_reg          := true.B
    dcache_write_req_valid := false.B
  }.otherwise {
    txd_start_reg := false.B
  }

  // 复位
  when(reset.asBool) {
    base_ram_ctrl.idle()
    ext_ram_ctrl.idle()
    uart_buffer.foreach(i => {
      i.data := 0.U
    })
    icache_req_valid       := false.B
    dcache_read_req_valid  := false.B
    dcache_write_req_valid := false.B
    base_counter           := 0.U
    ext_counter            := 0.U
    base_word_idx          := 0.U
    ext_word_idx           := 0.U
  }
}
