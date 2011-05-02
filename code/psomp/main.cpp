using namespace std;

#include <cstdlib>
#include <iostream>

#include "Config.h"
#include "Map.h"
#include "Swarm.h"


#define CANTIDAD_PARTICULAS 5

int main(int argc, char** argv) {


        // Inicializar la configuracion (singleton)
        //Config *o = Config::Instance();
        //o->getPhiG(1.1);
        /*
        conf.setIterations(20);
        conf.setOmega(20);
        conf.setPhiG(0.3);
        conf.setPhiP(0.7); */

        //Config::Instance()->setPhiG(0.1);
        
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
