#include <iostream>
#include <math.h>

#include "Particle.h"
#include "Util.h"
#include "Point.h"
#include "Config.h"

Particle::Particle(){
}

Particle::Particle(vector_punteros_a_punto position){
	this->position = position;
}

Particle::Particle(const Particle& orig) {
}

Particle::~Particle() {
}

// Initialize the particle's position with a uniformly distributed random
// vector: xi ~ U(blo, bup), where blo and bup are the lower and upper
// boundaries of the search-space
void Particle::createRandomRoute(Point* origin, Point* target){

	Config &config = Config::getInstance();
	Map* mapa = config.getMap();

	//cout << "Particle:createRandomRoute(): map[1][0]: " << mapa->getMap()[1][0] << endl;
	//cout << "Particle:createRandomRoute(): origin: " << origin->toString() << endl;
	//cout << "Particle:createRandomRoute(): target: " << target->toString() << endl;

	//ruta generada
	vector<Point*> ruta;

	//agregar el primer elemento de la ruta (origin)
	ruta.push_back(origin);

	//obtener camino hasta llegar a la meta
	bool llega_a_meta = false;

	Point* punto_actual = origin;

	//int i = 0;
	while(!llega_a_meta){
		Point* p = new Point();
		*p = mapa->selectRandomNextStep(punto_actual, &ruta, target);

		punto_actual = p;

		//cout << "Particle:createRandomRoute(): agregando punto " << punto_actual->toString() << " a la ruta" << endl;
		ruta.push_back(punto_actual);

		//cout << "Particle:createRandomRoute(): ruta[" << ruta.size()-1 << "] = " << ruta[ruta.size()-1]->toString() << endl;

		//i++;
		//llega_a_meta = true; //comentar esto al final
		if(*punto_actual == *target)
			llega_a_meta = true;
	}

	//copiar la ruta para que sea la posicion de la particula
	//TODO: verificar que la copia funciona en el Swarm
	this->position = ruta;

	//cout << "Particle:createRandomRoute(): ruta completa en " << this->position.size() << " pasos" << endl;

	//for(unsigned int i=0; i<ruta.size(); i++){
	//	cout << "Particle:createRandomRoute(): ruta[" << i << "] = " << ruta[i]->toString() << endl;
	//}
}

void Particle::updatePosition(){ // // x_{i+1} = ...
    return;
}

void Particle::updateVelocity(vector_punteros_a_punto bestGlobalKnownPosition){  // v_{i+1} = ...

   Config &config = Config::getInstance();

     //Pick random numbers: rp, rg ~ U(0,1)
    int rp = Util::getUniformPRand();
    int rg = Util::getUniformPRand();

    int w = config.getOmega();

    int op = config.getPhiP();
    int og = config.getPhiG();

    //  Update the particle's velocity:
     for(unsigned int i=0; i < this->velocity.size(); i++){

	 /*
         // point velocity reference
         Point* v = this->velocity[i];
         Point* x = this->position[i];
         Point* p = this->bestPosition[i];
         Point* g = bestGlobalKnownPosition[i];
	 // */

         //  vi ← ω vi + φp rp (pi-xi) + φg rg (g-xi)
         //v = w*v + phi_p*rp*(p-x) + phi_g*rg*(g-x);

     }

    return;
}

void Particle::printParticle(){
	cout << "Particle::printParticle()" << endl;
	for(unsigned int i=0; i<this->position.size(); i++){
		cout << "Particle::printParticle(): this->position[" << i << "]->toString() = " << this->position[i]->toString() <<endl;
	}
}

void Particle::evaluateFitness(){
	// f.o = ...
	Config &config = Config::getInstance();
	Map* map = config.getMap();

	float alpha = config.getAlpha();

	// get length of path
	// get the number of collisions
	int nc = 0;
	for(unsigned int i=0; i < this->position.size(); i++){
		Point *o = this->position[i];
		nc+=map->getCollision(o);
	}

	float lenght = (float)this->position.size();

	float newFitness = lenght + nc*(1+pow(lenght, alpha));

	this->setFitness(newFitness);
	return;
}

void Particle::particleConstraints(){
    // constraints
    return;
}

// GETTERS AND SETTERS
void Particle::setPosition(vector_punteros_a_punto newPosition){
    this->position = newPosition;
    return;
}

void Particle::setBestPosition(vector_punteros_a_punto newBestPosition){
    this->bestPosition = newBestPosition;
    return;
}
void Particle::setVelocity(vector_punteros_a_punto newVelocity){
    this->velocity = newVelocity;
    return;
}

void Particle::setFitness(float newFitness){
    this->fitness = newFitness;
}

void Particle::setBestFitness(float newFitness){
    this->bestFitness = newFitness;
    return;
}


vector_punteros_a_punto Particle::getPosition(){
    return this->position;
}

vector_punteros_a_punto Particle::getBestPosition(){
    return this->bestPosition;
}

vector_punteros_a_punto Particle::getVelocity(){
    return this->velocity;
}


float Particle::getFitness(){
    return this->fitness;
}
float Particle::getBestFitness(){
    return this->bestFitness;
}

int Particle::getSize(){
    return this->position.size();
}
