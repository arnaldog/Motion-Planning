#include <iostream>
#include "Particle.h"

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


   // for (unsigned int i = 0; i < this->position.size(); i++){
    for (unsigned int i = 0; i < 20 ; i++){
        Point p = Point(i,i);
        this->position.push_back(p);
    }

     this->evaluateFitness(); // evaluating fitness 

}

void Particle::updatePosition(){ // // x_{i+1} = ...
    return;
}

void Particle::updateVelocity(){  // v_{i+1} = ...
    return;
}

void Particle::evaluateFitness(){
    // f.o = ...
    int newFitness=0;

    for(unsigned int i=0; i < this->position.size(); i++){
        newFitness+=1; // replace this by a evaluation function
    }

    this->setFitness(newFitness);
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

void Particle::setFitness(int newFitness){
    this->fitness = newFitness;
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

int Particle::getFitness(){
    return this->fitness;
}

int Particle::getSize(){
    return this->size;
}