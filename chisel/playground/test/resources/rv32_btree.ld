ENTRY(_start)
SECTIONS {
  . = 0x80000000;
  .text : { *(.text.00) *(.text.startup) *(.text*) }
  .rodata : { *(.rodata*) }
  .data : { *(.sdata*) *(.data*) }
  .bss : { *(.sbss*) *(.bss*) *(COMMON) }
}
