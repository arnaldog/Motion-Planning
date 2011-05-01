/* 
 * File:   Particle.h
 * Author: alejandrasuarez
 *
 * Created on 1 de mayo de 2011, 17:57
 */

using namespace std;
#include "vector"
#include "Point.h";


#ifndef PARTICLE_H
#define	PARTICLE_H


class Particle {
public:
    Particle();
    Particle(const Particle& orig);
    virtual ~Particle();

    /* Metodos para particulas a considerar
     *  - Inicialización de la particula aleatoreamente
     *  - Actualizacion de posicion considerando velocidad
     *  - Actualizacion de velocidad
     *  - Evaluacion de funcion objetivo
     *  - Actualizacion para mejor posicion
     *  - Restricciones de la particula
     */

    void Init(Point start, Point goal);
private:

    /* Atributos para la clase particula
     * - posicion
     * - mejor posicion
     * - velocidad actual
     * - funcion objetivo
     */
    vector <Point> position;
    vector <Point> bestPosition;
    vector <Point> velocity;
    int objectiveFunctionValue;
    int size;


};

#endif	/* PARTICLE_H */

