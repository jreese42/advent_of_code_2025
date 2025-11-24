# Advent of Code 2025 - Makefile
# Compiles and runs any day's solution

CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
DEBUG_FLAGS := -g -DDEBUG

# Default day to build (can be overridden: make DAY=5)
DAY ?= 1

# Directories
SRC_DIR := src
BUILD_DIR := build
DAY_DIR := $(SRC_DIR)/day_$(DAY)

# Target executable
TARGET := $(BUILD_DIR)/day_$(DAY)

# Source file
SRC := $(DAY_DIR)/day_$(DAY).cpp

# Input file
INPUT := $(DAY_DIR)/input

# Default target - build and run the current day
.PHONY: all
all: run

# Build the specified day
.PHONY: build
build: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	@echo "Building day $(DAY)..."
	$(CXX) $(CXXFLAGS) -o $@ $<
	@echo "Build complete!"

# Run the specified day
.PHONY: run
run: $(TARGET)
	@echo "Running day $(DAY)..."
	@echo ""
	@cd $(DAY_DIR) && ../../$(TARGET)

# Build with debug symbols
.PHONY: debug
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete!"

# Clean and rebuild
.PHONY: rebuild
rebuild: clean build

# Build all days
.PHONY: all-days
all-days:
	@for i in 1 2 3 4 5 6 7 8 9 10 11 12; do \
		$(MAKE) build DAY=$$i; \
	done

# Clean all build artifacts
.PHONY: clean-all
clean-all: clean

# Help target
.PHONY: help
help:
	@echo "Advent of Code 2025 - Makefile Commands"
	@echo "======================================="
	@echo ""
	@echo "Usage: make [target] [DAY=N]"
	@echo ""
	@echo "Targets:"
	@echo "  all (default)  - Build and run the specified day"
	@echo "  build          - Build the specified day only"
	@echo "  run            - Run the specified day (builds if needed)"
	@echo "  debug          - Build with debug symbols"
	@echo "  clean          - Remove build artifacts"
	@echo "  rebuild        - Clean and rebuild"
	@echo "  all-days       - Build all 12 days"
	@echo "  help           - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make DAY=1     - Build and run day 1"
	@echo "  make build DAY=5  - Build day 5 only"
	@echo "  make debug DAY=3  - Build day 3 with debug symbols"
	@echo "  make all-days  - Build all days"
