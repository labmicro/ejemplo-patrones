# Ejemplo a compilar, por ejemplo:
#   observador/lista, observador/vector, interface/basico, interface/data, eventos/basico, estrategia
EXAMPLE ?= interface/basico
SRC_DIR = ./$(EXAMPLE)
OBJ_DIR = ./build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) 
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

PUML_FILES := $(shell find . -name '*.puml')
SVG_FILES := $(PUML_FILES:.puml=.svg)
PNG_FILES := $(PUML_FILES:.puml=.png)
KROKI ?= https://kroki.io/plantuml

-include $(OBJ_DIR)/*.d

.DEFAULT_GOAL := all

.PHONY: all clean diagrams clean-diagrams

all: $(OBJ_FILES)
	@gcc $(OBJ_FILES) -o $(OBJ_DIR)/app.out

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@gcc -o $@ -c $< -MMD

diagrams: $(SVG_FILES) $(PNG_FILES)

%.svg: %.puml
	@echo "Generando $@"
	@awk '/^@startuml/ { print; print "skinparam backgroundColor transparent"; next } { print }' $< | \
		curl -sS -f -H "Content-Type: text/plain" --data-binary @- "$(KROKI)/svg" -o $@

%.png: %.puml
	@echo "Generando $@"
	@curl -sS -f -H "Content-Type: text/plain" --data-binary @$< "$(KROKI)/png" -o $@

clean:
	@rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(OBJ_DIR)/app.out

clean-diagrams:
	@rm -f $(SVG_FILES) $(PNG_FILES)
