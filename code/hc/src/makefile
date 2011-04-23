SRC= motionplanning.c
OBJ= $(SRC:.c=.o)

BIN= hcmp.exe

all:	$(OBJ)
		gcc -o -Wall $(BIN)  $(SRC) -lm 

clean:
	rm -rf $(OBJ) $(BIN)
