using namespace std;

#include <vector>

#include "Point.h"
#include "Config.h"

#ifndef PARTICLE_H
#define	PARTICLE_H

typedef vector<Point*> vector_punteros_a_punto;

class Particle {
	public:
		Particle();
		Particle(const Particle& orig);
		Particle(vector <Point*> position);

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
		void updateVelocity(vector_punteros_a_punto bestGlobalKnownPosition); /* Actualiza velocidad */
		void evaluateFitness(); /* Evalua funcion objetivo */
		void particleConstraints(); /* Chequea restricciones de particulas */

		// Getters and setters ...

		void setPosition(vector_punteros_a_punto newPosition);
		void setBestPosition(vector_punteros_a_punto newBestPosition);
		void setVelocity(vector_punteros_a_punto newVelocity);
		void setPositionFitness(int newFitness);
		void setBestPositionFitness(int newFitness);
		void setSize(int newSize);

		vector_punteros_a_punto getPosition();
		vector_punteros_a_punto getBestPosition();
		vector_punteros_a_punto getVelocity();
		int getPositionFitness();
		int getBestPositionFitness();
		int getSize();

	private:
		vector_punteros_a_punto position; /* vector de posiciones que definen la ruta */
		vector_punteros_a_punto bestPosition; /* vector que guarda la mejor posicion */
		vector_punteros_a_punto velocity; /* vector de velocidades */
		int positionFitness; /* valor de la funcion objetivo actual */
		int bestPositionFitness; /* el valor de la f.o. de la mejor posicion */
		int size; /* tamano de la ruta */
};

#endif	/* PARTICLE_H */

