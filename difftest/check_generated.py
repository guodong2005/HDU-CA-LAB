#!/usr/bin/env python3
from pathlib import Path
import hashlib
import sys

Difftest = Path(__file__).resolve().parent
Repo = Difftest.parent
Generated = Difftest / "core_top.v"
Manifest = Difftest / "core_top.v.sha256"


def source_files():
    files = list((Repo / "chisel/playground/src").rglob("*.scala"))
    files.append(Repo / "chisel/build.sc")
    return sorted(p for p in files if p.is_file())


def source_hash():
    digest = hashlib.sha256()
    for path in source_files():
        digest.update(str(path.relative_to(Repo)).encode())
        digest.update(b"\0")
        digest.update(path.read_bytes())
        digest.update(b"\0")
    return digest.hexdigest()


def write_manifest():
    if not Generated.exists():
        print("ERROR: difftest/core_top.v is missing; generate it first", file=sys.stderr)
        return 2
    Manifest.write_text(source_hash() + "\n")
    print("generated Verilog manifest: WRITTEN")
    return 0


def check():
    if not Generated.exists():
        print("ERROR: difftest/core_top.v is missing; run make -C chisel verilog", file=sys.stderr)
        return 2
    expected = source_hash()
    if not Manifest.exists():
        print("ERROR: difftest/core_top.v.sha256 is missing; regenerate Verilog", file=sys.stderr)
        return 2
    actual = Manifest.read_text().strip()
    if actual != expected:
        print("ERROR: generated RTL does not match current Chisel sources; regenerate Verilog", file=sys.stderr)
        return 2
    print("generated Verilog freshness: PASS")
    return 0


if __name__ == "__main__":
    sys.exit(write_manifest() if "--write-manifest" in sys.argv else check())
