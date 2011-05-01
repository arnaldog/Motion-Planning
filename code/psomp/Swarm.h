/* 
 * File:   Swarm.h
 * Author: alejandrasuarez
 *
 * Created on 1 de mayo de 2011, 17:37
 */

using namespace std;
#include "vector";
#include "Particle.h";
#include "Point.h"

#ifndef SWARM_H
#define	SWARM_H

class Swarm {
    
public:
    Swarm();
    Swarm(const Swarm& orig);
    virtual ~Swarm();

    /*
     * Metodos a implementar:
     * - Inicializacion de cada particula considerando una distribucion uniforme
     * -
     * -
     */
private:
    
    vector <Particle> population; // particle population
    Particle bestPositioned; // best positioned particle
    Point start;
    Point goal;


};

#endif	/* SWARM_H */

