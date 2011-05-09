using namespace std;

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#ifndef POINT_H
#define	POINT_H

class Point {
public:
    Point();
    Point(const Point& orig);
    Point(int x, int y, int m); // point with magnitude for velocity
    Point(int x, int y);
    virtual ~Point();


    // GETTERS AND SETTERS
    int getX();
    int getY();

    void setX(int x);
    void setY(int y);

	//print methods
	string toString();
	float distanciaA(Point* target);

	//verifica si el punto es valido o no (-1,-1) = no valido
	bool isValid();
	bool isValid(int width, int height);

	//verifica si el punto esta en un vector
	bool isInVector(vector<Point*> v);

	//operadores
	bool operator==(const Point &other);
	bool operator!=(const Point &other);
private:
    int x;
    int y;
    int m;
};

#endif	/* POINT_H */

