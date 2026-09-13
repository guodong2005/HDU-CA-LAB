.section .text
.globl _start
_start:
  addi x1, x0, 0
  addi x2, x0, 200
branch_loop:
  addi x1, x1, 1
  andi x3, x1, 1
  beq x3, x0, even_path
  addi x4, x4, 1
  jal x0, branch_next
even_path:
  addi x5, x5, 1
branch_next:
  addi x2, x2, -1
  bne x2, x0, branch_loop
  ebreak
