#include "Util.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

Util::Util() {
}

Util::Util(const Util& orig) {
}

Util::~Util() {
}

Util::getPRandPoint(){

    float x = this->getUniformPRand();
    float y = this->getUniformPRand();

    Point p = Point(x, y);
    
    return p;
}


/*
 * TODO: PRandPoint
 * @params, max value x, min value x
 * @params, min value y, max value y
 *
 * Returns a 2d point between the params values
 *
 */


 Point Util::getPRandPoint(int min_x, int max_x, int min_y, int max_y){
    
     float x = rand() % max_x + min_x;
     float y = rand() % max_y + min_y;
     
     Point p = Point(x, y);
     
     return p;

 }
