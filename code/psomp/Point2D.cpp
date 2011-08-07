/*
 * File:   Point2D.cpp
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 2:02
 */


#include "Point2D.h"


Point2D::Point2D() {
}

Point2D::Point2D(int x, int y) {
    this->x = x;
    this->y = y;
}


Point2D Point2D::operator+(const Point2D& p) const {

    Point2D tmp;
    tmp.x = x + p.x;
    tmp.y = y + p.y;
    return (tmp);
}

Point2D* Point2D::operator+(const Point2D *p) const {

    Point2D* tmp;
    tmp->x = x + p->x;
    tmp->y = y + p->y;
    return (tmp);
}


Point2D Point2D::operator-(const Point2D& p) const {
	Point2D tmp;
	tmp.x = x - p.x;
	tmp.y = y - p.y;
	return (tmp);
}

Point2D Point2D::operator*(float m) const{

    Point2D tmp;
    tmp.x = x*m;
    tmp.y = y*m;
    return (tmp);
}

Point2D Point2D::operator/(float m) const{

    Point2D tmp;
    tmp.x = x/m;
    tmp.y = y/m;
    return (tmp);
}

bool Point2D::operator>(float m) const{

    bool tmp = false;
    tmp = (x > m);
    tmp &= (x > m);
    return (tmp);
}



bool Point2D::operator==(const Point2D &p) const{
    return (x == p.x && y == p.y);
}

bool Point2D::operator!=(const Point2D &p) const{
    return (x != p.x || y != p.y);
}

string Point2D::toString(){
    std::ostringstream ss;
    ss << '(' << x << ',' << y << ')';
    std::string o = ss.str();

    return o;
}

float Point2D::operator>>(const Point2D& p) const {

    float lenght;
    lenght = sqrt( (x - p.x)^2 + (y - p.y)^2 );
    return lenght;
}

Point2D::Point2D(const Point2D& orig) {
}

Point2D::~Point2D() {
}
void Point2D::setY(int y) {
    this->y = y;
}
int Point2D::getY() const {
    return y;
}
void Point2D::setX(int x) {
    this->x = x;
}
int Point2D::getX() const {
    return x;
}

void Point2D::scaleTo(int base){
	float norm = sqrt(pow(x,2)+pow(y,2));
	norm = (norm == 0) ? 1 : norm;
	float xf = (float)x/norm;
	float yf = (float)y/norm;

	x = xf*base;
	y = yf*base;
	return;
}
