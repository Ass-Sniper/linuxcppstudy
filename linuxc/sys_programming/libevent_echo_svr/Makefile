#-----------------------------------------------
# !!! Do not change the following lines !!!
#-----------------------------------------------

LIB=
LIB_SRC=
LIB_OBJ=

BIN=server
BIN_SRC=$(wildcard echo_server.c)
BIN_OBJ=$(patsubst %.c,%.o,$(BIN_SRC))

#-----------------------------------------------

CC=gcc
INCPATH=
CFLAGS += -Wall -g

LDFLAGS += -levent

.PHONY: build clean test

all: build

$(BIN): $(LIB) $(BIN_OBJ)
	$(CC) $(BIN_OBJ) -o $@ $(LIB) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)

build: $(LIB) $(BIN)
	@echo '------Build succeed------'

test: $(BIN)
	@./${BIN}