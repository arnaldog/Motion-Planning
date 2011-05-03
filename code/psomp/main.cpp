using namespace std;

#include <cstdlib>
#include <iostream>
#include <string>

#include "Map.h"
#include "Swarm.h"

#define CANTIDAD_PARTICULAS 5

bool verificarEntradas(int c);

int main(int argc, char** argv) {

	//verificar que se ingresaron 5 parámetros de entrada
	if(!verificarEntradas(argc)) return 0;

	//crear mapa
	cout << "Main: creando Map" << endl;
	Map mapa = Map(argv[1]);
	cout << "Main: END creando Map" << endl;
	
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