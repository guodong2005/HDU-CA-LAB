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

  // SRAM控制寄存器
  val base_ram_ctrl = Reg(new SramCtrlInfo)
  val ext_ram_ctrl  = Reg(new SramCtrlInfo)
  io.base_ram_ctrl.ctrl <> base_ram_ctrl
  io.ext_ram_ctrl.ctrl <> ext_ram_ctrl

  // 状态机定义
  val sIDLE :: iREAD :: dREAD :: dWrite :: dWriteWait :: iWait :: dWait :: Nil = Enum(7)
  val state                                                                    = RegInit(sIDLE)
  val wait_counter                                                             = RegInit(0.U(4.W))
  val icache_offset                                                            = RegInit(0.U(3.W))

  // 请求缓存寄存器
  val icache_req_valid = RegInit(false.B)
  val icache_req_addr  = RegInit(0.U(32.W))

  val dcache_read_req_valid = RegInit(false.B)
  val dcache_read_req_addr  = RegInit(0.U(32.W))

  val dcache_write_req_valid = RegInit(false.B)
  val dcache_write_req_addr  = RegInit(0.U(32.W))
  val dcache_write_req_data  = RegInit(0.U(32.W))
  val dcache_write_req_mask  = RegInit(0.U(4.W))

  // 当前正在处理的请求类型
  val reqNone :: reqIcache :: reqDcacheRead :: reqDcacheWrite :: Nil = Enum(4)
  val current_req_type                                               = RegInit(reqNone)

  // RAM选择
  val ramNone :: ramBase :: ramExt :: Nil = Enum(3)
  val current_ram                         = RegInit(ramNone)

  // Ready信号逻辑：
  // 1. icache: 没有pending的icache请求，或者当前没有正在进行的icache burst
  // 2. dcache read: 没有pending的dcache read请求
  // 3. dcache write: 没有pending的dcache write请求
  val icache_burst_active = state === iREAD || state === iWait
  io.icache_read_req.ready  := !icache_req_valid && !icache_burst_active
  io.dcache_read_req.ready  := !dcache_read_req_valid
  io.dcache_write_req.ready := !dcache_write_req_valid

  // 捕获请求（valid只持续一拍）
  when(io.icache_read_req.fire) {
    icache_req_valid := true.B
    icache_req_addr  := io.icache_read_req.bits.addr
  }

  when(io.dcache_read_req.fire) {
    dcache_read_req_valid := true.B
    dcache_read_req_addr  := io.dcache_read_req.bits.addr
  }

  when(io.dcache_write_req.fire) {
    dcache_write_req_valid := true.B
    dcache_write_req_addr  := io.dcache_write_req.bits.addr
    dcache_write_req_data  := io.dcache_write_req.bits.data
    dcache_write_req_mask  := io.dcache_write_req.bits.byte_mask
  }

  // 地址解析函数
  def isBaseAddr(addr:      UInt): Bool = addr(31, 22) === "b1000_0000_00".U(10.W)
  def isExtAddr(addr:       UInt): Bool = addr(31, 22) === "b1000_0000_01".U(10.W)
  def isUartDataAddr(addr:  UInt): Bool = addr === "hBFD003F8".U(32.W)
  def isUartStateAddr(addr: UInt): Bool = addr === "hBFD003FC".U(32.W)

  // 响应缓冲区
  val icache_buffer     = RegInit(VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W))))
  val icache_data_valid = RegInit(false.B)
  val dcache_buffer     = RegInit(0.U(32.W))
  val dcache_data_valid = RegInit(false.B)

  // 响应接口
  io.icache_read_resp.valid     := icache_data_valid
  io.icache_read_resp.bits.data := icache_buffer.asUInt
  io.dcache_read_resp.valid     := dcache_data_valid
  io.dcache_read_resp.bits.data := dcache_buffer

  // 清除响应valid
  when(io.icache_read_resp.fire) {
    icache_data_valid := false.B
  }
  when(io.dcache_read_resp.fire) {
    dcache_data_valid := false.B
  }

  // UART缓冲区管理
  val uart_buffer = Reg(Vec(UART_BUFFER_DEPTH, new UartBufferInfo))
  val uart_head   = RegInit(1.U(UART_BUFFER_DEPTH.W))
  val head_idx    = OHToUInt(uart_head)
  val uart_tail   = RegInit(1.U(UART_BUFFER_DEPTH.W))
  val tail_idx    = OHToUInt(uart_tail)
  val maybe_full  = RegInit(false.B)
  val uart_full   = uart_head === uart_tail && maybe_full
  val uart_empty  = uart_head === uart_tail && !maybe_full

  // UART接收处理
  when(io.rxd.uart_ready && !uart_full) {
    uart_buffer(tail_idx).data := io.rxd.uart_data
    uart_tail                  := leftRotate(uart_tail, 1)
    maybe_full                 := true.B
    io.rxd.uart_clear          := true.B
  }.otherwise {
    io.rxd.uart_clear := false.B
  }

  // TXD控制
  val txd_uart_start = RegInit(false.B)
  val txd_uart_data  = RegInit(0.U(8.W))
  io.txd.uart_start := txd_uart_start
  io.txd.uart_data  := txd_uart_data

  // 仲裁逻辑：dcache_write > dcache_read > icache (除非icache正在burst)
  val next_req = Wire(UInt(2.W))
  next_req := reqNone
  when(dcache_write_req_valid) {
    next_req := reqDcacheWrite
  }.elsewhen(dcache_read_req_valid) {
    next_req := reqDcacheRead
  }.elsewhen(icache_req_valid && !icache_burst_active) {
    next_req := reqIcache
  }

  // 统一状态机
  switch(state) {
    is(sIDLE) {
      // 根据仲裁结果选择下一个请求
      when(next_req === reqDcacheWrite) {
        when(isBaseAddr(dcache_write_req_addr)) {
          current_req_type := reqDcacheWrite
          current_ram      := ramBase
          base_ram_ctrl.write(
            dcache_write_req_addr(21, 2),
            EndianConvert(dcache_write_req_data),
            dcache_write_req_mask.asUInt.do_unary_~
          )
          wait_counter := 0.U
          state        := dWrite
        }.elsewhen(isExtAddr(dcache_write_req_addr)) {
          current_req_type := reqDcacheWrite
          current_ram      := ramExt
          ext_ram_ctrl.write(
            dcache_write_req_addr(21, 2),
            EndianConvert(dcache_write_req_data),
            dcache_write_req_mask.asUInt.do_unary_~
          )
          wait_counter := 0.U
          state        := dWrite
        }.elsewhen(isUartDataAddr(dcache_write_req_addr)) {
          when(!io.txd.uart_busy) {
            txd_uart_start         := true.B
            txd_uart_data          := dcache_write_req_data(7, 0)
            dcache_data_valid      := true.B
            dcache_write_req_valid := false.B
            state                  := dWait
          }
        }.otherwise {
          // 非法地址，直接响应
          dcache_data_valid      := true.B
          dcache_write_req_valid := false.B
          state                  := dWait
        }
      }.elsewhen(next_req === reqDcacheRead) {
        when(isBaseAddr(dcache_read_req_addr)) {
          current_req_type := reqDcacheRead
          current_ram      := ramBase
          base_ram_ctrl.read(dcache_read_req_addr(21, 2))
          wait_counter := 0.U
          state        := dREAD
        }.elsewhen(isExtAddr(dcache_read_req_addr)) {
          current_req_type := reqDcacheRead
          current_ram      := ramExt
          ext_ram_ctrl.read(dcache_read_req_addr(21, 2))
          wait_counter := 0.U
          state        := dREAD
        }.elsewhen(isUartDataAddr(dcache_read_req_addr)) {
          when(!uart_empty) {
            dcache_buffer := Cat(0.U(24.W), uart_buffer(head_idx).data)
            uart_head     := leftRotate(uart_head, 1)
            maybe_full    := false.B
          }.otherwise {
            dcache_buffer := 0.U
          }
          dcache_data_valid     := true.B
          dcache_read_req_valid := false.B
          state                 := dWait
        }.elsewhen(isUartStateAddr(dcache_read_req_addr)) {
          dcache_buffer         := Cat(0.U(30.W), !uart_empty, !io.txd.uart_busy)
          dcache_data_valid     := true.B
          dcache_read_req_valid := false.B
          state                 := dWait
        }.otherwise {
          // 非法地址
          dcache_buffer         := 0.U
          dcache_data_valid     := true.B
          dcache_read_req_valid := false.B
          state                 := dWait
        }
      }.elsewhen(next_req === reqIcache) {
        when(isBaseAddr(icache_req_addr)) {
          current_req_type := reqIcache
          current_ram      := ramBase
          base_ram_ctrl.read(icache_req_addr(21, 2))
          wait_counter  := 0.U
          icache_offset := 0.U
          state         := iREAD
        }.elsewhen(isExtAddr(icache_req_addr)) {
          current_req_type := reqIcache
          current_ram      := ramExt
          ext_ram_ctrl.read(icache_req_addr(21, 2))
          wait_counter  := 0.U
          icache_offset := 0.U
          state         := iREAD
        }.otherwise {
          // 非法地址
          icache_buffer     := VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W)))
          icache_data_valid := true.B
          icache_req_valid  := false.B
          state             := iWait
        }
      }
    }

    is(iREAD) {
      when(icache_offset === (FETCH_WIDTH - 1).U) {
        when(wait_counter === SRAM_DELAY.U) {
          val data = Mux(current_ram === ramBase, io.base_ram_ctrl.data_in, io.ext_ram_ctrl.data_in)
          icache_buffer(icache_offset) := EndianConvert(data)
          when(current_ram === ramBase) {
            base_ram_ctrl.idle()
          }.otherwise {
            ext_ram_ctrl.idle()
          }
          icache_data_valid := true.B
          icache_req_valid  := false.B
          state             := iWait
        }.otherwise {
          wait_counter := wait_counter + 1.U
        }
      }.otherwise {
        when(wait_counter === SRAM_DELAY.U) {
          val data = Mux(current_ram === ramBase, io.base_ram_ctrl.data_in, io.ext_ram_ctrl.data_in)
          icache_buffer(icache_offset) := EndianConvert(data)
          icache_offset                := icache_offset + 1.U

          val next_addr = Mux(current_ram === ramBase, base_ram_ctrl.addr, ext_ram_ctrl.addr) + 1.U
          when(current_ram === ramBase) {
            base_ram_ctrl.read(next_addr)
          }.otherwise {
            ext_ram_ctrl.read(next_addr)
          }
          wait_counter := 0.U
        }.otherwise {
          wait_counter := wait_counter + 1.U
        }
      }
    }

    is(iWait) {
      state            := sIDLE
      current_req_type := reqNone
      current_ram      := ramNone
    }

    is(dREAD) {
      when(wait_counter === SRAM_DELAY.U) {
        val data = Mux(current_ram === ramBase, io.base_ram_ctrl.data_in, io.ext_ram_ctrl.data_in)
        dcache_buffer         := EndianConvert(data)
        dcache_data_valid     := true.B
        dcache_read_req_valid := false.B
        when(current_ram === ramBase) {
          base_ram_ctrl.idle()
        }.otherwise {
          ext_ram_ctrl.idle()
        }
        state := dWait
      }.otherwise {
        wait_counter := wait_counter + 1.U
      }
    }

    is(dWrite) {
      when(wait_counter === SRAM_DELAY.U) {
        when(current_ram === ramBase) {
          base_ram_ctrl.idle()
        }.otherwise {
          ext_ram_ctrl.idle()
        }
        // 写操作完成后进入额外等待状态
        wait_counter := 0.U
        state        := dWriteWait
      }.otherwise {
        wait_counter := wait_counter + 1.U
      }
    }

    is(dWriteWait) {
      // 额外等待一个周期确保写入完成
      dcache_data_valid      := true.B
      dcache_write_req_valid := false.B
      state                  := dWait
    }

    is(dWait) {
      txd_uart_start   := false.B
      state            := sIDLE
      current_req_type := reqNone
      current_ram      := ramNone
    }
  }

  // 复位处理
  when(reset.asBool) {
    base_ram_ctrl.idle()
    ext_ram_ctrl.idle()
    uart_buffer.foreach(i => {
      i.data := 0.U
    })
    state                  := sIDLE
    current_req_type       := reqNone
    current_ram            := ramNone
    wait_counter           := 0.U
    icache_offset          := 0.U
    icache_data_valid      := false.B
    dcache_data_valid      := false.B
    txd_uart_start         := false.B
    txd_uart_data          := 0.U
    maybe_full             := false.B
    uart_head              := 1.U(UART_BUFFER_DEPTH.W)
    uart_tail              := 1.U(UART_BUFFER_DEPTH.W)
    icache_req_valid       := false.B
    dcache_read_req_valid  := false.B
    dcache_write_req_valid := false.B
  }
}
