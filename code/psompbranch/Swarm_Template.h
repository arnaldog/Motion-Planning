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

template <class T> void Swarm<T>::evaluateInitParticle(T &position){
    return ((position).*(this->initParticleFunction))(position);
}

template <class T> void Swarm<T>::setParticleSize(int particleSize) {
    this->particleSize = particleSize;
}
template <class T> int Swarm<T>::getParticleSize() const {
    return particleSize;
}


template <class T> void Swarm<T>::setInitParticleFunction(void (T::*f)(T&)){
    this->initParticleFunction = f;
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
        
        this->evaluateInitParticle(position);
        this->evaluateInitParticle(velocity);
    
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



#endif	/* SWARM_TEMPLATE_H */

