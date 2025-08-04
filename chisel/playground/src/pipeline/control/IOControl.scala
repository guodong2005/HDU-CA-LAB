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
    data_en  := true.B  // 写操作驱动数据总线
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

  // SRAM延迟常数调整为5
  val SRAM_DELAY = 5

  // SRAM控制寄存器
  val base_ram_ctrl = Reg(new SramCtrlInfo)
  val ext_ram_ctrl  = Reg(new SramCtrlInfo)
  io.base_ram_ctrl.ctrl <> base_ram_ctrl
  io.ext_ram_ctrl.ctrl  <> ext_ram_ctrl

  // 状态机定义
  val sIDLE :: iREAD :: dREAD :: dWrite :: dWriteWait :: iWait :: dWait :: Nil = Enum(7)
  val state                                                                    = RegInit(sIDLE)
  val wait_counter                                                             = RegInit(0.U(4.W))
  val icache_offset                                                            = RegInit(0.U(3.W))

  // 请求缓存寄存器 - 确保初始值为false/0
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

  // 共享的ready信号逻辑：
  // 只有在IDLE状态且没有pending请求时才能接收新请求
  val system_ready = state === sIDLE &&
    !icache_req_valid &&
    !dcache_read_req_valid &&
    !dcache_write_req_valid

  // 所有接口共用同一个ready信号
  io.icache_read_req.ready  := system_ready
  io.dcache_read_req.ready  := system_ready
  io.dcache_write_req.ready := system_ready

  // 捕获请求（valid只持续一拍）- 只在system_ready时才捕获
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

  // 地址解析函数 - 使用十六进制更清晰
  def isBaseAddr(addr:      UInt): Bool = addr(31, 22) === "h200".U(10.W) // 0x80000000>>22 = 0x200
  def isExtAddr(addr:       UInt): Bool = addr(31, 22) === "h201".U(10.W) // 0x80400000>>22 = 0x201
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

  // 仲裁逻辑：dcache_write > dcache_read > icache
  val next_req = Wire(UInt(3.W))
  next_req := reqNone
  when(dcache_write_req_valid) {
    next_req := reqDcacheWrite
  }.elsewhen(dcache_read_req_valid) {
    next_req := reqDcacheRead
  }.elsewhen(icache_req_valid) {
    next_req := reqIcache
  }

  // 统一状态机
  switch(state) {
    is(sIDLE) {
      // 严格按照优先级处理：dcache_write > dcache_read > icache
      when(dcache_write_req_valid) {
        when(isBaseAddr(dcache_write_req_addr)) {
          current_req_type := reqDcacheWrite
          current_ram      := ramBase
          // 写操作第一个周期：WE为低
          base_ram_ctrl.write(
            dcache_write_req_addr(21, 2),
            EndianConvert(dcache_write_req_data),
            dcache_write_req_mask.asUInt.do_unary_~,
            false.B // WE为低
          )
          wait_counter := 0.U
          state        := dWrite
        }.elsewhen(isExtAddr(dcache_write_req_addr)) {
          current_req_type := reqDcacheWrite
          current_ram      := ramExt
          // 写操作第一个周期：WE为低
          ext_ram_ctrl.write(
            dcache_write_req_addr(21, 2),
            EndianConvert(dcache_write_req_data),
            dcache_write_req_mask.asUInt.do_unary_~,
            false.B // WE为低
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
      }.elsewhen(dcache_read_req_valid) {
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
      }.elsewhen(icache_req_valid) {
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
      // 写操作时序控制：
      // 前3个周期WE为低，后2个周期WE为高
      when(wait_counter < 3.U) {
        // 继续保持WE为低
        wait_counter := wait_counter + 1.U
      }.elsewhen(wait_counter === 3.U) {
        // 第4个周期：将WE拉高，但CE和BE继续保持低
        when(current_ram === ramBase) {
          base_ram_ctrl.write(
            base_ram_ctrl.addr,
            base_ram_ctrl.data_out,
            base_ram_ctrl.be_n,
            true.B // WE拉高
          )
        }.otherwise {
          ext_ram_ctrl.write(
            ext_ram_ctrl.addr,
            ext_ram_ctrl.data_out,
            ext_ram_ctrl.be_n,
            true.B // WE拉高
          )
        }
        wait_counter := wait_counter + 1.U
      }.elsewhen(wait_counter < SRAM_DELAY.U) {
        // 第5个周期：继续保持WE为高
        wait_counter := wait_counter + 1.U
      }.elsewhen(wait_counter === SRAM_DELAY.U) {
        // 写操作完成，转入空闲状态
        when(current_ram === ramBase) {
          base_ram_ctrl.idle()
        }.otherwise {
          ext_ram_ctrl.idle()
        }
        dcache_data_valid      := true.B
        dcache_write_req_valid := false.B
        state                  := dWait
      }.otherwise {
        wait_counter := wait_counter + 1.U
      }
    }

    is(dWriteWait) {
      // 这个状态已经不需要了，可以删除
      state := dWait
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
    icache_req_addr        := 0.U
    dcache_read_req_addr   := 0.U
    dcache_write_req_addr  := 0.U
    dcache_write_req_data  := 0.U
    dcache_write_req_mask  := 0.U
  }
}
// package cpu.pipeline
// import chisel3._
// import chisel3.util._
// import cpu.defines._
// import cpu.defines.Const._
// import cpu.pipeline._

// class SramCtrlInfo extends Bundle {
//   def idle(): Unit = {
//     data_out := 0.U
//     addr     := 0.U
//     be_n     := "b1111".U
//     ce_n     := true.B
//     oe_n     := true.B
//     we_n     := true.B
//     data_en  := false.B // 数据总线禁用
//   }

//   def read(rAddr: UInt): Unit = {
//     data_out := 0.U
//     addr     := rAddr
//     be_n     := "b0000".U
//     ce_n     := false.B
//     oe_n     := false.B
//     we_n     := true.B
//     data_en  := false.B // 读操作不驱动数据总线
//   }

//   def write(wAddr: UInt, wData: UInt, wBe_n: UInt, weState: Bool = true.B): Unit = {
//     data_out := wData
//     addr     := wAddr
//     be_n     := wBe_n
//     ce_n     := false.B
//     oe_n     := true.B
//     we_n     := weState // 可以控制WE的状态
//     data_en  := true.B  // 写操作驱动数据总线
//   }

//   val data_out = UInt(32.W)
//   val addr     = UInt(20.W)
//   val be_n     = UInt(4.W)
//   val ce_n     = Bool()
//   val oe_n     = Bool()
//   val we_n     = Bool()
//   val data_en  = Bool() // 新增：数据总线使能信号
// }

// class SramCtrlIO extends Bundle {
//   val data_in = Input(UInt(32.W))
//   val ctrl    = Output(new SramCtrlInfo)
// }

// class RxDIO extends Bundle {
//   val uart_ready = Input(Bool())
//   val uart_clear = Output(Bool())
//   val uart_data  = Input(UInt(8.W))
// }

// class TxDIO extends Bundle {
//   val uart_start = Output(Bool())
//   val uart_data  = Output(UInt(8.W))
//   val uart_busy  = Input(Bool())
// }

// class UartBufferInfo extends Bundle {
//   val data = UInt(8.W)
// }

// class IoControlIO extends Bundle {
//   val icache_read_req  = Flipped(Decoupled(new ICacheReq))
//   val icache_read_resp = Decoupled(new ICacheResp)
//   val dcache_read_req  = Flipped(Decoupled(new DCacheReadReq))
//   val dcache_read_resp = Decoupled(new DCacheResp)
//   val dcache_write_req = Flipped(Decoupled(new DCacheWriteReq))
//   val base_ram_ctrl    = new SramCtrlIO
//   val ext_ram_ctrl     = new SramCtrlIO
//   val rxd              = new RxDIO
//   val txd              = new TxDIO
// }

// class IoControl extends Module {
//   def EndianConvert(data: UInt) = {
//     // do nothing
//     data
//   }

//   def leftRotate(i: UInt, n: Int): UInt = {
//     val w = i.getWidth
//     if (n > 0) {
//       Cat(i(w - n - 1, 0), i(w - 1, w - n))
//     } else {
//       i
//     }
//   }

//   val io = IO(new IoControlIO)

//   // SRAM延迟常数调整为4
//   val SRAM_DELAY = 4

//   // SRAM控制寄存器
//   val base_ram_ctrl = Reg(new SramCtrlInfo)
//   val ext_ram_ctrl  = Reg(new SramCtrlInfo)
//   io.base_ram_ctrl.ctrl <> base_ram_ctrl
//   io.ext_ram_ctrl.ctrl  <> ext_ram_ctrl

//   // 状态机定义
//   val sIDLE :: iREAD :: dREAD :: dWrite :: dWriteWait :: iWait :: dWait :: Nil = Enum(7)
//   val state                                                                    = RegInit(sIDLE)
//   val wait_counter                                                             = RegInit(0.U(4.W))
//   val icache_offset                                                            = RegInit(0.U(3.W))

//   // 请求缓存寄存器 - 确保初始值为false/0
//   val icache_req_valid = RegInit(false.B)
//   val icache_req_addr  = RegInit(0.U(32.W))

//   val dcache_read_req_valid = RegInit(false.B)
//   val dcache_read_req_addr  = RegInit(0.U(32.W))

//   val dcache_write_req_valid = RegInit(false.B)
//   val dcache_write_req_addr  = RegInit(0.U(32.W))
//   val dcache_write_req_data  = RegInit(0.U(32.W))
//   val dcache_write_req_mask  = RegInit(0.U(4.W))

//   // 当前正在处理的请求类型
//   val reqNone :: reqIcache :: reqDcacheRead :: reqDcacheWrite :: Nil = Enum(4)
//   val current_req_type                                               = RegInit(reqNone)

//   // RAM选择
//   val ramNone :: ramBase :: ramExt :: Nil = Enum(3)
//   val current_ram                         = RegInit(ramNone)

//   // 共享的ready信号逻辑：
//   // 只有在IDLE状态且没有pending请求时才能接收新请求
//   val system_ready = state === sIDLE &&
//     !icache_req_valid &&
//     !dcache_read_req_valid &&
//     !dcache_write_req_valid

//   // 所有接口共用同一个ready信号
//   io.icache_read_req.ready  := system_ready
//   io.dcache_read_req.ready  := system_ready
//   io.dcache_write_req.ready := system_ready

//   // 捕获请求（valid只持续一拍）- 只在system_ready时才捕获
//   when(io.icache_read_req.fire) {
//     icache_req_valid := true.B
//     icache_req_addr  := io.icache_read_req.bits.addr
//   }

//   when(io.dcache_read_req.fire) {
//     dcache_read_req_valid := true.B
//     dcache_read_req_addr  := io.dcache_read_req.bits.addr
//   }

//   when(io.dcache_write_req.fire) {
//     dcache_write_req_valid := true.B
//     dcache_write_req_addr  := io.dcache_write_req.bits.addr
//     dcache_write_req_data  := io.dcache_write_req.bits.data
//     dcache_write_req_mask  := io.dcache_write_req.bits.byte_mask
//   }

//   // 地址解析函数 - 使用十六进制更清晰
//   def isBaseAddr(addr:      UInt): Bool = addr(31, 22) === "h200".U(10.W) // 0x80000000>>22 = 0x200
//   def isExtAddr(addr:       UInt): Bool = addr(31, 22) === "h201".U(10.W) // 0x80400000>>22 = 0x201
//   def isUartDataAddr(addr:  UInt): Bool = addr === "hBFD003F8".U(32.W)
//   def isUartStateAddr(addr: UInt): Bool = addr === "hBFD003FC".U(32.W)

//   // 响应缓冲区
//   val icache_buffer     = RegInit(VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W))))
//   val icache_data_valid = RegInit(false.B)
//   val dcache_buffer     = RegInit(0.U(32.W))
//   val dcache_data_valid = RegInit(false.B)

//   // 响应接口
//   io.icache_read_resp.valid     := icache_data_valid
//   io.icache_read_resp.bits.data := icache_buffer.asUInt
//   io.dcache_read_resp.valid     := dcache_data_valid
//   io.dcache_read_resp.bits.data := dcache_buffer

//   // 清除响应valid
//   when(io.icache_read_resp.fire) {
//     icache_data_valid := false.B
//   }
//   when(io.dcache_read_resp.fire) {
//     dcache_data_valid := false.B
//   }

//   // UART缓冲区管理
//   val uart_buffer = Reg(Vec(UART_BUFFER_DEPTH, new UartBufferInfo))
//   val uart_head   = RegInit(1.U(UART_BUFFER_DEPTH.W))
//   val head_idx    = OHToUInt(uart_head)
//   val uart_tail   = RegInit(1.U(UART_BUFFER_DEPTH.W))
//   val tail_idx    = OHToUInt(uart_tail)
//   val maybe_full  = RegInit(false.B)
//   val uart_full   = uart_head === uart_tail && maybe_full
//   val uart_empty  = uart_head === uart_tail && !maybe_full

//   // UART接收处理
//   when(io.rxd.uart_ready && !uart_full) {
//     uart_buffer(tail_idx).data := io.rxd.uart_data
//     uart_tail                  := leftRotate(uart_tail, 1)
//     maybe_full                 := true.B
//     io.rxd.uart_clear          := true.B
//   }.otherwise {
//     io.rxd.uart_clear := false.B
//   }

//   // TXD控制
//   val txd_uart_start = RegInit(false.B)
//   val txd_uart_data  = RegInit(0.U(8.W))
//   io.txd.uart_start := txd_uart_start
//   io.txd.uart_data  := txd_uart_data

//   // 仲裁逻辑：dcache_write > dcache_read > icache
//   val next_req = Wire(UInt(3.W))
//   next_req := reqNone
//   when(dcache_write_req_valid) {
//     next_req := reqDcacheWrite
//   }.elsewhen(dcache_read_req_valid) {
//     next_req := reqDcacheRead
//   }.elsewhen(icache_req_valid) {
//     next_req := reqIcache
//   }

//   // 统一状态机
//   switch(state) {
//     is(sIDLE) {
//       // 严格按照优先级处理：dcache_write > dcache_read > icache
//       when(dcache_write_req_valid) {
//         when(isBaseAddr(dcache_write_req_addr)) {
//           current_req_type := reqDcacheWrite
//           current_ram      := ramBase
//           // 写操作第一个周期：WE为低
//           base_ram_ctrl.write(
//             dcache_write_req_addr(21, 2),
//             EndianConvert(dcache_write_req_data),
//             dcache_write_req_mask.asUInt.do_unary_~,
//             false.B // WE为低
//           )
//           wait_counter := 0.U
//           state        := dWrite
//         }.elsewhen(isExtAddr(dcache_write_req_addr)) {
//           current_req_type := reqDcacheWrite
//           current_ram      := ramExt
//           // 写操作第一个周期：WE为低
//           ext_ram_ctrl.write(
//             dcache_write_req_addr(21, 2),
//             EndianConvert(dcache_write_req_data),
//             dcache_write_req_mask.asUInt.do_unary_~,
//             false.B // WE为低
//           )
//           wait_counter := 0.U
//           state        := dWrite
//         }.elsewhen(isUartDataAddr(dcache_write_req_addr)) {
//           when(!io.txd.uart_busy) {
//             txd_uart_start         := true.B
//             txd_uart_data          := dcache_write_req_data(7, 0)
//             dcache_data_valid      := true.B
//             dcache_write_req_valid := false.B
//             state                  := dWait
//           }
//         }.otherwise {
//           // 非法地址，直接响应
//           dcache_data_valid      := true.B
//           dcache_write_req_valid := false.B
//           state                  := dWait
//         }
//       }.elsewhen(dcache_read_req_valid) {
//         when(isBaseAddr(dcache_read_req_addr)) {
//           current_req_type := reqDcacheRead
//           current_ram      := ramBase
//           base_ram_ctrl.read(dcache_read_req_addr(21, 2))
//           wait_counter := 0.U
//           state        := dREAD
//         }.elsewhen(isExtAddr(dcache_read_req_addr)) {
//           current_req_type := reqDcacheRead
//           current_ram      := ramExt
//           ext_ram_ctrl.read(dcache_read_req_addr(21, 2))
//           wait_counter := 0.U
//           state        := dREAD
//         }.elsewhen(isUartDataAddr(dcache_read_req_addr)) {
//           when(!uart_empty) {
//             dcache_buffer := Cat(0.U(24.W), uart_buffer(head_idx).data)
//             uart_head     := leftRotate(uart_head, 1)
//             maybe_full    := false.B
//           }.otherwise {
//             dcache_buffer := 0.U
//           }
//           dcache_data_valid     := true.B
//           dcache_read_req_valid := false.B
//           state                 := dWait
//         }.elsewhen(isUartStateAddr(dcache_read_req_addr)) {
//           dcache_buffer         := Cat(0.U(30.W), !uart_empty, !io.txd.uart_busy)
//           dcache_data_valid     := true.B
//           dcache_read_req_valid := false.B
//           state                 := dWait
//         }.otherwise {
//           // 非法地址
//           dcache_buffer         := 0.U
//           dcache_data_valid     := true.B
//           dcache_read_req_valid := false.B
//           state                 := dWait
//         }
//       }.elsewhen(icache_req_valid) {
//         when(isBaseAddr(icache_req_addr)) {
//           current_req_type := reqIcache
//           current_ram      := ramBase
//           base_ram_ctrl.read(icache_req_addr(21, 2))
//           wait_counter  := 0.U
//           icache_offset := 0.U
//           state         := iREAD
//         }.elsewhen(isExtAddr(icache_req_addr)) {
//           current_req_type := reqIcache
//           current_ram      := ramExt
//           ext_ram_ctrl.read(icache_req_addr(21, 2))
//           wait_counter  := 0.U
//           icache_offset := 0.U
//           state         := iREAD
//         }.otherwise {
//           // 非法地址
//           icache_buffer     := VecInit(Seq.fill(FETCH_WIDTH)(0.U(32.W)))
//           icache_data_valid := true.B
//           icache_req_valid  := false.B
//           state             := iWait
//         }
//       }
//     }

//     is(iREAD) {
//       when(icache_offset === (FETCH_WIDTH - 1).U) {
//         when(wait_counter === SRAM_DELAY.U) {
//           val data = Mux(current_ram === ramBase, io.base_ram_ctrl.data_in, io.ext_ram_ctrl.data_in)
//           icache_buffer(icache_offset) := EndianConvert(data)
//           when(current_ram === ramBase) {
//             base_ram_ctrl.idle()
//           }.otherwise {
//             ext_ram_ctrl.idle()
//           }
//           icache_data_valid := true.B
//           icache_req_valid  := false.B
//           state             := iWait
//         }.otherwise {
//           wait_counter := wait_counter + 1.U
//         }
//       }.otherwise {
//         when(wait_counter === SRAM_DELAY.U) {
//           val data = Mux(current_ram === ramBase, io.base_ram_ctrl.data_in, io.ext_ram_ctrl.data_in)
//           icache_buffer(icache_offset) := EndianConvert(data)
//           icache_offset                := icache_offset + 1.U

//           val next_addr = Mux(current_ram === ramBase, base_ram_ctrl.addr, ext_ram_ctrl.addr) + 1.U
//           when(current_ram === ramBase) {
//             base_ram_ctrl.read(next_addr)
//           }.otherwise {
//             ext_ram_ctrl.read(next_addr)
//           }
//           wait_counter := 0.U
//         }.otherwise {
//           wait_counter := wait_counter + 1.U
//         }
//       }
//     }

//     is(iWait) {
//       state            := sIDLE
//       current_req_type := reqNone
//       current_ram      := ramNone
//     }

//     is(dREAD) {
//       when(wait_counter === SRAM_DELAY.U) {
//         val data = Mux(current_ram === ramBase, io.base_ram_ctrl.data_in, io.ext_ram_ctrl.data_in)
//         dcache_buffer         := EndianConvert(data)
//         dcache_data_valid     := true.B
//         dcache_read_req_valid := false.B
//         when(current_ram === ramBase) {
//           base_ram_ctrl.idle()
//         }.otherwise {
//           ext_ram_ctrl.idle()
//         }
//         state := dWait
//       }.otherwise {
//         wait_counter := wait_counter + 1.U
//       }
//     }

//     is(dWrite) {
//       // 写操作时序控制：
//       // 前2个周期WE为低，后2个周期WE为高
//       when(wait_counter < 2.U) {
//         // 继续保持WE为低
//         wait_counter := wait_counter + 1.U
//       }.elsewhen(wait_counter === 2.U) {
//         // 第3个周期：将WE拉高，但CE和BE继续保持低
//         when(current_ram === ramBase) {
//           base_ram_ctrl.write(
//             base_ram_ctrl.addr,
//             base_ram_ctrl.data_out,
//             base_ram_ctrl.be_n,
//             true.B // WE拉高
//           )
//         }.otherwise {
//           ext_ram_ctrl.write(
//             ext_ram_ctrl.addr,
//             ext_ram_ctrl.data_out,
//             ext_ram_ctrl.be_n,
//             true.B // WE拉高
//           )
//         }
//         wait_counter := wait_counter + 1.U
//       }.elsewhen(wait_counter < SRAM_DELAY.U) {
//         // 第4个周期：继续保持WE为高
//         wait_counter := wait_counter + 1.U
//       }.elsewhen(wait_counter === SRAM_DELAY.U) {
//         // 写操作完成，转入空闲状态
//         when(current_ram === ramBase) {
//           base_ram_ctrl.idle()
//         }.otherwise {
//           ext_ram_ctrl.idle()
//         }
//         dcache_data_valid      := true.B
//         dcache_write_req_valid := false.B
//         state                  := dWait
//       }.otherwise {
//         wait_counter := wait_counter + 1.U
//       }
//     }

//     is(dWriteWait) {
//       // 这个状态已经不需要了，可以删除
//       state := dWait
//     }

//     is(dWait) {
//       txd_uart_start   := false.B
//       state            := sIDLE
//       current_req_type := reqNone
//       current_ram      := ramNone
//     }
//   }

//   // 复位处理
//   when(reset.asBool) {
//     base_ram_ctrl.idle()
//     ext_ram_ctrl.idle()
//     uart_buffer.foreach(i => {
//       i.data := 0.U
//     })
//     state                  := sIDLE
//     current_req_type       := reqNone
//     current_ram            := ramNone
//     wait_counter           := 0.U
//     icache_offset          := 0.U
//     icache_data_valid      := false.B
//     dcache_data_valid      := false.B
//     txd_uart_start         := false.B
//     txd_uart_data          := 0.U
//     maybe_full             := false.B
//     uart_head              := 1.U(UART_BUFFER_DEPTH.W)
//     uart_tail              := 1.U(UART_BUFFER_DEPTH.W)
//     icache_req_valid       := false.B
//     dcache_read_req_valid  := false.B
//     dcache_write_req_valid := false.B
//     icache_req_addr        := 0.U
//     dcache_read_req_addr   := 0.U
//     dcache_write_req_addr  := 0.U
//     dcache_write_req_data  := 0.U
//     dcache_write_req_mask  := 0.U
//   }
// }
