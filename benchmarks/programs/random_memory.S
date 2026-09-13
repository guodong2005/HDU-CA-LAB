.section .text
.globl _start
_start:
  lui x10, 0x80001
  addi x1, x0, 0
  addi x2, x0, 64
random_loop:
  andi x4, x1, 7
  slli x4, x4, 5
  add x5, x10, x4
  sw x1, 0(x5)
  lw x3, 0(x5)
  addi x1, x1, 3
  addi x2, x2, -1
  bne x2, x0, random_loop
  ebreak
