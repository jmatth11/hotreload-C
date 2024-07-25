CC=gcc
CFLAGS=-Wall -std=c11
LIBS=-lSDL2 -lSDL2_ttf -lm
INCLUDES=-I./
OBJ=obj
BIN=bin
SOURCES=$(shell find . -name '*.c' -not -path './plugins/*' -not -path './deps/*')
FILTER_SHARED_OBJS=obj/./main-shared.o obj/./driver/command.o
SHARED_OBJECTS=$(filter-out $(FILTER_SHARED_OBJS),$(addprefix $(OBJ)/,$(SOURCES:%.c=%-shared.o)))
DEPS=$(shell find . -name Makefile -printf '%h\n' | grep -v 'unittest' | grep -v '^.$$')
TARGET=hotreload
SHARED_TARGET=libdriver.so

.PHONY: all
all: command shared

.PHONY: command
command:
	$(CC) -c -o obj/main.o main.c $(CFLAGS) $(INCLUDES)
	$(CC) -c -o obj/command.o driver/command.c $(CFLAGS) $(INCLUDES)
	$(CC) obj/main.o obj/command.o -O2 $(CFLAGS) $(LIBS) -o $(BIN)/$(TARGET)

.PHONY: shared
shared: $(SHARED_OBJECTS)
	$(CC) -shared -fPIC $^ -O2 $(CFLAGS) $(LIBS) -o $(BIN)/$(SHARED_TARGET)

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

