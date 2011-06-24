/*
 * File:   Config.h
 * Author: alejandrasuarez
 *
 * Created on 5 de junio de 2011, 21:23
 */

#ifndef CONFIG_H
#define	CONFIG_H

using namespace std;

#include "Map.h"

class Config {
public:
    virtual ~Config();

    static Config& getInstance() {
        if(pInstance_ == NULL)
            pInstance_ = new Config();
        return *pInstance_;
    }

    void setPivots(int pivots);
    int getPivots() const;
    void setAlpha(float alpha);
    float getAlpha() const;
    void setMap(Map* map);
    Map* getMap() const;
    void setMapFile(string mapFile);
    string getMapFile() const;
    void setQuantity(unsigned int quantity);
    unsigned int getQuantity() const;
    void setOmega(int omega);
    int getOmega() const;
    void setPhi_g(float phi_g);
    float getPhi_g() const;
    void setPhi_p(float phi_p);
    float getPhi_p() const;
    void setIterations(int iterations);
    int getIterations() const;

	//mode
	void setMode(string mode);
	string getMode();

    //hermite inputs
	void setHermiteBase(unsigned int base);
	unsigned int getHermiteBase();


    void printConfiguration();

private:
    static Config* pInstance_;

    static void DestroyConfig(){
        if(pInstance_ != NULL) delete pInstance_;
    }

    Config(){
        //set global random seed
        srand ( time(NULL) );
    };

    Config(const Config& s){};

    string mode;
    unsigned int hermite_base;

    int iterations;
    float phi_p;
    float phi_g;
    int omega;
    unsigned int quantity; // particle quantity
    string mapFile;
    Map* map;

    float alpha; // objective function parameter for penalizing
    int pivots; // number of pivots to set the route
};

#endif	/* CONFIG_H */


