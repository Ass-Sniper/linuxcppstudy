.PHONY:clean all
CC=g++
CFALGS=-Wall -g
BIN=pass_large_object
all:$(BIN)
%.o:%.cpp
		$(CC) $(CFALGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
