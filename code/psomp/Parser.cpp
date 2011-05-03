#include "Parser.h"

Parser::Parser(){
	//debug
	cout << "PARSER::constructor inicializado" << endl;
}


void Parser::parsear(){
	//obtener tamaño de la matrices
	this->obtenerSize();
	
	//reservar memoria para el vector
	this->reservarMemoria();

	//parsear archivo de tiempos
	this->leerArchivo();
}

void Parser::reservarMemoria(){
	for(int i = 0; i < this->width; i++){
		this->map.push_back( vector<int>() );

		for (int j = 0; j < this->height; j++ )
			this->map[i].push_back(-1);
	}
}

void Parser::obtenerSize(){

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
		unsigned int i = 0;
		
		//saltar las primeras 2 lineas, que son de informacion
		for(i=0; i<2; i++){
			this->file >> line;
		}

		i = 0;
		while(this->file >> line){
			//cout << "linea: " << line << endl;

			cout << i << endl;
			
			//agregar nueva fila al vector
			//this->map.push_back(vector<int>());

			//por cada elemento de la fila...
			for(unsigned int j=0; j<line.length(); j++){
				cout << line[j] << ",";
				this->map[i][j] = line[j];
			}
			cout << endl;

			//cout << line.length() << endl;
			//cout << "C[" << i/this->size << "][" << i%this->size << "] = " << x << endl;

			i++;
		}

		this->file.close();
	} else {
		//cout << "ERROR: no se pudo abrir el archivo: " << this->map_file_url.c_str() << endl;
	}
}

void Parser::setMapFile(string url){
	this->map_file_url = url;
}

matrixInt Parser::getMap(){
	return this->map;
}
