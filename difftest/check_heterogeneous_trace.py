#!/usr/bin/env python3
import re
import sys
from pathlib import Path

if len(sys.argv) != 2:
    print(f"usage: {sys.argv[0]} TRACE", file=sys.stderr)
    raise SystemExit(2)

rows = []
for line in Path(sys.argv[1]).read_text().splitlines():
    if not line.startswith("TRACE "):
        continue
    fields = dict(re.findall(r"(\w+)=([0-9a-fA-F]+)", line))
    if fields:
        rows.append({k: int(v, 16) if k in {"pc", "instr"} else int(v)
                     for k, v in fields.items()})
if not rows:
    print("FAIL: no trace rows", file=sys.stderr)
    raise SystemExit(1)

commits = [r for r in rows if r.get("commit")]
launches = [r for r in rows if r.get("cube_launch")]
vector_issues = [r for r in rows if r.get("vector_issue")]
busy = [r for r in rows if r.get("cube_busy")]
busy_vector_issue = [r for r in busy if r.get("vector_issue")]
busy_commits = [r for r in busy if r.get("commit")]
busy_vector_commit = [r for r in busy_commits if r.get("instr", 0) & 0x7f == 0x0b]
busy_scalar_commit = [r for r in busy_commits if r.get("instr", 0) & 0x7f not in (0x0b, 0x2b)]
wait_stalls = [r for r in rows if r.get("cube_wait_stall")]
wait_commits = [r for r in commits if r.get("instr", 0) & 0x7f == 0x2b and
                ((r.get("instr", 0) >> 12) & 7) == 1]
done = [r for r in rows if r.get("cube_done")]
wait_release = [r for r in wait_commits if not r.get("cube_busy") and
                any(s.get("cycle", -1) < r.get("cycle", -1) for s in wait_stalls) and
                any(d.get("cycle", -1) < r.get("cycle", -1) for d in done)]
pcs = [r["pc"] for r in commits]

checks = {
    "two cube launches": len(launches) == 2,
    "vector issue": len(vector_issues) >= 4,
    "scalar commit while busy": bool(busy_scalar_commit),
    "vector issue while busy": bool(busy_vector_issue),
    "vector commit while busy": bool(busy_vector_commit),
    "cube.wait stalls": bool(wait_stalls),
    "cube.wait release": len(wait_release) == 1,
    "cube done pulse": len(done) >= 1,
    "no duplicate commit PC": len(pcs) == len(set(pcs)),
    "no EBREAK commit": all(r.get("instr") != 0x00100073 for r in commits),
}
for name, ok in checks.items():
    print(f"{name}: {'PASS' if ok else 'FAIL'}")
if not all(checks.values()):
    raise SystemExit(1)
print(f"heterogeneous trace: PASS, cycles={len(rows)} commits={len(commits)} launches={len(launches)}")
