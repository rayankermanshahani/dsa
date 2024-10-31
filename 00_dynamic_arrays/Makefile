# compiler
CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -std=c11
LDFLAGS =

# build directory
BUILDDIR = build

# source files
SRCS = $(wildcard *.c)
# object files
OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o)
# executable file
TARGET = $(BUILDDIR)/$(shell basename $(CURDIR))

# default target
all: $(BUILDDIR) $(TARGET)

# create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# linking rule (create executable)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# compilation rule (create object files)
$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# generate header dependencies
DEPS = $(OBJS:.o=.d)
-include $(DEPS)
$(BUILDDIR)/%.d: %.c | $(BUILDDIR)
	@set -e; rm -f $@; \
	$(CC) -MM -MT '$(BUILDDIR)/$*.o $(BUILDDIR)/$*.d' $(CFLAGS) $< > $@

# phony targets
.PHONY: clean run

# delete build directory
clean:
	rm -rf $(BUILDDIR)

run: $(TARGET)
	./$(TARGET)
