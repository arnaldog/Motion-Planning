#include <iostream>

#include "Particle.h"

Particle::Particle(){
}

Particle::Particle(const Particle& orig) {
}

Particle::~Particle() {
}

void Particle::createRandomRoute(Point start, Point goal){

    for (int i = 0; i < this->size; i++){
        // initiallling the particle
        Point p = Point(i,i); // example 
        this->position.push_back(p);
    }

}

void Particle::hablar(){
	cout << this->actual_fitness << endl;
}

int Particle::fitness(){
	return 8;
}