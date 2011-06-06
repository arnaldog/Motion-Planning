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

    Point* getStart();
    Point* getGoal();

    unsigned int getWidth();
    unsigned int getHeight();

    //validacion del mapa, que tenga un puntos de partida y otro de meta
    bool validarMapFile();
private:
    //mapa
    matrixInt matrix;

    //archivo de entrada
    string map_file_url;

    //puntero a archivo que se leerá
    ifstream file;

    //tamaño de la matriz
    unsigned int width;
    unsigned int height;

    //puntos de inicio y termino
    Point* start;
    Point* goal;

    //metodos

    //obetener el tamaño de la matriz
    void getSize();

    //reservar memoria para el vector
    void assertMemory();

    //leer archivos y llenar la matriz
    void readFile();
};

#endif
