#Compilador
CC=g++
#Flags que usara el compilador
CFLAGS=-c -Wall
#Ejecutable
BIN=psomp.bin
SRC=main.cpp Map.cpp Parser.cpp Swarm.cpp Particle.cpp Point.cpp Config.cpp Util.cpp
OBJ=$(SRC:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC)  $(OBJ) -o $(BIN)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Map.o: Map.cpp
	$(CC) $(CFLAGS) Map.cpp

Parser.o: Parser.cpp
	$(CC) $(CFLAGS) Parser.cpp

Swarm.o: Swarm.cpp
	$(CC) $(CFLAGS) Swarm.cpp

Particle.o: Particle.cpp
	$(CC) $(CFLAGS) Particle.cpp

Point.o: Point.cpp
	$(CC) $(CFLAGS) Point.cpp

Config.o: Config.cpp
	$(CC) $(CFLAGS) Config.cpp

Util.o:	Util.cpp
	$(CC) $(CFLAGS) Util.cpp

clean:
	rm $(OBJ) $(BIN)
