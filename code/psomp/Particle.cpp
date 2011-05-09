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
void Particle::initialize(){
	Config &config = Config::getInstance();
	Map* mapa = config.getMap();

	this->position = this->createRandomRoute(mapa->getStart(), mapa->getGoal());
}

vector_punteros_a_punto Particle::createRandomRoute(Point* origin, Point* target){

	Config &config = Config::getInstance();
	Map* mapa = config.getMap();

	//cout << "Particle:createRandomRoute(): map[1][0]: " << mapa->getMap()[1][0] << endl;
	//cout << "Particle:createRandomRoute(): origin: " << origin->toString() << endl;
	//cout << "Particle:createRandomRoute(): target: " << target->toString() << endl;

	//ruta generada
	vector_punteros_a_punto ruta;

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

	//cout << "Particle:createRandomRoute(): ruta completa en " << this->position.size() << " pasos" << endl;

	//for(unsigned int i=0; i<ruta.size(); i++){
	//	cout << "Particle:createRandomRoute(): ruta[" << i << "] = " << ruta[i]->toString() << endl;
	//}

	return ruta;
}

void Particle::updatePosition(){ // // x_{i+1} = ...
	//se tiene un vector de velocidad...
	//el cual es un vector con las posiciones por las que esta obligada a pasar esta particula
	//si quiere asi imitar a otras particulas mejores

	//por cada punto en la velocidad...
	Config &config = Config::getInstance();
	Map* mapa = config.getMap();

	//agregar el punto de meta al vector de velocidades
	this->velocity.push_back(mapa->getGoal());

	//crear vector que unira las subrutas a generar
	vector_punteros_a_punto final;

	//punto de inicio de la subruta (el comienzo del mapa al principio)
	Point* inicio = mapa->getStart();

	//puntero a vector de la subruta generada
	vector_punteros_a_punto* subruta = 0;
	for(unsigned int i=0; i<this->velocity.size(); i++){
		//hay que crear una ruta random desde el punto de la subruta anterior
		//(o el comienzo del mapa si es la primera)

		//reservar memoria para la subruta
		subruta = new vector_punteros_a_punto();

		//generar subruta
		*subruta = this->createRandomRoute(inicio,this->velocity[i]);

		//ahora que se tiene una subruta, recorrerla punto a punto y agregarla al vector final
		//se omite el ultimo punto, ya que la siguiente subruta parte por el mismo punto del final que esta
		for(unsigned int j=0; j<subruta->size()-1; j++){
			vector_punteros_a_punto ruta = *subruta;
			final.push_back(ruta[j]);
		}

		//actualizar punto de inicio
		inicio = this->velocity[i];
	}

	//por ultimo hay que hacer agregar el punto de meta ya que fue omitido
	final.push_back(mapa->getGoal());

	//ya que se tiene el vector final, hay que actualizar la posicion nueva
	this->position = final; //TODO: verificar si la posicion es efectivamente actualizada

	return;
}

void Particle::updateVelocity(vector_punteros_a_punto bestGlobalKnownPosition){  // v_{i+1} = ...

	Config &config = Config::getInstance();

	//pick random numbers: rp, rg ~ U(0,1)
	int rp = Util::getUniformPRand();
	int rg = Util::getUniformPRand();

	int w = config.getOmega();

	int op = config.getPhiP();
	int og = config.getPhiG();

	//update the particle's velocity:
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
