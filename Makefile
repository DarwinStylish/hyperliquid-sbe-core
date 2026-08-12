CC       = gcc
CFLAGS   = -O3 -Wall -Werror -std=c11
# All shared headers live in hft_core; adapters are header-only in hft_core/include
CORE_INC = ../../engine/private/include
INCLUDES = -I$(CORE_INC)

BUILD_DIR = build

TEST_HL = $(BUILD_DIR)/test_hl_sbe

.PHONY: all test clean

all: $(TEST_HL)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_HL): tests/test_hl_sbe.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

test: $(TEST_HL)
	@$(TEST_HL)

clean:
	rm -rf $(BUILD_DIR)
