package cpu.pipeline

import chisel3._
import chisel3.util._
import cpu.defines._
import cpu.defines.Const._
import cpu.CpuConfig
import coursier.Fetch

class FetchPassData extends Bundle {
  val pc    = UInt(XLEN.W)
  val inst  = UInt(XLEN.W)
  val valid = Bool()
}

class FetchPassUnit extends Bundle {
  val data = new FetchPassData()
}
class PassStage extends Module {
  val io = IO(new Bundle {
    val fetchUnit     = Input(new FetchPassUnit())
    val controlSignal = Input(new Signals())
    val passUnit      = Output(new FetchPassUnit())
  })

  val data = RegInit(0.U.asTypeOf(new FetchPassData()))
  when(io.controlSignal.passUnitSignal.allow_to_go === false.B) {
    data := data
  }.otherwise {
    data := io.fetchUnit.data // Update data if units are allowed to proceed
  }
  // flush logic:
  when(io.controlSignal.memoryUnitSignal.do_flush === true.B) {
    data := 0.U.asTypeOf(new FetchPassData()) // Reset data if flush signal is high
  }
  // Output the data to the next stage
  io.passUnit.data := data
}
