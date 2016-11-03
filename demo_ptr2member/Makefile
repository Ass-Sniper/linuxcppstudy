.PHONY:clean all
CC=g++
CFALGS=-Wall -g
BIN=ptr2member
all:$(BIN)
%.o:%.c.cpp
		$(CC) $(CFALGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
