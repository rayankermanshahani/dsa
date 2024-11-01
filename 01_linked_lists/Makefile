# Compiler
CC := gcc

# Compiler flags
CC_FLAGS := -Wall -Wextra -O3 

# Build directory
BUILD_DIR := build

# Source files
SRCS := $(wildcard *.c)

# Executables (one for each source file)
EXECS := $(SRCS:%.c=$(BUILD_DIR)/%)

# Default target
all: $(BUILD_DIR) $(EXECS)

# Rule to create build directory
$(BUILD_DIR):
	mkdir -p $@

# Rule to create executables
$(BUILD_DIR)/%: %.c
	$(CC) $(CC_FLAGS) $< -o $@

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
