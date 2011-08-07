#Compilador
CC=g++
#Flags que usara el compilador
CFLAGS=-c -Wall
#Ejecutable
BIN=psomp.bin
#SRC=main.cpp Map.cpp Parser.cpp Swarm.cpp Particle.cpp Point.cpp Config.cpp Util.cpp
SRC = main.cpp Swarm.cpp Particle.cpp Route.cpp Point2D.cpp Map.cpp Config.cpp
OBJ=$(SRC:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC)  $(OBJ) -o $(BIN)

clean:
	rm -rf $(BIN) $(OBJ) 
