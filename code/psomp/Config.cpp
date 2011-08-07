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

void Config::writePpm(string input){

    Map *map = this->getMap();
    int width  = map->getWidth();
    int height = map->getHeight();

    std::ostringstream ss;

    ofstream myfile;
    /* File name conventions
     * date_instance_particles_alpha_omega_phip_phig_pivotes_mehod_[init|end]
     *
     */

    ss << this->resultfile << "/";
    //ss << nfile << "_";
    ss << this->getInitDate() << "_";
    ss << this->getMapFileName() << "_";
    ss << this->quantity << "_";
    ss << this->alpha << "_";
    ss << this->omega << "_";
    ss << this->phi_p << "_";
    ss << this->phi_g << "_";
    ss << this->pivots << "_";
    ss << this->mode << "_";

    string resultfile = ss.str();

    //remove(resultfile.begin(), resultfile.end(), '.');

    resultfile = (nfile == 0) ? resultfile + "init.ppm": resultfile + "end.ppm";
    const char* filename = resultfile.c_str ();
    myfile.open(filename);
    // format for pnm
    myfile << "P3" << endl;
    myfile << height <<  " " << width << endl;
    myfile << "255" << endl;
    myfile << input ;
    myfile.close();
    nfile++;
    return;
}

void Config::writeCsv(string filename, string input){

	ofstream myfile;

	string fileurl;

	std::ostringstream ss;

	ss << this->resultfile << "/";
	ss << this->getInitDate() << "_";
	ss << this->getMapFileName() << "_";
	ss << this->quantity << "_";
	ss << this->alpha << "_";
	ss << this->omega << "_";
	ss << this->phi_p << "_";
	ss << this->phi_g << "_";
	ss << this->pivots << "_";
	ss << this->mode << "_";
	ss << filename << ".csv";

	fileurl = ss.str();

	const char* filestr = fileurl.c_str();

	myfile.open(filestr);
	myfile << input ;
	myfile.close();

	return;
}

string Config::getDate(){

  time_t tiempo;
  char cad[80];
  struct tm *tmPtr;

  tiempo = time(NULL);
  tmPtr = localtime(&tiempo);
  strftime( cad, 80, "%Y_%B_%A_%H%M%S", tmPtr );

//  printf( "La hora local es: %s\n", asctime(tmPtr) );
//  printf( "La hora y fecha locales son: %s\n", cad );

  string date = cad;

  //set the initial date
  this->setInitDate(date);
  return date;

}
void Config::setInitDate(const string s){
	if(this->initDate.empty()){
		if(s.empty()){
			this->initDate.assign(this->getDate());
		} else {
			this->initDate.assign(s);
		}
	}
}
string Config::getInitDate(){
	if(this->initDate.empty()){
		this->initDate.assign(this->getDate());
	}
	return this->initDate;
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
string Config::getMapFileName() const {
	size_t pos;
	pos = this->mapFile.find_last_of("/\\");;
	return this->mapFile.substr(pos+1);
}
void Config::setQuantity(unsigned int quantity) {
    this->quantity = quantity;
}
unsigned int Config::getQuantity() const {
    return quantity;
}
void Config::setOmega(float omega) {
    this->omega = omega;
}
float Config::getOmega() const {
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
void Config::setResultfile(string resultfile) {
    this->resultfile = resultfile;
}
string Config::getResultfile() const {
    return resultfile;
}
