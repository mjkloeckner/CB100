SRC_DIR = src
BIN_DIR = bin
SOURCES = $(shell find $(SRC_DIR) -name "*.gv")
TARGETS = $(patsubst $(SRC_DIR)/%.gv,$(BIN_DIR)/%.png,$(SOURCES))

all: $(BIN_DIR) $(TARGETS)
.PHONY: all clean

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.png: $(SRC_DIR)/%.gv
	@if [ ! -d "$(BIN_DIR)" ]; then \
		mkdir -p $(BIN_DIR); \
	fi
	dot -T png $< -o $@

clean:
	rm -rf $(BIN_DIR)
