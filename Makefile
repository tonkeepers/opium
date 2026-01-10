# Compiler and tools
CC      := gcc
AR      := ar

# Directories
PROJECT_DIR  := $(abspath project)
CORE_DIR     := $(PROJECT_DIR)/src/core

OS_DIR       := $(PROJECT_DIR)/src/os/unix
UNIX_PROCESS_DIR       := $(PROJECT_DIR)/src/os/unix/process
UNIX_PROCESS_DIR1       := $(PROJECT_DIR)/src/os/unix/process/entrails

SUPERVISOR_DIR := $(PROJECT_DIR)/src/runtime/execute
MASTER_DIR     := $(PROJECT_DIR)/src/runtime/master
WORKER_DIR     := $(PROJECT_DIR)/src/runtime/worker
INC_DIR      := $(PROJECT_DIR)/include
OBJ_DIR      := $(PROJECT_DIR)/build/obj
BIN_DIR      := $(PROJECT_DIR)/build/bin
LIB_DIR      := $(PROJECT_DIR)/build/lib

CFLAGS  := -Wall -Wextra -O3 -fPIC -march=native -D_GNU_SOURCE\
           -I$(PROJECT_DIR) \
           -I$(PROJECT_DIR)/include \
           -I$(PROJECT_DIR)/src \
           -pthread \
           -Wno-unused-function -Wno-unused-variable
# Targets
TARGET       := $(BIN_DIR)/project
TARGET_LIB   := $(LIB_DIR)/libopium.a

# Source files
CORE_SRCS       := $(wildcard $(CORE_DIR)/*.c)
SUPERVISOR_SRCS := $(wildcard $(SUPERVISOR_DIR)/*.c)
MASTER_SRCS     := $(wildcard $(MASTER_DIR)/*.c)
WORKER_SRCS     := $(wildcard $(WORKER_DIR)/*.c)
OS_SRCS         := $(wildcard $(OS_DIR)/*.c)
PROCESS_SRCS    := $(wildcard $(UNIX_PROCESS_DIR)/*.c)
PROCESS_SRCS1    := $(wildcard $(UNIX_PROCESS_DIR1)/*.c)

SRCS := $(CORE_SRCS) $(SUPERVISOR_SRCS) $(MASTER_SRCS) $(WORKER_SRCS) $(OS_SRCS) $(PROCESS_SRCS) $(PROCESS_SRCS1)
OBJS := $(SRCS:$(PROJECT_DIR)/src/%.c=$(OBJ_DIR)/%.o)

# Main application file (entry point)
MAIN_SRC     := $(SUPERVISOR_DIR)/opium_supervisor.c

.PHONY: all clean run debug test lib

all: $(TARGET)

# Static library target (core only)
lib: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $^
	@echo "Static library built: $(TARGET_LIB)"

# Main executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -lm -o $@
	@echo "Executable built: $(TARGET) (port 8080 → 4308)"

# Compile object files
$(OBJ_DIR)/%.o: $(PROJECT_DIR)/src/%.c
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

clean:
	rm -rf $(PROJECT_DIR)/build
	@echo "Build directory cleaned"

# Generate compile_commands.json
bear: clean
	bear -- make -C $(PROJECT_DIR)

# Show project structure
tree:
	@tree -I 'build|*.o|*.a' --dirsfirst

# Help
help:
	@echo "Available targets:"
	@echo "  all     - Build everything (default)"
	@echo "  lib     - Build static library only"
	@echo "  run     - Build and run the executable"
	@echo "  debug   - Build with debug symbols"
	@echo "  test    - Run tests"
	@echo "  clean   - Remove build files"
	@echo "  bear    - Generate compile_commands.json"
	@echo "  tree    - Show project structure"
