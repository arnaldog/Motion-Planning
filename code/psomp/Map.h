#include <vector>
#include <string>

using namespace std;

#include "Point.h"
#include "Parser.h"

#ifndef MAP_H
#define	MAP_H

class Map {
	public:
		//constructor
		Map(string url);

		//parsear archivo
		void parseMapFile();
		void printMap();

		Point* getStart();
		Point* getGoal();

		unsigned int getWidth();
		unsigned int getHeight();

		vector <vector <int> > getMap();

		int getValue(Point* p);

		Point selectRandomNextStep(Point* p, vector<Point*>* camino_actual);
	private:
		vector < vector <int> > map;
		string map_file_url;
		Point* start;
		Point* goal;

		//tamaño del mapa
		unsigned int width;
		unsigned int height;

		//variable que indica si un mapa es valido o no
		//(si tiene puntos de entrada y meta)
		bool isValid;
};

#endif	/* MAP_H */
