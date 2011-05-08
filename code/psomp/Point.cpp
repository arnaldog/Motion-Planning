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

bool Point::isValid(){
	if(this->x == -1)
		return false;

	if(this->y == -1)
		return false;

	return true;
}
