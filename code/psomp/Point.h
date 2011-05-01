/* 
 * File:   Point.h
 * Author: alejandrasuarez
 *
 * Created on 1 de mayo de 2011, 18:00
 */

#ifndef POINT_H
#define	POINT_H

class Point {
public:
    Point();
    Point(const Point& orig);
    Point(int x, int y, int m); // point with magnitude for velocity 
    Point(int x, int y);
    virtual ~Point();
private:
    int x;
    int y;
    int m;
};

#endif	/* POINT_H */

