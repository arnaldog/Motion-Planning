#include <stdlib.h>
#include <time.h>

#ifndef CONFIG_H
#define	CONFIG_H

#include "Map.h"


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
        Map *map;
public:
        virtual ~Config(){};

        static Config& getInstance() {
                if(pInstance_ == NULL)
                    pInstance_ = new Config();
                        //atexit(&DestroyConfig);	// At exit, destroy the singleton
                return *pInstance_;
        }

        void setIterations(int iterations);
        void setPhiP(float phi_p);
        void setPhiG(float phi_g);
        void setOmega(int omega);
        void setMap(Map* map);

        int getIterations();
        float getPhiP();
        float getPhiG();
        float getOmega();
        Map* getMap();

        int getRandomInt(int max);
};

#endif	/* CONFIG_H */
