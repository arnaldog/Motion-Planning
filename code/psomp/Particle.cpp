    /* 
 * File:   Particle.cpp
 * Author: alejandrasuarez
 * 
 * Created on 1 de mayo de 2011, 17:57
 */

#include "Particle.h"

Particle::Particle() {
}

Particle::Particle(const Particle& orig) {
}

Particle::~Particle() {
}

void Particle::Init(Point start, Point goal){

    for (int i = 0; i < this->size; i++){
        // initiallling the particle
        Point p = Point(i,i); // example 
        this->position.push_back(p);
    }

}
