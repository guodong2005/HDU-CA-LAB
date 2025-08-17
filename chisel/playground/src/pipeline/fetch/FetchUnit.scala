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
  val alignedPC   = pc & ~((1 << ICACHE_OFFSET_WIDTH) - 1).U
  val instIdx     = pc(ICACHE_OFFSET_WIDTH - 1, 2)

  // 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := state === sIdle && !stall && RegNext(canStart)

  // 当前请求的指令索引和地址匹配
  val currentInstIdx = pc(ICACHE_OFFSET_WIDTH - 1, 2)
  val respMatchAddr  = io.icache_resp.bits.addr === alignedPC

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
  val waitingMatchAddr = io.icache_resp.bits.addr === (reqPC & ~((1 << ICACHE_OFFSET_WIDTH) - 1).U)

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
关键改进点：

1. 单周期响应检测：
   - 在sIdle状态发送请求的同时检查io.icache_resp.valid
   - 如果同周期返回响应且地址匹配，直接处理
   - 避免不必要的状态转换

2. 组合逻辑路径：
   icache_req.valid → ICache hit检测 → icache_resp.valid → FetchUnit处理
   整个路径在同一个周期完成

3. 连续请求能力：
   - hit情况下保持在sIdle状态
   - 每周期可以处理一个hit请求
   - 支持指令流的连续fetch

4. 兼容性：
   - 仍然支持多周期响应（miss情况）
   - 自动适应icache的响应时序

5. 性能提升：
   - hit延迟：从2周期减少到1周期
   - 吞吐量：连续hit时每周期一条指令
   - 分支恢复：分支后立即发送新请求

配合寄存器实现的ICache，这样的FetchUnit可以实现：
- 单周期指令fetch（hit情况）
- 连续的指令流处理能力
- 最小的分支延迟

注意：需要确保ICache的icache_resp.valid在请求的同周期就能正确返回（对于hit情况）
 */
