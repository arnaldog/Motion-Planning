#Compilador
CC=g++
#Flags que usara el compilador
CFLAGS=-c -Wall
#Ejecutable
BIN=psomp.bin
SRC=main.cpp Map.cpp Swarm.cpp Particle.cpp Point.cpp
OBJ=$(SRC:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJ)
	g++  $(OBJ) -o $(BIN)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Map.o: Map.cpp
	$(CC) $(CFLAGS) Map.cpp

Swarm.o: Swarm.cpp
	$(CC) $(CFLAGS) Swarm.cpp

Particle.o: Particle.cpp
	$(CC) $(CFLAGS) Particle.cpp

Point.o: Point.cpp
	$(CC) $(CFLAGS) Point.cpp

clean:
	rm $(OBJ) $(BIN)
