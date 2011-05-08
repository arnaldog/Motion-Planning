#include "Config.h"

//Config* Config::pinstance = NULL;

/*
Config* Config::Instance() {
	if (!pinstance)
		pinstance = new Config;

	return pinstance;
}
*/

Config* Config::pInstance_ = NULL;

float Config::getPhiP(){
	return this->phi_p;
}
float Config::getPhiG(){
	return this->phi_g;
}
float Config::getOmega(){
	return this->omega;
}
Map* Config::getMap(){
	return this->map;
}

int Config::getIterations(){
	return this->iterations;
}


void Config::setPhiP(float phi_p){
	this->phi_p = phi_p;
	return;
}
void Config::setPhiG(float phi_g){
	this->phi_g = phi_g;
	return;
}
void Config::setOmega(int omega){
	this->omega=omega;
	return;
}
void Config::setMap(Map* map){
	this->map=map;
	return;
}