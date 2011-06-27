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
template <class T> float Particle<T>::getBestFitness()  {
    return bestFitness;
}
template <class T> void Particle<T>::setFitness(float fitness) {
    this->fitness = fitness;
}
template <class T> float Particle<T>::getFitness()  {
    return fitness;
}

template <class T> void Particle<T>::setBestVelocity(T const& bestVelocity) {
    this->bestVelocity = bestVelocity;
}
template <class T> T const& Particle<T>::getBestVelocity()  {
    return bestVelocity;
}

template <class T> void Particle<T>::setBestPosition(T const& bestPosition) {
    this->bestPosition = bestPosition;
}

template <class T> T const& Particle<T>::getBestPosition()  {
    return bestPosition;
}
template <class T> void Particle<T>::setVelocity(T const& velocity) {
    this->velocity = velocity;


}
template <class T> T const& Particle<T>::getVelocity()  {
    return velocity;
}
template <class T> void Particle<T>::setPosition(T const& position) {
    this->position = position;
}
template <class T> T const& Particle<T>::getPosition() {
    return this->position;
}

template <class T> Particle<T>::Particle(const Particle& orig) {
}

template <class T> Particle<T>::~Particle() {
}

template <class T> string Particle<T>::toString(){
	this->position.printPath();
    return this->position.toString();
}

template <class T> void Particle<T>::updatePosition(){
    this->position = this->position > this->velocity;
}

#endif	/* PARTICLE_TEMPLATE_H */

