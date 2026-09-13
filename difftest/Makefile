SRC_DIR := ./core
BUILD := obj_dir
VERILATOR ?= verilator

$(BUILD)/Vcore_top: core_top.v src/sim_axi.cpp src/axi_memory.hpp src/rv32_reference.hpp
	$(VERILATOR) --cc --exe --build -Wall -Wno-fatal --top-module core_top core_top.v src/sim_axi.cpp -Isrc -Mdir $(BUILD)

verilog:
	$(MAKE) -C ../chisel verilog
	cp ../chisel/build/core_top.v ./core_top.v

sim: $(BUILD)/Vcore_top
	./$(BUILD)/Vcore_top $(PROGRAM)

difftest-red: $(BUILD)/Vcore_top
	@if ./$(BUILD)/Vcore_top $(PROGRAM) --inject-difftest-error >/tmp/difftest-red.$$$$.log 2>&1; then \
		echo "FAIL: injected mismatch was not detected"; exit 1; \
	else grep -q "EXPECTED DIFFTEST MISMATCH" /tmp/difftest-red.$$$$.log && echo "PASS: injected mismatch was detected" || { cat /tmp/difftest-red.$$$$.log; exit 1; }; fi; \
	rm -f /tmp/difftest-red.$$$$.log

clean:
	rm -rf $(BUILD) core_top.v

.PHONY: verilog sim difftest-red clean
