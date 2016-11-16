#-----------------------------------------------
# !!! Do not change the following lines !!!
#-----------------------------------------------

LIB=
LIB_SRC=
LIB_OBJ=

BIN=test
BIN_SRC=$(wildcard synthesized_functions.cpp)
BIN_OBJ=$(patsubst %.cpp,%.o,$(BIN_SRC))

#-----------------------------------------------

CXX=g++
INCPATH=
CXXFLAGS += -Wall -g

LDFLAGS +=

.PHONY: build clean

all: build

$(BIN): $(LIB) $(BIN_OBJ)
	$(CXX) $(BIN_OBJ) -o $@ $(LIB) $(LDFLAGS)

%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)

build: $(LIB) $(BIN)
	@echo
	@echo 'Build succeed !'

# CC=g++
# CFLAGS=-c -Wall
# LDFLAGS=
# SOURCES=synthesized_functions.cpp
# OBJECTS=$(SOURCES:.cpp=.o)
# EXECUTABLE=test

# all: $(SOURCES) $(EXECUTABLE)
    
# $(EXECUTABLE): $(OBJECTS) 
# 	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# .cpp.o:
# 	$(CC) $(CFLAGS) $< -o $@

# clean:
# 	rm -f *.o $(EXECUTABLE)