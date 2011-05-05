using namespace std;

#include "Map.h"

Map::Map(string url){
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
}

void Map::printMap(){
	for(unsigned int i = 0; i<this->map.size(); i++){
		for(unsigned int j = 0; j<this->map[i].size(); j++){
			//cout << this->map[i][j];
		}
		//cout << endl;
	}
}
