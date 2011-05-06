#include "Parser.h"

Parser::Parser(){
	//debug
	cout << "PARSER::constructor inicializado" << endl;
}

void Parser::parsear(){
	//obtener tamaño de la matrices
	this->obtenerSize();

	//reservar memoria para el vector
	//this->reservarMemoria();

	//parsear archivo de tiempos
	this->leerArchivo();
}

void Parser::reservarMemoria(){
	for(unsigned int i = 0; i < this->width; i++){
		this->matrix.push_back( vector<int>() );

		for (unsigned int j = 0; j < this->height; j++ )
			this->matrix[i].push_back(-1);
	}
}

void Parser::obtenerSize(){
	cout << "Parser: Obteniendo dimension del mapa" << endl;

	this->file.open(this->map_file_url.c_str(), ios::in);

	if(this->file.is_open()){
		//leyendo
		string line;
		int width;
		int height;

		//extraer la cantidad de nodos
		this->file >> width;
		this->file >> height;

		this->width = width;
		this->height = height;

		//debug
		cout << "width >> " << this->width << endl;
		cout << "height >> " << this->height << endl;

		this->file.close();
	} else {
		cout << "ERROR [Parser::obtenerSize]: no se pudo abrir el archivo: " << this->map_file_url.c_str() << endl;
	}
}

void Parser::leerArchivo(){
	this->file.open(this->map_file_url.c_str(), ios::in);

	if(this->file.is_open()){
		cout << "parseando el archivo: " << this->map_file_url.c_str() << endl;

		//leyendolo
		string line;

		//saltar las primeras 2 lineas, que son de informacion
		for(unsigned int i=0; i<2; i++){
			this->file >> line;
		}

		char caracter;

		for(unsigned int i=0; i < this->height; i++){
			//cout << "linea: " << line << endl;

			//agregar nueva fila al vector
			this->matrix.push_back(vector<int>());

			//por cada elemento de la fila...
			for(unsigned int j=0; j < this->width; j++){
				this->file >> caracter;

				//ver si se trata de un espacio libre (0)
				if (caracter == '0')
					this->matrix[i].push_back(0);

				//ver si se trata de un obstaculo (1)
				if (caracter == '1')
					this->matrix[i].push_back(1);

				//ver si se trata del caracter de inicio "S" (Start)
				if (caracter == 'S'){
					cout << "Detectado caracter \"S\" en i: " << i << endl;
					this->matrix[i].push_back(2);
					this->start = Point(i,j);

					cout << "Start: " << this->start.toString() << endl;
				}

				//ver si se trata del caracter de termino "E" (End)
				if (caracter == 'G'){
					cout << "Detectado caracter \"G\" en i: " << i << endl;
					this->matrix[i].push_back(3);
					this->goal = Point(i,j);

					cout << "Goal: " << this->goal.toString() << endl;
				}

				//this->matrix[i].push_back((int)caracter - '0');
			}
		}
		this->file.close();
	} else {
		//cout << "ERROR: no se pudo abrir el archivo: " << this->map_file_url.c_str() << endl;
	}

	cout << "this->getStart().toString(): " << this->getStart().toString() << endl;//
	cout << "this->start.toString(): " << this->start.toString() << endl;//
}

void Parser::setMapFile(string url){
	this->map_file_url = url;
}

matrixInt Parser::getMatrix(){
	return this->matrix;
}

Point Parser::getStart(){
	//cout << "getStart: " << this->start.toString() << endl;
	return this->start;
}
Point Parser::getGoal(){
	return this->goal;
}