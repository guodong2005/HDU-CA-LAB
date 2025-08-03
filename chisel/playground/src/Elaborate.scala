import cpu._
import circt.stage._
import chisel3.stage._
import firrtl.options.TargetDirAnnotation

object Elaborate extends App {
  implicit val cpuConfig = new CpuConfig()
  def top                = new core_top()

  val generator = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))

  val annotations = generator ++ Seq(
    CIRCTTargetAnnotation(CIRCTTarget.Verilog),
    FirtoolOption("--strip-debug-info"),
    FirtoolOption("--disable-annotation-unknown")
  )

  (new ChiselStage).execute(args, annotations)
}
