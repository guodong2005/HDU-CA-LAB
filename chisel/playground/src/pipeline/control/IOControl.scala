package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.pipeline._

class SramCtrlInfo extends Bundle {
  val data_out = UInt(32.W)
  val addr     = UInt(20.W)
  val be_n     = UInt(4.W)
  val ce_n     = Bool()
  val oe_n     = Bool()
  val we_n     = Bool()
  val data_en  = Bool()

  def idle(): Unit = {
    data_out := 0.U
    addr     := 0.U
    be_n     := "b1111".U
    ce_n     := true.B
    oe_n     := true.B
    we_n     := true.B
    data_en  := false.B
  }

  def read(rAddr: UInt): Unit = {
    data_out := 0.U
    addr     := rAddr
    be_n     := "b0000".U
    ce_n     := false.B
    oe_n     := false.B
    we_n     := true.B
    data_en  := false.B
  }

  def write(wAddr: UInt, wData: UInt, wBe_n: UInt, weState: Bool = true.B): Unit = {
    data_out := wData
    addr     := wAddr
    be_n     := wBe_n
    ce_n     := false.B
    oe_n     := true.B
    we_n     := weState
    data_en  := true.B
  }
}

class SramCtrlIO extends Bundle {
  val data_in = Input(UInt(32.W))
  val ctrl    = Output(new SramCtrlInfo)
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
}

// 简化的请求类型定义
class ReadRequest extends Bundle {
  val valid = Bool()
  val addr  = UInt(32.W)
}

class WriteRequest extends Bundle {
  val valid = Bool()
  val addr  = UInt(32.W)
  val data  = UInt(32.W)
  val mask  = UInt(4.W)
}

class IoControl extends Module {
  val io = IO(new IoControlIO)

  def EndianConvert(data: UInt) = data

  def leftRotate(i: UInt, n: Int): UInt = {
    val w = i.getWidth
    if (n > 0) {
      Cat(i(w - n - 1, 0), i(w - 1, w - n))
    } else {
      i
    }
  }

  val SRAM_DELAY = 5
  io.rxd.uart_clear := io.rxd.uart_ready

  // ========== SRAM控制寄存器 ==========
  val base_ram_ctrl = Reg(new SramCtrlInfo)
  val ext_ram_ctrl  = Reg(new SramCtrlInfo)
  io.base_ram_ctrl.ctrl <> base_ram_ctrl
  io.ext_ram_ctrl.ctrl <> ext_ram_ctrl

  // ========== 地址解析函数 ==========
  def isBaseAddr(addr:      UInt): Bool = addr(31, 22) === "h200".U(10.W)
  def isExtAddr(addr:       UInt): Bool = addr(31, 22) === "h201".U(10.W)
  def isUartDataAddr(addr:  UInt): Bool = addr === "hBFD003F8".U(32.W)
  def isUartStateAddr(addr: UInt): Bool = addr === "hBFD003FC".U(32.W)
  def isUartAddr(addr:      UInt): Bool = isUartDataAddr(addr) || isUartStateAddr(addr)

  // ========== 请求类型枚举 ==========
  val reqNone :: reqIcache :: reqDcacheRead :: reqDcacheWrite :: Nil = Enum(4)

  // ========== 响应缓冲区 ==========
  val icache_buffer     = RegInit(VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W))))
  val icache_data_valid = RegInit(false.B)
  val dcache_buffer     = RegInit(0.U(32.W))
  val dcache_data_valid = RegInit(false.B)

  // ========== BASE RAM 请求管理 ==========
  val regBaseIcacheReq = RegInit(0.U.asTypeOf(new ReadRequest))
  val regBaseDcacheReq = RegInit(0.U.asTypeOf(new ReadRequest))

  // ========== EXT RAM 请求管理 (只有DCache) ==========
  val regExtDcacheReadReq  = RegInit(0.U.asTypeOf(new ReadRequest))
  val regExtDcacheWriteReq = RegInit(0.U.asTypeOf(new WriteRequest))

  // ========== UART 请求管理 (只有DCache) ==========
  val regUartDcacheReadReq  = RegInit(0.U.asTypeOf(new ReadRequest))
  val regUartDcacheWriteReq = RegInit(0.U.asTypeOf(new WriteRequest))

  // ========== 简化的 ready 信号 ==========
  // icache: 只访问BASE RAM或非法地址
  io.icache_read_req.ready := !icache_data_valid && (
    (io.icache_read_req.valid && isBaseAddr(io.icache_read_req.bits.addr) && !regBaseIcacheReq.valid) ||
      (io.icache_read_req.valid && !isBaseAddr(io.icache_read_req.bits.addr)) // 非BASE地址直接处理
  )

  // dcache read: BASE或EXT或UART或特殊地址
  io.dcache_read_req.ready := !dcache_data_valid && (
    (io.dcache_read_req.valid && isBaseAddr(io.dcache_read_req.bits.addr) && !regBaseDcacheReq.valid) ||
      (io.dcache_read_req.valid && isExtAddr(io.dcache_read_req.bits.addr) && !regExtDcacheReadReq.valid) ||
      (io.dcache_read_req.valid && isUartAddr(io.dcache_read_req.bits.addr) && !regUartDcacheReadReq.valid) ||
      (io.dcache_read_req.valid && !isBaseAddr(io.dcache_read_req.bits.addr) &&
        !isExtAddr(io.dcache_read_req.bits.addr) && !isUartAddr(io.dcache_read_req.bits.addr))
  )

  // dcache write: EXT或UART或特殊地址
  io.dcache_write_req.ready := !dcache_data_valid && (
    (io.dcache_write_req.valid && isExtAddr(io.dcache_write_req.bits.addr) && !regExtDcacheWriteReq.valid) ||
      (io.dcache_write_req.valid && isUartDataAddr(io.dcache_write_req.bits.addr) && !regUartDcacheWriteReq.valid) ||
      (io.dcache_write_req.valid && !isExtAddr(io.dcache_write_req.bits.addr) &&
        !isUartDataAddr(io.dcache_write_req.bits.addr))
  )

  // ========== 请求锁存 ==========
  // BASE RAM ICache 请求
  when(io.icache_read_req.fire && isBaseAddr(io.icache_read_req.bits.addr)) {
    regBaseIcacheReq.valid := true.B
    regBaseIcacheReq.addr  := io.icache_read_req.bits.addr
  }

  // BASE RAM DCache 请求
  when(io.dcache_read_req.fire && isBaseAddr(io.dcache_read_req.bits.addr)) {
    regBaseDcacheReq.valid := true.B
    regBaseDcacheReq.addr  := io.dcache_read_req.bits.addr
  }

  // EXT RAM DCache 读请求
  when(io.dcache_read_req.fire && isExtAddr(io.dcache_read_req.bits.addr)) {
    regExtDcacheReadReq.valid := true.B
    regExtDcacheReadReq.addr  := io.dcache_read_req.bits.addr
  }

  // EXT RAM DCache 写请求
  when(io.dcache_write_req.fire && isExtAddr(io.dcache_write_req.bits.addr)) {
    regExtDcacheWriteReq.valid := true.B
    regExtDcacheWriteReq.addr  := io.dcache_write_req.bits.addr
    regExtDcacheWriteReq.data  := io.dcache_write_req.bits.data
    regExtDcacheWriteReq.mask  := io.dcache_write_req.bits.byte_mask
  }

  // UART DCache 读请求
  when(io.dcache_read_req.fire && isUartAddr(io.dcache_read_req.bits.addr)) {
    regUartDcacheReadReq.valid := true.B
    regUartDcacheReadReq.addr  := io.dcache_read_req.bits.addr
  }

  // UART DCache 写请求
  when(io.dcache_write_req.fire && isUartDataAddr(io.dcache_write_req.bits.addr)) {
    regUartDcacheWriteReq.valid := true.B
    regUartDcacheWriteReq.addr  := io.dcache_write_req.bits.addr
    regUartDcacheWriteReq.data  := io.dcache_write_req.bits.data
  }

  // ========== BASE RAM 状态机 ==========
  val baseIDLE :: baseREAD :: Nil = Enum(2)
  val base_state                  = RegInit(baseIDLE)
  val base_wait_counter           = RegInit(0.U(4.W))
  val base_req_type               = RegInit(reqNone)
  val base_word_counter           = RegInit(0.U(3.W))

  switch(base_state) {
    is(baseIDLE) {
      // 仲裁：dcache_read > icache
      when(regBaseDcacheReq.valid) {
        base_req_type := reqDcacheRead
        base_ram_ctrl.read(regBaseDcacheReq.addr(21, 2))
        base_wait_counter := 0.U
        base_state        := baseREAD
      }.elsewhen(regBaseIcacheReq.valid) {
        base_req_type := reqIcache
        base_ram_ctrl.read(regBaseIcacheReq.addr(21, 2))
        base_wait_counter := 0.U
        base_word_counter := 0.U
        base_state        := baseREAD
      }.otherwise {
        base_ram_ctrl.idle()
      }
    }

    is(baseREAD) {
      when(base_req_type === reqIcache) {
        // ICache 多字读取
        when(base_word_counter === (FETCH_WIDTH - 1).U) {
          when(base_wait_counter === SRAM_DELAY.U) {
            icache_buffer(base_word_counter) := EndianConvert(io.base_ram_ctrl.data_in)
            base_ram_ctrl.idle()
            icache_data_valid      := true.B
            regBaseIcacheReq.valid := false.B
            base_state             := baseIDLE
            base_req_type          := reqNone
          }.otherwise {
            base_wait_counter := base_wait_counter + 1.U
          }
        }.otherwise {
          when(base_wait_counter === SRAM_DELAY.U) {
            icache_buffer(base_word_counter) := EndianConvert(io.base_ram_ctrl.data_in)
            base_word_counter                := base_word_counter + 1.U
            base_ram_ctrl.read(base_ram_ctrl.addr + 1.U)
            base_wait_counter := 0.U
          }.otherwise {
            base_wait_counter := base_wait_counter + 1.U
          }
        }
      }.elsewhen(base_req_type === reqDcacheRead) {
        // DCache 单字读取
        when(base_wait_counter === SRAM_DELAY.U) {
          dcache_buffer := EndianConvert(io.base_ram_ctrl.data_in)
          base_ram_ctrl.idle()
          dcache_data_valid      := true.B
          regBaseDcacheReq.valid := false.B
          base_state             := baseIDLE
          base_req_type          := reqNone
        }.otherwise {
          base_wait_counter := base_wait_counter + 1.U
        }
      }
    }
  }

  // ========== EXT RAM 状态机 (只处理DCache) ==========
  val extIDLE :: extREAD :: extWRITE :: Nil = Enum(3)
  val ext_state                             = RegInit(extIDLE)
  val ext_wait_counter                      = RegInit(0.U(4.W))

  switch(ext_state) {
    is(extIDLE) {
      // 仲裁：dcache_write > dcache_read
      when(regExtDcacheWriteReq.valid) {
        ext_ram_ctrl.write(
          regExtDcacheWriteReq.addr(21, 2),
          EndianConvert(regExtDcacheWriteReq.data),
          regExtDcacheWriteReq.mask.asUInt.do_unary_~,
          false.B
        )
        ext_wait_counter := 0.U
        ext_state        := extWRITE
      }.elsewhen(regExtDcacheReadReq.valid) {
        ext_ram_ctrl.read(regExtDcacheReadReq.addr(21, 2))
        ext_wait_counter := 0.U
        ext_state        := extREAD
      }.otherwise {
        ext_ram_ctrl.idle()
      }
    }

    is(extREAD) {
      when(ext_wait_counter === SRAM_DELAY.U) {
        dcache_buffer := EndianConvert(io.ext_ram_ctrl.data_in)
        ext_ram_ctrl.idle()
        dcache_data_valid         := true.B
        regExtDcacheReadReq.valid := false.B
        ext_state                 := extIDLE
      }.otherwise {
        ext_wait_counter := ext_wait_counter + 1.U
      }
    }

    is(extWRITE) {
      when(ext_wait_counter < 2.U) {
        ext_wait_counter := ext_wait_counter + 1.U
      }.elsewhen(ext_wait_counter === 2.U) {
        // 第3个周期：将WE拉高
        ext_ram_ctrl.write(
          ext_ram_ctrl.addr,
          ext_ram_ctrl.data_out,
          ext_ram_ctrl.be_n,
          true.B
        )
        ext_wait_counter := ext_wait_counter + 1.U
      }.elsewhen(ext_wait_counter === SRAM_DELAY.U) {
        ext_ram_ctrl.idle()
        dcache_data_valid          := true.B
        regExtDcacheWriteReq.valid := false.B
        ext_state                  := extIDLE
      }.otherwise {
        ext_wait_counter := ext_wait_counter + 1.U
      }
    }
  }

  // ========== UART 缓冲区和控制信号 ==========
  val uart_buffer = RegInit(
    VecInit(
      Seq.fill(UART_BUFFER_DEPTH)(
        0.U.asTypeOf(new UartBufferInfo)
      )
    )
  )
  val uart_head  = RegInit(1.U(UART_BUFFER_DEPTH.W))
  val head_idx   = OHToUInt(uart_head)
  val uart_tail  = RegInit(1.U(UART_BUFFER_DEPTH.W))
  val tail_idx   = OHToUInt(uart_tail)
  val maybe_full = RegInit(false.B)
  val uart_full  = uart_head === uart_tail && maybe_full
  val uart_empty = uart_head === uart_tail && !maybe_full

  // TXD 控制信号
  val txd_uart_start = RegInit(false.B)
  val txd_uart_data  = RegInit(0.U(8.W))
  io.txd.uart_start := txd_uart_start
  io.txd.uart_data  := txd_uart_data

  // 用于UART状态机的辅助信号
  val dcache_write_uart      = regUartDcacheWriteReq.valid
  val dcache_read_uart       = regUartDcacheReadReq.valid && isUartDataAddr(regUartDcacheReadReq.addr)
  val dcache_read_uart_state = regUartDcacheReadReq.valid && isUartStateAddr(regUartDcacheReadReq.addr)
  val read_valid             = !uart_empty
  val read_data              = uart_buffer(head_idx).data
  val read_req               = RegInit(false.B)
  val dcache_write_complete  = RegInit(false.B)
  val dcache_read_ready      = RegInit(false.B)

  // ========== UART 状态机 ==========
  val uIDLE :: uWRITE :: uREAD :: Nil = Enum(3)
  val uart_state                      = RegInit(uIDLE)

  switch(uart_state) {
    is(uIDLE) {
      when(dcache_write_uart && !io.txd.uart_busy) {
        txd_uart_start        := true.B
        txd_uart_data         := regUartDcacheWriteReq.data(7, 0)
        dcache_write_complete := true.B
        uart_state            := uWRITE
      }.elsewhen(dcache_read_uart && read_valid) {
        dcache_buffer     := Cat(0.U(24.W), read_data)
        dcache_data_valid := true.B
        dcache_read_ready := true.B
        read_req          := true.B
        uart_state        := uREAD
      }.elsewhen(dcache_read_uart && !read_valid) {
        // UART为空时读取，返回0
        dcache_buffer     := 0.U(32.W)
        dcache_data_valid := true.B
        dcache_read_ready := true.B
        read_req          := false.B
        uart_state        := uREAD
      }.elsewhen(dcache_read_uart_state) {
        dcache_buffer     := Cat(0.U(30.W), read_valid, !io.txd.uart_busy)
        dcache_data_valid := true.B
        dcache_read_ready := true.B
        uart_state        := uREAD
      }
    }
    is(uWRITE) {
      txd_uart_start              := false.B
      dcache_write_complete       := false.B
      dcache_data_valid           := true.B // 写完成，设置响应valid
      regUartDcacheWriteReq.valid := false.B // 清除写请求
      uart_state                  := uIDLE
    }
    is(uREAD) {
      dcache_data_valid := false.B
      dcache_read_ready := false.B
      // 如果读取了数据，更新UART缓冲区
      when(read_req) {
        uart_head  := leftRotate(uart_head, 1)
        maybe_full := false.B
      }
      read_req                   := false.B
      regUartDcacheReadReq.valid := false.B // 清除读请求
      uart_state                 := uIDLE
    }
  }

  // ========== UART 接收处理 ==========
  when(io.rxd.uart_ready && !uart_full) {
    uart_buffer(tail_idx).data := io.rxd.uart_data
    val new_tail = leftRotate(uart_tail, 1)
    uart_tail  := new_tail
    maybe_full := new_tail === uart_head
  }

  // ========== 其他特殊地址处理 ==========
  // 处理既不是BASE/EXT/UART的非法地址
  when(io.dcache_read_req.fire) {
    when(
      !isBaseAddr(io.dcache_read_req.bits.addr) &&
        !isExtAddr(io.dcache_read_req.bits.addr) &&
        !isUartAddr(io.dcache_read_req.bits.addr)
    ) {
      dcache_buffer     := 0.U
      dcache_data_valid := true.B
    }
  }

  when(io.dcache_write_req.fire) {
    when(
      !isExtAddr(io.dcache_write_req.bits.addr) &&
        !isUartDataAddr(io.dcache_write_req.bits.addr)
    ) {
      dcache_data_valid := true.B
    }
  }

  // ========== 响应接口 ==========
  io.icache_read_resp.valid     := icache_data_valid
  io.icache_read_resp.bits.data := icache_buffer.asUInt
  io.dcache_read_resp.valid     := dcache_data_valid
  io.dcache_read_resp.bits.data := dcache_buffer

  // 清除响应 valid
  when(io.icache_read_resp.fire) {
    icache_data_valid := false.B
  }
  when(io.dcache_read_resp.fire) {
    dcache_data_valid := false.B
  }

  // ========== 复位处理 ==========
  when(reset.asBool) {
    base_ram_ctrl.idle()
    ext_ram_ctrl.idle()

    // 清除所有请求寄存器
    regBaseIcacheReq.valid      := false.B
    regBaseDcacheReq.valid      := false.B
    regExtDcacheReadReq.valid   := false.B
    regExtDcacheWriteReq.valid  := false.B
    regUartDcacheReadReq.valid  := false.B
    regUartDcacheWriteReq.valid := false.B

    // 状态机复位
    base_state        := baseIDLE
    base_wait_counter := 0.U
    base_req_type     := reqNone
    base_word_counter := 0.U
    ext_state         := extIDLE
    ext_wait_counter  := 0.U
    uart_state        := uIDLE

    // 响应缓冲复位
    icache_data_valid := false.B
    dcache_data_valid := false.B

    // UART 复位
    uart_buffer.foreach(i => i.data := 0.U)
    txd_uart_start        := false.B
    txd_uart_data         := 0.U
    maybe_full            := false.B
    uart_head             := 1.U(UART_BUFFER_DEPTH.W)
    uart_tail             := 1.U(UART_BUFFER_DEPTH.W)
    read_req              := false.B
    dcache_write_complete := false.B
    dcache_read_ready     := false.B
  }
}
