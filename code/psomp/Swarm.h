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

		void initialize();
		void iterate();

		void setPopulation(vector<Particle> population);
		void setBestParticle(int bestParticle);
		void setBestFitness(float newBestFitness);

		void setIterations(int newIteration);
		vector<Particle> getPopulation();
		int getBestParticle();
		float getBestFitness();

		int getIterations();

		void printBestPosition();

	private:
		vector<Particle> population;	//particle population
		int bestParticle;		//best positioned particle

		float bestFitness;		//fitness de la mejor particula
		float iterations;
};

#endif	/* SWARM_H */
