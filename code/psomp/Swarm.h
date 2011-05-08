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
		void initialize();
                void iteration();
		void init();

                /*
                 * Getters and setters for attributes
                 */

                void setPopulation(vector <Particle> population);
                void setBestParticle(int bestParticle);
                void setBestFitness(int newBestFitness);
                void setIterations(int newIteration);

                vector <Particle> getPopulation();
                int getBestParticle();
                int getBestFitness();
                int getIterations();
                
	private:
		vector <Particle> population;	//particle population
		int bestParticle;		//best positioned particle
		int bestFitness;		//fitness de la mejor particula
                int iterations;
};

#endif	/* SWARM_H */