/*
 * File:   main.cpp
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 0:23
 */



using namespace std;
#include <cstdlib>
#include <vector>
#include "Swarm.h"
#include "Route.h"
#include "Point2D.h"
#include "Map.h"
#include "Config.h"
/*
 *
 */

typedef  float (Route::*fnRoute)(Route &r);
typedef  void (Route::*fnpRoute)(Route &r);

bool verificarEntradas(int argc,char** argv);

int main(int argc, char** argv) {

    if(!verificarEntradas(argc,argv)) return 0;

    Config &config = Config::getInstance();

    //si no hay errores en las entradas imprimir configuracion
    config.printConfiguration();

    //crear mapa en la configuracion
    string mapfilename = config.getMapFile();
    Map map = Map(mapfilename);
    config.setMap(&map);

    //imprimir informacion del mapa
    map.printInformation();

    // ROUTE Swarm(size, iterations, fitness);
    int swarmSize = config.getQuantity();
    int swarmIterations = config.getIterations();
    float swarmFitness = 99999999999999;
    Swarm<Route> swarm = Swarm<Route>(swarmSize, swarmIterations, swarmFitness);

    int particleSize = config.getPivots();
    swarm.setParticleSize(particleSize);

    // setting the objective function
    fnRoute objectiveFunction = &Route::fitnessEvaluation;
    fnpRoute initPositionFunction = &Route::initRandomRoute;
    fnpRoute initVelocityFunction = &Route::initRandomVelocity;

    swarm.setFitnessFunction(objectiveFunction);
    swarm.setInitPositionFunction(initPositionFunction);
    swarm.setInitVelocityFunction(initVelocityFunction);

    swarm.setPhig(config.getPhi_g());
    swarm.setPhip(config.getPhi_p());
    swarm.setOmega(config.getOmega());
    swarm.setRhog(0.1);
    swarm.setRhop(0.1);

    //swarm.initialization();
    swarm.initialize();

    //swarm.iterate();



    cout << "main(): Mejor particula obtenida al iterar: ";
    cout << swarm.getBestParticleIndex() << endl;

    cout << "main(): Mejor fitness obtenido al incializar: ";
    cout << swarm.getFitness() << endl;
    cout << endl;

    cout << "main(): La ruta resultante es: " << endl;
    swarm.printBestParticle();


    /*
    Route r = Route();
    r.initRandomRoute(r);
    r.printPath();

    Route r2 = Route();
    r2.initRandomRoute(r2);
    r2.printPath();

    Route r3 = Route();
    r3 = r2 - r;
    r3.printPath();

    Route r4 = Route();
    r4 = r3 + r;
    r4.printPath();
    */
    return 0;
}


bool verificarEntradas(int argc, char** argv){
    //verificar numero de entradas

    int nargs = (1 + 2*1);
    if(argc < nargs){
	cout << "ERROR: numero de parametros de entrada incorrectos, debe ser ";
	cout << nargs << endl;
	cout << "formato: ./psomp.bin <archivo de mapa>" << endl;
	return false;
    }

    //set defaults
    Config &config = Config::getInstance();

    config.setIterations(1);
    config.setQuantity(1); // particle cuantity
    config.setOmega(1);
    config.setPhi_g(2);
    config.setPhi_p(2);
    config.setAlpha(0.5);
    config.setPivots(3);

    //hermite inputs
	config.setMode("hermite");
	config.setHermiteBase(1);

    //revisar cada argumento dado
    for(int i=1; i<argc; i++){
    //cout << "main(): argv[" << i << "] = " << argv[i] << endl;

	if(string(argv[i]) == "-map"){
	    //cout << "main::verificarEntradas(): mapa = " << argv[i+1] << endl;
	    string t = string(argv[i+1]);
	    config.setMapFile(t);
	}

	if(string(argv[i]) == "-mode"){
	    string t = string(argv[i+1]);
	    config.setMode(t);
	}

	if(string(argv[i]) == "-hbase"){
	    config.setHermiteBase(atoi(argv[i+1]));
	}

	if(string(argv[i]) == "-iteraciones"){
	    //cout << "main::verificarEntradas(): iteraciones = " << argv[i+1] << endl;
	    config.setIterations(atoi(argv[i+1]));
	}

	if(string(argv[i]) == "-particulas"){
	    //cout << "main::verificarEntradas(): particulas = " << argv[i+1] << endl;
	    config.setQuantity(atoi(argv[i+1]));
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
	    config.setPhi_p(atoi(argv[i+1]));
	}

	if(string(argv[i]) == "-phig"){
	    //cout << "main::verificarEntradas(): phig = " << argv[i+1] << endl;
	    config.setPhi_g(atoi(argv[i+1]));
	}

    }

    return true;
}
