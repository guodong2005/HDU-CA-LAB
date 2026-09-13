SRC_DIR := ./core
BUILD := obj_dir
VERILATOR ?= verilator

$(BUILD)/Vcore_top: core_top.v src/sim_axi.cpp src/axi_memory.hpp src/rv32_reference.hpp
	$(VERILATOR) --cc --exe --build -Wall -Wno-fatal --top-module core_top core_top.v src/sim_axi.cpp -Isrc -Mdir $(BUILD)

verilog:
	$(MAKE) -C ../chisel verilog
	cp ../chisel/build/core_top.v ./core_top.v

sim: check-generated $(BUILD)/Vcore_top
	./$(BUILD)/Vcore_top $(PROGRAM) $(OPTIONS)

difftest-red: check-generated $(BUILD)/Vcore_top
	@tmp=$$(mktemp); if ./$(BUILD)/Vcore_top $(PROGRAM) --inject-difftest-error >$$tmp 2>&1; then \
		echo "FAIL: injected mismatch was not detected"; rm -f $$tmp; exit 1; \
	else grep -q "EXPECTED DIFFTEST MISMATCH" $$tmp && echo "PASS: injected mismatch was detected" || { cat $$tmp; rm -f $$tmp; exit 1; }; fi; \
	rm -f $$tmp

clean:
	rm -rf $(BUILD) core_top.v

check-generated:
	python3 check_generated.py

.PHONY: verilog sim difftest-red clean check-generated
