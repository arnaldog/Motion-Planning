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
	private:		
		vector < vector <int> > map;
		string map_file_url;
		Point start;
		Point goal;
		
		//parseador
		//Parser parser;
};

#endif	/* MAP_H */
