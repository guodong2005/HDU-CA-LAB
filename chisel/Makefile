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
	mill -i playground.test.test
	$(MAKE) pipeline-test

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
	python3 ../difftest/check_generated.py --write-manifest
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_axi_smoke.bin)

axi-backpressure: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_axi_smoke.S -o $(BUILD_DIR)/tests/rv32_axi_smoke.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_axi_smoke.elf $(BUILD_DIR)/tests/rv32_axi_smoke.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_axi_smoke.bin) OPTIONS=--backpressure

algorithm-tests: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,--no-relax,-Ttext=0x80000000 playground/test/resources/rv32_sort.S -o $(BUILD_DIR)/tests/rv32_sort.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_sort.elf $(BUILD_DIR)/tests/rv32_sort.bin
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,--no-relax,-Ttext=0x80000000 playground/test/resources/rv32_shortest_path.S -o $(BUILD_DIR)/tests/rv32_shortest_path.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_shortest_path.elf $(BUILD_DIR)/tests/rv32_shortest_path.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_sort.bin)
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_shortest_path.bin)

btree-test: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -O2 -ffreestanding -fno-pic -fno-stack-protector -msmall-data-limit=0 -nostdlib -nostartfiles -Wl,--no-relax,-T,playground/test/resources/rv32_btree.ld playground/test/resources/rv32_btree_start.S playground/test/resources/rv32_btree.c -o $(BUILD_DIR)/tests/rv32_btree.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_btree.elf $(BUILD_DIR)/tests/rv32_btree.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_btree.bin)

rv32-m-test: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_m.S -o $(BUILD_DIR)/tests/rv32_m.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_m.elf $(BUILD_DIR)/tests/rv32_m.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_m.bin)

pipeline-test: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_pipeline.S -o $(BUILD_DIR)/tests/rv32_pipeline.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_pipeline.elf $(BUILD_DIR)/tests/rv32_pipeline.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_pipeline.bin)

illegal-test: illegal-op-test illegal-shift-test illegal-unknown-test
	$(MAKE) -C . illegal-zero-test

define ILLEGAL_TEST_template
illegal-$1-test: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_illegal_$1.S -o $(BUILD_DIR)/tests/rv32_illegal_$1.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_illegal_$1.elf $(BUILD_DIR)/tests/rv32_illegal_$1.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	@if $(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_illegal_$1.bin) >/tmp/rv32-illegal-$1.log 2>&1; then cat /tmp/rv32-illegal-$1.log; rm -f /tmp/rv32-illegal-$1.log; echo "FAIL: illegal $1 instruction was accepted"; exit 1; else grep -q "ILLEGAL instruction reported by RTL" /tmp/rv32-illegal-$1.log && echo "PASS: illegal $1 instruction was reported" || { cat /tmp/rv32-illegal-$1.log; rm -f /tmp/rv32-illegal-$1.log; exit 1; }; rm -f /tmp/rv32-illegal-$1.log; fi
endef

$(eval $(call ILLEGAL_TEST_template,op))
$(eval $(call ILLEGAL_TEST_template,shift))
$(eval $(call ILLEGAL_TEST_template,unknown))

illegal-zero-test: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_illegal.S -o $(BUILD_DIR)/tests/rv32_illegal.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_illegal.elf $(BUILD_DIR)/tests/rv32_illegal.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	@if $(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_illegal.bin) >/tmp/rv32-illegal.$$$$.log 2>&1; then cat /tmp/rv32-illegal.$$$$.log; rm -f /tmp/rv32-illegal.$$$$.log; echo "FAIL: illegal instruction was accepted"; exit 1; else grep -q "ILLEGAL instruction reported by RTL" /tmp/rv32-illegal.$$$$.log && echo "PASS: illegal instruction was reported" || { cat /tmp/rv32-illegal.$$$$.log; rm -f /tmp/rv32-illegal.$$$$.log; exit 1; }; rm -f /tmp/rv32-illegal.$$$$.log; fi

vector-test: verilog
	mill -i playground.test.test

cube-test: verilog
	mill -i playground.test.test

heterogeneous-test: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_heterogeneous.S -o $(BUILD_DIR)/tests/rv32_heterogeneous.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_heterogeneous.elf $(BUILD_DIR)/tests/rv32_heterogeneous.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_heterogeneous.bin)
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_heterogeneous.bin) OPTIONS=--backpressure

heterogeneous-trace: verilog
	mkdir -p $(BUILD_DIR)/tests
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_heterogeneous.S -o $(BUILD_DIR)/tests/rv32_heterogeneous.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_heterogeneous.elf $(BUILD_DIR)/tests/rv32_heterogeneous.bin
	cp $(BUILD_DIR)/core_top.v ../difftest/core_top.v
	python3 ../difftest/check_generated.py --write-manifest
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_heterogeneous.bin) OPTIONS=--heterogeneous-trace | tee $(BUILD_DIR)/heterogeneous.trace
	python3 ../difftest/check_heterogeneous_trace.py $(BUILD_DIR)/heterogeneous.trace
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_heterogeneous_sequential.S -o $(BUILD_DIR)/tests/rv32_heterogeneous_sequential.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_heterogeneous_sequential.elf $(BUILD_DIR)/tests/rv32_heterogeneous_sequential.bin
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_heterogeneous_sequential.bin) OPTIONS=--heterogeneous-trace | tee $(BUILD_DIR)/heterogeneous-sequential.trace
	$(RV32_CC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x80000000 playground/test/resources/rv32_heterogeneous_overlap.S -o $(BUILD_DIR)/tests/rv32_heterogeneous_overlap.elf
	$(RV32_OBJCOPY) -O binary $(BUILD_DIR)/tests/rv32_heterogeneous_overlap.elf $(BUILD_DIR)/tests/rv32_heterogeneous_overlap.bin
	$(MAKE) -C ../difftest sim PROGRAM=$(abspath $(BUILD_DIR)/tests/rv32_heterogeneous_overlap.bin) OPTIONS=--heterogeneous-trace | tee $(BUILD_DIR)/heterogeneous-overlap.trace
	python3 ../difftest/check_heterogeneous_cycles.py $(BUILD_DIR)/heterogeneous-overlap.trace $(BUILD_DIR)/heterogeneous-sequential.trace

heterogeneous-check: vector-test cube-test heterogeneous-test heterogeneous-trace

clean:
	-rm -rf $(BUILD_DIR)

.PHONY: test verilog help compile bsp reformat checkformat rv32-smoke axi-smoke axi-backpressure algorithm-tests btree-test rv32-m-test pipeline-test illegal-test illegal-zero-test illegal-op-test illegal-shift-test illegal-unknown-test vector-test cube-test heterogeneous-test heterogeneous-trace heterogeneous-check clean

sim:
	@echo "Write this Makefile by yourself."

-include ../Makefile
