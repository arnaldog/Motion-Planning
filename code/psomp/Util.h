/* 
 * File:   Util.h
 * Author: alejandrasuarez
 *
 * Created on 8 de mayo de 2011, 16:39
 */

#include <ctime>
#include <cstdlib>
#include <iostream>

#ifndef UTIL_H
#define	UTIL_H

class Util {
public:
    Util();
    Util(const Util& orig);
    virtual ~Util();

    // uniform pseudo random generator;
    static float getUniformPRand() { return (float)rand()/(float)RAND_MAX; } ;
private:

};

#endif	/* UTIL_H */

