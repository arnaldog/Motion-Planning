#include <stdlib.h>
#include <time.h>

#ifndef CONFIG_H
#define	CONFIG_H

#include "Map.h"

//Joe
//Implementacion obtenida desde: http://caymcorp.wordpress.com/2010/09/28/singletons-en-c-el-problema-de-la-destruccion/
class Config {
	private:
		static Config* pInstance_;
		// Delete the singleton instance
		static void DestroyConfig(){
			if(pInstance_ != NULL) delete pInstance_;
		}
		// Private to ensure single instance
		Config(){
			//set global random seed
			srand ( time(NULL) );
		};
		Config(const Config& s){};

		int iterations;
		float phi_p;
		float phi_g;
		int omega;
		unsigned int quantity;
		string map_file;
		Map* map;

		float alpha; // objective function parameter for penalizing
		int pivots; // number of pivots to partitionning the route


	public:
		virtual ~Config(){};

		static Config& getInstance() {
			if(pInstance_ == NULL)
			{
				pInstance_ = new Config();
				//atexit(&DestroyConfig);	// At exit, destroy the singleton
			}
			return *pInstance_;
		}

		void setIterations(int iterations);
		void setPhiP(float phi_p);
		void setPhiG(float phi_g);
		void setOmega(int omega);
		void setMap(Map* map);
		void setAlpha(float alpha);
		void setPivots(int pivots);
		void setMapFile(string map_file);
		void setParticleQuantity(unsigned int quantity);

		int getIterations();
		int getParticleQuantity();
		float getPhiP();
		float getPhiG();
		float getOmega();
		float getAlpha();
		string getMapFile();
		Map* getMap();

		//imprime configuraciones a la salida estandar
		void printConfiguration();

		int getRandomInt(int max);
		int getWeightedRandomInt(vector<int> distancias);

                int getPivots();
};

#endif	/* CONFIG_H */
