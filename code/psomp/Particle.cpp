#include <iostream>

#include "Particle.h"
#include "Util.h"
#include "Point.h"
#include "Config.h"

Particle::Particle(){
}

Particle::Particle(vector <Point> position){
	this->position = position;
	this->size = position.size();
}

Particle::Particle(const Particle& orig) {
}

Particle::~Particle() {
}

// Initialize the particle's position with a uniformly distributed random
// vector: xi ~ U(blo, bup), where blo and bup are the lower and upper
// boundaries of the search-space
void Particle::createRandomRoute(){

    Config &config = Config::getInstance();

    cout << config.getOmega() << " OK" << endl;

   //for (unsigned int i = 0; i < this->position.size(); i++){
    for (unsigned int i = 0; i < 20 ; i++){
        Point p = Point(i,i);
        this->position.push_back(p);
        //cout << p.getX() << " " << p.getY() << endl;
    }

	Map* mapa = config.getMap();
	Point* start = mapa->getStart();
	Point* goal = mapa->getGoal();

	//cout << "Particle:createRandomRoute(): map[1][0]: " << mapa->getMap()[1][0] << endl;
	cout << "Particle:createRandomRoute(): start: " << start->toString() << endl;
	cout << "Particle:createRandomRoute(): goal: " << goal->toString() << endl;

	//ruta generada
	vector<Point*> ruta;

	//agregar el primer elemento de la ruta (start)
	ruta.push_back(start);

	//obtener camino hasta llegar a la meta
	bool llega_a_meta = false;

	Point* punto_actual = start;

	//int i = 0;
	while(!llega_a_meta){
		Point* p = new Point();
		*p = mapa->selectRandomNextStep(punto_actual, &ruta);

		punto_actual = p;

		cout << "Particle:createRandomRoute(): agregando punto " << punto_actual->toString() << " a la ruta" << endl;
		ruta.push_back(punto_actual);

		cout << "Particle:createRandomRoute(): ruta[" << ruta.size()-1 << "] = " << ruta[ruta.size()-1]->toString() << endl;

		//i++;
		if(*punto_actual == *goal)
			llega_a_meta = true;
	}

	for(unsigned int i=0; i<ruta.size(); i++){
		cout << "Particle:createRandomRoute(): ruta[" << i << "] = " << ruta[i]->toString() << endl;
	}
	cout << "Particle:createRandomRoute(): ruta completa en " << ruta.size() << " pasos" << endl;

	this->evaluateFitness(); // evaluating fitness
}

void Particle::updatePosition(){ // // x_{i+1} = ...
    return;
}

void Particle::updateVelocity(vector <Point> bestGlobalKnownPosition){  // v_{i+1} = ...

   Config &config = Config::getInstance();

     //Pick random numbers: rp, rg ~ U(0,1)
    int rp = Util::getUniformPRand();
    int rg = Util::getUniformPRand();

    int w = config.getOmega();
    
    int phi_p = config.getPhiP();
    int phi_g = config.getPhiG();

    //  Update the particle's velocity:
     for(unsigned int i=0; i < this->velocity.size(); i++){

         // point velocity reference
         Point &v = this->velocity[i];
         Point x = this->position[i];
         Point p = this->bestPosition[i];
         Point g = bestGlobalKnownPosition[i];

         //  vi ← ω vi + φp rp (pi-xi) + φg rg (g-xi)
         //v = w*v + phi_p*rp*(p-x) + phi_g*rg*(g-x);

     }
     
    return;
}

void Particle::evaluateFitness(){
	// f.o = ...
	int newFitness=0;

	for(unsigned int i=0; i < this->position.size(); i++){
		newFitness+=1; // replace this by a evaluation function
	}

	this->setPositionFitness(newFitness);
	return;
}

void Particle::particleConstraints(){
    // constraints
    return;
}

// GETTERS AND SETTERS
void Particle::setPosition(vector <Point> newPosition){
    this->position = newPosition;
    return;
}

void Particle::setBestPosition(vector <Point> newBestPosition){
    this->bestPosition = newBestPosition;
    return;
}
void Particle::setVelocity(vector <Point> newVelocity){
    this->velocity = newVelocity;
    return;
}

void Particle::setPositionFitness(int newFitness){
    this->positionFitness = newFitness;
    return;
}

void Particle::setBestPositionFitness(int newFitness){
    this->bestPositionFitness = newFitness;
    return;
}


void Particle::setSize(int newSize){
    this->size = newSize;
    return;
}

vector <Point> Particle::getPosition(){
    return this->position;
}

vector <Point> Particle::getBestPosition(){
    return this->bestPosition;
}

vector <Point> Particle::getVelocity(){
    return this->velocity;
}

int Particle::getPositionFitness(){
    return this->positionFitness;
}

int Particle::getBestPositionFitness(){
    return this->bestPositionFitness;
}

int Particle::getSize(){
    return this->size;
}
