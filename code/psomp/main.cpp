using namespace std;

#include <cstdlib>
#include <iostream>
#include <string>

#include "Config.h"
#include "Map.h"
#include "Swarm.h"
#include "Particle.h"

#define CANTIDAD_PARTICULAS 30

bool verificarEntradas(int c);

int main(int argc, char** argv) {

	//verificar que se ingresaron 5 parámetros de entrada
	if(!verificarEntradas(argc)) return 0;

	//inicializar la configuracion (singleton)
	Config &config = Config::getInstance();
        config.setOmega(20);
	config.setIterations(20);
	config.setOmega(20);
	config.setPhiG(0.3);
	config.setPhiP(0.7);
	config.setAlpha(0.5);
	config.setPivots(5);

	//crear mapa
	Map mapa = Map(argv[1]);

	//imprimir mapa (opcional)
	//mapa.printMap();

	//agregar mapa a los datos de configuracion global
	config.setMap(&mapa);

	//crear enjambre de particulas
	Swarm swarm = Swarm();

	//inicialización de la población de particulas
	vector <Particle> newPopulation = vector<Particle> (CANTIDAD_PARTICULAS);

	swarm.setPopulation(newPopulation);
	swarm.setBestFitness(9999);
	swarm.setIterations(config.getIterations());

	//inicializar
	swarm.initialize();

	//debug
	cout << "Mejor fitness obtenido despues de inicializar = " << swarm.getBestFitness() << endl;

	//comenzar PSO F*CK YEAH!
	swarm.iterate();

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
