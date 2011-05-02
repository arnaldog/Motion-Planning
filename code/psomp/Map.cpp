using namespace std;

#include <iostream>

#include "vector"
#include "Map.h"
#include "Point.h"

Map::Map(string url){
	this->url = url;
	
	this->parseMapFile();
}

void Map::parseMapFile(){
	cout << "abriendo y parseando mapa: " << this->url << endl;
}