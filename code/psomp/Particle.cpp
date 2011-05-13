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

	//slice(cortar) (cortar en la primera interseccion de si misma)
	//cout << "Particle::createRandomRoute: largo antes de slice(): " << ruta.size() << endl;
	this->slice(&ruta);
	//cout << "Particle::createRandomRoute: largo despues de slice(): " << ruta.size() << endl;

	return ruta;
}

void Particle::slice(vector_punteros_a_punto* ruta){
	//obtener los indices
	unsigned int indice_inicial = 0;
	unsigned int indice_final = 0;

	//referencia a la ruta
	//vector_punteros_a_punto &ref_ruta = *ruta;

	for(unsigned int i = 0; i < ruta->size(); i++){
		/*cout <<
			"i="<<
			i<<
			endl;
		*/

		//setear indice final
		indice_inicial = i;

		//reiniciar valor a buscar
		Point* valor_a_buscar = ruta->at(i);
		/*
		cout <<
			"valor a buscar="<<
			valor_a_buscar->toString()<<
			endl;
		*/

		//buscar desde el final
		for(unsigned int j=ruta->size()-1; j>0; j--){
			/*
			cout <<
				"j="<<
				j<<
				endl;

			cout <<
				"intentando entrar al elemento ruta->at(j) "<<
				endl;

			cout <<
				"ruta->at(j) ="<<
				ruta->at(j) <<
				endl;

			cout <<
				"intentando entrar al elemento ruta->at(j) "<<
				endl;
			*/

			//si no es la misma posicion y es el mismo valor...
			if( (j != i) && (*(ruta->at(j)) == *valor_a_buscar) ){
				indice_final = j;
				break;
			}
		}

		//verificar si ya se tiene el indice final
		if(indice_final != 0){
			break;
		}
	}

	/*
	cout <<
		"finalmente indice_inicial = " <<
		indice_inicial <<
		" indice_final = " <<
		indice_final <<
		endl;
	*/

	//vector final
	vector_punteros_a_punto f;

	//llenar el vector final
	for(unsigned int i = 0; i < ruta->size(); i++){
		//si esta dentro de los indices, no agregar al vector final
		if( (indice_inicial < i) && (i <= indice_final) ){
			continue;
		}
		//cout << i << endl;
		f.push_back(ruta->at(i));
	}

	//impresion debug
	/*
	cout << "f (" << f.size() << ") contains:       ";
	for (unsigned int k=0; k < f.size(); k++ )
		cout << " " << f.at(k)->toString();
	cout << endl;

	cout << "ruta (" << ruta->size() << ") contains:    ";
	for (unsigned int k=0; k < ruta->size(); k++ )
		cout << " " << ruta->at(k)->toString();
	cout << endl;
	*/

	//cout << "Particle::slice(): ruta size = " << ruta->size() << endl;
	//cout << "Particle::slice(): f size = " << f.size() << endl;


	//sobreescribir la ruta con esta nueva generada
	*ruta = f;
}

void Particle::updatePosition(){ // // x_{i+1} = ...
	//se tiene un vector de velocidad...
	//el cual es un vector con las posiciones por las que esta obligada a pasar esta particula
	//si quiere asi imitar a otras particulas mejores

	cout << "Particle::updatePosition()" << endl;

	//por cada punto en la velocidad...
	Config &config = Config::getInstance();
	Map* mapa = config.getMap();

	//agregar el punto de meta al vector de velocidades
	vector_punteros_a_punto path = this->velocity;
	path.push_back(mapa->getGoal());

	//crear vector que unira las subrutas a generar
	vector_punteros_a_punto final;

	//punto de inicio de la subruta (el comienzo del mapa al principio)
	Point* inicio = mapa->getStart();

	//puntero a vector de la subruta generada
	cout << "Particle::updatePosition(): creando ruta random" << endl;
	vector_punteros_a_punto* subruta = 0;

	for(unsigned int i=0; i < path.size(); i++){
		cout << "Particle::updatePosition(): iteracion " << i << "/" << path.size() << endl;

		//hay que crear una ruta random desde el punto de la subruta anterior
		//(o el comienzo del mapa si es la primera)

		//reservar memoria para la subruta
		cout << "Particle::updatePosition(): reservando memoria para la ruta" << endl;
		subruta = new vector_punteros_a_punto();

		//generar subruta
		cout << "Particle::updatePosition(): generando subruta random desde " << inicio->toString() << " hasta " << path[i]->toString() << endl;
		*subruta = this->createRandomRoute(inicio,path[i]);

		//ahora que se tiene una subruta, recorrerla punto a punto y agregarla al vector final
		//se omite el ultimo punto, ya que la siguiente subruta parte por el mismo punto del final que esta
		cout << "Particle::updatePosition(): ahora que se tiene subruta, punto a punto agregar al vector final" << endl;
		for(unsigned int j=0; j < subruta->size()-1; j++){
			vector_punteros_a_punto ruta = *subruta;
			//cout << "Particle::updatePosition(): intentando push_back(ruta[j]) = " << ruta[j]->toString() << endl;
			final.push_back(ruta[j]);
		}

		//actualizar punto de inicio
		cout << "Particle::updatePosition(): actualizando punto de inicio" << endl;
		inicio = path[i];
	}

	//por ultimo hay que hacer agregar el punto de meta ya que fue omitido
	final.push_back(mapa->getGoal());

	//ya que se tiene el vector final, hay que actualizar la posicion nueva
	this->position = final; //TODO: verificar si la posicion es efectivamente actualizada

	return;
}

void Particle::initVelocity(){

	Config &config = Config::getInstance();
    int n = config.getPivots();
    int lenght = this->position.size();

    for(int i=0; i < n; i+=1){
		int index = (int)floor((i+1)*(float)lenght/(float)n);
		index = (index == lenght) ? index-1: index;
		this->velocity.push_back(this->position[index]);
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

		 //  vi ← ω vi + φp rp (pi-xi) + φg rg (g-xi)
		 // cartesian coords v = v(x,y);

		 if(v != NULL && p != NULL && g != NULL){
		     float vx = v->getX();
		     float vy = v->getY();
		     //cout << op*rp*vx << " " << og*rg*vx << endl;
		     vx = om*vx+op*rg*(p->getX()-vx)+og*rg*(g->getX()-vx);
		     vy = om*vy+op*rg*(p->getY()-vy)+og*rp*(g->getY()-vy);

		     vx = (vx < 0) ? 0 : ((vx > width) ? width : vx);
		     vy = (vy < 0) ? 0 : ((vy > height) ? height: vy);

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
		cout << "Particle::printParticle(): this->position[" << i << "]->toString() = " << this->position[i]->toString() <<endl;
	}
}
void Particle::evaluateFitness(){

	Config &config = Config::getInstance();
	Map* map = config.getMap();

	float alpha = config.getAlpha();

	//contar numero de colisiones
	int nc = 0;
	for(unsigned int i=0; i < this->position.size(); i++){
		Point* o = this->position[i];
		nc+=map->getCollision(o);
	}

	float lenght = (float)this->position.size();

	float newFitness = lenght + nc*(1+pow(lenght, alpha));
	this->setFitness(newFitness);

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


