BUILD_DIR = ./build
RV32_CC = riscv64-unknown-elf-gcc
RV32_OBJCOPY = riscv64-unknown-elf-objcopy
DIFF_DIR = ../difftest/core
DIFF_WORK_DIR = ../difftest

export PATH := $(PATH):$(abspath ./utils)

verilog:
	$(call git_commit, "generate verilog") # DO NOT REMOVE THIS LINE!!!
	$(MAKE) clean
	mkdir -p $(BUILD_DIR)
	mill -i __.test.runMain Elaborate -td $(BUILD_DIR)

test:
	@echo "make test"
	$(call git_commit, "test chisel module") # DO NOT REMOVE THIS LINE!!!
	mill -i playground.test.test

count:
	find ./playground/ -name "*.scala" | xargs wc -l 

help:
	mill -i __.test.runMain Elaborate --help

compile:
	mill -i __.compile

bsp:
	mill -i mill.bsp.BSP/install

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

rv32-smoke:
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im_zicsr -mabi=ilp32 -nostdlib -nostartfiles \
		-Wl,-Ttext=0x80000000 playground/test/resources/rv32_smoke.S \
		-o $(BUILD_DIR)/tests/rv32_smoke.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_smoke.elf $(BUILD_DIR)/tests/rv32_smoke.bin

clean:
	-rm -rf $(BUILD_DIR)

.PHONY: test verilog help compile bsp reformat checkformat rv32-smoke clean

sim:
	@echo "Write this Makefile by yourself."

-include ../Makefile
