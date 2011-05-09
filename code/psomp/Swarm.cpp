using namespace std;

#include "Swarm.h"
#include "Particle.h"
#include "Util.h"
#include <iostream>

#define MAX_VALUE 9999
#define PARTICLE_LENGTH 20

Swarm::Swarm() {
}

Swarm::Swarm(const Swarm& orig) {
}

Swarm::~Swarm() {
}

void Swarm::initialize(){

	//inicializar cada particula de la poblacion
	for(unsigned int i=0; i < this->population.size(); i++){

		//cout << "inicializando particula: " << i << endl;

		// Referencia al objeto de la poblacion
		Particle &p = this->population[i];

		// Inicializacion de la posicion
		Config &config = Config::getInstance();
		Map* mapa = config.getMap();

		p.createRandomRoute(mapa->getStart(), mapa->getGoal());

		// evaluar función objetivo
		p.evaluateFitness();

		//imprimir particula:
		//p.printParticle();

		//inicializacion mejor posicion
		p.setBestPosition(p.getPosition());
		p.setBestPositionFitness(p.getPositionFitness());

		//mejor solucion conocida
		if(p.getPositionFitness() <= this->bestFitness) {
				//actualizar la mejor solucion de la poblacion
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

			/*
			 * Updating velocity:
			 * The particle knows their best kwnown position
			 * , position and velocity but
			 * unknown swarm best known position
			 */

			Particle bestParticle = this->population[this->getBestParticle()];
			p.updateVelocity(bestParticle.getBestPosition());

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

void Swarm::setPopulation(vector<Particle> newPopulation){
	this->population = newPopulation;
	return;
}
void Swarm::setBestParticle(int newParticle){
	this->bestParticle = newParticle;
	return;
}
void Swarm::setBestFitness(float newBestFitness){
	this->bestFitness = newBestFitness;
	return;
}

void Swarm::setIterations(int newIterations){
	this->iterations = newIterations;
	return;
}

vector<Particle> Swarm::getPopulation(){
	return this->population;
}

int Swarm::getBestParticle(){
	return this->bestParticle;
}

float Swarm::getBestFitness(){
	return this->bestFitness;
}

int Swarm::getIterations(){
	return this->iterations;
}
