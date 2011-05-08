using namespace std;

#include "Map.h"

Map::Map(string url){
	this->isValid = false;

	this->map_file_url = url;
	this->parseMapFile();
}

void Map::parseMapFile(){
	//debug
	cout << "Map::parseMapFile: abriendo y parseando mapa: " << this->map_file_url << endl;

	Parser p;
	p.setMapFile(this->map_file_url);
	p.parsear();

	this->map = p.getMatrix();

	this->start = p.getStart();
	this->goal = p.getGoal();

	this->width = p.getWidth();
	this->height = p.getHeight();

	this->isValid = p.validarMapFile();
}

void Map::printMap(){
	for(unsigned int i = 0; i<this->map.size(); i++){
		for(unsigned int j = 0; j<this->map[i].size(); j++){
			cout << this->map[i][j];
		}
		cout << endl;
	}

	//imprimir puntos de inicio y meta
	cout << "punto de inicio: " << this->start->toString() << endl;
	cout << "punto de meta: " << this->goal->toString() << endl;
}

Point* Map::getStart(){
	return this->start;
}
Point* Map::getGoal(){
	return this->goal;
}

unsigned int Map::getWidth(){
	return this->width;
}

unsigned int Map::getHeight(){
	return this->height;
}


vector <vector <int> > Map::getMap(){
	return this->map;
}

int Map::getValue(Point* p){
	return this->map[p->getX()][p->getY()];
}

Point Map::selectRandomNextStep(Point* p){
	cout << "Map:selectRandomNextStep(): seleccionando siguiente paso para el punto " << p->toString() << endl;

	//punto a entregar
	Point next = Point(-1,-1);

	//obtener los puntos vecinos
	Point norte = Point(p->getX(), p->getY() - 1);
	Point sur = Point(p->getX(), p->getY() + 1);

	Point este = Point(p->getX() + 1, p->getY());
	Point oeste = Point(p->getX() -1, p->getY());

	//calcular cuantos puntos son factibles
	int factibles = 0;

	//norte
	cout << "Map:selectRandomNextStep(): revisando norte " << norte.toString() << endl;
	if(norte.isValid(this->width, this->height))
		factibles++;

	cout << "Map:selectRandomNextStep(): revisando sur " << sur.toString() << endl;
	if(sur.isValid(this->width, this->height))
		factibles++;

	cout << "Map:selectRandomNextStep(): revisando este " << este.toString() << endl;
	if(este.isValid(this->width, this->height))
		factibles++;

	cout << "Map:selectRandomNextStep(): revisando oeste " << oeste.toString() << endl;
	if(oeste.isValid(this->width, this->height))
		factibles++;

	cout << "Map:selectRandomNextStep(): factibles = " << factibles << endl;

	return next;
}
