using namespace std;

#include <cstdlib>
#include <iostream>

#include "Map.h"
#include "Swarm.h"

#define CANTIDAD_PARTICULAS 5

int main(int argc, char** argv) {

	//crear mapa
	Map mapa = Map(argv[1]);
	
	//crear enjambre de particulas
	Swarm swarm = Swarm();
	
	//inicializar
	swarm.initialize(CANTIDAD_PARTICULAS);
	
	//comenzar PSO
	swarm.init();
	
	return 0;
}
