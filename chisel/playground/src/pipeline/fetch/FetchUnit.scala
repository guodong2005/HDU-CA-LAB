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

  val pc    = RegInit(PC_INIT)
  val reqPC = Reg(UInt(XLEN.W))
  val state = RegInit(0.U(2.W)) // sIdle :: sWait
  val sIdle = 0.U
  val sWait = 1.U

  val ifid_reg    = RegInit(0.U.asTypeOf(new IfIdData()))
  val decodeReady = io.signal.fetchUnitSignal.allow_to_go
  val stall       = !decodeReady || ifid_reg.valid

  val alignedPC = pc & ~((1 << ICACHE_OFFSET_WIDTH) - 1).U
  val instIdx   = pc(ICACHE_OFFSET_WIDTH - 1, 2)

  // ✅ 启动条件
  val canStartInternal = !reset.asBool
  val canStart         = RegNext(canStartInternal) && canStartInternal
  io.canStart := state === sIdle && !stall && RegNext(canStart)

  // ✅ 默认输出
  io.icache_req.bits.addr := pc
  io.icache_req.valid     := io.canStart
  io.decodeStage.data     := 0.U.asTypeOf(new IfIdData())

  // ========== 修复后的逻辑 ==========

  // 分支处理：统一的PC更新逻辑
  when(io.branch) {
    pc             := io.target
    state          := sIdle
    ifid_reg.valid := false.B // 清除缓存的指令
  }.otherwise {
    switch(state) {
      is(sIdle) {
        when(canStart && pc === 0.U) {
          pc := PC_INIT
        }
        when(io.canStart && io.icache_req.ready) {
          reqPC := pc
          state := sWait
        }
      }
      is(sWait) {
        val respLineAddr = io.icache_resp.bits.addr
        val reqLineAddr  = reqPC & ~((1 << ICACHE_OFFSET_WIDTH) - 1).U
        val inst         = io.icache_resp.bits.data(reqPC(ICACHE_OFFSET_WIDTH - 1, 2))
        val matchAddr    = respLineAddr === reqLineAddr // 修复：应该比较line地址

        when(io.icache_resp.valid && matchAddr) {
          when(decodeReady) {
            io.decodeStage.data.inst  := inst
            io.decodeStage.data.pc    := reqPC
            io.decodeStage.data.valid := true.B
            pc                        := reqPC + 4.U // 正常情况下PC+4
            state                     := sIdle
          }.otherwise {
            ifid_reg.inst  := inst
            ifid_reg.pc    := reqPC
            ifid_reg.valid := true.B
            state          := sIdle // 回到idle状态，等待decode ready
          }
        }
      }
    }

    // 处理缓存的指令
    when(ifid_reg.valid && decodeReady) {
      io.decodeStage.data := ifid_reg
      ifid_reg.valid      := false.B
      pc                  := ifid_reg.pc + 4.U // 正常情况下PC+4
    }
  }

  // 分支时立即更新icache请求地址
  when(io.branch) {
    io.icache_req.bits.addr := io.target
    io.icache_req.valid     := true.B // 分支时立即发送新地址的请求
  }
}
