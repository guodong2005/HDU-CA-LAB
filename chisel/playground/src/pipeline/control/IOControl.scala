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
    data_en  := false.B // 数据总线禁用
  }

  def read(rAddr: UInt): Unit = {
    data_out := 0.U
    addr     := rAddr
    be_n     := "b0000".U
    ce_n     := false.B
    oe_n     := false.B
    we_n     := true.B
    data_en  := false.B // 读操作不驱动数据总线
  }

  def write(wAddr: UInt, wData: UInt, wBe_n: UInt, weState: Bool = true.B): Unit = {
    data_out := wData
    addr     := wAddr
    be_n     := wBe_n
    ce_n     := false.B
    oe_n     := true.B
    we_n     := weState // 可以控制WE的状态
    data_en  := true.B // 写操作驱动数据总线
  }

  val data_out = UInt(32.W)
  val addr     = UInt(20.W)
  val be_n     = UInt(4.W)
  val ce_n     = Bool()
  val oe_n     = Bool()
  val we_n     = Bool()
  val data_en  = Bool() // 新增：数据总线使能信号
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

  val SRAM_DELAY = 5

  // SRAM控制寄存器
  val base_ram_ctrl = Reg(new SramCtrlInfo)
  val ext_ram_ctrl  = Reg(new SramCtrlInfo)
  io.base_ram_ctrl.ctrl <> base_ram_ctrl
  io.ext_ram_ctrl.ctrl <> ext_ram_ctrl

  // 地址解析函数
  def isBaseAddr(addr:      UInt): Bool = addr(31, 22) === "h200".U(10.W)
  def isExtAddr(addr:       UInt): Bool = addr(31, 22) === "h201".U(10.W)
  def isUartDataAddr(addr:  UInt): Bool = addr === "hBFD003F8".U(32.W)
  def isUartStateAddr(addr: UInt): Bool = addr === "hBFD003FC".U(32.W)

  // 请求类型定义
  val reqNone :: reqIcache :: reqDcacheRead :: reqDcacheWrite :: Nil = Enum(4)

  // ========== BASE RAM 状态机 ==========
  val baseIDLE :: baseREAD :: baseWRITE :: Nil = Enum(3)
  val base_state                               = RegInit(baseIDLE)
  val base_wait_counter                        = RegInit(0.U(4.W))
  val base_req_type                            = RegInit(reqNone)

  // BASE RAM 请求缓存
  val base_icache_req    = RegInit(false.B)
  val base_icache_addr   = RegInit(0.U(32.W))
  val base_icache_offset = RegInit(0.U(3.W))

  val base_dcache_read_req  = RegInit(false.B)
  val base_dcache_read_addr = RegInit(0.U(32.W))

  val base_dcache_write_req  = RegInit(false.B)
  val base_dcache_write_addr = RegInit(0.U(32.W))
  val base_dcache_write_data = RegInit(0.U(32.W))
  val base_dcache_write_mask = RegInit(0.U(4.W))

  // ========== EXT RAM 状态机 ==========
  val extIDLE :: extREAD :: extWRITE :: Nil = Enum(3)
  val ext_state                             = RegInit(extIDLE)
  val ext_wait_counter                      = RegInit(0.U(4.W))
  val ext_req_type                          = RegInit(reqNone)

  // EXT RAM 请求缓存
  val ext_icache_req    = RegInit(false.B)
  val ext_icache_addr   = RegInit(0.U(32.W))
  val ext_icache_offset = RegInit(0.U(3.W))

  val ext_dcache_read_req  = RegInit(false.B)
  val ext_dcache_read_addr = RegInit(0.U(32.W))

  val ext_dcache_write_req  = RegInit(false.B)
  val ext_dcache_write_addr = RegInit(0.U(32.W))
  val ext_dcache_write_data = RegInit(0.U(32.W))
  val ext_dcache_write_mask = RegInit(0.U(4.W))

  // ========== 响应缓冲区 ==========
  val icache_buffer         = RegInit(VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W))))
  val icache_data_valid     = RegInit(false.B)
  val icache_resp_from_base = RegInit(false.B) // 标记响应来源

  val dcache_buffer     = RegInit(0.U(32.W))
  val dcache_data_valid = RegInit(false.B)

  // ========== UART 相关 ==========
  val uart_buffer = Reg(Vec(UART_BUFFER_DEPTH, new UartBufferInfo))
  val uart_head   = RegInit(1.U(UART_BUFFER_DEPTH.W))
  val head_idx    = OHToUInt(uart_head)
  val uart_tail   = RegInit(1.U(UART_BUFFER_DEPTH.W))
  val tail_idx    = OHToUInt(uart_tail)
  val maybe_full  = RegInit(false.B)
  val uart_full   = uart_head === uart_tail && maybe_full
  val uart_empty  = uart_head === uart_tail && !maybe_full

  // UART 接收处理
  when(io.rxd.uart_ready && !uart_full) {
    uart_buffer(tail_idx).data := io.rxd.uart_data
    uart_tail                  := leftRotate(uart_tail, 1)
    maybe_full                 := true.B
    io.rxd.uart_clear          := true.B
  }.otherwise {
    io.rxd.uart_clear := false.B
  }

  // TXD 控制
  val txd_uart_start = RegInit(false.B)
  val txd_uart_data  = RegInit(0.U(8.W))
  io.txd.uart_start := txd_uart_start
  io.txd.uart_data  := txd_uart_data

  // ========== 请求接收逻辑 ==========
  // 根据地址判断是否可以接收请求
  val icache_can_accept = Wire(Bool())
  val dcache_can_accept = Wire(Bool())

  icache_can_accept := false.B
  dcache_can_accept := false.B

  // ICache 请求接收条件
  when(io.icache_read_req.valid) {
    when(isBaseAddr(io.icache_read_req.bits.addr)) {
      icache_can_accept := base_state === baseIDLE && !base_icache_req
    }.elsewhen(isExtAddr(io.icache_read_req.bits.addr)) {
      icache_can_accept := ext_state === extIDLE && !ext_icache_req
    }.otherwise {
      icache_can_accept := true.B // 非法地址直接接收并响应
    }
  }

  // DCache 请求接收条件
  when(io.dcache_read_req.valid) {
    when(isBaseAddr(io.dcache_read_req.bits.addr)) {
      dcache_can_accept := base_state === baseIDLE && !base_dcache_read_req && !base_dcache_write_req
    }.elsewhen(isExtAddr(io.dcache_read_req.bits.addr)) {
      dcache_can_accept := ext_state === extIDLE && !ext_dcache_read_req && !ext_dcache_write_req
    }.otherwise {
      dcache_can_accept := true.B // UART 或非法地址
    }
  }

  when(io.dcache_write_req.valid) {
    when(isBaseAddr(io.dcache_write_req.bits.addr)) {
      dcache_can_accept := base_state === baseIDLE && !base_dcache_read_req && !base_dcache_write_req
    }.elsewhen(isExtAddr(io.dcache_write_req.bits.addr)) {
      dcache_can_accept := ext_state === extIDLE && !ext_dcache_read_req && !ext_dcache_write_req
    }.otherwise {
      dcache_can_accept := true.B // UART 或非法地址
    }
  }

  io.icache_read_req.ready  := icache_can_accept && !icache_data_valid
  io.dcache_read_req.ready  := dcache_can_accept && !dcache_data_valid
  io.dcache_write_req.ready := dcache_can_accept && !dcache_data_valid

  // ========== 请求分发逻辑 ==========
  // ICache 请求分发
  when(io.icache_read_req.fire) {
    when(isBaseAddr(io.icache_read_req.bits.addr)) {
      base_icache_req    := true.B
      base_icache_addr   := io.icache_read_req.bits.addr
      base_icache_offset := 0.U
    }.elsewhen(isExtAddr(io.icache_read_req.bits.addr)) {
      ext_icache_req    := true.B
      ext_icache_addr   := io.icache_read_req.bits.addr
      ext_icache_offset := 0.U
    }.otherwise {
      // 非法地址，直接生成响应
      icache_buffer     := VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W)))
      icache_data_valid := true.B
    }
  }

  // DCache 读请求分发
  when(io.dcache_read_req.fire) {
    when(isBaseAddr(io.dcache_read_req.bits.addr)) {
      base_dcache_read_req  := true.B
      base_dcache_read_addr := io.dcache_read_req.bits.addr
    }.elsewhen(isExtAddr(io.dcache_read_req.bits.addr)) {
      ext_dcache_read_req  := true.B
      ext_dcache_read_addr := io.dcache_read_req.bits.addr
    }.elsewhen(isUartDataAddr(io.dcache_read_req.bits.addr)) {
      when(!uart_empty) {
        dcache_buffer := Cat(0.U(24.W), uart_buffer(head_idx).data)
        uart_head     := leftRotate(uart_head, 1)
        maybe_full    := false.B
      }.otherwise {
        dcache_buffer := 0.U
      }
      dcache_data_valid := true.B
    }.elsewhen(isUartStateAddr(io.dcache_read_req.bits.addr)) {
      dcache_buffer     := Cat(0.U(30.W), !uart_empty, !io.txd.uart_busy)
      dcache_data_valid := true.B
    }.otherwise {
      // 非法地址
      dcache_buffer     := 0.U
      dcache_data_valid := true.B
    }
  }

  // DCache 写请求分发
  when(io.dcache_write_req.fire) {
    when(isBaseAddr(io.dcache_write_req.bits.addr)) {
      base_dcache_write_req  := true.B
      base_dcache_write_addr := io.dcache_write_req.bits.addr
      base_dcache_write_data := io.dcache_write_req.bits.data
      base_dcache_write_mask := io.dcache_write_req.bits.byte_mask
    }.elsewhen(isExtAddr(io.dcache_write_req.bits.addr)) {
      ext_dcache_write_req  := true.B
      ext_dcache_write_addr := io.dcache_write_req.bits.addr
      ext_dcache_write_data := io.dcache_write_req.bits.data
      ext_dcache_write_mask := io.dcache_write_req.bits.byte_mask
    }.elsewhen(isUartDataAddr(io.dcache_write_req.bits.addr)) {
      when(!io.txd.uart_busy) {
        txd_uart_start    := true.B
        txd_uart_data     := io.dcache_write_req.bits.data(7, 0)
        dcache_data_valid := true.B
      }
    }.otherwise {
      // 非法地址
      dcache_data_valid := true.B
    }
  }

  // ========== BASE RAM 状态机 ==========
  switch(base_state) {
    is(baseIDLE) {
      // 仲裁：dcache_write > dcache_read > icache
      when(base_dcache_write_req) {
        base_req_type := reqDcacheWrite
        base_ram_ctrl.write(
          base_dcache_write_addr(21, 2),
          EndianConvert(base_dcache_write_data),
          base_dcache_write_mask.asUInt.do_unary_~,
          false.B
        )
        base_wait_counter := 0.U
        base_state        := baseWRITE
      }.elsewhen(base_dcache_read_req) {
        base_req_type := reqDcacheRead
        base_ram_ctrl.read(base_dcache_read_addr(21, 2))
        base_wait_counter := 0.U
        base_state        := baseREAD
      }.elsewhen(base_icache_req) {
        base_req_type := reqIcache
        base_ram_ctrl.read(base_icache_addr(21, 2))
        base_wait_counter  := 0.U
        base_icache_offset := 0.U
        base_state         := baseREAD
      }
    }

    is(baseREAD) {
      when(base_req_type === reqIcache) {
        // ICache 多字读取
        when(base_icache_offset === (FETCH_WIDTH - 1).U) {
          when(base_wait_counter === SRAM_DELAY.U) {
            icache_buffer(base_icache_offset) := EndianConvert(io.base_ram_ctrl.data_in)
            base_ram_ctrl.idle()
            icache_data_valid     := true.B
            icache_resp_from_base := true.B
            base_icache_req       := false.B
            base_state            := baseIDLE
            base_req_type         := reqNone
          }.otherwise {
            base_wait_counter := base_wait_counter + 1.U
          }
        }.otherwise {
          when(base_wait_counter === SRAM_DELAY.U) {
            icache_buffer(base_icache_offset) := EndianConvert(io.base_ram_ctrl.data_in)
            base_icache_offset                := base_icache_offset + 1.U
            base_ram_ctrl.read(base_ram_ctrl.addr + 1.U)
            base_wait_counter := 0.U
          }.otherwise {
            base_wait_counter := base_wait_counter + 1.U
          }
        }
      }.otherwise {
        // DCache 单字读取
        when(base_wait_counter === SRAM_DELAY.U) {
          dcache_buffer := EndianConvert(io.base_ram_ctrl.data_in)
          base_ram_ctrl.idle()
          dcache_data_valid    := true.B
          base_dcache_read_req := false.B
          base_state           := baseIDLE
          base_req_type        := reqNone
        }.otherwise {
          base_wait_counter := base_wait_counter + 1.U
        }
      }
    }

    is(baseWRITE) {
      when(base_wait_counter < 2.U) {
        base_wait_counter := base_wait_counter + 1.U
      }.elsewhen(base_wait_counter === 2.U) {
        // 第3个周期：将WE拉高
        base_ram_ctrl.write(
          base_ram_ctrl.addr,
          base_ram_ctrl.data_out,
          base_ram_ctrl.be_n,
          true.B
        )
        base_wait_counter := base_wait_counter + 1.U
      }.elsewhen(base_wait_counter === SRAM_DELAY.U) {
        base_ram_ctrl.idle()
        dcache_data_valid     := true.B
        base_dcache_write_req := false.B
        base_state            := baseIDLE
        base_req_type         := reqNone
      }.otherwise {
        base_wait_counter := base_wait_counter + 1.U
      }
    }
  }

  // ========== EXT RAM 状态机 ==========
  switch(ext_state) {
    is(extIDLE) {
      // 仲裁：dcache_write > dcache_read > icache
      when(ext_dcache_write_req) {
        ext_req_type := reqDcacheWrite
        ext_ram_ctrl.write(
          ext_dcache_write_addr(21, 2),
          EndianConvert(ext_dcache_write_data),
          ext_dcache_write_mask.asUInt.do_unary_~,
          false.B
        )
        ext_wait_counter := 0.U
        ext_state        := extWRITE
      }.elsewhen(ext_dcache_read_req) {
        ext_req_type := reqDcacheRead
        ext_ram_ctrl.read(ext_dcache_read_addr(21, 2))
        ext_wait_counter := 0.U
        ext_state        := extREAD
      }.elsewhen(ext_icache_req) {
        ext_req_type := reqIcache
        ext_ram_ctrl.read(ext_icache_addr(21, 2))
        ext_wait_counter  := 0.U
        ext_icache_offset := 0.U
        ext_state         := extREAD
      }
    }

    is(extREAD) {
      when(ext_req_type === reqIcache) {
        // ICache 多字读取
        when(ext_icache_offset === (FETCH_WIDTH - 1).U) {
          when(ext_wait_counter === SRAM_DELAY.U) {
            icache_buffer(ext_icache_offset) := EndianConvert(io.ext_ram_ctrl.data_in)
            ext_ram_ctrl.idle()
            icache_data_valid     := true.B
            icache_resp_from_base := false.B
            ext_icache_req        := false.B
            ext_state             := extIDLE
            ext_req_type          := reqNone
          }.otherwise {
            ext_wait_counter := ext_wait_counter + 1.U
          }
        }.otherwise {
          when(ext_wait_counter === SRAM_DELAY.U) {
            icache_buffer(ext_icache_offset) := EndianConvert(io.ext_ram_ctrl.data_in)
            ext_icache_offset                := ext_icache_offset + 1.U
            ext_ram_ctrl.read(ext_ram_ctrl.addr + 1.U)
            ext_wait_counter := 0.U
          }.otherwise {
            ext_wait_counter := ext_wait_counter + 1.U
          }
        }
      }.otherwise {
        // DCache 单字读取
        when(ext_wait_counter === SRAM_DELAY.U) {
          dcache_buffer := EndianConvert(io.ext_ram_ctrl.data_in)
          ext_ram_ctrl.idle()
          dcache_data_valid   := true.B
          ext_dcache_read_req := false.B
          ext_state           := extIDLE
          ext_req_type        := reqNone
        }.otherwise {
          ext_wait_counter := ext_wait_counter + 1.U
        }
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
        dcache_data_valid    := true.B
        ext_dcache_write_req := false.B
        ext_state            := extIDLE
        ext_req_type         := reqNone
      }.otherwise {
        ext_wait_counter := ext_wait_counter + 1.U
      }
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

  // 清除 UART 发送信号
  when(txd_uart_start) {
    txd_uart_start := false.B
  }

  // ========== 复位处理 ==========
  when(reset.asBool) {
    base_ram_ctrl.idle()
    ext_ram_ctrl.idle()
    uart_buffer.foreach(i => {
      i.data := 0.U
    })

    // BASE RAM 状态复位
    base_state             := baseIDLE
    base_wait_counter      := 0.U
    base_req_type          := reqNone
    base_icache_req        := false.B
    base_icache_addr       := 0.U
    base_icache_offset     := 0.U
    base_dcache_read_req   := false.B
    base_dcache_read_addr  := 0.U
    base_dcache_write_req  := false.B
    base_dcache_write_addr := 0.U
    base_dcache_write_data := 0.U
    base_dcache_write_mask := 0.U

    // EXT RAM 状态复位
    ext_state             := extIDLE
    ext_wait_counter      := 0.U
    ext_req_type          := reqNone
    ext_icache_req        := false.B
    ext_icache_addr       := 0.U
    ext_icache_offset     := 0.U
    ext_dcache_read_req   := false.B
    ext_dcache_read_addr  := 0.U
    ext_dcache_write_req  := false.B
    ext_dcache_write_addr := 0.U
    ext_dcache_write_data := 0.U
    ext_dcache_write_mask := 0.U

    // 响应缓冲复位
    icache_data_valid     := false.B
    icache_resp_from_base := false.B
    dcache_data_valid     := false.B

    // UART 复位
    txd_uart_start := false.B
    txd_uart_data  := 0.U
    maybe_full     := false.B
    uart_head      := 1.U(UART_BUFFER_DEPTH.W)
    uart_tail      := 1.U(UART_BUFFER_DEPTH.W)
  }
}
