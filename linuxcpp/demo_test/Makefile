#-----------------------------------------------
# !!! Do not change the following lines !!!
#-----------------------------------------------

LIB=
LIB_SRC=
LIB_OBJ=

BIN=testbin
BIN_SRC=$(wildcard test.cpp)
BIN_OBJ=$(patsubst %.cpp,%.o,$(BIN_SRC))

#-----------------------------------------------

CXX=g++
INCPATH=
CXXFLAGS += -Wall -g

LDFLAGS +=

.PHONY: build clean test

all: build

$(BIN): $(LIB) $(BIN_OBJ)
	$(CXX) $(BIN_OBJ) -o $@ $(LIB) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)

build: $(LIB) $(BIN)
	@echo '------Build succeed------'

test: $(BIN)
	@./${BIN}