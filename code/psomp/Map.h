using namespace std;

#include "vector"
#include "Point.h"

#ifndef MAP_H
#define	MAP_H

class Map {
	public:
		//constructor
		Map(string url);
		
		//parsear archivo
		void parseMapFile();
	private:
		vector < vector <int> > map;
		string url;
		Point start;
		Point goal;
};

#endif	/* MAP_H */