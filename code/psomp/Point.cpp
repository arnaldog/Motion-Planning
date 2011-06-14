/*
 * File:   Point.cpp
 * Author: alejandrasuarez
 *
 * Created on 1 de mayo de 2011, 18:00
 */

#include "Point.h"

Point::Point() {
	//set to a not valid value
	this->x = -1;
	this->y = -1;
}

Point::Point(const Point& orig) {
}

Point::~Point() {
}


Point::Point(int x, int y, int m){
    this->x = x;
    this->y = y;
    this->m = m;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX(){
	return this->x;
}
int Point::getY(){
	return this->y;
}

void Point::setX(int x){
	this->x = x;
	return;
}

void Point::setY(int y){
	this->y = y;
	return;
}

string Point::toString(){

	std::stringstream _x;
	std::stringstream _y;
	_x << this->x;
	_y << this->y;

	return string("(") + _x.str() + string(",") + _y.str() + string(")");
}

float Point::distanciaA(Point* target){
	//cout << "Point::distanciaA(): abs(target->getX() - this->x) = " << abs(target->getX() - this->x) << endl;
	//cout << "Point::distanciaA(): abs(target->getY() - this->y) = (" << target->getY() << " - " << this->y << ") = " << abs(target->getY() - this->y) << endl;
	return abs(target->getX() - this->x) + abs(target->getY() - this->y);
}

bool Point::isValid(){
	if(this->x < 0)
		return false;

	if(this->y < 0)
		return false;

	return true;
}

bool Point::isValid(int width,int height){
	//cout << "Point::isValid(w,h): verificando si es valido dentro de los limites minimos (0,0)" << endl;
	if(!this->isValid())
		return false;

	//cout << "Point::isValid(w,h): verificando si se sale de los limites maximos: " << width << "," << height << endl;
	if(this->x >= width)
		return false;

	if(this->y >= height)
		return false;

	return true;
}

bool Point::isInVector(vector<Point*> v){
	for(unsigned int i=0; i<v.size(); i++){
		//cout << "Point::isInVector(): vector[" << i << "] = " << v->at(i)->toString() << endl;
		Point* p = v.at(i);
		if(*this == *p){
			return true;
		}
	}

	return false;
}

//obtener un punto random

void Point::randomize(){
	Config &config = Config::getInstance();

	this->x = Util::getRandomInt( config.getMap()->getWidth() )-1;
	this->y = Util::getRandomInt( config.getMap()->getHeight() )-1;

	return;
}

//operadores
bool Point::operator==(const Point &other){
	if( (this->x == other.x) && (this->y == other.y) )
		return true;

	return false;
}

bool Point::operator!=(const Point &other){
    return !(*this == other);
  }
