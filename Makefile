# Master Makefile

# Find all immediate subdirectories. These are assumed to be the projects.
PROJECTS := $(wildcard */)

# Phony targets prevent conflicts with files of the same name.
# 'all' is the default target, executed when you just run 'make'.
.PHONY: all clean

# The 'all' target iterates through each project directory and runs 'make' inside it.
all:
	@echo "--- Building all projects ---"
	@for project in $(PROJECTS); do \
		echo "==> Building $$project"; \
		$(MAKE) -C $$project || exit 1; \
	done
	@echo "--- All projects built successfully ---"

# The 'clean' target iterates through each project and runs 'make clean'.
clean:
	@echo "--- Cleaning all projects ---"
	@for project in $(PROJECTS); do \
		echo "==> Cleaning $$project"; \
		$(MAKE) -C $$project clean; \
	done
	@echo "--- All projects cleaned ---"

