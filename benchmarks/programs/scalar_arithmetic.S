.section .text
.globl _start
_start:
  addi x1, x0, 0
  addi x2, x0, 100
  addi x3, x0, 3
loop:
  add x1, x1, x3
  addi x2, x2, -1
  bne x2, x0, loop
  ebreak
