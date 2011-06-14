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

	this->position = this->createRoute(mapa->getStart(), mapa->getGoal());

	/*cout << "Particle::initialize(): ";
	for (unsigned int k=0; k < this->position.size(); k++ )
		cout << " " << this->position.at(k)->toString();
	cout << endl;
	*/
}

//crear ruta COMPLETA desde el origen al destino, usando pivotes
//TODO: implementar con pnuteros a funcion
vector_punteros_a_punto Particle::createRoute(Point* origin, Point* target){
	Config &config = Config::getInstance();

	if(config.getMode() == "linear"){
		return this->createLinearRoute(origin, target);
	}

	//si no hay ningun modo especial, se asume random
	return this->createRandomRoute(origin, target);
}

//crear ruta PARCIAL entre un punto a otro, sin pivotes
vector_punteros_a_punto Particle::createSubRoute(Point* origin, Point* target){
	Config &config = Config::getInstance();

	if(config.getMode() == "linear"){
		return this->createLinearSubRoute(origin, target);
	}

	//si no hay ningun modo especial, se asume random
	return this->createRandomRoute(origin, target);
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

vector_punteros_a_punto Particle::createLinearRoute(Point* origin, Point* target){
	cout << "Particle::createLinearRoute(): creando ruta linear completa" << endl;
	this->updatePosition();
	//this->printPosition();
	return this->position;
}

vector_punteros_a_punto Particle::createLinearSubRoute(Point* origin, Point* target){
	//cout << "Particle::createLinearSubRoute(): creando subruta: " << origin->toString() << " --> " << target->toString() << endl;

	vector_punteros_a_punto path;

	//puntos
	Point* p1 = origin;
	Point* p2 = target;

	//agregar inicio al path
	path.push_back(p1);

	//crear linea

	//calcular m
	// m = abs(y2-y1) / abs(x2-x1)
	int dx = (p2->getX() - p1->getX());
	int dy = (p2->getY() - p1->getY());

	//dx = (dx == 0) ? 1 : dx;
	//dy = (dy == 0) ? 1 : dy;

	//cout << "Particle::createLinearRoute(): dx = " << dx << endl;
	//cout << "Particle::createLinearRoute(): dy = " << dy << endl;

	//determinar el signo de la diferencia de los indices, para la iteracion
	int signo_dx = (dx == 0) ? 0 : ((dx > 0) ? 1 : -1);
	//cout << "Particle::createLinearRoute(): signo_dx: " << signo_dx << endl;

	//verificar si se trata de una linea vertical (dx=0 => m=0)
	if (dx == 0){
		//cout << "Particle::createLinearRoute(): dx = " << dx << " por lo tanto es una linea vertical" << endl;

		//determinar signo de dy
		int signo_dy = (dy == 0) ? 0 : ((dy > 0) ? 1 : -1);
		for(int i=0; (signo_dy*i)<(signo_dy*dy); i+=signo_dy){

			//evitar el punto de inicio y fin
			if( (p1->getY()+i == p1->getY()) || (p1->getY()+i == p2->getY()) ){
				continue;
			}

			Point* p = new Point(p1->getX(),p1->getY()+i);
			//cout << "Particle::createLinearRoute(): agregar punto: " << p->toString() << endl;
			path.push_back(p);
		}

		//agregar final al path
		path.push_back(p2);

		return path;
	}

	//si no es una linea vertical, calcular pendiente

	float m = float(float(dy)/float(dx));
	//cout << "Particle::createLinearRoute(): m = " << m << endl;

	//calcular coeficiente de posicion
	// n = y - mt   <==> n = y -mx (cualquier punto)
	float n = float( p1->getY() - float( m * p1->getX() ) );
	//cout << "Particle::createLinearRoute(): n = " << n << endl;
	//cout << endl;

	//forma de grillo (desde ahora, metodo de herrera :P)
	//otra forma: http://www.cplusplus.com/forum/general/8709/

	//obtener punto de mas arriba
	//deprecated: no sirve ya que altera el orden
	/*
	Point* psup;
	if(p1->getX() <= p2->getX()){
		psup = p1;
		//cout << "Particle::createLinearRoute(): psup = p1 = " << p1->toString() << endl;
	} else {
		psup = p2;
		//cout << "Particle::createLinearRoute(): psup = p2 = " << p2->toString() << endl;
	}
	*/

	//1) ir por cada elemento vertical rayando
	for(int i=0;(signo_dx*i)<(signo_dx*dx);i+=signo_dx){
		//limites inferior y superior
		float linf = (p1->getX() + i);
		float lsup = (p1->getX() + i) + signo_dx;

		//ver que indices deben ser marcados por los limites en el mapa
		float finf = (m * linf + n);
		float fsup = (m * lsup + n);

		int iinf = finf;
		int isup = fsup;

		//cout << "Particle::createLinearRoute(): i: " << i << ", linf: " << linf << ", lsup: " << lsup << ", iinf: " << iinf << ", isup: " << isup << endl;

		//determinar el signo de la diferencia de los indices, para la iteracion
		int signo_indices = ((isup - iinf) > 0) ? 1 : -1;
		//cout << "Particle::createLinearRoute(): signo_indices: " << signo_indices << endl;

		//ahora que se tienen los indices, marcarlos
		//cout << "Particle::createLinearRoute(): (signo_dx*iinf): " << (signo_dx*iinf) << endl;
		//cout << "Particle::createLinearRoute(): (signo_dx*isup): " << (signo_dx*isup) << endl;
		for(int j=iinf; (signo_indices*j)<=(signo_indices*isup); j+=signo_indices){
			//cout << "Particle::createLinearRoute(): j: " << j << endl;

			//cout << "Particle::createLinearRoute(): p1->getX()+i: " << p1->getX()+i << endl;
			//cout << "Particle::createLinearRoute(): p1->getX(): " << p1->getX() << endl;

			//cout << "Particle::createLinearRoute(): j: " << j << endl;
			//cout << "Particle::createLinearRoute(): p1->getY(): " << p1->getY() << endl;

			//debug
			/*
			if(j<0){
				cout << "Particle::createLinearRoute(): ERROR j = " << j << endl;
			}
			*/

			//evitar el punto de inicio
			if( (p1->getX()+i == p1->getX()) && (j == p1->getY()) ){
				continue;
			}
			//evitar el punto de fin
			if( (p1->getX()+i == p2->getX()) && (j == p2->getY()) ){
				continue;
			}

			//marcar
			//map->getMap()[psup->getX() + i][j] = 1;

			//agregar al path
			Point* p = new Point(p1->getX() + i,j);
			//cout << "Particle::createLinearRoute(): agregar punto: " << p->toString() << endl;
			path.push_back(p);
		}
	}

	//agregar final al path
	path.push_back(p2);

	//this->slice(&path);
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
	//cout << "Particle::updatePosition()" << endl;

	Config &config = Config::getInstance();
	Map* mapa = config.getMap();

	vector_punteros_a_punto pivots = this->velocity;
	pivots.push_back(mapa->getGoal());

	vector_punteros_a_punto final;
	Point* inicio = mapa->getStart();

	//cout << "Particle::updatePosition(): creando ruta random" << endl;

	vector_punteros_a_punto* subruta = 0;

	for(unsigned int i=0; i < pivots.size(); i++){
		//cout << "Particle::updatePosition(): iteracion " << i+1 << "/" << pivots.size() << endl;

		//cout << "Particle::updatePosition(): reservando memoria para la ruta" << endl;

		subruta = new vector_punteros_a_punto();

		//cout << "Particle::updatePosition(): generando subruta desde " << inicio->toString() << " hasta " << pivots[i]->toString() << endl;

		*subruta = this->createSubRoute(inicio,pivots[i]);

		//cout << "Particle::updatePosition(): ahora que se tiene subruta, punto a punto agregar al vector final"	<< endl;

		for(unsigned int j=0; j < subruta->size()-1; j++){
			vector_punteros_a_punto ruta = *subruta;
			final.push_back(ruta[j]);
		}

		//cout << "Particle::updatePosition(): actualizando punto de inicio" << endl;

		inicio = pivots[i];
	}

	final.push_back(mapa->getGoal());

	this->position = final;

	//slice: recortar intersecciones generadas por el desplazamiento
	this->slice(&this->position);

	return;
}

void Particle::initVelocity(){
	Config &config = Config::getInstance();
	int n = config.getPivots();
	int lenght = this->position.size();
	this->velocity.clear();

	if(config.getMode() == "random"){
		for(int i=0; i < n; i+=1){
			int index = (int)floor((i+1)*(float)(lenght-1)/(float)(n+1));
			this->velocity.push_back(this->position[(index==lenght)?index-1:index]);
		}
	}

	if(config.getMode() == "linear"){
		//hay que crear n puntos aleatorios en el mapa
		cout << "Particle::initVelocity(): inicializando velicidad en modo linear" << endl;
		for(int i=0;i<n;i++){
			Point* p = new Point();
			p->randomize();
			this->velocity.push_back(p);
		}
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

	cout << "Particle::updateVelocity(): rp = " << rp << endl;
	cout << "Particle::updateVelocity(): rg = " << rg << endl;

	int om = config.getOmega();
	int op = config.getPhiP();
	int og = config.getPhiG();

	cout << "Particle::updateVelocity(): om = " << om << endl;
	cout << "Particle::updateVelocity(): op = " << op << endl;
	cout << "Particle::updateVelocity(): og = " << og << endl;

	//update the particle's velocity:
	for(unsigned int i=0; i < this->velocity.size(); i++){
		Point *v = this->velocity[i]; // get velocity
		Point *p = this->bestVelocity[i]; // get best local position
		Point *g = bestGlobalVelocity[i]; // get best global position

		Point *r = new Point(); //random point
		r->randomize();

		cout << "Particle::updateVelocity(): v = " << v->toString() << endl;
		cout << "Particle::updateVelocity(): p = " << p->toString() << endl;
		cout << "Particle::updateVelocity(): g = " << g->toString() << endl;
		cout << "Particle::updateVelocity(): r = " << r->toString() << endl;

		if(v != NULL && p != NULL && g != NULL){
			float vx = v->getX();
			float vy = v->getY();

			//antes
			//vx = om*vx+op*rp*(p->getX()-vx)+og*rg*(g->getX()-vx);
			//vy = om*vy+op*rp*(p->getY()-vy)+og*rg*(g->getY()-vy);

			//omega debiera ser la tendencia a moverse libremente
			vx = om*(r->getX()-vx)+op*rp*(p->getX()-vx)+og*rg*(g->getX()-vx);
			vy = om*(r->getY()-vy)+op*rp*(p->getY()-vy)+og*rg*(g->getY()-vy);

			//comprobar si se salio de los limites
			if(vx<0){
				cout << "Particle::updateVelocity(): SALIO DE LIMITES vx < 0" << endl;
			}
			if(vx>width){
				cout << "Particle::updateVelocity(): SALIO DE LIMITES vx > width" << endl;
			}
			if(vy<0){
				cout << "Particle::updateVelocity(): SALIO DE LIMITES vy < 0" << endl;
			}
			if(vy>width){
				cout << "Particle::updateVelocity(): SALIO DE LIMITES vy > width" << endl;
			}

			vx = (vx < 0) ? 0 : ( (vx > width) ? width : vx);
			vy = (vy < 0) ? 0 : ( (vy > height) ? height : vy);

			cout << "Particle::updateVelocity(): vx = " << vx << endl;
			cout << "Particle::updateVelocity(): vy = " << vy << endl;

			v->setX((int)vx);
			v->setY((int)vy); // updating the velocity
			this->velocity[i] = v;
		} else {
			//informar error
			cout << "Particle::updateVelocity(): ERROR: (v != NULL && p != NULL && g != NULL) = FALSE" << endl;
		}
	}
	return;
}

void Particle::printPosition(){
	cout << "Particle::printPosition()" << endl;
	for(unsigned int i=0; i<this->position.size(); i++){
		cout << "Particle::printPosition(): this->position[" << i << "]->toString() = " << this->position[i]->toString() << endl;
	}
}

void Particle::printVelocity(){
	cout << "Particle::printVelocity(): this->velocity.size() = " << this->velocity.size() << endl;
	for(unsigned int i=0; i<this->velocity.size(); i++){
		cout << "Particle::printVelocity(): this->velocity[" << i << "]->toString() = " << this->velocity[i]->toString() << endl;
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
	//cout << "Particle::evaluateFitness(): numero colisiones nc = " << nc << endl;

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


