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

int Config::getRandomInt(int max){
	return rand()%max + 1;
}

int Config::getWeightedRandomInt(const vector<int> &distancias){
	//crear vector de probabilidades
	vector<float> probabilidades;

	//calcular suma de las distancias
	int suma_distancias = 0;
	for(unsigned int i=0; i<distancias.size(); i++){
		suma_distancias += distancias[i];
	}

	//cout << "Config::getWeightedRandomInt(): suma_distancias = " << suma_distancias << endl;

	//calcular las ponderaciones nuevas

	//como vamos a privilegiar a las distancias mas cortas hay que hacer otro vector
	//que le de mas valor a las distancias cortas en la misma posicion
	vector<int> ponderaciones;

	for(unsigned int i=0; i<distancias.size(); i++){
		ponderaciones.push_back(suma_distancias - distancias[i]);
	}

	//calcular la suma de las ponderaciones
	int suma_ponderaciones = 0;
	for(unsigned int i=0; i<ponderaciones.size(); i++){
		suma_ponderaciones += ponderaciones[i];
	}

	//cout << "Config::getWeightedRandomInt(): suma_ponderaciones = " << suma_ponderaciones << endl;

	//calcular las probabilidades de cada una de las distancias
	float p;
	for(unsigned int i=0; i<distancias.size(); i++){
		p = (1.0/suma_ponderaciones) * (ponderaciones[i]);

		//cout << "Config::getWeightedRandomInt(): distancias[" << i << "] = " << distancias[i] << endl;
		//cout << "Config::getWeightedRandomInt(): ponderaciones[" << i << "] = " << ponderaciones[i] << endl;
		//cout << "Config::getWeightedRandomInt(): (suma_ponderaciones - ponderaciones[i]) = " << (suma_ponderaciones - ponderaciones[i]) << endl;

		probabilidades.push_back(p);

		//cout << "Config::getWeightedRandomInt(): probabilidad calculada = " << p << endl;
	}

	//lanzar numero random
	float random = this->getRandomInt(1000)/1000.0;

	//cout << "Config::getWeightedRandomInt(): random = " << random << endl;

	//ver cual de todos los elementos sale sorteado
	float suma_probabilidades = 0.0;
	int indice_escogido = 0;
	for(unsigned int i=0; i<probabilidades.size(); i++){
		suma_probabilidades += probabilidades[i];

		//cout << "Config::getWeightedRandomInt(): suma_probabilidades = " << suma_probabilidades << endl;

		if(random <= suma_probabilidades){
			indice_escogido = i;

			//cout << "Config::getWeightedRandomInt(): indice_escogido = " << indice_escogido << endl;

			break;
		}
	}

	return indice_escogido;
}
