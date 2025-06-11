# Project details
PROJECT := dynamic-string
CC := bear -- clang
CFLAGS := -Wall -Wextra -Werror -Wconversion -Wunused-result
CPPFLAGS := -Iinclude -DNDEBUG -DTESTING

# Dirs
SRC_DIR := src
TEST_SRC_DIR := tests
BUILD_DIR := build
TEST_EXE_DIR := $(BUILD_DIR)/tests
OBJ_DIR := $(BUILD_DIR)/objs

# Src files
SRC := $(wildcard $(SRC_DIR)/*.c)
TEST_SRC := $(wildcard $(TEST_SRC_DIR)/*.c)

# Targets
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_EXE_DIR)/%)

# Rules
.PHONY: test clean

RUN_TEST := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=./$(TEST_EXE_DIR)/%)

test: $(TEST)
	@echo ""
	@$(RUN_TEST)
	
$(TEST_EXE_DIR)/%: $(TEST_SRC_DIR)/%.c $(OBJ) | $(TEST_EXE_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@
	@echo "$@ built."

$(TEST_EXE_DIR): | $(BUILD_DIR)
	@mkdir -p $@
	@echo "$@ dir created."

$(BUILD_DIR):
	@mkdir -p $@
	@echo "$@ dir created."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	@echo "$@ built."

$(OBJ_DIR): | $(BUILD_DIR)
	@mkdir -p $@
	@echo "$@ dir created."

clean:
	@echo "Deleting build files."
	@rm -rf $(BUILD_DIR) compile_commands.json
