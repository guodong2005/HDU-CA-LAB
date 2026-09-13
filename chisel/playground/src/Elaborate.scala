import circt.stage._
import chisel3.stage._

object Elaborate extends App {
  val annotations = Seq(
    ChiselGeneratorAnnotation(() => new core_top),
    CIRCTTargetAnnotation(CIRCTTarget.Verilog),
    FirtoolOption("--strip-debug-info")
  )
  (new ChiselStage).execute(args, annotations)
}
