#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "Point.h" 

typedef vector < vector <int> > matrixInt;

#ifndef _PARSER_H_
#define _PARSER_H_

class Parser {
	public:
		//metodos
		Parser();

		void setMapFile(string url);
		void parsear();
		
		matrixInt getMatrix();
	private:
		//mapa
		matrixInt matrix;

		//archivo de entrada
		string map_file_url;
		
		//puntero a archivo que se leerá
		ifstream file;
		
		//tamaño de la matriz
		int width;
		int height;

		//metodos

		//obetener el tamaño de la matriz
		void obtenerSize();

		//reservar memoria para el vector
		void reservarMemoria();

		//leer archivos y llenar la matriz
		void leerArchivo();
};

#endif
