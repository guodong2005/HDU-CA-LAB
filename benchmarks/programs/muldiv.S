.section .text
.globl _start
_start:
  addi x1, x0, 7
  addi x2, x0, 200
muldiv_loop:
  mul x3, x1, x2
  div x4, x3, x1
  rem x5, x3, x1
  addi x2, x2, -1
  bne x2, x0, muldiv_loop
  ebreak
