.section .text
.globl _start
_start:
  .word 0x0000002b       # cube.mma.async
  .word 0x0000008b       # vadd   v1, v0, v0
  .word 0x0010910b       # vmul   v2, v1, v1
  .word 0x0021218b       # vshift v3, v2, shamt=2
  .word 0x0011b20b       # vgather v4, v3, v1
  .word 0x0000102b       # cube.wait
  ebreak
