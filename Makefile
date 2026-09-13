STUID = 23150919
STUNAME = WangJiadong

# DO NOT modify the following code!!!

TRACER = tracer-rvlab
GITFLAGS = -q --author='$(TRACER) <tracer@kairos.hdu.edu.cn>' --no-verify --allow-empty

RVLAB_HOME = $(RVDIFF_HOME)/..
WORK_BRANCH = $(shell git rev-parse --abbrev-ref HEAD)
WORK_INDEX = $(RVLAB_HOME)/.git/index.$(WORK_BRANCH)
TRACER_BRANCH = $(TRACER)

LOCK_DIR = $(RVLAB_HOME)/.git/

# prototype: git_soft_checkout(branch)
define git_soft_checkout
	git checkout --detach -q && git reset --soft $(1) -q -- && git checkout $(1) -q --
endef

# prototype: git_commit(msg)
define git_commit
	-@flock $(LOCK_DIR) $(MAKE) -C $(RVLAB_HOME) .git_commit MSG='$(1)'
	-@sync $(LOCK_DIR)
endef

.git_commit:
	-@while (test -e .git/index.lock); do sleep 0.1; done;               `# wait for other git instances`
	-@git branch $(TRACER_BRANCH) -q 2>/dev/null || true                 `# create tracer branch if not existent`
	-@cp -a .git/index $(WORK_INDEX)                                     `# backup git index`
	-@$(call git_soft_checkout, $(TRACER_BRANCH))                        `# switch to tracer branch`
	-@git add . -A --ignore-errors                                       `# add files to commit`
	-@(echo "> $(MSG)" && echo $(STUID) $(STUNAME) && uname -a && uptime `# generate commit msg`) \
	                | git commit -F - $(GITFLAGS)                        `# commit changes in tracer branch`
	-@$(call git_soft_checkout, $(WORK_BRANCH))                          `# switch to work branch`
	-@mv $(WORK_INDEX) .git/index                                        `# restore git index`

.clean_index:
	rm -f $(WORK_INDEX)

_default:
	@echo "Please run 'make' under subprojects."

.PHONY: .git_commit .clean_index _default

ifeq ($(notdir $(CURDIR)),HDU-CA-LAB)
.PHONY: test axi-smoke axi-backpressure algorithm-tests btree-test rv32-m-test pipeline-test illegal-test rv32-check

test:
	$(MAKE) -C chisel test

axi-smoke:
	$(MAKE) -C chisel axi-smoke

axi-backpressure:
	$(MAKE) -C chisel axi-backpressure

algorithm-tests:
	$(MAKE) -C chisel algorithm-tests

btree-test:
	$(MAKE) -C chisel btree-test

rv32-m-test:
	$(MAKE) -C chisel rv32-m-test

pipeline-test:
	$(MAKE) -C chisel pipeline-test

illegal-test:
	$(MAKE) -C chisel illegal-test

rv32-check:
	$(MAKE) test
	$(MAKE) axi-smoke
	$(MAKE) axi-backpressure
	$(MAKE) -C difftest difftest-red PROGRAM=$(abspath chisel/build/tests/rv32_axi_smoke.bin)
	$(MAKE) rv32-m-test
	$(MAKE) pipeline-test
	$(MAKE) illegal-test
	$(MAKE) algorithm-tests
	$(MAKE) btree-test
endif
