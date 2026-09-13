.section .text
.globl _start
_start:
  # Five Cube operations are launched before the same useful work.
  .word 0x0000002b
  .word 0x0000002b
  .word 0x0000002b
  .word 0x0000002b
  .word 0x0000002b

  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b
  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b

  addi x1, x1, 1
  .word 0x0000008b
  .word 0x0010910b
  .word 0x0021218b
  .word 0x0011b20b

  .word 0x0000102b
  ebreak
