# Variable con la ruta del codigo fuente
SRC_DIR = ./src
INC_DIR = ./inc

OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin
DOC_DIR = $(OUT_DIR)/doc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) 
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(OBJ_FILES)
	@echo "Linking object files to create the executable"
	@mkdir -p $(BIN_DIR)
	@gcc $(OBJ_FILES) -o $(BIN_DIR)/app.out

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< to $@"
	@mkdir -p $(OBJ_DIR)
		gcc -o $@ -c $< $(foreach DIR,$(INC_DIR),-I $(DIR)) -MMD

clean:
	@rm -rf $(OUT_DIR)

info:
	echo "OBJ_FILES=$(OBJ_FILES)"

doc:
	@echo "Generating documentation"
	@mkdir -p $(OUT_DIR)/doc
	@doxygen doxyfile
