BUILD_DIR = ./build
RV32_CC = riscv64-unknown-elf-gcc
RV32_OBJCOPY = riscv64-unknown-elf-objcopy
DIFF_DIR = ../difftest/core
DIFF_WORK_DIR = ../difftest

export PATH := $(PATH):$(abspath ./utils)

verilog:
	$(MAKE) clean
	mkdir -p $(BUILD_DIR)
	mill -i __.test.runMain Elaborate -td $(BUILD_DIR)

test:
	@echo "make test"
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

axi-smoke: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles \
		-Wl,-Ttext=0x80000000 playground/test/resources/rv32_axi_smoke.S \
		-o $(BUILD_DIR)/tests/rv32_axi_smoke.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_axi_smoke.elf $(BUILD_DIR)/tests/rv32_axi_smoke.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_axi_smoke.bin)

algorithm-tests: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,--no-relax,-Ttext=0x80000000 playground/test/resources/rv32_sort.S -o $(BUILD_DIR)/tests/rv32_sort.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_sort.elf $(BUILD_DIR)/tests/rv32_sort.bin
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,--no-relax,-Ttext=0x80000000 playground/test/resources/rv32_shortest_path.S -o $(BUILD_DIR)/tests/rv32_shortest_path.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_shortest_path.elf $(BUILD_DIR)/tests/rv32_shortest_path.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_sort.bin)
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_shortest_path.bin)

clean:
	-rm -rf $(BUILD_DIR)

.PHONY: test verilog help compile bsp reformat checkformat rv32-smoke axi-smoke algorithm-tests clean

sim:
	@echo "Write this Makefile by yourself."

-include ../Makefile
