# RV32IM AXI core

This tree contains a fresh single-issue RV32IM implementation. The previous fetch, decode, execute, writeback, cache, and SRAM-control state machines are not used.

## Interface

`core_top` exposes one AXI master:

- `AR/R`: instruction and load reads, one outstanding transaction
- `AW/W/B`: stores, with independent address and data handshakes
- 32-bit data, four byte strobes, single-beat transfers
- every request remains asserted until `valid && ready`

The core starts at `0x80000000`. `EBREAK` (`0x00100073`) halts the simulation. The debug commit output is a one-cycle architectural retirement pulse.

## Generate Verilog

```sh
cd chisel
make verilog
```

## Verilator simulation

The memory model is `difftest/src/axi_memory.hpp`. It provides:

- binary loading at a configurable address
- programmable read response latency
- independent AW and W acceptance
- byte-enable writes
- held R and B responses until handshake

Build and run with:

```sh
cd difftest
make sim PROGRAM=/absolute/path/to/program.bin
```

The simulation fails if the binary cannot be loaded or the core does not reach `EBREAK` within one million cycles. A successful run prints `PASS: RV32 AXI simulation halted`.

## Difftest

`difftest/src/rv32_reference.hpp` is an independent RV32IM interpreter. At every RTL architectural commit, the Verilator driver executes one reference instruction and compares the program counter, instruction, register-write enable, destination register, and writeback data. Store and load instructions are included in the same commit stream. The run also requires both implementations to stop at the same `EBREAK`.

```sh
cd difftest
make difftest-red PROGRAM=/absolute/path/to/program.bin
```

`difftest-red` deliberately corrupts the first reference writeback and must fail the comparison. This verifies that the checker is active rather than merely checking for simulation termination.

Algorithm regressions are included in the Chisel build:

```sh
cd chisel
make algorithm-tests
```

This runs an assembly bubble sort with final array assertions and an assembly Bellman–Ford shortest-path test with final distance assertions. Both are checked against the independent reference model.

The long-running B-tree regression is separate:

```sh
cd chisel
make btree-test
```

It inserts `N=10000` pseudo-random keys into an order-four B-tree, exercises node splitting and recursive insertion, then checks the in-order count, ordering, and checksum before executing `EBREAK`.
