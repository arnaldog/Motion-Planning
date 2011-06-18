/* 
 * File:   Particle.h
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 1:30
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

#include "Route.h"

template <class T> class Particle {
    
public:
    /* Constructors and others*/
    Particle();
    Particle(const Particle& orig);
    virtual ~Particle();

    /* Concrete Methods */
    void initialize();
    void initVelocity();
    
    void updatePosition();
    void updateVelocity(T velocity);

    /* Function by parameter */
    void evaluateFitness();
    
    void printPosition();
    void printVelocity();

    /*  Getters and Setters */
    void setBestFitness(float bestFitness);
    float getBestFitness() ;
    void setFitness(float fitness);
    float getFitness() ;

    void setBestVelocity(T const& bestVelocity);
    T const& getBestVelocity() ;

    void setBestPosition(T const& bestPosition);
    T const& getBestPosition() ;

    void setVelocity(T const& velocity);
    T const& getVelocity() ;
    
    void setPosition(T const& position);
    T const& getPosition();

    void setFitnessFunction(float (T::*fitnessFunction)(T));
    
private:
    T position;
    T velocity;
    T bestPosition;
    T bestVelocity;
    float fitness;
    float bestFitness;

    // function that evaluate the fitness
    float (T::*fitnessFunction) (T);
};

#endif	/* PARTICLE_H */

