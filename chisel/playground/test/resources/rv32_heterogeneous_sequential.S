.section .text
.globl _start
_start:
  # Batch 0: wait before the useful work.
  .word 0x0000002b       # cube.mma.async
  .word 0x0000102b       # cube.wait
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  .word 0x0000008b       # vadd
  .word 0x0010910b       # vmul
  .word 0x0021218b       # vshift
  .word 0x0011b20b       # vgather

  # Batch 1: same work and ordering.
  .word 0x0000002b
  .word 0x0000102b
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b

  # Batch 2: same work and ordering.
  .word 0x0000002b
  .word 0x0000102b
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b

  # Batch 3: same work and ordering.
  .word 0x0000002b
  .word 0x0000102b
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b
  ebreak
