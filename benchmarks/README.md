# Benchmark suite

Run the complete real-simulation matrix from the repository root:

```bash
make benchmarks
```

The runner performs fresh Chisel elaboration, generated-Verilog freshness validation, RV32 assembly/linking, Verilator compilation, scalar differential testing, and emits:

- `benchmarks/results/benchmark_results.csv`
- `benchmarks/results/benchmark_report.md`

The current top-level hardware is the actual `AxiCache(4)` configuration: four direct-mapped single-word lines shared by instruction and data traffic. It is not a 2 KiB instruction-only cache. The RV32 top level has no Store FIFO or UART memory-mapped interface; those rows are reported as `UNAVAILABLE` rather than estimated.

All timed rows require both a zero simulator exit code and the `DIFFTEST PASS` marker. The cycle boundary is after reset release and before the halted state is observed.
