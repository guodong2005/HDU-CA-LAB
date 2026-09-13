.section .text
.option norelax
.globl _start
_start:
  la   t0, array
  li   t1, 5
  li   t2, 0
outer:
  bge  t2, t1, done
  li   t3, 0
  sub  t4, t1, t2
  addi t4, t4, -1
inner:
  bge  t3, t4, next_outer
  slli t5, t3, 2
  add  t6, t0, t5
  lw   a0, 0(t6)
  lw   a1, 4(t6)
  bge  a1, a0, no_swap
  sw   a1, 0(t6)
  sw   a0, 4(t6)
no_swap:
  addi t3, t3, 1
  jal  x0, inner
next_outer:
  addi t2, t2, 1
  jal  x0, outer
done:
  lw   a0, 0(t0)
  li   a1, 1
  bne  a0, a1, fail
  lw   a0, 4(t0)
  li   a1, 2
  bne  a0, a1, fail
  lw   a0, 8(t0)
  li   a1, 5
  bne  a0, a1, fail
  lw   a0, 12(t0)
  li   a1, 8
  bne  a0, a1, fail
  lw   a0, 16(t0)
  li   a1, 9
  bne  a0, a1, fail
  ebreak
fail:
  jal  x0, fail

.section .data
.align 2
array:
  .word 9, 1, 8, 2, 5
