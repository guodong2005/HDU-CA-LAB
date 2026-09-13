.section .text
.globl _start
_start:
  # Batch 0: execute scalar and Vector work while Cube is BUSY.
  .word 0x0000002b       # cube.mma.async
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  .word 0x0000008b       # vadd
  .word 0x0010910b       # vmul
  .word 0x0021218b       # vshift
  .word 0x0011b20b       # vgather
  .word 0x0000102b       # cube.wait

  # Batch 1: same work and ordering.
  .word 0x0000002b
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b
  .word 0x0000102b

  # Batch 2: same work and ordering.
  .word 0x0000002b
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b
  .word 0x0000102b

  # Batch 3: same work and ordering.
  .word 0x0000002b
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b
  .word 0x0000102b
  ebreak
