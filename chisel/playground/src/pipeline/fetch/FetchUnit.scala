package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

// ========== PreFetch阶段：负责PC管理和发送请求 ==========
class PreFetchUnit extends Module {
  val io = IO(new Bundle {
    val fetchStage = new Bundle {
      val req_valid = Output(Bool())
      val req_pc    = Output(UInt(XLEN.W))
      val req_ready = Input(Bool()) // FetchUnit是否可以接受新请求
    }
    val icache_req = Decoupled(new ICacheReq)
    val branch     = Input(Bool())
    val target     = Input(UInt(XLEN.W))
    val canStart   = Output(Bool())
  })

  // PC寄存器
  val pc = RegInit(PC_INIT)

  // 控制信号
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := canStart

  // 默认输出
  io.fetchStage.req_valid := false.B
  io.fetchStage.req_pc    := pc
  io.icache_req.valid     := false.B
  io.icache_req.bits.addr := pc

  // ========== 主逻辑 ==========
  when(canStart && !io.branch) {
    // 向FetchUnit发送请求
    io.fetchStage.req_valid := true.B
    io.fetchStage.req_pc    := pc

    // 同时向ICache发送请求
    io.icache_req.valid     := true.B
    io.icache_req.bits.addr := pc

    // 当两者都准备好时，更新PC
    when(io.fetchStage.req_ready && io.icache_req.ready) {
      pc := pc + 4.U
    }
  }

  // ========== 分支处理 ==========
  when(io.branch) {
    pc := io.target
  }

  // ========== 初始化处理 ==========
  when(canStart && pc === 0.U && !io.branch) {
    pc := PC_INIT
  }

  // Debug
  dontTouch(pc)
}

// ========== Fetch阶段：负责接收响应和指令缓冲 ==========
class FetchUnit extends Module {
  val io = IO(new Bundle {
    val preFetchStage = Flipped(new Bundle {
      val req_valid = Input(Bool())
      val req_pc    = Input(UInt(XLEN.W))
      val req_ready = Output(Bool())
    })
    val decodeStage = new FetchUnitDecodeUnit()
    val icache_resp = Flipped(Valid(new InstPacket))
    val branch      = Input(Bool())
    val signal      = Input(new Signals())
  })

  // 等待响应的请求队列（FIFO）
  val pending_queue = Module(new Queue(UInt(XLEN.W), entries = 2))

  // 指令缓冲
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  // 控制信号
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val bufferFull  = ifid_reg.valid && !decodeReady

  // 指令提取辅助函数
  def extractInst(data: UInt, pc: UInt): UInt = {
    val instIdx = pc(ICACHE_OFFSET_WIDTH - 1, 2)
    MuxLookup(instIdx, 0.U)(
      Seq(
        0.U -> data(31, 0),
        1.U -> data(63, 32),
        2.U -> data(95, 64),
        3.U -> data(127, 96),
        4.U -> data(159, 128),
        5.U -> data(191, 160),
        6.U -> data(223, 192),
        7.U -> data(255, 224)
      )
    )
  }

  // ========== 接收PreFetch请求 ==========
  pending_queue.io.enq.valid := io.preFetchStage.req_valid
  pending_queue.io.enq.bits  := io.preFetchStage.req_pc
  io.preFetchStage.req_ready := pending_queue.io.enq.ready

  // ========== 处理ICache响应 ==========
  pending_queue.io.deq.ready := false.B

  when(io.icache_resp.valid && pending_queue.io.deq.valid) {
    val resp_addr     = io.icache_resp.bits.addr
    val expected_addr = pending_queue.io.deq.bits

    when(resp_addr === expected_addr) {
      // 地址匹配，处理响应
      val inst = extractInst(io.icache_resp.bits.data, expected_addr)

      when(!bufferFull) {
        // 缓冲区可用，存储指令
        ifid_reg.inst  := inst
        ifid_reg.pc    := expected_addr
        ifid_reg.valid := true.B

        // 标记请求已完成
        pending_queue.io.deq.ready := true.B
      }
      // 如果缓冲区满，等待下一个周期
    }
  }

  // ========== 向Decode阶段传递指令 ==========
  io.decodeStage.data.valid := false.B
  io.decodeStage.data.inst  := DontCare
  io.decodeStage.data.pc    := DontCare

  when(ifid_reg.valid && decodeReady && !io.branch) {
    io.decodeStage.data := ifid_reg
    ifid_reg.valid      := false.B
  }

  // ========== 分支处理 ==========
  when(io.branch) {
    // 清空所有状态
    ifid_reg.valid             := false.B
    pending_queue.io.deq.ready := true.B // 清空队列
  }

  // Debug
  dontTouch(ifid_reg)
  dontTouch(bufferFull)
}

// ========== 顶层模块：组合PreFetch和Fetch ==========
class FetchUnitWithPreFetch extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val icache_resp = Flipped(Valid(new InstPacket))
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(new ICacheReq)
    val canStart    = Output(Bool())
  })

  // 实例化两个阶段
  val preFetchUnit = Module(new PreFetchUnit)
  val fetchUnit    = Module(new FetchUnit)

  // ========== 连接PreFetch和Fetch ==========
  fetchUnit.io.preFetchStage <> preFetchUnit.io.fetchStage

  // ========== 外部接口连接 ==========
  // PreFetch阶段
  preFetchUnit.io.icache_req <> io.icache_req
  preFetchUnit.io.branch := io.branch
  preFetchUnit.io.target := io.target
  io.canStart            := preFetchUnit.io.canStart

  // Fetch阶段
  fetchUnit.io.decodeStage <> io.decodeStage
  fetchUnit.io.icache_resp <> io.icache_resp
  fetchUnit.io.branch := io.branch
  fetchUnit.io.signal <> io.signal
}

// ========== 使用示例 ==========
/*
class ExampleCPU extends Module {
  val io = IO(new Bundle {
    // ... 其他接口
  })

  // 直接替换原来的FetchUnit
  val fetchUnit = Module(new FetchUnitWithPreFetch)

  // 连接接口
  fetchUnit.io.decodeStage <> decodeStage.io.fetchUnit
  fetchUnit.io.icache_resp <> icache.io.resp
  fetchUnit.io.branch      := branch_signal
  fetchUnit.io.target      := branch_target
  fetchUnit.io.signal      <> control_signals
  fetchUnit.io.icache_req  <> icache.io.req

  // ... 其他连接
}
 */
