#Compilador
CC=g++
#Flags que usara el compilador
CFLAGS=-c -Wall
#Ejecutable
EXE=psomp.exe

all: $(EXE)

$(EXE): main.o Map.o Swarm.o Particle.o Point.o
	g++ main.o Map.o Swarm.o Particle.o Point.o -o $(EXE)

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
	rm *.o $(EXE)