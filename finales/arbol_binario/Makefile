SRC_DIR    = src
BIN_DIR    = bin
MAIN_CLASS = Main
SOURCES    = $(shell find $(SRC_DIR) -name "*.java")
CLASSES    = $(patsubst $(SRC_DIR)/%.java, $(BIN_DIR)/%.class, $(SOURCES))

.PHONY: all compile run clean

all: run

compile: $(CLASSES)

# Compilar todos los .java si alguno está desactualizado
$(BIN_DIR)/%.class: $(SRC_DIR)/%.java
	@mkdir -p $(BIN_DIR)
	javac -d $(BIN_DIR) $(SOURCES)

run: compile
	java -cp $(BIN_DIR) $(MAIN_CLASS)

clean:
	rm -rf $(BIN_DIR)
