CC=gcc
CFLAGS=-Wall -std=c11
LIBS=-lSDL2 -lSDL2_ttf -lm
INCLUDES=-I./
OBJ=obj
BIN=bin
SOURCES=$(shell find . -name '*.c' -not -path './plugins/*' -not -path './deps/*')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))
DEBUG_OBJECTS=$(patsubst %.c, $(OBJ)/%-debug.o, $(SOURCES))
SHARED_OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%-shared.o))
DEPS=$(shell find . -name Makefile -printf '%h\n' | grep -v 'unittest' | grep -v '^.$$')
TARGET=sgf
SHARED_TARGET=libdriver.so

.PHONY: all
all: deps src

.PHONY: hotreload
hotreload: command shared

.PHONY: command
command:
	$(CC) -c -o obj/main.o main.c $(CFLAGS) $(INCLUDES)
	$(CC) -c -o obj/command.o driver/command.c $(CFLAGS) $(INCLUDES)
	$(CC) -c -o obj/ui/win.o ui/win.c $(CLFAGS) $(INCLUDES)
	$(CC) obj/main.o obj/command.o obj/ui/win.o -O2 $(CFLAGS) $(LIBS) -o $(BIN)/$(TARGET)

.PHONY: shared
shared: $(SHARED_OBJECTS)
	$(CC) -shared -fPIC $^ -O2 $(CFLAGS) $(LIBS) -o $(BIN)/$(SHARED_TARGET)

.PHONY: src
src: $(OBJECTS)
	$(CC) $^ -O2 $(CFLAGS) $(LIBS) -o $(BIN)/$(TARGET)

.PHONY: debug
debug: deps debugsrc

.PHONY: debugsrc
debugsrc: $(DEBUG_OBJECTS)
	$(CC) $^ -ggdb $(CFLAGS) $(LIBS) -o $(BIN)/$(TARGET)

$(OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(BIN)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

$(OBJ)/%-debug.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(BIN)
	$(CC) -ggdb -c -o $@ $< $(CFLAGS) $(INCLUDES)

$(OBJ)/%-shared.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(BIN)
	$(CC) -c -fPIC -o $@ $< $(CFLAGS) $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(OBJ)/* 2> /dev/null
	@rm -f $(BIN)/* 2> /dev/null

.PHONY: clean_deps
clean_deps:
	$(foreach dir, $(DEPS), $(shell cd $(dir) && $(MAKE) clean))

.PHONY: clean_all
clean_all: clean clean_deps

.PHONY: deps
deps:
	@for i in $(DEPS); do\
		cd $${i} && $(MAKE) && cd -;\
	done

