#!/usr/bin/env python3
import csv
import re
import sys
from pathlib import Path


def cycles(path):
    values = []
    for line in Path(path).read_text().splitlines():
        match = re.search(r"^TRACE cycle=(\d+) ", line)
        if match:
            values.append(int(match.group(1)))
    if not values:
        raise RuntimeError(f"no trace rows in {path}")
    return max(values) + 1


if len(sys.argv) not in (3, 4):
    print(f"usage: {sys.argv[0]} OVERLAPPED SEQUENTIAL [CSV]", file=sys.stderr)
    raise SystemExit(2)

overlap = cycles(sys.argv[1])
sequential = cycles(sys.argv[2])
if sequential <= 0 or overlap <= 0:
    print("FAIL: invalid cycle count", file=sys.stderr)
    raise SystemExit(1)

saved = sequential - overlap
saved_percent = saved / sequential * 100.0
speedup = sequential / overlap
print(f"sequential_cycles={sequential}")
print(f"overlapped_cycles={overlap}")
print(f"saved_cycles={saved}")
print(f"saved_percent={saved_percent:.2f}%")
print(f"speedup={speedup:.6f}")

if len(sys.argv) == 4:
    with Path(sys.argv[3]).open("w", newline="") as output:
        writer = csv.writer(output)
        writer.writerow(("mode", "cycles"))
        writer.writerow(("sequential", sequential))
        writer.writerow(("overlapped", overlap))

if overlap >= sequential:
    print("FAIL: asynchronous overlap did not improve execution time", file=sys.stderr)
    raise SystemExit(1)
