/*
 * File:   Config.cpp
 * Author: alejandrasuarez
 *
 * Created on 5 de junio de 2011, 21:23
 */

#include "Config.h"

Config* Config::pInstance_ = NULL;


Config::~Config() {
}
void Config::setPivots(int pivots) {
    this->pivots = pivots;
}
int Config::getPivots() const {
    return pivots;
}
void Config::setAlpha(float alpha) {
    this->alpha = alpha;
}
float Config::getAlpha() const {
    return alpha;
}
void Config::setMap(Map* map) {
    this->map = map;
}
Map* Config::getMap() const {
    return map;
}
void Config::setMapFile(string mapFile) {
    this->mapFile = mapFile;
}
string Config::getMapFile() const {
    return mapFile;
}
void Config::setQuantity(unsigned int quantity) {
    this->quantity = quantity;
}
unsigned int Config::getQuantity() const {
    return quantity;
}
void Config::setOmega(int omega) {
    this->omega = omega;
}
int Config::getOmega() const {
    return omega;
}
void Config::setPhi_g(float phi_g) {
    this->phi_g = phi_g;
}
float Config::getPhi_g() const {
    return phi_g;
}
void Config::setPhi_p(float phi_p) {
    this->phi_p = phi_p;
}
float Config::getPhi_p() const {
    return phi_p;
}
void Config::setIterations(int iterations) {
    this->iterations = iterations;
}
int Config::getIterations() const {
    return iterations;
}

void Config::setMode(string _mode){
	this->mode = _mode;
}
string Config::getMode(){
	return this->mode;
}

void Config::setHermiteBase(unsigned int _base){
	this->hermite_base = _base;
}
unsigned int Config::getHermiteBase(){
	return this->hermite_base;
}

void Config::printConfiguration(){
	cout << endl;
	cout << "Config:printConfiguration(): archivo de mapa = " << this->mapFile << endl;
	cout << "Config:printConfiguration(): numero particulas = " << this->quantity << endl;
	cout << "Config:printConfiguration(): numero iteraciones = " << this->iterations << endl;
	cout << "Config:printConfiguration(): numero pivotes = " << this->pivots << endl;
	cout << "Config:printConfiguration(): alpha = " << this->alpha << endl;
	cout << "Config:printConfiguration(): omega = " << this->omega << endl;
	cout << "Config:printConfiguration(): phi_p = " << this->phi_p << endl;
	cout << "Config:printConfiguration(): phi_g = " << this->phi_g << endl;

	//cout << "Config:printConfiguration():  = " << this-> << endl;

	cout << endl;
}
