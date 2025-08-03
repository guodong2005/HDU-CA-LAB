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
  val unified_state     = Output(UInt(4.W))
  val delay_counter     = Output(UInt(8.W))
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

  // SRAM_DELAY parameter (you can adjust this)
  val SRAM_DELAY = 2

  // 统一状态机
  val sIdle :: sSetup :: sWait :: sCapture :: sDone :: Nil = Enum(5)
  val state                                                = RegInit(sIdle)

  // 延迟计数器
  val delay_counter = RegInit(0.U(8.W))

  // 请求类型
  val reqNone :: reqIRead :: reqDRead :: reqDWrite :: Nil = Enum(4)
  val current_req                                         = RegInit(reqNone)

  // 当前操作的RAM
  val ramNone :: ramBase :: ramExt :: Nil = Enum(3)
  val current_ram                         = RegInit(ramNone)

  // SRAM控制寄存器
  val base_ram_addr_r = RegInit(0.U(20.W))
  val base_ram_be_n_r = RegInit("hF".U(4.W))
  val base_ram_ce_n_r = RegInit(true.B)
  val base_ram_oe_n_r = RegInit(true.B)
  val base_ram_we_n_r = RegInit(true.B)
  val base_ram_data_r = RegInit(0.U(32.W))

  val ext_ram_addr_r = RegInit(0.U(20.W))
  val ext_ram_be_n_r = RegInit("hF".U(4.W))
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

  // 三态门控制
  io.base_ram_ctrl.data.data_out := base_ram_data_r
  io.base_ram_ctrl.data.data_en  := !base_ram_we_n_r

  io.ext_ram_ctrl.data.data_out := ext_ram_data_r
  io.ext_ram_ctrl.data.data_en  := !ext_ram_we_n_r

  // 请求缓存
  val icache_addr_r   = Reg(UInt(32.W))
  val dcache_addr_r   = Reg(UInt(32.W))
  val dcache_data_r   = Reg(UInt(32.W))
  val dcache_wstrb_r  = Reg(UInt(4.W))
  val dcache_is_write = RegInit(false.B)

  // ICache burst读取控制
  val icache_offset       = RegInit(0.U(4.W))
  val icache_burst_active = RegInit(false.B)

  // 响应数据
  val icacheline_new   = RegInit(VecInit(Seq.fill(8)(0.U(32.W))))
  val dcache_resp_data = RegInit(0.U(32.W))

  // 响应valid信号
  val icache_resp_valid = RegInit(false.B)
  val dcache_resp_valid = RegInit(false.B)

  // 地址解析
  def isBaseAddr(addr:      UInt): Bool = addr(31, 22) === "b1000_0000_00".U(10.W)
  def isExtAddr(addr:       UInt): Bool = addr(31, 22) === "b1000_0000_01".U(10.W)
  def isUartDataAddr(addr:  UInt): Bool = addr === "hBFD003F8".U(32.W)
  def isUartStateAddr(addr: UInt): Bool = addr === "hBFD003FC".U(32.W)

  // 等待中的请求标志
  val icache_pending = RegInit(false.B)
  val dcache_pending = RegInit(false.B)

  // Ready信号 - 只在空闲状态且没有正在进行的burst时才接受新请求
  io.icache_read_req.ready  := state === sIdle && !icache_pending && !icache_burst_active
  io.dcache_read_req.ready  := state === sIdle && !dcache_pending && !icache_burst_active
  io.dcache_write_req.ready := state === sIdle && !dcache_pending && !icache_burst_active

  // 接收请求
  when(io.icache_read_req.fire) {
    icache_pending := true.B
    icache_addr_r  := io.icache_read_req.bits.addr
  }

  when(io.dcache_read_req.fire) {
    dcache_pending  := true.B
    dcache_addr_r   := io.dcache_read_req.bits.addr
    dcache_is_write := false.B
  }

  when(io.dcache_write_req.fire) {
    dcache_pending  := true.B
    dcache_addr_r   := io.dcache_write_req.bits.addr
    dcache_data_r   := io.dcache_write_req.bits.data
    dcache_wstrb_r  := io.dcache_write_req.bits.byte_mask
    dcache_is_write := true.B
  }

  // 响应接口
  io.icache_read_resp.valid     := icache_resp_valid
  io.icache_read_resp.bits.data := icacheline_new.asUInt
  io.dcache_read_resp.valid     := dcache_resp_valid
  io.dcache_read_resp.bits.data := dcache_resp_data

  when(io.icache_read_resp.fire) {
    icache_resp_valid := false.B
  }
  when(io.dcache_read_resp.fire) {
    dcache_resp_valid := false.B
  }

  // 统一状态机
  // UART处理（独立于SRAM访问）
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

  // UART发送
  io.txd.uart_start := state === sIdle && dcache_pending && isUartDataAddr(dcache_addr_r) &&
    dcache_is_write && !io.txd.uart_busy
  io.txd.uart_data := dcache_data_r(7, 0)

  // Debug信号
  io.debug.base_state        := 0.U // 兼容旧接口
  io.debug.ext_state         := 0.U // 兼容旧接口
  io.debug.unified_state     := state.asUInt
  io.debug.delay_counter     := delay_counter
  io.debug.icache_read_base  := current_req === reqIRead && current_ram === ramBase
  io.debug.icache_read_ext   := current_req === reqIRead && current_ram === ramExt
  io.debug.dcache_read_base  := current_req === reqDRead && current_ram === ramBase
  io.debug.dcache_read_ext   := current_req === reqDRead && current_ram === ramExt
  io.debug.dcache_write_base := current_req === reqDWrite && current_ram === ramBase
  io.debug.dcache_write_ext  := current_req === reqDWrite && current_ram === ramExt
  io.debug.icache_read_addr  := icache_addr_r(21, 2)
  io.debug.dcache_read_addr  := dcache_addr_r(21, 2)
  io.debug.dcache_write_addr := dcache_addr_r(21, 2)
  switch(state) {
    is(sIdle) {
      // 优先级：dcache > icache (除非icache正在burst)
      when(dcache_pending) {
        when(isBaseAddr(dcache_addr_r)) {
          current_req := Mux(dcache_is_write, reqDWrite, reqDRead)
          current_ram := ramBase
          state       := sSetup
        }.elsewhen(isExtAddr(dcache_addr_r)) {
          current_req := Mux(dcache_is_write, reqDWrite, reqDRead)
          current_ram := ramExt
          state       := sSetup
        }.elsewhen(isUartDataAddr(dcache_addr_r) && !dcache_is_write) {
          // UART读取
          when(!uart_empty) {
            dcache_resp_data := Cat(0.U(24.W), uart_buffer(head_idx).data)
            uart_head        := leftRotate(uart_head, 1)
            maybe_full       := false.B
          }.otherwise {
            dcache_resp_data := 0.U(32.W)
          }
          dcache_resp_valid := true.B
          dcache_pending    := false.B
        }.elsewhen(isUartStateAddr(dcache_addr_r) && !dcache_is_write) {
          // UART状态读取
          dcache_resp_data  := Cat(0.U(30.W), !uart_empty, !io.txd.uart_busy)
          dcache_resp_valid := true.B
          dcache_pending    := false.B
        }.elsewhen(isUartDataAddr(dcache_addr_r) && dcache_is_write) {
          // UART写入
          when(!io.txd.uart_busy) {
            io.txd.uart_start := true.B
            io.txd.uart_data  := dcache_data_r(7, 0)
            dcache_resp_valid := true.B
            dcache_pending    := false.B
          }
        }.otherwise {
          // 非SRAM地址，直接响应
          dcache_resp_data  := 0.U
          dcache_resp_valid := true.B
          dcache_pending    := false.B
        }
      }.elsewhen(icache_pending) {
        when(isBaseAddr(icache_addr_r)) {
          current_req         := reqIRead
          current_ram         := ramBase
          icache_offset       := 0.U
          icache_burst_active := true.B
          state               := sSetup
        }.elsewhen(isExtAddr(icache_addr_r)) {
          current_req         := reqIRead
          current_ram         := ramExt
          icache_offset       := 0.U
          icache_burst_active := true.B
          state               := sSetup
        }.otherwise {
          // 非SRAM地址，直接响应
          icacheline_new.foreach(_ := 0.U)
          icache_resp_valid        := true.B
          icache_pending           := false.B
        }
      }
    }

    is(sSetup) {
      // 设置SRAM控制信号
      when(current_ram === ramBase) {
        when(current_req === reqIRead) {
          base_ram_addr_r := icache_addr_r(21, 2) + icache_offset
          base_ram_be_n_r := 0.U
          base_ram_ce_n_r := false.B
          base_ram_oe_n_r := false.B
          base_ram_we_n_r := true.B
        }.elsewhen(current_req === reqDRead) {
          base_ram_addr_r := dcache_addr_r(21, 2)
          base_ram_be_n_r := 0.U
          base_ram_ce_n_r := false.B
          base_ram_oe_n_r := false.B
          base_ram_we_n_r := true.B
        }.elsewhen(current_req === reqDWrite) {
          base_ram_addr_r := dcache_addr_r(21, 2)
          base_ram_be_n_r := ~dcache_wstrb_r
          base_ram_ce_n_r := false.B
          base_ram_oe_n_r := true.B
          base_ram_we_n_r := false.B
          base_ram_data_r := EndianConvert(dcache_data_r)
        }
      }.elsewhen(current_ram === ramExt) {
        when(current_req === reqIRead) {
          ext_ram_addr_r := icache_addr_r(21, 2) + icache_offset
          ext_ram_be_n_r := 0.U
          ext_ram_ce_n_r := false.B
          ext_ram_oe_n_r := false.B
          ext_ram_we_n_r := true.B
        }.elsewhen(current_req === reqDRead) {
          ext_ram_addr_r := dcache_addr_r(21, 2)
          ext_ram_be_n_r := 0.U
          ext_ram_ce_n_r := false.B
          ext_ram_oe_n_r := false.B
          ext_ram_we_n_r := true.B
        }.elsewhen(current_req === reqDWrite) {
          ext_ram_addr_r := dcache_addr_r(21, 2)
          ext_ram_be_n_r := ~dcache_wstrb_r
          ext_ram_ce_n_r := false.B
          ext_ram_oe_n_r := true.B
          ext_ram_we_n_r := false.B
          ext_ram_data_r := EndianConvert(dcache_data_r)
        }
      }

      delay_counter := 0.U
      state         := sWait
    }

    is(sWait) {
      // 等待SRAM_DELAY周期
      when(delay_counter < SRAM_DELAY.U) {
        delay_counter := delay_counter + 1.U
      }.otherwise {
        state := sCapture
      }
    }

    is(sCapture) {
      // 捕获读数据
      when(current_req === reqIRead) {
        when(current_ram === ramBase) {
          icacheline_new(icache_offset) := EndianConvert(io.base_ram_ctrl.data.data_in)
        }.elsewhen(current_ram === ramExt) {
          icacheline_new(icache_offset) := EndianConvert(io.ext_ram_ctrl.data.data_in)
        }
      }.elsewhen(current_req === reqDRead) {
        when(current_ram === ramBase) {
          dcache_resp_data := EndianConvert(io.base_ram_ctrl.data.data_in)
        }.elsewhen(current_ram === ramExt) {
          dcache_resp_data := EndianConvert(io.ext_ram_ctrl.data.data_in)
        }
      }

      state := sDone
    }

    is(sDone) {
      // 清除控制信号
      when(current_ram === ramBase) {
        base_ram_addr_r := 0.U
        base_ram_be_n_r := "hF".U
        base_ram_ce_n_r := true.B
        base_ram_oe_n_r := true.B
        base_ram_we_n_r := true.B
        base_ram_data_r := 0.U
      }.elsewhen(current_ram === ramExt) {
        ext_ram_addr_r := 0.U
        ext_ram_be_n_r := "hF".U
        ext_ram_ce_n_r := true.B
        ext_ram_oe_n_r := true.B
        ext_ram_we_n_r := true.B
        ext_ram_data_r := 0.U
      }

      // 处理响应
      when(current_req === reqIRead) {
        when(icache_offset === 7.U) {
          // ICache burst完成
          icache_resp_valid   := true.B
          icache_pending      := false.B
          icache_burst_active := false.B
          current_req         := reqNone
          current_ram         := ramNone
          state               := sIdle
        }.otherwise {
          // 继续burst读取
          icache_offset := icache_offset + 1.U
          state         := sSetup
        }
      }.otherwise {
        // DCache请求完成
        dcache_resp_valid := true.B
        dcache_pending    := false.B
        current_req       := reqNone
        current_ram       := ramNone
        state             := sIdle
      }
    }
  }

  // 复位
  when(reset.asBool) {
    state               := sIdle
    delay_counter       := 0.U
    current_req         := reqNone
    current_ram         := ramNone
    icache_pending      := false.B
    dcache_pending      := false.B
    icache_burst_active := false.B
    icache_resp_valid   := false.B
    dcache_resp_valid   := false.B
    uart_buffer.foreach(i => {
      i.data := 0.U
    })
  }
}
