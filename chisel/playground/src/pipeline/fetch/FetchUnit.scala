package cpu.pipeline
import chisel3._
import chisel3.util._
import cpu.defines.Const._
import cpu.defines._

class FetchUnit extends Module {
  val io = IO(new Bundle {
    val decodeStage = new FetchUnitDecodeUnit()
    val icache_resp = Flipped(Valid(new InstPacket))
    val branch      = Input(Bool())
    val target      = Input(UInt(XLEN.W))
    val signal      = Input(new Signals())
    val icache_req  = Decoupled(new ICacheReq)
    val canStart    = Output(Bool())
  })

  val pc       = RegInit(PC_INIT)
  val reqPC    = Reg(UInt(XLEN.W))
  val state    = RegInit(0.U(2.W))
  val sIdle    = 0.U
  val sWait    = 1.U
  val ifid_reg = RegInit(0.U.asTypeOf(new IfIdData()))

  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid
  val instIdx     = pc(ICACHE_OFFSET_WIDTH - 1, 2)

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := state === sIdle && !stall && RegNext(canStart)

  // 当前请求的指令索引，响应地址直接匹配请求的PC
  val currentInstIdx = pc(ICACHE_OFFSET_WIDTH - 1, 2)
  val respMatchAddr  = io.icache_resp.bits.addr === pc // 直接匹配pc，不是对齐后的地址

  // 从cache line中提取指令的组合逻辑
  def extractInst(data: UInt, idx: UInt): UInt = {
    MuxLookup(idx, 0.U)(
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

  // 等待状态下的指令提取
  val waitingInstIdx   = reqPC(ICACHE_OFFSET_WIDTH - 1, 2)
  val waitingMatchAddr = io.icache_resp.bits.addr === reqPC // 直接匹配reqPC

  // 默认输出
  io.icache_req.bits.addr := pc
  io.icache_req.valid     := false.B
  io.decodeStage.data     := 0.U.asTypeOf(new IfIdData())

  // 分支处理：立即更新PC并发送新请求
  when(io.branch) {
    pc             := io.target
    state          := sIdle
    ifid_reg.valid := false.B
    // 分支时立即发送新地址请求
    io.icache_req.bits.addr := io.target
    io.icache_req.valid     := true.B
  }.otherwise {

    switch(state) {
      is(sIdle) {
        // 初始化PC
        when(canStart && pc === 0.U) {
          pc := PC_INIT
        }

        when(io.canStart) {
          // 发送icache请求
          io.icache_req.valid     := true.B
          io.icache_req.bits.addr := pc

          when(io.icache_req.ready) {
            // 检查是否同周期返回响应（单周期hit）
            when(io.icache_resp.valid && respMatchAddr) {
              // 单周期hit：直接处理响应
              val inst = extractInst(io.icache_resp.bits.data, currentInstIdx)

              when(decodeReady) {
                // 直接传递给decode stage
                io.decodeStage.data.inst  := inst
                io.decodeStage.data.pc    := pc
                io.decodeStage.data.valid := true.B
                pc                        := pc + 4.U
                // 保持在sIdle状态，可以连续处理
              }.otherwise {
                // decode没ready，缓存指令
                ifid_reg.inst  := inst
                ifid_reg.pc    := pc
                ifid_reg.valid := true.B
                pc             := pc + 4.U
              }
            }.otherwise {
              // 没有同周期响应，进入等待状态
              reqPC := pc
              state := sWait
            }
          }
        }
      }

      is(sWait) {
        // 等待icache响应
        when(io.icache_resp.valid && waitingMatchAddr) {
          val inst = extractInst(io.icache_resp.bits.data, waitingInstIdx)

          when(decodeReady) {
            // 直接传递给decode stage
            io.decodeStage.data.inst  := inst
            io.decodeStage.data.pc    := reqPC
            io.decodeStage.data.valid := true.B
            pc                        := reqPC + 4.U
            state                     := sIdle
          }.otherwise {
            // decode没ready，缓存指令
            ifid_reg.inst  := inst
            ifid_reg.pc    := reqPC
            ifid_reg.valid := true.B
            pc             := reqPC + 4.U
            state          := sIdle
          }
        }
      }
    }

    // 处理缓存的指令
    when(ifid_reg.valid && decodeReady) {
      io.decodeStage.data := ifid_reg
      ifid_reg.valid      := false.B
    }
  }
}

/*
修正要点：

1. 地址匹配修正：
   - respMatchAddr: io.icache_resp.bits.addr === pc (原来是alignedPC)
   - waitingMatchAddr: io.icache_resp.bits.addr === reqPC (原来用了复杂的对齐计算)

2. 逻辑简化：
   - 直接匹配发送出去的地址，不需要额外的对齐计算
   - ICache内部会处理地址对齐，FetchUnit只需要匹配请求的原始地址

3. 正确性：
   - 确保响应确实对应当前或等待中的请求
   - 避免处理不匹配的响应数据

这样修改后，逻辑更加清晰简单，也更容易验证正确性。
 */
