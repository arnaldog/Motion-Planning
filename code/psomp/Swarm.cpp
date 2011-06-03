using namespace std;

#include "Swarm.h"
#include "Particle.h"
#include "Util.h"
#include <iostream>

#define MAX_VALUE 9999

Swarm::Swarm()
{
}

Swarm::Swarm(const Swarm & orig)
{
}

Swarm::~Swarm()
{
}

void Swarm::initialize(){

	cout << "Swarm::initialize(): inicializando particulas..." << endl;

	//inicializar cada particula de la poblacion
	for(unsigned int i=0; i < this->population.size(); i++){

		//referencia al objeto de la poblacion
		Particle &p = this->population[i];

		// inicializar la velocidad
		//TODO: analizar si conviene primero setear la velocidad
		p.initVelocity();

		//imprimir velocidad inicial (debug)
		p.printVelocity();

		//inicializacion de la posicion
		p.initialize();

		//imprimir posicion inicial (debug)
		//p.printPosition();

		//evaluar función objetivo de la particula ya inicializada
		p.evaluateFitness();

		//inicializacion mejor posicion, velocidad y fitness de la particula
		p.setBestPosition(p.getPosition());
		p.setBestVelocity(p.getVelocity());
		p.setBestFitness(p.getFitness());


		//actualizar la mejor solucion conocida
		if(p.getFitness() <= this->bestFitness) {
			//actualizar la mejor solucion de la poblacion
			this->setBestFitness(p.getFitness());
			this->bestParticle = i;
		}
	}

	cout << "Swarm::initialize(): la mejor particula fue la " << this->bestParticle << endl;
	cout << "Swarm::initialize(): this->bestFitness = " << this->bestFitness << endl;
	cout << "Swarm::initialize(): this->population[this->bestParticle].getFitness() = " << this->population[this->bestParticle].getFitness() << endl;
	cout << "Swarm::initialize(): this->population[this->bestParticle].getBestPosition().size() = " << this->population[this->bestParticle].getBestPosition().size() << endl;

}

void Swarm::iterate()
{
    //criterio de parada: numero de iteraciones.
    int iteration = 0;

    while (iteration < this->iterations)
    {
		// debug
		//cout << endl;
		cout << "Swarm::iterate(): COMENZANDO ITERACION PSO " << endl;
		cout << "Swarm::iterate(): iteracion " << iteration << endl;
		cout << endl;

		// para cada partícula, hacer:
		for (unsigned int i = 0; i < this -> population.size(); i++)
		{
			//cout << "Swarm::iterate(): particula " << i << endl;

			// referencia a la particula para ser modificada.
			Particle &p = this -> population[i];

			//imprimir velocidad antes de ser actualizada (debug opcional)
			cout << "Swarm::iterate(): velocidad inicial: " << endl;
			p.printVelocity();

			// actualiza la velocidad de la partícula
			//cout << "Swarm::iterate(): actualizando velocidad... " << endl;
			p.updateVelocity(this->population[this -> getBestParticle()].getBestVelocity());

			//imprimir velocidad despues de ser actualizada (debug opcional)
			cout << "Swarm::iterate(): velocidad despues de actualizar:" << endl;
			p.printVelocity();

			// update the particle's position: xi ← xi + vi
			//cout << "Swarm::iterate(): actualizando posicion... " << endl;
			p.updatePosition();

			//imprimir posicion despues de ser actualizada
			//p.printPosition();

			//redistribuir los pivotes equidistantemente
			//DEPRECATED (?): ya no porque ahora los pivotes son los puntos de apoyo
			//solo servia en el random, pero sigue sirviendo?
			//p.initVelocity();

			// evaluate the new fitness
			p.evaluateFitness();

			//if (f(xi) < f(pi)) do:
			if (p.getFitness() < p.getBestFitness()) {
				//inicializacion mejor posicion, velocidad
				//y fitness de la particula
				p.setBestPosition(p.getPosition());
				p.setBestVelocity(p.getBestVelocity());
				p.setBestFitness(p.getFitness());
			}

			//if (f(pi) < f(g)) update the swarm's best known position:
			//g ← pi
			if (p.getFitness() < this ->bestFitness) {
				this->bestFitness  = p.getFitness();
				this->bestParticle = i;
			}
		}

		cout << endl;
		cout << "Swarm::iterate(): resumen de la iteracion " << iteration << endl;

		for(unsigned j=0; j<this->population.size(); j++){
			cout << "Swarm::iterate(): this->population[" << j << "].getFitness() : " << this->population[j].getFitness() << endl;
		}

		cout << "Swarm::iterate(): mejor particula: " << this->bestParticle << endl;
		cout << "Swarm::iterate(): mejor fitness  : " << this->bestFitness << endl;
		cout << "Swarm::iterate(): this->population[this->bestParticle].getBestPosition().size() = " << this->population[this->bestParticle].getBestPosition().size() << endl;

		//next iteration
		iteration++;
	}
}

// GETTERS AND SETTERS
void Swarm::setPopulation(vector<Particle> newPopulation)
{
    this -> population = newPopulation;

    return;
}

void Swarm::setBestParticle(int newParticle)
{
    this -> bestParticle = newParticle;

    return;
}

void Swarm::setBestFitness(float newBestFitness)
{
    this -> bestFitness = newBestFitness;

    return;
}

void Swarm::setIterations(int newIterations)
{
    this -> iterations = newIterations;

    return;
}

vector<Particle> Swarm::getPopulation()
{
    return this -> population;
}

int Swarm::getBestParticle()
{
    return this -> bestParticle;
}

float Swarm::getBestFitness()
{
    return this -> bestFitness;
}

int Swarm::getIterations()
{
    return this -> iterations;
}

void Swarm::printBestPosition(){
	Particle best_particle = this -> population[this -> getBestParticle()];

	//esto está mal ya que imprime la posicion final, no la mejor
	best_particle.printPosition();
}

void Swarm::printBestParticleAsMatrix(){

	//usaremos la singleton de Config que contiene el mapa
	Config &config = Config::getInstance();

	//generar un mapa vacio
	vector< vector<int> > render;

	//llenar de ceros
	for(unsigned int i = 0; i < config.getMap()->getWidth(); i++){
		render.push_back( vector<int>() );

		for (unsigned int j = 0; j < config.getMap()->getHeight(); j++ )
			render[i].push_back(0);
	}

	//obtener la mejor posicion (ruta) de la mejor particula de la poblacion (swarm)
	vector_punteros_a_punto mejor_ruta = this->population[this->getBestParticle()].getBestPosition();

	//ahora que se tiene el mapa vacio y la mejor ruta, hay que punto
	//a punto de la mejor ruta, ir escribiendo sobre el mapa vacio
	cout << "Swarm::printBestParticleAsMatrix(): entrando a rayar el mapa" << endl;
	cout << "Swarm::printBestParticleAsMatrix(): mejor_ruta.size() = " << mejor_ruta.size() << endl;
	for(unsigned int i=0; i<mejor_ruta.size(); i++){
		//escribir un uno en el mapa vacio
		int x = mejor_ruta.at(i)->getX();
		int y = mejor_ruta.at(i)->getY();
		render[x][y] = 1;

		//cout << "Swarm::printBestParticleAsMatrix(): render[" << x << "][" << y << "] = " << render[x][y] << endl;
	}

	//ahora que se tiene el mapa con la ruta dibujada, hay que imprimirlo
	for(unsigned int i=0; i<render.size(); i++){
		for(unsigned int j=0; j<render[i].size(); j++){
			cout << render.at(i).at(j);
		}
		cout << endl;
	}
}
