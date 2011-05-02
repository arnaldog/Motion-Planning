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

        // inicializar cada particula de la poblacion
        for(unsigned int i=0; i < this->population.size(); i++){
            
            // Referencia al objeto de la poblacion
            Particle &p = this->population[i];

            // Inicializacion de la posicion
            p.createRandomRoute(); // se necesita especificar

            // evaluar función objetivo
            p.evaluateFitness();

            // Inicializacion mejor posicion
            p.setBestPosition(p.getPosition());
            p.setBestPositionFitness(p.getPositionFitness());

            // Mejor solucion conocida
            if(p.getPositionFitness() <= this->bestFitness) {

                // actualizar la mejor solucion de la poblaion
                this->setBestFitness(p.getPositionFitness());
                this->bestParticle = i;
            }   
        }
}

void Swarm::init(){
	
}

void Swarm::iteration(){

    // Criterio de parada: numero de iteraciones.
    int iteration=0;
    
    while(iteration < this->iterations){

        //Para cada partícula, hacer: 
        for(unsigned int i=0; i < this->population.size(); i++){

            // referencia a la particula para ser modificada.
            Particle &p = this->population[i];

            //Pick random numbers: rp, rg ~ U(0,1)
            //int rp = this->pickRandomNumber(0, 1);
            //int rg = this->pickRandomNumber(0, 1);

            //Update the particle's velocity:
            //vi ← ω vi + φp rp (pi-xi) + φg rg (g-xi)
            p.updateVelocity();
            
            //Update the particle's position: xi ← xi + vi
            p.updatePosition();

            // evaluate the new fitness
            p.evaluateFitness();

            //If (f(xi) < f(pi)) do:
            if(p.getPositionFitness() < p.getBestPositionFitness()) {
                //Update the particle's best known position: pi ← xi

                p.setBestPosition(p.getPosition()); // actualiza mejor posicion
                p.setBestPositionFitness(p.getPositionFitness());

                //If (f(pi) < f(g)) update the swarm's best known position:
                //g ← pi
                if(p.getBestPositionFitness() < this->bestFitness){
                    this->bestFitness = p.getBestPositionFitness();
                    this->bestParticle = i;
                }
            }
        }
        iteration++; // next iteration;

    }

}

// GETTERS AND SETTERS
void Swarm::setBestFitness(int newBestFitness){
    this->bestFitness = newBestFitness;
    return;
}