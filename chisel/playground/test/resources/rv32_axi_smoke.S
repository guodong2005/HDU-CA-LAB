.section .text
.globl _start
_start:
  addi x1, x0, 42
  lui  x2, 0x80000
  addi x2, x2, 0x100
  sw   x1, 0(x2)
  lw   x3, 0(x2)
  lw   x4, 0(x2)
  addi x5, x3, 1
  mul  x6, x5, x1
  div  x7, x6, x1
  beq  x7, x5, 1f
  addi x8, x0, 99
1:
  ebreak
