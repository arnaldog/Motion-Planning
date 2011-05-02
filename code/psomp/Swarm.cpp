using namespace std;

#include "Swarm.h"
#include "Particle.h"
#include <iostream>

#define MAX_VALUE 9999
#define PARTICLE_LENGTH 20

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
	this->bestFitness = MAX_VALUE;
        
        for(unsigned int i=0; i < this->population.size(); i++){
            
            // Referencia al objeto de la poblacion
            Particle &p = this->population[i];

            // Inicializacion de la posicion
            p.createRandomRoute();

            // Inicializacion mejor posicion
            p.setBestPosition(p.getPosition()); 

            // Mejor solucion conocida
            if(p.getFitness() <= this->bestFitness) {
                
                this->setBestFitness(p.getFitness());
                this->bestParticle = i;
            }   
        }
}

void Swarm::init(){
	
}

// GETTERS AND SETTERS
void Swarm::setBestFitness(int newBestFitness){
    this->bestFitness = newBestFitness;
    return;
}