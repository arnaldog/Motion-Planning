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
		//generar ruta random (inicializar)
		p.initialize();

		// evaluar función objetivo
		p.evaluateFitness();


		//imprimir particula:
		//p.printParticle();

		//inicializacion mejor posicion
		p.setBestPosition(p.getPosition());
		p.setBestFitness(p.getFitness());

		//debug: mostrar si efectivamente se esta guardando la mejor posicion
		/*
		cout << "------------" << endl;
		vector_punteros_a_punto b = p.getBestPosition();
		for(unsigned int j=0; j<b.size(); j++){
			cout << b[j]->toString() << endl;
		}
		*/

		//actualizar la mejor solucion conocida
		if(p.getFitness() <= this->bestFitness) {
			//actualizar la mejor solucion de la poblacion
			this->setBestFitness(p.getFitness());
			this->bestParticle = i;
		}
	}
}

void Swarm::iterate(){

    //criterio de parada: numero de iteraciones.
    int iteration=0;

	while(iteration < this->iterations){

		//debug
		cout << "Swarm::iterate(): iteracion " << iteration << endl;

		//para cada partícula, hacer:
		for(unsigned int i=0; i < this->population.size(); i++){

			cout << "Swarm::iterate(): >> particula " << i << endl;

			// referencia a la particula para ser modificada.
			Particle &p = this->population[i];

			//pick random numbers: rp, rg ~ U(0,1)

			/*
			 * Updating velocity:
			 * The particle knows their best kwnown position
			 * , position and velocity but
			 * unknown swarm best known position
			 */

			Particle best_particle = this->population[this->getBestParticle()];

			//TODO: comentar que hace esto
			p.updateVelocity(best_particle.getBestPosition());

			//update the particle's position: xi ← xi + vi
			p.updatePosition();

			//evaluate the new fitness
			p.evaluateFitness();

			//if (f(xi) < f(pi)) do:
			if(p.getFitness() < p.getBestFitness()) {
				//Update the particle's best known position: pi ← xi

				p.setBestPosition(p.getPosition()); //actualiza mejor posicion
				p.setBestFitness(p.getFitness());
			}

			//If (f(pi) < f(g)) update the swarm's best known position:
			//g ← pi
			if(p.getFitness() < this->bestFitness){
				this->bestFitness = p.getFitness();
				this->bestParticle = i;
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

void Swarm::printBestPosition(){
	//obtener la mejor particula
	Particle best_particle = this->population[this->getBestParticle()];

	best_particle.printParticle();
}
