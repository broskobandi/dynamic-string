# Project details
PROJECT_GROUP := c-tools
PROJECT := dynamic-string
CC := $(shell command -v clang || command -v gcc)
CFLAGS := -Wall -Wextra -Werror -Wconversion -Wunused-result
CPPFLAGS := -Iinclude

# Dirs
SRC_DIR := src
INC_DIR := include
DOC := README.md
TEST_SRC_DIR := tests
BUILD_DIR := build
TEST_EXE_DIR := $(BUILD_DIR)/tests
OBJ_DIR := $(BUILD_DIR)/objs
SYS_PREFIX := /usr/local
SYS_LIB_DIR := $(SYS_PREFIX)/lib
SYS_DOC_DIR := $(SYS_PREFIX)/share/doc/$(PROJECT_GROUP)/$(PROJECT)
SYS_INC_DIR := $(SYS_PREFIX)/include/$(PROJECT_GROUP)

# Src files
SRC := $(wildcard $(SRC_DIR)/*.c)
TEST_SRC := $(wildcard $(TEST_SRC_DIR)/*.c)
INC := $(INC_DIR)/$(PROJECT).h

# Targets
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_EXE_DIR)/%)
LIB := $(BUILD_DIR)/lib$(PROJECT_GROUP)_$(PROJECT).a

# Command to execute all tests
RUN_TEST := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=./$(TEST_EXE_DIR)/%)

# Rules
.PHONY: default test clean install uninstall

default: $(LIB)

$(LIB): $(OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

test: CPPFLAGS += -DNDEBUG -DTESTING
test: CC := bear -- $(CC)
test: $(TEST)
	@echo ""
	$(RUN_TEST)
	
$(TEST_EXE_DIR)/%: $(TEST_SRC_DIR)/%.c $(OBJ) | $(TEST_EXE_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(TEST_EXE_DIR): | $(BUILD_DIR)
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR): | $(BUILD_DIR)
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) compile_commands.json

install:
	install -d $(SYS_INC_DIR)
	install -d $(SYS_DOC_DIR)
	install -d $(SYS_LIB_DIR)
	install -m 644 $(LIB) $(SYS_LIB_DIR)
	install -m 644 $(INC) $(SYS_INC_DIR)
	install -m 644 $(DOC) $(SYS_DOC_DIR)

uninstall:
	rm -f $(addprefix $(SYS_LIB_DIR)/, $(notdir $(LIB)))
	rm -f $(addprefix $(SYS_INC_DIR)/, $(notdir $(INC)))
	rm -rf $(SYS_DOC_DIR)
