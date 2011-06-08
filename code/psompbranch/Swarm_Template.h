/* 
 * File:   Swarm_Template.h
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 1:10
 */

#ifndef SWARM_TEMPLATE_H
#define	SWARM_TEMPLATE_H

#include "Swarm.h"

/*
 * Templating functions
 */
template <class T> Swarm<T>::Swarm(){
}

template <class T> Swarm<T>::Swarm(int size, int iterations, float fitness){
    
    this->size = size;
    this->iterations = iterations;
    this->fitness = fitness;
    this->population = vector < Particle<T> > (size);
}

template <class T> Swarm<T>::~Swarm(){
    
}
template <class T> void Swarm<T>::setBestParticleIndex(int bestParticleIndex) {
    this->bestParticleIndex = bestParticleIndex;
}
template <class T> int Swarm<T>::getBestParticleIndex() const {
    return bestParticleIndex;
}
template <class T> void Swarm<T>::setFitness(float fitness) {
    this->fitness = fitness;
}
template <class T> float Swarm<T>::getFitness() const {
    return fitness;
}
template <class T> void Swarm<T>::setIterations(int iterations) {
    this->iterations = iterations;
}
template <class T> int Swarm<T>::getIterations() const {
    return iterations;
}
template <class T> void Swarm<T>::setPopulation(vector<Particle<T> > population) {
    this->population = population;
}
template <class T> vector<Particle<T> > Swarm<T>::getPopulation() const {
    return population;
}
template <class T> void Swarm<T>::setSize(int size) {
    this->size = size;
}
template <class T> int Swarm<T>::getSize() const {
    return size;
}

template <class T> Swarm<T>::Swarm(const Swarm& orig){
    
}

template <class T> void Swarm<T>::setFitnessFunction(float (T::*f)(T)){
    this->fitnessFunction = f;
}

template <class T> float Swarm<T>::evaluateFitness(T position){
    return ((position).*(this->fitnessFunction))(position);

}

/* Evaluation functions callers */
template <class T> void Swarm<T>::evaluateInitPosition(T &position){
    return ((position).*(this->initPositionFunction))(position);
}
template <class T> void Swarm<T>::evaluateInitVelocity(T &velocity){
    return ((velocity).*(this->initVelocityFunction))(velocity);
}

template <class T> void Swarm<T>::setParticleSize(int particleSize) {
    this->particleSize = particleSize;
}
template <class T> int Swarm<T>::getParticleSize() const {
    return particleSize;
}

/* setters for initializer functions */
template <class T> void Swarm<T>::setInitPositionFunction(void (T::*f)(T&)){
    this->initPositionFunction = f;
}

template <class T> void Swarm<T>::setInitVelocityFunction(void (T::*f)(T&)){
    this->initVelocityFunction = f;
}



//template <class T> float Swarm<T>::initPositionFunction(void (T::*f)(T)){
//    this->initPositionFunction = f;
//    //return ((position).*(this->fitnessFunction))(particle.getPosition());
//}

/* Concrete Methods */
template <class T> void Swarm<T>::initialize(){

    cout << "Swarm::initialize(): inicializando particulas..." << endl;

    //inicializar cada particula de la poblacion
    for(unsigned int i=0; i < this->population.size(); i++){
        
        cout << "Swarm::initialize(): inicializando la particula: " << i << endl;
        //referencia al objeto de la poblacion
        Particle<T> &p = this->population[i];

        /* Particle Initialization */
        T position = T();
        T velocity = T();
        float fitness;
        
        this->evaluateInitPosition(position);
        this->evaluateInitVelocity(velocity);
    
        p.setPosition(position);
        p.setVelocity(velocity);

        fitness = this->evaluateFitness(p.getPosition());
        p.setFitness(fitness);

        p.setBestPosition(position);
        p.setBestVelocity(velocity);
        p.setBestFitness(fitness);


        //actualizar la mejor solucion conocida
        if(fitness <= this->fitness) {
            //actualizar la mejor solucion de la poblacion
            this->setFitness(fitness);
            this->bestParticleIndex = i;
        }
    }

    //cout << "Swarm::initialize(): la major particula fue la " << this->bestParticleIndex << endl;
    //cout << "Swarm::initialize(): this->bestFitness = " << this->fitness << endl;
    //cout << "Swarm::initialize(): this->population[this->bestParticle].getFitness() = " << this->population[this->bestParticleIndex].getFitness() << endl;
    //cout << "Swarm::initialize(): this->population[this->bestParticle].getBestPosition().size() = " << this->population[this->bestParticle].getBestPosition().size() << endl;

}



template <class T> void Swarm<T>::iterate()
{
    //criterio de parada: numero de iteraciones.
    int iteration = 0;

    while (iteration < this->iterations)
    {
	// debug
	cout << endl;
	cout << "Swarm::iterate(): iteracion " << iteration << endl;
	cout << endl;

	// para cada partícula, hacer:
	for (unsigned int i = 0; i < this -> population.size(); i++) {
	    //cout << "Swarm::iterate(): particula " << i << endl;

	    // referencia a la particula para ser modificada.
	    Particle<T> &p = this -> population[i];

	    //imprimir velocidad antes de ser actualizada (debug opcional)
	    //cout << "Swarm::iterate(): velocidad inicial: " << endl;
	    //p.printVelocity();

	    // actualiza la velocidad de la partícula
	    //cout << "Swarm::iterate(): actualizando velocidad... " << endl;
	   //p.updateVelocity(this -> population[this -> getBestParticle()].getBestVelocity());

	    //imprimir velocidad despues de ser actualizada (debug opcional)
	    //cout << "Swarm::iterate(): velocidad despues de actualizar:" << endl;
	    //p.printVelocity();

	    // update the particle's position: xi ← xi + vi
	    //cout << "Swarm::iterate(): actualizando posicion... " << endl;
	    // p.updatePosition();

	    //redistribuir los pivotes equidistantemente
	    //p.initVelocity();

	    // evaluate the new fitness
	    //p.evaluateFitness();

	    //if (f(xi) < f(pi)) do:
	    if (p.getFitness() < p.getBestFitness()) {
		//inicializacion mejor posicion, velocidad
		//y fitness de la particula
//		p.setBestPosition(p.getPosition());
//		p.setBestVelocity(p.getBestVelocity());
//		p.setFitness(p.getFitness());
	    }

	    //if (f(pi) < f(g)) update the swarm's best known position:
	    //g ← pi
//	    if (p.getFitness() < this ->bestFitness) {
//		this->bestFitness  = p.getFitness();
//		this->bestParticle = i;
//	    }
	}

	//next iteration
	iteration++;

	cout << "Swarm::iterate(): resumen de la iteracion " << iteration << endl;
	cout << endl;

	for(unsigned j=0; j<this->population.size(); j++){
	    cout << "Swarm::iterate(): this->population[" << j << "].getFitness() : " << this->population[j].getFitness() << endl;
	}

//	cout << "Swarm::iterate(): mejor particula: " << this->bestParticle << endl;
//	cout << "Swarm::iterate(): mejor fitness  : " << this->bestFitness << endl;
//	cout << "Swarm::iterate(): this->population[this->bestParticle].getBestPosition().size() = " << this->population[this->bestParticle].getBestPosition().size() << endl;
    }
}




#endif	/* SWARM_TEMPLATE_H */

