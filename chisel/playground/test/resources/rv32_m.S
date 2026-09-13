.option norelax
.section .text
.globl _start
_start:
  li t0, 7
  li t1, 3
  mul t2, t0, t1
  li t3, 21
  bne t2, t3, fail
  mulh t2, t0, t1
  bnez t2, fail
  mulhsu t2, t0, t1
  bnez t2, fail
  mulhu t2, t0, t1
  bnez t2, fail
  li t0, 0x10000
  li t1, 0x10000
  mulh t2, t0, t1
  li t3, 1
  bne t2, t3, fail
  mulhsu t2, t0, t1
  bne t2, t3, fail
  mulhu t2, t0, t1
  bne t2, t3, fail
  li t0, -65536
  li t1, 65536
  mulh t2, t0, t1
  li t3, -1
  bne t2, t3, fail
  mulhsu t2, t0, t1
  bne t2, t3, fail
  li t0, 0xFFFF0000
  mulhu t2, t0, t1
  li t3, 0xFFFF
  bne t2, t3, fail
  li t0, 7
  li t1, 3
  rem t2, t0, t1
  li t3, 1
  bne t2, t3, fail
  divu t2, t0, t1
  li t3, 2
  bne t2, t3, fail
  remu t2, t0, t1
  li t3, 1
  bne t2, t3, fail
  li t0, -7
  div t2, t0, t1
  li t3, -2
  bne t2, t3, fail
  rem t2, t0, t1
  li t3, -1
  bne t2, t3, fail
  divu t2, t0, t1
  li t3, 0x55555553
  bne t2, t3, fail
  remu t2, t0, t1
  li t3, 0
  bne t2, t3, fail
  li t0, 0x80000000
  li t1, -1
  div t2, t0, t1
  bne t2, t0, fail
  rem t2, t0, t1
  bnez t2, fail
  li t1, 0
  div t2, t0, t1
  li t3, -1
  bne t2, t3, fail
  rem t2, t0, t1
  bne t2, t0, fail
  ebreak
fail:
  .word 0
