using namespace std;

#include "Map.h"
#include "Config.h" //TODO: esto deberia ir incluido en el Map.h

Map::Map(string url){
	this->isValid = false;

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

	this->start = p.getStart();
	this->goal = p.getGoal();

	this->width = p.getWidth();
	this->height = p.getHeight();

	this->isValid = p.validarMapFile();
}

void Map::printMap(){
	for(unsigned int i = 0; i<this->map.size(); i++){
		for(unsigned int j = 0; j<this->map[i].size(); j++){
			cout << this->map[i][j];
		}
		cout << endl;
	}

	//imprimir puntos de inicio y meta
	cout << "punto de inicio: " << this->start->toString() << endl;
	cout << "punto de meta: " << this->goal->toString() << endl;
}

Point* Map::getStart(){
	return this->start;
}
Point* Map::getGoal(){
	return this->goal;
}

unsigned int Map::getWidth(){
	return this->width;
}

unsigned int Map::getHeight(){
	return this->height;
}


vector <vector <int> > Map::getMap(){
	return this->map;
}

int Map::getValue(Point* p){
	return this->map[p->getX()][p->getY()];
}

Point Map::selectRandomNextStep(Point* p, vector<Point*>* camino_actual, Point* goal){
	cout << "Map:selectRandomNextStep(): seleccionando siguiente paso para el punto " << p->toString() << endl;

	//punto a entregar
	Point next;

	//obtener los puntos vecinos
	Point norte = Point(p->getX(), p->getY() - 1);
	Point sur = Point(p->getX(), p->getY() + 1);

	Point este = Point(p->getX() + 1, p->getY());
	Point oeste = Point(p->getX() -1, p->getY());

	//crear vector que almacenara los puntos factibles (no funciona aun)
	//vector<Point> puntos_factibles;

	//solucion rapida: tickets para el sorteo
	int ticket_norte = -1;
	int ticket_sur = -1;
	int ticket_este = -1;
	int ticket_oeste = -1;

	//vector de distancias de las zonas factibles (largo variable = cantidad de factibles)
	vector<int> distancias;

	//norte
	//cout << "Map:selectRandomNextStep(): revisando norte " << norte.toString() << endl;
	if( (norte.isValid(this->width, this->height)) && !norte.isInVector(*camino_actual) ){
		//puntos_factibles.push_back(norte);

		//agregar al vector de distancias
		distancias.push_back(norte.distanciaA(goal));

		//solucion rapida
		ticket_norte = distancias.size();
	} else {
		cout << "Map:selectRandomNextStep(): norte " << norte.toString() << " NO FACTIBLE" << endl;
	}

	//cout << "Map:selectRandomNextStep(): revisando sur " << sur.toString() << endl;
	if( (sur.isValid(this->width, this->height)) && !sur.isInVector(*camino_actual) ){
		//puntos_factibles.push_back(sur);

		//agregar al vector de distancias
		distancias.push_back(sur.distanciaA(goal));

		//solucion rapida
		ticket_sur = distancias.size();
	} else {
		cout << "Map:selectRandomNextStep(): sur " << sur.toString() << " NO FACTIBLE" << endl;
	}

	//cout << "Map:selectRandomNextStep(): revisando este " << este.toString() << endl;
	if( (este.isValid(this->width, this->height)) && !este.isInVector(*camino_actual) ){
		//puntos_factibles.push_back(este);

		//agregar al vector de distancias
		distancias.push_back(este.distanciaA(goal));

		//solucion rapida
		ticket_este = distancias.size();
	} else {
		cout << "Map:selectRandomNextStep(): este " << este.toString() << " NO FACTIBLE" << endl;
	}

	//cout << "Map:selectRandomNextStep(): revisando oeste " << oeste.toString() << endl;
	if( (oeste.isValid(this->width, this->height)) && !oeste.isInVector(*camino_actual) ){
		//puntos_factibles.push_back(oeste);

		//agregar al vector de distancias
		distancias.push_back(oeste.distanciaA(goal));

		//solucion rapida
		ticket_oeste = distancias.size();
	} else {
		cout << "Map:selectRandomNextStep(): oeste " << oeste.toString() << " NO FACTIBLE" << endl;
	}

	cout << "Map:selectRandomNextStep(): casillas factibles = " << distancias.size() << endl;
	cout << "Map:selectRandomNextStep(): distancias.size() = " << distancias.size() << endl;

	//TODO: si factibles es cero, es porque el robot se ha quedado encerrado, y hay que implementar alguna
	//forma de salir de ahi, o permitir que camine sobre si mismo solo por esa vez (sera castigado en la F.O.)
	if(distancias.size() == 0){
		cout << "Map:selectRandomNextStep(): QUEDE ATRAPADO, tomando camino ya explorado por razones de fuerza mayor" << endl;
		//agregar nodos si son factibles, aunque se haya pasado por ellos
		if( (norte.isValid(this->width, this->height)) ){

			//agregar al vector de distancias
			distancias.push_back(norte.distanciaA(goal));

			//solucion rapida
			ticket_norte = distancias.size();
		} else {
			cout << "Map:selectRandomNextStep(): norte " << norte.toString() << " NO FACTIBLE" << endl;
		}

		if( (sur.isValid(this->width, this->height)) ){

			//agregar al vector de distancias
			distancias.push_back(sur.distanciaA(goal));

			//solucion rapida
			ticket_sur = distancias.size();
		} else {
			cout << "Map:selectRandomNextStep(): sur " << sur.toString() << " NO FACTIBLE" << endl;
		}

		if( (este.isValid(this->width, this->height)) ){

			//agregar al vector de distancias
			distancias.push_back(este.distanciaA(goal));

			//solucion rapida
			ticket_este = distancias.size();
		} else {
			cout << "Map:selectRandomNextStep(): este " << este.toString() << " NO FACTIBLE" << endl;
		}

		if( (oeste.isValid(this->width, this->height)) ){

			//agregar al vector de distancias
			distancias.push_back(oeste.distanciaA(goal));

			//solucion rapida
			ticket_oeste = distancias.size();
		} else {
			cout << "Map:selectRandomNextStep(): oeste " << oeste.toString() << " NO FACTIBLE" << endl;
		}
	}

	//dentro de los factibles, seleccionar uno
	int choice = -1;
	Config &config = Config::getInstance();

	//escoger uno dependiendo la distancia (privilegia a los mas cercanos)
	choice = config.getWeightedRandomInt(distancias) + 1;

	cout << "Map:selectRandomNextStep(): config::getWeightedRandomInt(distancias) = " << choice << endl;

	//solucion rapida: premiar al sorteado
	if(choice == ticket_norte)
		next = norte;

	if(choice == ticket_sur)
		next = sur;

	if(choice == ticket_este)
		next = este;

	if(choice == ticket_oeste)
		next = oeste;

	cout << "Map:selectRandomNextStep(): punto seleccionado finalmente: " << next.toString() << endl;

	return next;
}
