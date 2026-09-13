.section .text
.globl _start
_start:
  addi x1, x0, 0
  addi x2, x0, 200
seq_loop:
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x1, x1, 1
  addi x2, x2, -1
  bne x2, x0, seq_loop
  ebreak
