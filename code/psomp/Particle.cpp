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

void Particle::initialize(){
	Config &config = Config::getInstance();
	Map* mapa = config.getMap();
	this->position = this->createRandomRoute(mapa->getStart(), mapa->getGoal());

	cout << "Particle::initialize(): ";
	for (unsigned int k=0; k < this->position.size(); k++ )
		cout << " " << this->position.at(k)->toString();
	cout << endl;
}

vector_punteros_a_punto Particle::createRandomRoute(Point* origin, Point* target){
    Config &config = Config::getInstance();
    Map* map = config.getMap();

    vector_punteros_a_punto path;
    path.push_back(origin);

    bool finish = false;
    Point* current = origin;

    while(!finish){
		Point *p = new Point();
		*p = map->selectRandomNextStep(current, &path, target);
		current = p;
		path.push_back(current);
		finish = (*current == *target) ? true : false;
    }

    this->slice(&path);
    return path;
}

void Particle::slice(vector_punteros_a_punto* ruta){
    //obtener los indices
    unsigned int indice_inicial = 0;
    unsigned int indice_final = 0;

    for(unsigned int i = 0; i < ruta->size(); i++){
		indice_inicial = i;
		Point* valor_a_buscar = ruta->at(i);

		//buscar desde el final
		for(unsigned int j=ruta->size()-1; j>0; j--){
			if( (j != i) && (*(ruta->at(j)) == *valor_a_buscar) ){
				indice_final = j;
				break;
			}
		}

		if(indice_final != 0){
			break;
		}
    }

    vector_punteros_a_punto f;

    for(unsigned int i = 0; i < ruta->size(); i++){
		if( (indice_inicial < i) && (i <= indice_final) ){
			continue;
		}
		f.push_back(ruta->at(i));
    }
    
    *ruta = f;
}

void Particle::updatePosition(){ // // x_{i+1} = ...
    cout << "Particle::updatePosition()" << endl;

    Config &config = Config::getInstance();
    Map* mapa = config.getMap();

    vector_punteros_a_punto pivots = this->velocity;
    pivots.push_back(mapa->getGoal());

    vector_punteros_a_punto final;
    Point* inicio = mapa->getStart();

    cout << "Particle::updatePosition(): creando ruta random" << endl;
    vector_punteros_a_punto* subruta = 0;

    for(unsigned int i=0; i < pivots.size(); i++){
	cout << "Particle::updatePosition(): iteracion "
	     << i+1 << "/" << pivots.size()
	     << endl;

	cout << "Particle::updatePosition(): reservando memoria para la ruta"
		<< endl;
	subruta = new vector_punteros_a_punto();

	cout << "Particle::updatePosition(): generando subruta random desde "
		<< inicio->toString() << " hasta " << pivots[i]->toString()
		<< endl;

	*subruta = this->createRandomRoute(inicio,pivots[i]);

	cout << "Particle::updatePosition(): ahora que se tiene subruta, "
		"punto a punto agregar al vector final"
		<< endl;

	for(unsigned int j=0; j < subruta->size()-1; j++){
	    vector_punteros_a_punto ruta = *subruta;
	    final.push_back(ruta[j]);
	}

	cout << "Particle::updatePosition(): actualizando punto de inicio" 
		<< endl;
	
	inicio = pivots[i];
    }

    final.push_back(mapa->getGoal());

    this->position = final; //TODO: verificar si la posicion es efectivamente actualizada

    return;
}

void Particle::initVelocity(){
    Config &config = Config::getInstance();
    int n = config.getPivots();
    int lenght = this->position.size();
	this->velocity.clear();
    for(int i=0; i < n; i+=1){
		int index = (int)floor((i+1)*(float)lenght/(float)n);
		this->velocity.push_back(this->position[(index==lenght)?index-1:index]);
    }

    for(unsigned int i=0; i<this->velocity.size(); i++){
	cout << "Particle::initVelocity: this->velocity[" << i << "] = " << this->velocity[i]->toString() << endl;
    }

}
void Particle::updateVelocity(vector_punteros_a_punto bestGlobalVelocity){  // v_{i+1} = ...

    Config &config = Config::getInstance();
    Map *map = config.getMap();
    int width = map->getWidth()-1;
    int height = map->getHeight()-1;

    //pick random numbers: rp, rg ~ U(0,1)
    float rp = Util::getUniformPRand();
    float rg = Util::getUniformPRand();

    int om = config.getOmega();
    int op = config.getPhiP();
    int og = config.getPhiG();
	
    //update the particle's velocity:
    for(unsigned int i=0; i < this->velocity.size(); i++){
		Point *v = this->velocity[i]; // get velocity
		Point *p = this->bestVelocity[i]; // get best local position
		Point *g = bestGlobalVelocity[i]; // get best global position
		
		if(v != NULL && p != NULL && g != NULL){
			float vx = v->getX();
			float vy = v->getY();
			
			vx = om*vx+op*rg*(p->getX()-vx)+og*rg*(g->getX()-vx);
			vy = om*vy+op*rg*(p->getY()-vy)+og*rp*(g->getY()-vy);

			vx = (vx < 0) ? 0 : ( (vx > width) ? width : vx);
			vy = (vy < 0) ? 0 : ( (vy > height) ? height : vy);

			v->setX((int)vx);
			v->setY((int)vy); // updating the velocity
			this->velocity[i] = v;
		}
    }
    return;
}

void Particle::printParticle(){
	cout << "Particle::printParticle()" << endl;
	for(unsigned int i=0; i<this->position.size(); i++){
		cout << "Particle::printParticle(): this->position[" << i << "]->toString() = " << this->position[i]->toString() << endl;
	}
}


void Particle::evaluateFitness(){
    Config &config = Config::getInstance();
    Map* map = config.getMap();

    float alpha = config.getAlpha();

    //contar numero de colisiones
    int nc = 0;
    for(unsigned int i=0; i < this->position.size(); i++){
	nc+=map->getCollision(this->position[i]);
    }

    float lenght = (float) this->position.size();
    float newFitness = lenght + nc*(1+pow(lenght, alpha));
    this->setFitness(newFitness);
    
	//debug
	cout << "Particle::evaluateFitness(): numero colisiones nc = " << nc << endl;

	return;
}

// GETTERS AND SETTERS
/* setters*/
void Particle::setPosition(vector_punteros_a_punto newPosition){
	this->position = newPosition;
	return;
}
void Particle::setBestPosition(vector_punteros_a_punto newBestPosition){
	this->bestPosition = newBestPosition;

	/*
	cout << "Particle::setBestPosition() bestPosition[" << this->bestPosition.size() << "] contains:    ";
	for (unsigned int k=0; k < this->bestPosition.size(); k++ )
		cout << " " << this->bestPosition.at(k)->toString();
	cout << endl;
	*/

	return;
}

void Particle::setVelocity(vector_punteros_a_punto newVelocity){
	this->velocity = newVelocity;
	return;
}
void Particle::setBestVelocity(vector_punteros_a_punto newVelocity){
    this->bestVelocity = newVelocity;
    return;
}

void Particle::setFitness(float newFitness){
	this->fitness = newFitness;
}
void Particle::setBestFitness(float newFitness){
	this->bestFitness = newFitness;
	return;
}
/* getters*/
vector_punteros_a_punto Particle::getPosition(){
	return this->position;
}
vector_punteros_a_punto Particle::getBestPosition(){
	return this->bestPosition;
}

vector_punteros_a_punto Particle::getVelocity(){
	return this->velocity;
}
vector_punteros_a_punto Particle::getBestVelocity(){
    return this->bestVelocity;
}

float Particle::getFitness(){
	return this->fitness;
}
float Particle::getBestFitness(){
	return this->bestFitness;
}


