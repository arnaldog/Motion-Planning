using namespace std;

#include "vector"
#include "Particle.h"

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
		void initialize(int cantidad_particulas);
		void init();
                void setBestFitness(int newBestFitness);
                
	private:
		vector <Particle> population;	//particle population
		int bestParticle;		//best positioned particle
		int bestFitness;		//fitness de la mejor particula
};

#endif	/* SWARM_H */