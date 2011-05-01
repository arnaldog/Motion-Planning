/* 
 * File:   Point.cpp
 * Author: alejandrasuarez
 * 
 * Created on 1 de mayo de 2011, 18:00
 */

#include "Point.h"

Point::Point() {
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

