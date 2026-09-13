# Classic RV32 Pipeline and Vector-Cube Extension Plan

**Goal:** Preserve the existing RV32IM architectural behavior and AXI/cache interfaces while converting the single-transaction core into a classic five-stage pipeline, then attach Vector and asynchronous Cube execution units.

**Architecture:** Keep `core_top`, `AxiCache`, AXI bundles, Verilator memory, and the existing difftest protocol unchanged. Replace only the internal `Core` control/data path with explicit IF, ID, EX, MEM, and WB registers. Add Vector and Cube as execution-side units; Cube launch is non-blocking, while `cube.wait` and a second launch while busy use the pipeline stall mechanism.

**Baseline constraint:** The checked-in `Core.scala` is an FSM, not an existing pipeline. The pipeline conversion is therefore required by the latest architecture decision. Cache and external memory hierarchy remain untouched.

## Stage 1: Freeze baseline and define pipeline contracts

Files:
- `chisel/playground/src/Core.scala`
- `chisel/playground/src/PuaCpu.scala`
- `chisel/playground/src/AxiCache.scala`
- `difftest/src/sim_axi.cpp`

Define explicit stage records:

```text
IF/ID   valid, pc, instruction
ID/EX   valid, pc, instruction, rs1/rs2 values, immediate, control
EX/MEM  valid, pc, instruction, ALU result, store data, memory controls
MEM/WB  valid, pc, instruction, load/ALU result, writeback controls
```

Keep `Core.io.axi` unchanged so the cache remains the existing memory boundary. Initially support one outstanding cache transaction by freezing the pipeline around MEM; do not redesign the cache.

Verification:

```sh
cd chisel
make compile
make axi-smoke
make algorithm-tests
make btree-test
```

All existing tests must pass before extension instructions are added.

## Stage 2: Implement scalar five-stage behavior

Modify:

```text
chisel/playground/src/Core.scala
```

Add:

- PC and IF request/response handling
- IF/ID register
- decode control bundle
- ID/EX register
- EX ALU and branch target logic
- EX/MEM register
- MEM request/response hold logic
- MEM/WB register
- register-file writeback
- valid-bit propagation
- pipeline flush for taken branches and jumps
- load-use hazard stall
- forwarding from EX/MEM and MEM/WB where required

The first scalar milestone must pass the existing RV32IM tests without Vector/Cube instructions.

## Stage 3: Centralize custom instruction encoding

Create:

```text
chisel/playground/src/defines/CustomOpcode.scala
```

Define the two custom opcode spaces and all `funct3` values in one place:

```text
custom-0: Vector
  funct3=000 vadd
  funct3=001 vmul
  funct3=010 vshift
  funct3=011 vgather

custom-1: Cube
  funct3=000 cube.mma.async
  funct3=001 cube.wait
```

Extend the scalar decode control bundle with explicit custom instruction classifications. Unknown encodings remain inert or illegal according to the existing scalar policy; they must not accidentally write scalar registers.

## Stage 4: Add Vector Core

Create:

```text
chisel/playground/src/VectorRegisterFile.scala
chisel/playground/src/VectorPermute.scala
chisel/playground/src/VectorCore.scala
```

Specifications:

```text
8 registers
4 lanes per register
32 bits per lane
```

Implement:

```text
vadd
vmul
vshift
vgather
```

Keep `vshift` and `vgather` in `VectorPermute.scala`. Vector results commit to the vector register file, not the scalar register file.

## Stage 5: Add Cube Core

Create:

```text
chisel/playground/src/CubeCore.scala
```

Specifications:

```text
4 × 4 matrix
A and B elements: signed 16-bit integers
accumulator: signed 32-bit integers
operation: C = A × B + C
states: IDLE, BUSY, DONE
one outstanding operation
```

The initial operand path may use explicit testbench/register initialization. No vector load/store subsystem is added.

## Stage 6: Integrate asynchronous Cube dispatch

Modify:

```text
chisel/playground/src/Core.scala
```

Semantics:

```text
cube.mma.async:
  if cube_busy == 0, launch Cube and allow the instruction to leave EX
  if cube_busy == 1, hold/stall the instruction in the pipeline

cube.wait:
  if cube_busy == 1, hold the instruction and stall younger instructions
  if cube_busy == 0, allow normal retirement
```

Do not add a command queue, semaphore system, or second global handshake protocol. Use the pipeline valid/ready or enable/stall mechanism defined in Stage 1.

## Stage 7: Overlap test and trace

Create:

```text
chisel/playground/test/resources/rv32_heterogeneous.S
```

Extend the simulation trace without changing existing difftest correctness fields. Record:

```text
cycle
instruction PC
instruction class
cube_busy
vector write event
cube launch/done event
pipeline stall reason
```

Required sequence:

```text
cube.mma.async
vadd
vmul
vshift
cube.wait
EBREAK
```

Required evidence:

```text
Vector instructions commit while Cube is BUSY
cube.wait stalls while Cube is BUSY
cube.wait continues after Cube reaches DONE
```

## Stage 8: Cycle evaluation

Report separately:

```text
Vector instruction latency
Cube MMA latency
Sequential Vector + Cube cycles
Overlapped cycles
Speedup = sequential_cycles / overlapped_cycles
```

Do not claim overlap from instruction order alone; require cycle-level trace evidence.

## Explicit non-goals

- compiler or assembler backend
- cache redesign
- memory hierarchy redesign
- coherence
- virtual memory
- floating point
- multiple Cube operations
- command queue
- out-of-order execution
- FPGA deployment
