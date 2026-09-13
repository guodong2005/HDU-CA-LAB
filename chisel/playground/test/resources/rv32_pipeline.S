.option norelax
.section .text
.globl _start
_start:
  li t0, 1
  addi t1, t0, 2
  add t2, t1, t0
  addi t3, t2, 4
  lui t4, 0x80001
  sw t3, 0(t4)
  lw t5, 0(t4)
  bne t5, t3, fail
  beq t5, t3, branch_taken
  j fail
branch_taken:
  addi t2, t2, 1
  jal ra, subroutine
  j return_point
subroutine:
  addi t2, t2, 1
  jalr x0, 0(ra)
return_point:
  la t6, target
  jalr x0, 0(t6)
  j fail
target:
  ebreak
fail:
  .word 0
