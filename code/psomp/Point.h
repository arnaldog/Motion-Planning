using namespace std;

#include <string>
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

	//verifica si el punto es valido o no (-1,-1) = no valido
	bool isValid();
private:
    int x;
    int y;
    int m;
};

#endif	/* POINT_H */

