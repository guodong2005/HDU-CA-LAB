#!/usr/bin/env python3
import re
import sys
from pathlib import Path

if len(sys.argv) != 2:
    print(f"usage: {sys.argv[0]} TRACE", file=sys.stderr)
    raise SystemExit(2)

text = Path(sys.argv[1]).read_text()
rows = []
for line in text.splitlines():
    if line.startswith("TRACE "):
        fields = dict(re.findall(r"(\w+)=([0-9a-fA-F]+)", line))
        if fields:
            rows.append({k: int(v, 16) if k in {"pc", "instr"} else int(v) for k, v in fields.items()})
if not rows:
    print("FAIL: no trace rows", file=sys.stderr)
    raise SystemExit(1)
commits = [r for r in rows if r.get("commit")]
launches = [r for r in rows if r.get("cube_launch")]
vector_issues = [r for r in rows if r.get("vector_issue")]
busy_scalar = [r for r in rows if r.get("cube_busy") and r.get("commit") and not r.get("vector_issue")]
busy_vector = [r for r in rows if r.get("cube_busy") and r.get("vector_issue")]
wait_stalls = [r for r in rows if r.get("cube_wait_stall")]
done = [r for r in rows if r.get("cube_done")]
pcs = [r["pc"] for r in commits]
checks = {
    "two cube launches": len(launches) == 2,
    "vector issue": len(vector_issues) >= 4,
    "scalar commit while busy": bool(busy_scalar),
    "vector issue while busy": bool(busy_vector),
    "cube.wait stalls": bool(wait_stalls),
    "cube done pulse": len(done) >= 1,
    "no duplicate commit PC": len(pcs) == len(set(pcs)),
    "no EBREAK commit": all(r.get("instr") != 0x00100073 for r in commits),
}
for name, ok in checks.items():
    print(f"{name}: {'PASS' if ok else 'FAIL'}")
if not all(checks.values()):
    raise SystemExit(1)
print(f"heterogeneous trace: PASS, cycles={len(rows)} commits={len(commits)} launches={len(launches)}")
