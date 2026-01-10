# Compiler and tools
CC      := gcc
AR      := ar

# Directories
PROJECT_DIR  := $(abspath project)
SRC_DIR      := $(PROJECT_DIR)/src
CORE_DIR     := $(PROJECT_DIR)/src/core
OS_DIR       := $(PROJECT_DIR)/src/os/unix
INC_DIR      := $(PROJECT_DIR)/include
OBJ_DIR      := $(PROJECT_DIR)/build/obj
BIN_DIR      := $(PROJECT_DIR)/build/bin
LIB_DIR      := $(PROJECT_DIR)/build/lib

# Find ALL C source files recursively
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Flags
CFLAGS  := -Wall -Wextra -O3 -fPIC -march=native -D_GNU_SOURCE \
           -I$(PROJECT_DIR) \
           -I$(INC_DIR) \
           -I$(SRC_DIR) \
           -pthread \
           -Wno-unused-function \
           -Wno-unused-variable

# Targets
TARGET       := $(BIN_DIR)/opium
TARGET_LIB   := $(LIB_DIR)/libopium.a

.PHONY: all clean run debug test lib help tree bear

all: $(TARGET)

# Static library target
lib: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $^
	@echo "Static library built: $(TARGET_LIB)"

# Main executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -lm -o $@
	@echo "Executable built: $(TARGET)"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Commands
run: all
	@echo "Running $(TARGET)..."
	cd $(PROJECT_DIR) && ./build/bin/opium

debug: CFLAGS += -g -O0 -DDEBUG
debug: clean all

test: all
	@echo "Running tests..."
	# Add your test commands here

clean:
	rm -rf $(PROJECT_DIR)/build
	@echo "Build directory cleaned"

# Generate compile_commands.json
bear: clean
	bear -- make all

# Show project structure
tree:
	@tree -I 'build|*.o|*.a|*.so' --dirsfirst $(PROJECT_DIR)

# Show found source files
sources:
	@echo "Found source files:"
	@echo "$(SRCS)" | tr ' ' '\n'

# Show object files
objects:
	@echo "Object files to build:"
	@echo "$(OBJS)" | tr ' ' '\n'

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build everything (default)"
	@echo "  lib      - Build static library only"
	@echo "  run      - Build and run the executable"
	@echo "  debug    - Build with debug symbols"
	@echo "  test     - Run tests"
	@echo "  clean    - Remove build files"
	@echo "  bear     - Generate compile_commands.json"
	@echo "  tree     - Show project structure"
	@echo "  sources  - List all found source files"
	@echo "  objects  - List all object files"
