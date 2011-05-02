/* 
 * File:   Particle.h
 * Author: joecabezas
 *
 * Created on 1 de mayo de 2011, 17:57
 */

using namespace std;
#include "vector"
#include "Point.h"


#ifndef PARTICLE_H
#define	PARTICLE_H

class Particle {
public:
	Particle();
	Particle(const Particle& orig);
        Particle(vector <Point> position);

	virtual ~Particle();

	/* Metodos para particulas a considerar
	 *  - Inicialización de la particula aleatoreamente
	 *  - Actualizacion de posicion considerando velocidad
	 *  - Actualizacion de velocidad
	 *  - Evaluacion de funcion objetivo
	 *  - Actualizacion para mejor posicion
	 *  - Restricciones de la particula
	 */

	void createRandomRoute(); /* ruta inicial */
        void updatePosition(); /* Actualiza posicion */
        void updateVelocity(); /* Actualiza velocidad */
        void evaluateFitness(); /* Evalua funcion objetivo */
        void particleConstraints(); /* Chequea restricciones de particulas */

        // Getters and setters ...

        void setPosition(vector <Point> newPosition);
        void setBestPosition(vector <Point> newBestPosition);
        void setVelocity(vector <Point> newVelocity);
        void setFitness(int newFitness);
        void setSize(int newSize);

        vector <Point> getPosition();
        vector <Point> getBestPosition();
        vector <Point> getVelocity();
        int getFitness();
        int getSize();

private:

	vector <Point> position; /* vector de posiciones */
	vector <Point> bestPosition; /* vector que guarda la mejor posicion */
	vector <Point> velocity; /* vector de velocidades */
	int fitness; /* valor de la funcion objetivo actual */
	int size; /* tamano de la ruta */
};

#endif	/* PARTICLE_H */

