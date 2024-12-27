# compiler
CC := g++

# compiler flags
CC_FLAGS := -O3 -Wall -Wextra

# build directory
BUILD_DIR := build

# source files
SRCS := $(wildcard *.cpp)

# executables
EXECS := $(SRCS:%.cpp=$(BUILD_DIR)/%)

# default target
all: $(BUILD_DIR) $(EXECS)

# rule to create build directory
$(BUILD_DIR):
	mkdir -p $@

# rule to create executables
$(BUILD_DIR)/%: %.cpp
	$(CC) $(CC_FLAGS) $< -o $@

# clean target
clean:
	rm -rf $(BUILD_DIR)

# phony targets
.PHONY: all clean
