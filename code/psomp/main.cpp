using namespace std;

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

#include "Config.h"
#include "Map.h"
#include "Swarm.h"
#include "Particle.h"

bool verificarEntradas(int argc,char** argv);

int main(int argc, char** argv) {

	//verificar que se ingresaron 5 parámetros de entrada
	if(!verificarEntradas(argc,argv)) return 0;

	//usar clase Config
	Config &config = Config::getInstance();

	//si no hay errores en las entradas imprimir configuracion
	config.printConfiguration();

	//crear mapa
	Map mapa = Map(config.getMapFile());

	//imprimir mapa (opcional)
	//mapa.printMap();

	//agregar mapa a los datos de configuracion global
	config.setMap(&mapa);

	//crear enjambre de particulas
	Swarm swarm = Swarm();

	//inicialización de la población de particulas
	vector <Particle> newPopulation = vector<Particle>(config.getParticleQuantity());

	swarm.setPopulation(newPopulation);
	swarm.setBestFitness(99999999); //infinite's for noobs
	swarm.setIterations(config.getIterations());

	//inicializar
	swarm.initialize();

	//debug
	cout << endl;
	cout << "main(): Mejor fitness obtenido despues de inicializar = " << swarm.getBestFitness() << endl;
	cout << endl;

	//comenzar PSO
	swarm.iterate();

	//terminado el PSO, imprimir la mejor posicion de las particulas (opcional)
	//swarm.printBestPosition();

	cout << "PRINTING THE BEST PARTICLE NUMBER: " << swarm.getBestParticle() << endl;
	cout << "PRINTING THE BEST PARTICLE FITNESS:  " << swarm.getBestFitness() << endl;
	cout << "FINISH OF PSO" << endl;

	//imprimir la mejor particula del swarm, en forma de matriz
	swarm.printBestParticleAsMatrix();

	return 0;
}

bool verificarEntradas(int argc, char** argv){
	//verificar numero de entradas
	int argumentos_esperados = (1 + 2*1);
	if(argc < argumentos_esperados){
		cout << "ERROR: numero de parametros de entrada incorrectos, se esperaba " << argumentos_esperados << endl;
		cout << "formato: ./psomp.bin <archivo de mapa>" << endl;
		return false;
	}

	//set defaults
	Config &config = Config::getInstance();

	config.setMode("random");
	config.setIterations(1);
	config.setParticleQuantity(1);
	config.setOmega(1);
	config.setPhiG(2);
	config.setPhiP(2);
	config.setAlpha(0.5);
	config.setPivots(3);

	//revisar cada argumento dado
	for(int i=1; i<argc; i++){
		//cout << "main(): argv[" << i << "] = " << argv[i] << endl;

		if(string(argv[i]) == "-modo"){
			//cout << "main::verificarEntradas(): mmode = " << argv[i+1] << endl;
			string t = string(argv[i+1]);
			config.setMode(t);
		}

		if(string(argv[i]) == "-map"){
			//cout << "main::verificarEntradas(): mapa = " << argv[i+1] << endl;
			string t = string(argv[i+1]);
			config.setMapFile(t);
		}

		if(string(argv[i]) == "-iteraciones"){
			//cout << "main::verificarEntradas(): iteraciones = " << argv[i+1] << endl;
			config.setIterations(atoi(argv[i+1]));
		}

		if(string(argv[i]) == "-particulas"){
			//cout << "main::verificarEntradas(): particulas = " << argv[i+1] << endl;
			config.setParticleQuantity(atoi(argv[i+1]));
		}

		if(string(argv[i]) == "-pivotes"){
			//cout << "main::verificarEntradas(): pivotes = " << argv[i+1] << endl;
			config.setPivots(atoi(argv[i+1]));
		}

		if(string(argv[i]) == "-alpha"){
			//cout << "main::verificarEntradas(): alpha = " << argv[i+1] << endl;
			config.setAlpha(atoi(argv[i+1]));
		}

		if(string(argv[i]) == "-omega"){
			//cout << "main::verificarEntradas(): omega = " << argv[i+1] << endl;
			config.setOmega(atoi(argv[i+1]));
		}

		if(string(argv[i]) == "-phip"){
			//cout << "main::verificarEntradas(): phip = " << argv[i+1] << endl;
			config.setPhiP(atoi(argv[i+1]));
		}

		if(string(argv[i]) == "-phig"){
			//cout << "main::verificarEntradas(): phig = " << argv[i+1] << endl;
			config.setPhiG(atoi(argv[i+1]));
		}

	}

	return true;
}
