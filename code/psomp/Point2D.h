/*
 * File:   Point2D.h
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 2:02
 */

#ifndef POINT2D_H
#define	POINT2D_H

using namespace std;

#include <iostream>
#include <math.h>
#include <string>
#include <cstdlib>

#include <sstream>

class Point2D {
public:
    int x, y;

    Point2D();
    Point2D(int x, int y);

    Point2D(const Point2D& orig);
    virtual ~Point2D();
    void setY(int y);
    int getY() const;
    void setX(int x);
    int getX() const;
    static float getUniformPRand() { return (float)rand()/(float)RAND_MAX; } ;
	void scaleTo(int base);

    static Point2D* getRandomAbsPoint(float min_x, float min_y, float max_x, float max_y){

        float rmin_x = (min_x <= max_x) ? min_x: max_x;
        float rmin_y = (min_y <= max_y) ? min_y: max_y;
        float rmax_x = (min_x >= max_x) ? min_x: max_x;
        float rmax_y = (min_y >= max_y) ? min_y: max_y;

        float x = (rmax_x-rmin_x)*((float)rand()/(float)RAND_MAX) + rmin_x;
        float y = (rmax_y-rmin_y)*((float)rand()/(float)RAND_MAX) + rmin_y;

        x = sqrt(pow(x,2));
        y = sqrt(pow(y,2));

        Point2D *p = new Point2D(x, y);

        return p;
    }

    void setToBound(int minx, int miny, int maxx, int maxy){

	x = (x < minx) ? minx : ((x >= maxx) ? maxx: x);
        y = (y < miny) ? miny : ((y >= maxy) ? maxy: y);

        return;
    }

    static Point2D* getRandomPoint(float min_x, float min_y, float max_x, float max_y){

		//cout << "G> min_x: " << min_x << endl;
		//cout << "G> min_y: " << min_y << endl;
		//cout << "G> max_y: " << max_x << endl;
		//cout << "G> max_y: " << max_y << endl;


        float rmin_x = (min_x <= max_x) ? min_x: max_x;
        float rmin_y = (min_y <= max_y) ? min_y: max_y;
        float rmax_x = (min_x >= max_x) ? min_x: max_x;
        float rmax_y = (min_y >= max_y) ? min_y: max_y;


		//cout << "G> rmin_x: " << rmin_x << endl;
		//cout << "G> rmin_y: " << rmin_y << endl;
		//cout << "G> rmax_x: " << rmax_x << endl;
		//cout << "G> rmax_y: " << rmax_y << endl;

        float x = (rmax_x-rmin_x)*((float)rand()/(float)RAND_MAX) + rmin_x;
        float y = (rmax_y-rmin_y)*((float)rand()/(float)RAND_MAX) + rmin_y;

        //cout << "G> x: " << x << endl;
        //cout << "G> y: " << y << endl;

        Point2D *p = new Point2D(x, y);

        return p;
    }

    string toString();

    Point2D operator+(const Point2D &p) const;
    Point2D* operator+(const Point2D *p) const;
    Point2D operator-(const Point2D &p) const;
    Point2D operator*(float m) const;
    Point2D operator/(float m) const;
    bool operator>(float m) const;
    float operator>>(const Point2D& p) const; // get the distance betweeen points
    bool operator==(const Point2D &p) const;
    bool operator!=(const Point2D &p) const;
private:



};

#endif	/* POINT2D_H */

