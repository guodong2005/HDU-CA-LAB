.section .text
.globl _start
_start:
  .word 0x400010b3  # illegal OP funct7=0x20, funct3=001
  ebreak
