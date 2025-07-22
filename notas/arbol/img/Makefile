SRC_DIR = src
BIN_DIR = bin
SOURCES = $(shell find $(SRC_DIR) -name "*.gv")
TARGETS = $(patsubst $(SRC_DIR)/%.gv,%.png,$(SOURCES))

all: $(BIN_DIR) $(TARGETS)
.PHONY: all clean

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

%.png: $(SRC_DIR)/%.gv
	@if [ ! -d "$(BIN_DIR)" ]; then \
		mkdir -p $(BIN_DIR); \
	fi
	dot -Tpng $< -o $(BIN_DIR)/$@

clean:
	rm -r $(BIN_DIR)
