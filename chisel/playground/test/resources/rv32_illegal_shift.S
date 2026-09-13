.section .text
.globl _start
_start:
  .word 0x02001093  # illegal SLLI funct7=0x01
  ebreak
