#include "Parser.h"

Parser::Parser(){
	//debug
	cout << "PARSER::constructor inicializado" << endl;

	Point p = Point(-1,-1);
	this->start = &p;
	this->goal = &p;
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
					this->matrix[i].push_back(2);
					Point* p = new Point(i,j);
					this->start = p;

					cout << "Detectado caracter \"S\" en coordenadas: " << this->start->toString() << endl;
				}

				//ver si se trata del caracter de termino "E" (End)
				if (caracter == 'G'){
					this->matrix[i].push_back(3);
					Point* p = new Point(i,j);
					this->goal = p;

					cout << "Detectado caracter \"G\" en coordenadas: " << this->goal->toString() << endl;
				}
				//cout << "Parser::leerArchivo() " << this->start->toString() << endl;
			}
		}

		this->file.close();

	} else {
		cout << "ERROR: no se pudo abrir el archivo: " << this->map_file_url.c_str() << endl;
	}

	//cout << "this->getStart().toString(): " << this->getStart().toString() << endl;//
	//cout << "this->start.toString(): " << this->start.toString() << endl;//
}

bool Parser::validarMapFile(){
	if(!this->start->isValid()){
		cout << "ERROR: Punto de partida no valido" << endl;
		cout << "ERROR: por favor escriba una S donde quiera poner el punto de partida" << endl;
		return false;
	}

	if(!this->goal->isValid()){
		cout << "ERROR: Punto de llegada no valido" << endl;
		cout << "ERROR: por favor escriba una E donde quiera poner el punto de meta" << endl;
		return false;
	}

	return true;
}

void Parser::setMapFile(string url){
	this->map_file_url = url;
}

matrixInt Parser::getMatrix(){
	return this->matrix;
}

Point* Parser::getStart(){
	return this->start;
}

Point* Parser::getGoal(){
	return this->goal;
}

unsigned int Parser::getWidth(){
	return this->width;
}

unsigned int Parser::getHeight(){
	return this->height;
}
