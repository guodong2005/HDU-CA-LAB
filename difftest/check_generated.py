#!/usr/bin/env python3
from pathlib import Path
import sys

difftest = Path(__file__).resolve().parent
repo = difftest.parent
generated = difftest / "core_top.v"
sources = sorted((repo / "chisel/playground/src").rglob("*.scala"))
if not generated.exists():
    print("ERROR: difftest/core_top.v is missing; run make -C chisel verilog", file=sys.stderr)
    raise SystemExit(2)
if sources and max(p.stat().st_mtime_ns for p in sources) > generated.stat().st_mtime_ns:
    print("ERROR: difftest/core_top.v is older than Chisel sources; run make -C chisel verilog", file=sys.stderr)
    raise SystemExit(2)
print("generated Verilog freshness: PASS")
