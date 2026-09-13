.section .text
.option norelax
.globl _start
_start:
  la   s0, dist
  li   t0, 0
  sw   t0, 0(s0)
  li   t0, 1000
  sw   t0, 4(s0)
  sw   t0, 8(s0)
  sw   t0, 12(s0)

  la   s1, edge_src
  la   s2, edge_dst
  la   s3, edge_weight
  li   s4, 3
  li   s5, 0
pass_loop:
  bge  s5, s4, done
  mv   t1, s1
  mv   t2, s2
  mv   t3, s3
  li   t4, 0
edge_loop:
  li   t5, 5
  bge  t4, t5, next_pass
  lw   t5, 0(t1)
  slli t5, t5, 2
  add  t5, s0, t5
  lw   a0, 0(t5)
  lw   a2, 0(t3)
  add  a0, a0, a2
  lw   t6, 0(t2)
  slli t6, t6, 2
  add  t6, s0, t6
  lw   a1, 0(t6)
  bge  a0, a1, no_relax
  sw   a0, 0(t6)
no_relax:
  addi t1, t1, 4
  addi t2, t2, 4
  addi t3, t3, 4
  addi t4, t4, 1
  jal  x0, edge_loop
next_pass:
  addi s5, s5, 1
  jal  x0, pass_loop
done:
  lw   a0, 0(s0)
  bne  a0, x0, fail
  lw   a0, 4(s0)
  li   a1, 3
  bne  a0, a1, fail
  lw   a0, 8(s0)
  li   a1, 1
  bne  a0, a1, fail
  lw   a0, 12(s0)
  li   a1, 4
  bne  a0, a1, fail
  ebreak
fail:
  jal  x0, fail

.section .data
.align 2
dist:
  .word 0, 1000, 1000, 1000
edge_src:
  .word 0, 0, 2, 1, 2
edge_dst:
  .word 1, 2, 1, 3, 3
edge_weight:
  .word 4, 1, 2, 1, 5
