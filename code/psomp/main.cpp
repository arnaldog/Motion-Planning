using namespace std;

#include <cstdlib>
#include <iostream>
#include <string>

#include "Config.h"
#include "Map.h"
#include "Swarm.h"

#define CANTIDAD_PARTICULAS 5

bool verificarEntradas(int c);

int main(int argc, char** argv) {

	//verificar que se ingresaron 5 parámetros de entrada
	if(!verificarEntradas(argc)) return 0;

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
	
	//imprimir mapa (opcional)
	mapa.printMap();
	
	//crear enjambre de particulas
	Swarm swarm = Swarm();
	
	//inicializar
	swarm.initialize(CANTIDAD_PARTICULAS);
	
	//comenzar PSO
	swarm.init();
	
	return 0;
}

bool verificarEntradas(int c){
	if(c != 2){
		cout << "ERROR: numero de parametros de entrada incorrectos, se esperaba 1" << endl;
		cout << "formato: ./psomp.bin <archivo de mapa>" << endl;
		return false;
	}
	return true;
}
