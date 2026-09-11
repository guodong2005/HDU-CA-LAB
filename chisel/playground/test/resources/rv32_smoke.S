  .section .text
  .globl _start
_start:
  addi x1, x0, 5
  addi x2, x0, 7
  add  x3, x1, x2
  sub  x4, x3, x1
  slli x5, x4, 2
  xor  x6, x5, x3
  mul  x7, x1, x2
  div  x8, x7, x1
  rem  x9, x7, x2
  lui  x10, 0x10000
  auipc x11, 0
  beq  x8, x2, 1f
  addi x12, x0, -1
1:
  jal  x13, 2f
  addi x14, x0, -1
2:
  jal  x0, 2b
