/* 
 * File:   Route.h
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 2:02
 */

#ifndef ROUTE_H
#define	ROUTE_H

using namespace std;
#include <vector>
#include <algorithm>

#include "Config.h"
#include "Point2D.h"

class Route {
public:
    Route();
    Route(const Route& orig);
    virtual ~Route();
    
    string toString();
    //friend Route operator+(Route ob, Route r2);

    Route operator+(const Route &b);
    Route operator*(float m);
    Route operator-(const Route &b);

    //void createRandomRoute();

    vector<Point2D*> splines();
//    void setPointsRandom(Point2D min, Point2D max);
    void printPath();
    void Interpolation();
    void setAccelerations(vector<Point2D*> accelerations);
    vector<Point2D*> getAccelerations() const;
    void setGradients(vector<Point2D*> gradients);
    vector<Point2D*> getGradients() const;
    void setPoints(vector<Point2D*> points);
    vector<Point2D*> getPoints() const;
    void setPath(vector<Point2D*> path);
    vector<Point2D*> getPath() const;
    void setLength(int length);
    int getLength() const;
    void setSize(int size);
    int getSize() const;

    void setStart(Point2D* start);
    void setGoal(Point2D* goal);

    float fitnessEvaluation(Route &r);

    void initRandomGradients();
    void initRandomPoints();

    void initRandomRoute(Route &r);
    void initRandomVelocity(Route &r);
    


private: 
    int size;
    int length;

    Point2D* start;
    Point2D* goal;
    
    vector <Point2D*> points;
    vector <Point2D*> gradients;
    vector <Point2D*> accelerations;
    vector <Point2D*> path;

};

#endif	/* ROUTE_H */

