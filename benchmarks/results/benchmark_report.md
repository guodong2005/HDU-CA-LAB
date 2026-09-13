# HDU-CA-LAB 教学型处理器数据测试报告

所有数值来自当前提交的真实 Verilator 仿真；正确性由逐条 RV32IM difftest 判定。

## 测量口径

- `cycles`：复位释放后的仿真周期，到 Core 报告 halted 为止。
- `instructions`：scalar architectural commit 数；EBREAK 不计入。
- `CPI = cycles / instructions`。
- Cache 统计来自当前实际 `AxiCache(4)`，不是假设的 2 KiB I-Cache；该模块为 4 行、每行 1 个 32-bit word 的统一直接映射 Cache。
- 当前 RV32 路径没有 Store FIFO 和 UART MMIO，因此对应项目为未测，不生成伪造数据。

## 实测汇总

| 测试项目 | 输入规模 | 周期 | 指令数 | CPI | Cache 缺失 | 正确性 |
|---|---:|---:|---:|---:|---:|---|
| scalar/arithmetic |  | 932 | 303 | 3.075908 | 7 | PASS |
| scalar/branch |  | 8915 | 1302 | 6.847158 | 1702 | PASS |
| scalar/sequential_memory |  | 3028 | 387 | 7.824289 | 515 | PASS |
| scalar/random_memory |  | 3668 | 515 | 7.122330 | 643 | PASS |
| scalar/muldiv |  | 5021 | 1002 | 5.010978 | 804 | PASS |
| icache/sequential_fetch | sequential | 6618 | 1202 | 5.505824 | 1203 | PASS |
| icache/small_loop | small_loop | 646 | 127 | 5.086614 | 104 | PASS |
| icache/over_capacity | over_capacity | 3343 | 658 | 5.080547 | 666 | PASS |
| vector/gather_8 | 8 | 21 | 2 | 10.500000 | 3 | PASS |
| vector/shift_8 | 8 | 21 | 2 | 10.500000 | 3 | PASS |
| vector/gather_16 | 16 | 31 | 4 | 7.750000 | 5 | PASS |
| vector/shift_16 | 16 | 31 | 4 | 7.750000 | 5 | PASS |
| vector/gather_32 | 32 | 51 | 8 | 6.375000 | 9 | PASS |
| vector/shift_32 | 32 | 51 | 8 | 6.375000 | 9 | PASS |
| vector/gather_64 | 64 | 91 | 16 | 5.687500 | 17 | PASS |
| vector/shift_64 | 64 | 91 | 16 | 5.687500 | 17 | PASS |
| cube/sequential | 6 tasks | 3275 | 42 | 77.976190 | 43 | PASS |
| cube/overlapped | 6 tasks | 580 | 42 | 13.809524 | 43 | PASS |
| axi/sequential_memory_backpressure | 64 stores/loads | 3384 | 387 | 8.744186 | 515 | PASS |
| cube_parallel/sequential_1 | 1 | 530 | 2 | 265.000000 | 3 | PASS |
| cube_parallel/overlapped_1 | 1 | 530 | 2 | 265.000000 | 3 | PASS |
| cube_parallel/sequential_2 | 2 | 1049 | 4 | 262.250000 | 5 | PASS |
| cube_parallel/overlapped_2 | 2 | 540 | 4 | 135.000000 | 5 | PASS |
| cube_parallel/sequential_3 | 3 | 1568 | 6 | 261.333333 | 7 | PASS |
| cube_parallel/overlapped_3 | 3 | 550 | 6 | 91.666667 | 7 | PASS |
| cube_parallel/sequential_6 | 6 | 3125 | 12 | 260.416667 | 13 | PASS |
| cube_parallel/overlapped_6 | 6 | 580 | 12 | 48.333333 | 13 | PASS |

## 论文可直接引用的对比

| 测试项目 | 基线周期 | 优化后周期 | 加速比 | 正确性 | 备注 |
|---|---:|---:|---:|---|---|
| Cube 顺序/异步重叠 | 3275 | 580 | 5.646552 | PASS/PASS | 6 个 Cube 任务，当前集群规格 |
| Vector Gather/Shift 8 elements | 21 | 21 | 1.000000 | PASS/PASS | 当前实现两条路径周期相同 |
| Vector Gather/Shift 16 elements | 31 | 31 | 1.000000 | PASS/PASS | 当前实现两条路径周期相同 |
| Vector Gather/Shift 32 elements | 51 | 51 | 1.000000 | PASS/PASS | 当前实现两条路径周期相同 |
| Vector Gather/Shift 64 elements | 91 | 91 | 1.000000 | PASS/PASS | 当前实现两条路径周期相同 |
| Cube parallelism 1 tasks | 530 | 530 | 1.000000 | PASS/PASS | 任务数变化，6-engine 集群 |
| Cube parallelism 2 tasks | 1049 | 540 | 1.942593 | PASS/PASS | 任务数变化，6-engine 集群 |
| Cube parallelism 3 tasks | 1568 | 550 | 2.850909 | PASS/PASS | 任务数变化，6-engine 集群 |
| Cube parallelism 6 tasks | 3125 | 580 | 5.387931 | PASS/PASS | 任务数变化，6-engine 集群 |

## AXI 与不可用项目

- AXI 反压：`axi/sequential_memory_backpressure` 通过逐条 difftest；记录了 AR/AW/W 被 ready 拉低时的 stall 周期。
- Store FIFO：源码中没有 Store FIFO 实现或深度配置，不能比较深度 4 与禁用状态，CSV 明确标记 `UNAVAILABLE`。
- 2 KiB I-Cache：当前顶层实例是 `AxiCache(4)`，实际容量为 16 bytes 且为统一 Cache；本报告不把它标成 2 KiB I-Cache。
- UART：当前 RV32 `core_top` 没有 UART MMIO 端口；仓库中的 UART 属于 LoongArch 仿真路径，CSV 明确标记 `UNAVAILABLE`。
- LUT、寄存器、BRAM、DSP：未运行 FPGA 综合工具，因此没有资源估算。

## 复现

```bash
python3 benchmarks/run_benchmarks.py
```


## Cube 时序 trace

- 6-task overlapped trace cycles: 580
- launch cycles: 9,14,19,24,29,34
- first launch interval: 5 cycles
- done cycles: 522,527,532,537,542,547
- cube.wait stall cycles: 512

## 复现

```bash
python3 benchmarks/run_benchmarks.py
```
