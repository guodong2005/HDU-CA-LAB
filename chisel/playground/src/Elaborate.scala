import cpu._
import circt.stage._
import chisel3.dontTouch

object Elaborate extends App {
  implicit val cpuConfig = new CpuConfig()
  def top                = new core_top()
  val generator          = Seq(chisel3.stage.ChiselGeneratorAnnotation(() => top))
  (new ChiselStage).execute(args, generator :+ CIRCTTargetAnnotation(CIRCTTarget.Verilog))
}
