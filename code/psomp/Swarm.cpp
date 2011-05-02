using namespace std;

#include "Swarm.h"
#include <iostream>

#define MAX_VALUE 9999

Swarm::Swarm() {
}

Swarm::Swarm(const Swarm& orig) {
}

Swarm::~Swarm() {
}

void Swarm::initialize(int cantidad_particulas = 10){
	//crear las particulas
	this->population = vector<Particle> (cantidad_particulas);
	
	//que el mejor fitness al momento de creacion sea un valor alto
	this->best_fitness = MAX_VALUE;

	//buscar cual de todas las particulas es la mejor
	for (unsigned int i=0; i < this->population.size(); i++){
		Particle p = this->population[i];
		int bf = p.fitness();
		
		if(bf <= this->best_fitness){
			this->best_fitness = bf;
			this->best_particle = p;
		}
	}
}

void Swarm::init(){
	
}