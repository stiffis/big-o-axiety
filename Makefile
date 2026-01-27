CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -g
INCLUDES = -Iinclude

SRC_DIR = src
BUILD_DIR = build
EXAMPLES_DIR = examples
TESTS_DIR = tests

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

EXAMPLE_SOURCES = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLE_BINS = $(EXAMPLE_SOURCES:$(EXAMPLES_DIR)/%.c=$(BUILD_DIR)/%)

TEST_SOURCES = $(wildcard $(TESTS_DIR)/*.c)
TEST_BINS = $(TEST_SOURCES:$(TESTS_DIR)/%.c=$(BUILD_DIR)/%)

.PHONY: all clean examples tests run-examples run-tests

all: $(OBJECTS)

examples: $(EXAMPLE_BINS)

tests: $(TEST_BINS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%: $(EXAMPLES_DIR)/%.c $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BUILD_DIR)/%: $(TESTS_DIR)/%.c $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run-examples: examples
	@echo "Running examples..."
	@for bin in $(EXAMPLE_BINS); do \
		echo "\n=== Running $$bin ==="; \
		$$bin; \
	done

run-tests: tests
	@echo "Running tests..."
	@for bin in $(TEST_BINS); do \
		echo "\n=== Running $$bin ==="; \
		$$bin; \
	done

clean:
	rm -rf $(BUILD_DIR)
