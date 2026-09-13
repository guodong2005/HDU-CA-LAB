.section .text
.globl _start
_start:
  lui x10, 0x80001
  addi x1, x0, 0
  addi x2, x0, 64
store_loop:
  sw x1, 0(x10)
  lw x3, 0(x10)
  addi x10, x10, 4
  addi x1, x1, 1
  addi x2, x2, -1
  bne x2, x0, store_loop
  ebreak
