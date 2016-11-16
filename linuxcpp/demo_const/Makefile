.PHONY:clean all
CC=gcc
CFALGS=-Wall -g
BIN=constpointer
all:$(BIN)
%.o:%.c.cpp
		$(CC) $(CFALGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
