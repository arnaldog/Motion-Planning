/*
 * File:   Map.h
 * Author: alejandrasuarez
 *
 * Created on 5 de junio de 2011, 19:41
 */

#ifndef MAP_H
#define	MAP_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Point2D.h"

class Map {
public:
    Map();
    Map(const Map& orig);
    virtual ~Map();
    Map(string filename);

    vector < vector <int> > getMatrix();

    void printInformation();

    int getCollision(Point2D &p);
    void setGoal(Point2D* goal);
    Point2D* getGoal() const;
    void setStart(Point2D* start);
    Point2D* getStart() const;
    void setHeight(unsigned int height);
    unsigned int getHeight() const;
    void setWidth(unsigned int width);
    unsigned int getWidth() const;
    void setFilename(string filename);
    string getFilename() const;
    void setMatrix(vector<vector<int> > matrix);

private:
    vector < vector <int> > matrix;
    string filename;
    unsigned int width, height;
    Point2D *start, *goal;
};

#endif	/* MAP_H */

