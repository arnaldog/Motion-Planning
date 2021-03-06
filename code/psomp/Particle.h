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

		//crea una ruta random entre el punto de inicio y la meta, segun indique el mapa
		void initialize();

		void updatePosition(); /* Actualiza posicion */
		void initVelocity();

		void updateVelocity(vector_punteros_a_punto bestGlobalVelocity);
		void evaluateFitness();

		void printPosition();
		void printVelocity();

		// Getters and setters ...
		/* setters */
		void setPosition(vector_punteros_a_punto newPosition);
		void setBestPosition(vector_punteros_a_punto newBestPosition);

		void setVelocity(vector_punteros_a_punto newVelocity);
		void setBestVelocity(vector_punteros_a_punto newVelocity);

		void setFitness(float newFitness);
		void setBestFitness(float newFitness);

		/* getters */
		vector_punteros_a_punto getPosition();
		vector_punteros_a_punto getBestPosition();

		vector_punteros_a_punto getVelocity();
                vector_punteros_a_punto getBestVelocity();

		float getFitness();
		float getBestFitness();

	private:
		vector_punteros_a_punto position; /* vector de posiciones que definen la ruta */
		vector_punteros_a_punto bestPosition; /* vector que guarda la mejor posicion */
		vector_punteros_a_punto velocity; /* vector de velocidades */
		vector_punteros_a_punto bestVelocity;

		float fitness; /* valor de la funcion objetivo actual */
		float bestFitness; /* el valor de la f.o. de la mejor posicion */

		//funciones de creacion de ruta
		vector_punteros_a_punto createRoute(Point* origin, Point* target);
		vector_punteros_a_punto createSubRoute(Point* origin, Point* target);

		vector_punteros_a_punto createRandomRoute(Point* origin, Point* target);

		vector_punteros_a_punto createLinearRoute(Point* origin, Point* target);
		vector_punteros_a_punto createLinearSubRoute(Point* origin, Point* target);

		//hace in corte en la primera interseccion de si misma,
		//para acortar la ruta y obtener un resultado mejor
		void slice(vector_punteros_a_punto* ruta_ineficiente);
};

#endif	/* PARTICLE_H */
