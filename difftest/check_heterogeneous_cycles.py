#!/usr/bin/env python3
import re
import sys
from pathlib import Path

def cycles(path):
    values=[]
    for line in Path(path).read_text().splitlines():
        m=re.search(r"^TRACE cycle=(\d+) ", line)
        if m: values.append(int(m.group(1)))
    if not values: raise RuntimeError(f"no trace rows in {path}")
    return max(values)

if len(sys.argv) != 3:
    print(f"usage: {sys.argv[0]} OVERLAPPED SEQUENTIAL", file=sys.stderr)
    raise SystemExit(2)
overlap=cycles(sys.argv[1]); sequential=cycles(sys.argv[2])
if sequential <= 0 or overlap <= 0:
    raise SystemExit("invalid cycle count")
print(f"sequential_cycles={sequential}")
print(f"overlapped_cycles={overlap}")
print(f"speedup={sequential / overlap:.6f}")
if overlap >= sequential:
    print("WARNING: overlap did not reduce total cycles")
