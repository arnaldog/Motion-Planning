/* 
 * File:   Route.cpp
 * Author: alejandrasuarez
 * 
 * Created on 3 de junio de 2011, 2:02
 */

#include "Route.h"


Route::Route() {
    this->length = 0;
    this->size = 0;
}
void Route::setAccelerations(vector<Point2D*> accelerations) {
    this->accelerations = accelerations;
}
vector<Point2D*> Route::getAccelerations() const {
    return accelerations;
}
void Route::setGradients(vector<Point2D*> gradients) {
    this->gradients = gradients;
}
vector<Point2D*> Route::getGradients() const {
    return gradients;
}
void Route::setPoints(vector<Point2D*> points) {
    this->size = points.size();
    this->points = points;
}
vector<Point2D*> Route::getPoints() const {
    return points;
}

void Route::setPath(vector<Point2D*> path) {
    this->length = path.size();
    this->path = path;
}
vector<Point2D*> Route::getPath() const {
    return path;
}

void Route::setLength(int length) {
    this->length = length;
}
int Route::getLength() const {
    return length;
}
void Route::setSize(int size) {
    this->size = size;
}
int Route::getSize() const {
    return size;
}


void Route::setStart(Point2D* start){
    this->start = start;
}
void Route::setGoal(Point2D* goal){
    this->goal = goal;
}

Route::Route(const Route& orig) {
}

Route::~Route() {

}

//void Route::setPointsRandom(Point2D min, Point2D max){
//
//    for(unsigned int i=0; i < size; i++){
//	Point2D p = Point2D::getRandom(min.x, max.x, min.y, max.y);
//	points.push_back(&p);
//    }
//
//}

string Route::toString(){
    std::ostringstream ss;

    ss << "Route::toString Size:\t\t" << this->size << endl;
    
    ss << "Route::toString Points:\t\t";
    for(unsigned int i = 0; i < this->points.size(); i++){
	ss << this->points[i]->toString();
	if (i % 15 == 0 && i > 0)
	    ss << endl << "\t\t\t\t\t\t\t";
    }
    ss << endl;

    ss << "Route::ToString Gradient:\t";
    for(unsigned int i = 0; i < this->gradients.size(); i++){
	ss << this->gradients[i]->toString();
    }
    ss << endl;

    ss << "Route::toString Length:\t\t" << this->length << endl;
    
    ss << "Route::toString Path:\t\t";
    for(unsigned i=0; i< this->path.size(); i++){
	ss << this->path[i]->toString();
	if (i % 15 == 0 && i > 0)
	    ss << endl << "\t\t\t\t\t\t\t";
    }
    
    std::string o = ss.str();
    
    return o;
}

float Route::evaluation(Route r){

    int length = r.length;
    return 3.14156;
}

void Route::initRandomRoute(Route &r){

    Config &config = Config::getInstance();
    int n = config.getPivots();
    Map *map = config.getMap();

    /* points, gradients, accelerations casting */
    vector <Point2D*> points (n);
    vector <Point2D*> gradients (n);
    vector <Point2D*> accelerations (n);

    /* setting the bound of route*/
    r.setGoal(map->getGoal());
    r.setStart(map->getStart());

    /* setting the attributes of route */
    r.setSize(n);
    r.setPoints(points);
    r.setGradients(gradients);
    r.setAccelerations(accelerations);

    /* setting the points */
    r.initRandomPoints();
    r.initRandomGradients();
    r.setPath(r.splines());


    cout << r.toString() << endl;
     cout << endl;
}

void Route::initRandomGradients(){
    if (gradients.size() < 1) return;
    gradients[0] = Point2D::getRandomPoint(0, 0, 3, 3);
    for(unsigned int i=1; i<gradients.size()-1; i++){
	Point2D *p = Point2D::getRandomPoint(0, 0, 3, 3);
	if ( ((*p) == (*start)) || ((*p) == (*goal))){
	    i--;
	    continue;
	}
	gradients[i] = p;
    }
    gradients[gradients.size()-1] = Point2D::getRandomPoint(0, 0, 3, 3);
    return;
}

void Route::initRandomPoints(){
    if (points.size() < 1) return;
    points[0] = start;
    for(unsigned int i=1; i<points.size()-1; i++){
	Point2D *p = Point2D::getRandomAbsPoint(start->x, start->y, goal->x, goal->y);
	if ( ((*p) == (*start)) || ((*p) == (*goal))){
	    i--;
	    continue;
	}
	points[i] = p;
    }
    points[points.size()-1] = goal;
    return;
}

// HERMITE SPLINES

void Route::printPath(){
    cout << "Route::printPath():\t\t";
    for(unsigned i=0; i< this->path.size(); i++){
	cout << this->path[i]->toString();
    }
    cout << endl;
}


vector <Point2D*> Route::splines()
{
    int n = this->points.size();
    vector <Point2D*> path;

    for (unsigned int i=0, j=1; i<n; i++, j=(i==n-1)?0:i+1 ) {

	Point2D p1 = Point2D();
	Point2D p2 = Point2D();

	Point2D g1 = Point2D();
	Point2D g2 = Point2D();

	p1 = *this->points[i];
	p2 = *this->points[j];

	g1 = *this->gradients[i];
	g2 = *this->gradients[j];

	Point2D a = (p1*2) - (p2*2) + g1 + g2;
	Point2D b = (p2*3) - (p1*3) - (g1*2) - g2;
	Point2D c = g1*1;
	Point2D d = p1*1;

	/*
	cout << "Route::Splines: Coefficients: ";
	cout << a.ToString();
	cout << b.ToString();
	cout << c.ToString();
	cout << d.ToString();
	cout << endl;
	*/

	
	Point2D p  = Point2D(p1.x, p1.y);
	
	for (float t = 0; t <= 1; t+=0.00001) {

	    int x = pow(t,3)*a.x + pow(t, 2)*b.x + t*c.x + d.x;
	    int y = pow(t,3)*a.y + pow(t, 2)*b.y + t*c.y + d.y;
	    
	    if(!(p.getX() == x && p.getY() == y)){
		Point2D *point = new Point2D(x, y);
		path.push_back(point);
	    }
	
	    p.setX(x);
	    p.setY(y);
	   
	   
	}
    }

    return path;
}

