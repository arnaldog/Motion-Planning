/* 
 * File:   Map.cpp
 * Author: alejandrasuarez
 * 
 * Created on 5 de junio de 2011, 19:41
 */

#include "Map.h"

Map::Map() {
}

Map::Map(const Map& orig) {
}

Map::~Map() {
}

vector < vector <int> > Map::getMatrix(){
    return matrix;
}

int Map::getCollision(Point2D &p){
    //cout << p.toString() << endl;
    int o = matrix[p.x][p.y];
    return o;
}
void Map::setGoal(Point2D* goal) {
    this->goal = goal;
}
Point2D* Map::getGoal() const {
    return goal;
}
void Map::setStart(Point2D* start) {
    this->start = start;
}
Point2D* Map::getStart() const {
    return start;
}
void Map::setHeight(unsigned int height) {
    this->height = height;
}
unsigned int Map::getHeight() const {
    return height;
}
void Map::setWidth(unsigned int width) {
    this->width = width;
}
unsigned int Map::getWidth() const {
    return width;
}
void Map::setFilename(string filename) {
    this->filename = filename;
}
string Map::getFilename() const {
    return filename;
}
void Map::setMatrix(vector<vector<int> > matrix) {
    this->matrix = matrix;
}

Map::Map(string filename){
    
    ifstream file;
    file.open(filename.c_str(), ios::in);
    char c;

    if(file.is_open()){
	file >> width;
	file >> height;
    }

    for(unsigned int i=0; i< width; i++){
	matrix.push_back(vector<int>());
	for(unsigned int j=0; j < height; j++){
	    file >> c;
	    if (c == '0')
		matrix[i].push_back(0);

	    if (c == '1')
		matrix[i].push_back(1);

	    if (c == 'S'){
		matrix[i].push_back(0);
		start = new Point2D(i,j);
	    }

	    if (c == 'G'){
		matrix[i].push_back(0);
		goal = new Point2D(i,j);
	    }

	}
    }

    file.close();
}

