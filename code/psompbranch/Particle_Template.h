/* 
 * File:   Particle_Template.h
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 1:30
 */

#include "Particle.h"
#include "Config.h"

#ifndef PARTICLE_TEMPLATE_H
#define	PARTICLE_TEMPLATE_H

template <class T> Particle<T>::Particle() {
}
template <class T> void Particle<T>::setBestFitness(float bestFitness) {
    this->bestFitness = bestFitness;
}
template <class T> float Particle<T>::getBestFitness() const {
    return bestFitness;
}
template <class T> void Particle<T>::setFitness(float fitness) {
    this->fitness = fitness;
}
template <class T> float Particle<T>::getFitness() const {
    return fitness;
}
template <class T> void Particle<T>::setBestVelocity(T bestVelocity) {
    this->bestVelocity = bestVelocity;
}
template <class T> T Particle<T>::getBestVelocity() const {
    return bestVelocity;
}
template <class T> void Particle<T>::setBestPosition(T bestPosition) {
    this->bestPosition = bestPosition;
}
template <class T> T Particle<T>::getBestPosition() const {
    return bestPosition;
}
template <class T> void Particle<T>::setVelocity(T velocity) {
    this->velocity = velocity;
}
template <class T> T Particle<T>::getVelocity() const {
    return velocity;
}
template <class T> void Particle<T>::setPosition(T position) {
    this->position = position;
}
template <class T> T Particle<T>::getPosition() const {
    return position;
}

template <class T> Particle<T>::Particle(const Particle& orig) {
}

template <class T> Particle<T>::~Particle() {
}

template <class T> void Particle<T>::setFitnessFunction(float (T::*f)(T)){
    this->fitnessFunction = f;
}

/*  Concrete Methods */
template <class T> void Particle<T>::initialize(){
    cout << "Particle::initialize(): inicializando particula" << endl;
    

    // inicializar la particula con una ruta random.
}

template <class T> void Particle<T>::updatePosition(T position){
    //this->position+=this->velocity;
}

template <class T> void Particle<T>::initVelocity(){
    cout << "Particle::initVelocity(): inicializando velocidad de la particula" << endl;
}
template <class T> void Particle<T>::evaluateFitness(){
    cout << "Particle::evaluateFitness(): evaluando el Fitness" << endl;
    //this->fitness = this->*fitnessFunction(this);
    return;
}
template <class T> void Particle<T>::printPosition(){
    cout << "Particle::printPosition(): imprimiendo posicion de la particula" << endl;
}
template <class T> void Particle<T>::printVelocity(){
    cout << "Particle::printVelocity(): imprimiendo velocidad de la particula" << endl;
}


#endif	/* PARTICLE_TEMPLATE_H */

