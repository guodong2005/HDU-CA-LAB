.section .text.00
.option norelax
.globl _start
_start:
  lui sp, 0x81000
  addi sp, sp, -16
  jal x0, main
1:
  j 1b
