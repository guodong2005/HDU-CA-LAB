.section .text
.globl _start
_start:
  addi x1, x0, 0
  addi x2, x0, 100
small_loop:
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  bne x1, x2, small_loop
  ebreak
