/* 
 * File:   Swarm.h
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 0:25
 */

#ifndef SWARM_H
#define	SWARM_H

using namespace std;
#include <iostream>
#include <vector>

/*
 * Context Includes
 */

#include "Particle.h"
#include "Route.h"

template <class T> class Swarm {
public:
    Swarm();
    Swarm(int size, int iterations, float fitness);
    Swarm(const Swarm& orig);
    virtual ~Swarm();

    /*
     * Iterations Methods
     */

    /*
     * Getters and Setters
     */
    
    void initialize();
    void iterate();
    
    void setBestParticleIndex(int bestParticleIndex);
    int getBestParticleIndex() const;
    void setFitness(float fitness);
    float getFitness() const;
    void setIterations(int iterations);
    int getIterations() const;
    void setPopulation(vector<Particle<T> > population);
    vector<Particle<T> > getPopulation() const;
    void setSize(int size);
    int getSize() const;

    void setFitnessFunction(float (T::*f)(T));
//    void setInitPositionFunction(void (T::*f)(T));
//    void setInitVelocityFunction(void (T::*f)(T));
    
    float evaluateFitness(T particle);
    void evaluateInitPosition(T &position);
    void evaluateInitVelocity(T &velocity);

    void setInitPositionFunction(void (T::*f)(T&));
    void setInitVelocityFunction(void (T::*f)(T&));

    void setParticleSize(int particleSize);
    int getParticleSize() const;


private:

    /* Swarm general attributes */
    int size;
    vector < Particle<T> > population;  // particle template based population
    int particleSize;
    
    /* Swarm optimization attributes */
    int iterations;
    
    float fitness;
    int bestParticleIndex;
    
    float (T::*fitnessFunction) (T);
    void (T::*initPositionFunction) (T&);
    void (T::*initVelocityFunction) (T&);

};


#endif	/* SWARM_H */

