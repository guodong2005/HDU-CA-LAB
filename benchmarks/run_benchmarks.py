#!/usr/bin/env python3
"""Run the repository's real RV32 Verilator benchmarks and emit CSV/Markdown."""
from __future__ import annotations
import csv, re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "benchmarks" / "results"
BIN = OUT / "bin"
SIM = ROOT / "difftest" / "obj_dir" / "Vcore_top"
CC = "riscv64-unknown-elf-gcc"
OBJCOPY = "riscv64-unknown-elf-objcopy"

CASES = [
    ("scalar", "arithmetic", ROOT/"benchmarks/programs/scalar_arithmetic.S", "normal", ""),
    ("scalar", "branch", ROOT/"benchmarks/programs/scalar_branch.S", "normal", ""),
    ("scalar", "sequential_memory", ROOT/"benchmarks/programs/sequential_memory.S", "normal", ""),
    ("scalar", "random_memory", ROOT/"benchmarks/programs/random_memory.S", "normal", ""),
    ("scalar", "muldiv", ROOT/"benchmarks/programs/muldiv.S", "normal", ""),
    ("icache", "sequential_fetch", ROOT/"benchmarks/programs/icache_sequential.S", "normal", "sequential"),
    ("icache", "small_loop", ROOT/"benchmarks/programs/icache_small_loop.S", "normal", "small_loop"),
    ("icache", "over_capacity", ROOT/"benchmarks/programs/icache_over_capacity.S", "normal", "over_capacity"),
]
for n in (8, 16, 32, 64):
    CASES += [("vector", f"gather_{n}", ROOT/f"benchmarks/programs/vector_gather_{n}.S", "normal", str(n)),
              ("vector", f"shift_{n}", ROOT/f"benchmarks/programs/vector_shift_{n}.S", "normal", str(n))]
CASES += [
    ("cube", "sequential", ROOT/"chisel/playground/test/resources/rv32_heterogeneous_sequential.S", "normal", "6 tasks"),
    ("cube", "overlapped", ROOT/"chisel/playground/test/resources/rv32_heterogeneous_overlap.S", "normal", "6 tasks"),
    ("axi", "sequential_memory_backpressure", ROOT/"benchmarks/programs/sequential_memory.S", "backpressure", "64 stores/loads"),
]
for n in (1, 2, 3, 6):
    CASES += [("cube_parallel", f"sequential_{n}", ROOT/f"benchmarks/programs/cube_tasks_{n}_sequential.S", "normal", str(n)),
              ("cube_parallel", f"overlapped_{n}", ROOT/f"benchmarks/programs/cube_tasks_{n}_overlap.S", "normal", str(n))]


def run(cmd, **kw):
    print("+", " ".join(map(str, cmd)), flush=True)
    return subprocess.run(cmd, cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, **kw)


def build():
    OUT.mkdir(parents=True, exist_ok=True); BIN.mkdir(parents=True, exist_ok=True)
    r = run(["make", "-C", "chisel", "verilog"])
    if r.returncode: raise RuntimeError(r.stdout)
    r = run(["cp", "chisel/build/core_top.v", "difftest/core_top.v"])
    if r.returncode: raise RuntimeError(r.stdout)
    r = run(["python3", "difftest/check_generated.py", "--write-manifest"])
    if r.returncode: raise RuntimeError(r.stdout)


def one(category, name, source, option, size):
    stem = category + "_" + name
    elf = BIN/(stem+".elf"); binary = BIN/(stem+".bin")
    r = run([CC, "-march=rv32im", "-mabi=ilp32", "-nostdlib", "-nostartfiles",
             "-Wl,-Ttext=0x80000000", str(source), "-o", str(elf)])
    if r.returncode: raise RuntimeError(f"compile {name}:\n{r.stdout}")
    r = run([OBJCOPY, "-O", "binary", str(elf), str(binary)])
    if r.returncode: raise RuntimeError(f"objcopy {name}:\n{r.stdout}")
    opts = ["--metrics"] + (["--backpressure"] if option == "backpressure" else [])
    r = run(["make", "-C", "difftest", "sim", f"PROGRAM={binary}", f"OPTIONS={' '.join(opts)}"], timeout=600)
    text = r.stdout
    if r.returncode or "DIFFTEST PASS:" not in text:
        raise RuntimeError(f"{name} failed (rc={r.returncode}):\n{text}")
    match = re.search(r"^METRICS (.+)$", text, re.MULTILINE)
    if not match: raise RuntimeError(f"{name}: missing METRICS line")
    values = dict(item.split("=", 1) for item in match.group(1).split())
    values.update({"category": category, "benchmark": name, "input_size": size,
                   "mode": option, "correctness": "PASS"})
    return values


def cube_trace_summary(binary):
    r = run(["make", "-C", "difftest", "sim", f"PROGRAM={binary}", "OPTIONS=--heterogeneous-trace"], timeout=600)
    if r.returncode or "DIFFTEST PASS:" not in r.stdout:
        raise RuntimeError(f"cube trace failed (rc={r.returncode}):\n{r.stdout}")
    rows = []
    for line in r.stdout.splitlines():
        if not line.startswith("TRACE "):
            continue
        fields = dict(item.split("=", 1) for item in line.split()[1:])
        rows.append({k: int(v, 16) if k in {"pc", "instr"} else int(v) for k, v in fields.items()})
    launches = [r["cycle"] for r in rows if r.get("cube_launch")]
    done = [r["cycle"] for r in rows if r.get("cube_done")]
    waits = [r for r in rows if r.get("cube_wait_stall")]
    if not rows or not launches or not done:
        raise RuntimeError("cube trace missing launch or done events")
    return {"cycles": max(r["cycle"] for r in rows) + 1,
            "launch_cycles": launches, "done_cycles": done,
            "launch_interval": launches[1] - launches[0] if len(launches) > 1 else 0,
            "wait_stall_cycles": len(waits)}


def main():
    build()
    rows = []
    for case in CASES:
        print(f"\n=== {case[0]}/{case[1]} ===", flush=True)
        rows.append(one(*case))
    cube_trace = cube_trace_summary(BIN/"cube_parallel_overlapped_6.bin")
    rows += [
        {"category": "store_fifo", "benchmark": "depth4_vs_disabled", "input_size": "not implemented", "mode": "unavailable", "correctness": "UNAVAILABLE"},
        {"category": "uart", "benchmark": "rv32_mmio_output", "input_size": "no RV32 UART port", "mode": "unavailable", "correctness": "UNAVAILABLE"},
    ]
    fields = ["category", "benchmark", "input_size", "mode", "correctness", "cycles", "instructions", "cpi",
              "cache_accesses", "cache_hits", "cache_misses", "cache_hit_rate", "cache_miss_stall_cycles",
              "stores", "axi_ar_stall_cycles", "axi_aw_stall_cycles", "axi_w_stall_cycles", "vector_issues",
              "cube_launches", "cube_busy_cycles", "cube_wait_cycles"]
    csv_path = OUT/"benchmark_results.csv"
    with csv_path.open("w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fields, lineterminator="\n"); w.writeheader()
        for row in rows: w.writerow({k: row.get(k, "") for k in fields})
    report = OUT/"benchmark_report.md"
    by = {(r["category"], r["benchmark"]): r for r in rows}
    lines = ["# HDU-CA-LAB 教学型处理器数据测试报告", "", "所有数值来自当前提交的真实 Verilator 仿真；正确性由逐条 RV32IM difftest 判定。", "",
             "## 测量口径", "", "- `cycles`：复位释放后的仿真周期，到 Core 报告 halted 为止。", "- `instructions`：scalar architectural commit 数；EBREAK 不计入。", "- `CPI = cycles / instructions`。", "- Cache 统计来自当前实际 `AxiCache(4)`，不是假设的 2 KiB I-Cache；该模块为 4 行、每行 1 个 32-bit word 的统一直接映射 Cache。", "- 当前 RV32 路径没有 Store FIFO 和 UART MMIO，因此对应项目为未测，不生成伪造数据。", "", "## 实测汇总", "", "| 测试项目 | 输入规模 | 周期 | 指令数 | CPI | Cache 缺失 | 正确性 |", "|---|---:|---:|---:|---:|---:|---|"]
    for r in rows:
        if "cycles" not in r:
            continue
        lines.append(f"| {r['category']}/{r['benchmark']} | {r['input_size']} | {r['cycles']} | {r['instructions']} | {r['cpi']} | {r['cache_misses']} | {r['correctness']} |")
    lines += ["", "## 论文可直接引用的对比", "", "| 测试项目 | 基线周期 | 优化后周期 | 加速比 | 正确性 | 备注 |", "|---|---:|---:|---:|---|---|"]
    seq, ov = by.get(("cube", "sequential")), by.get(("cube", "overlapped"))
    if seq and ov:
        lines.append(f"| Cube 顺序/异步重叠 | {seq['cycles']} | {ov['cycles']} | {float(seq['cycles'])/float(ov['cycles']):.6f} | PASS/PASS | 6 个 Cube 任务，当前集群规格 |")
    for n in (8, 16, 32, 64):
        gather, shift = by[("vector", f"gather_{n}")], by[("vector", f"shift_{n}")]
        lines.append(f"| Vector Gather/Shift {n} elements | {gather['cycles']} | {shift['cycles']} | {float(gather['cycles'])/float(shift['cycles']):.6f} | PASS/PASS | 当前实现两条路径周期相同 |")
    for n in (1, 2, 3, 6):
        seq_n, ov_n = by[("cube_parallel", f"sequential_{n}")], by[("cube_parallel", f"overlapped_{n}")]
        lines.append(f"| Cube parallelism {n} tasks | {seq_n['cycles']} | {ov_n['cycles']} | {float(seq_n['cycles'])/float(ov_n['cycles']):.6f} | PASS/PASS | 任务数变化，6-engine 集群 |")
    lines += ["", "## AXI 与不可用项目", "", "- AXI 反压：`axi/sequential_memory_backpressure` 通过逐条 difftest；记录了 AR/AW/W 被 ready 拉低时的 stall 周期。", "- Store FIFO：源码中没有 Store FIFO 实现或深度配置，不能比较深度 4 与禁用状态，CSV 明确标记 `UNAVAILABLE`。", "- 2 KiB I-Cache：当前顶层实例是 `AxiCache(4)`，实际容量为 16 bytes 且为统一 Cache；本报告不把它标成 2 KiB I-Cache。", "- UART：当前 RV32 `core_top` 没有 UART MMIO 端口；仓库中的 UART 属于 LoongArch 仿真路径，CSV 明确标记 `UNAVAILABLE`。", "- LUT、寄存器、BRAM、DSP：未运行 FPGA 综合工具，因此没有资源估算。", "", "## 复现", "", "```bash", "python3 benchmarks/run_benchmarks.py", "```", ""]
    lines += ["", "## Cube 时序 trace", "", f"- 6-task overlapped trace cycles: {cube_trace['cycles']}", f"- launch cycles: {','.join(map(str, cube_trace['launch_cycles']))}", f"- first launch interval: {cube_trace['launch_interval']} cycles", f"- done cycles: {','.join(map(str, cube_trace['done_cycles']))}", f"- cube.wait stall cycles: {cube_trace['wait_stall_cycles']}", "", "## 复现", "", "```bash", "python3 benchmarks/run_benchmarks.py", "```", ""]
    report.write_text("\n".join(lines))
    print(f"WROTE {csv_path}")
    print(f"WROTE {report}")

if __name__ == "__main__":
    main()
