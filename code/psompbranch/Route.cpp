/*
 * File:   Route.cpp
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 2:02
 */

#include "Route.h"

Route::Route() {

	Config &config = Config::getInstance();
    Map *map = config.getMap();

    this->length = 0;
    this->size = 0;
    this->start = map->getStart();
    this->goal = map->getGoal();
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
    //this->size = points.size();
    this->points = points;
}
vector<Point2D*> Route::getPoints() const {
    return points;
}
void Route::setPath(vector<Point2D*> path) {
    //this->length = path.size();
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

// suma de una ruta para hoy
Route Route::operator+(const Route &b){
    // sumar los puntos
    // sumar las gradientes
    // recalcular el path
    Route tmp = Route();
    Config &config = Config::getInstance();
    Map* map = config.getMap();
    int base = config.getHermiteBase();

    int width = map->getWidth() -1;
    int height = map->getHeight() -1;

    int n = size;

    vector <Point2D*> tmppoints;
    vector <Point2D*> tmpgradients;
    vector <Point2D*> tmpaccelerations ;

    int size_b = b.getSize();
    if (size_b != size ) return tmp;

    // updating points
    tmppoints.push_back(start);
    for(unsigned int i=1; i < n-1 ; i++){
	Point2D r = Point2D();
	r = (*points[i]) + (*b.points[i]);
	Point2D *s = new Point2D(r.x, r.y);
	s->setToBound(0, 0, width, height); /* fitting into bound map */
	tmppoints.push_back(s);
    }
    tmppoints.push_back(goal);


    // updating velocity
    for(unsigned int i=0; i < n; i++){
	Point2D r = Point2D();
	r = (*gradients[i]) + (*b.gradients[i]);
	Point2D *s = new Point2D(r.x, r.y);
	tmpgradients.push_back(s);
    }

        /* setting the attributes of route */
    tmp.setLength(length);
    tmp.setStart(start);
    tmp.setGoal(goal);
    tmp.setSize(n);
    tmp.setPoints(tmppoints);
    tmp.setGradients(tmpgradients);
    tmp.setAccelerations(tmpaccelerations);

    tmp.setPath(tmp.HermiteSplines());
    tmp.setLength(tmp.getPath().size());
    //cout << tmp.toString() << endl;
    return tmp;

    // TODO: updating acceleration

}
// resta de una ruta para hoy
Route Route::operator-(const Route &b){
    // sumar los puntos
    // sumar las gradientes
    // recalcular el path
	Route tmp = Route();
	int n = size;
	Config &config = Config::getInstance();
	Map* map = config.getMap();
	int base = config.getHermiteBase();

	vector <Point2D*> tmppoints;
	vector <Point2D*> tmpgradients;
	vector <Point2D*> tmpaccelerations;

	int size_b = b.getSize();
	if (size_b != size ) return tmp;


	// updating points
	tmppoints.push_back(start);
	for(unsigned int i=1; i < n-1 ; i++){

	    Point2D r = Point2D();
	    r = (*points[i]) - (*b.points[i]);
	    Point2D *s = new Point2D(r.x, r.y);
	    s->setToBound(0, 0, map->getWidth()-1, map->getHeight()-1);
	    tmppoints.push_back(s);
	}

	tmppoints.push_back(goal);

	//updating velocity
	for(unsigned int i=0; i < n; i++){
	    Point2D r = Point2D();
	    r = (*gradients[i]) - (*b.gradients[i]);
	    r.scaleTo(base);
	    Point2D *s = new Point2D(r.x, r.y);
	    tmpgradients.push_back(s);
	}

	/* setting the attributes of route */

	tmp.setLength(length);
	tmp.setStart(start);
	tmp.setGoal(goal);
	tmp.setSize(n);
	tmp.setPoints(tmppoints);
	tmp.setGradients(tmpgradients);
	tmp.setAccelerations(tmpaccelerations);

	//tmp.setPath(tmp.HermiteSplines());

	//setear path dependiendo del parametro de entrada
    if(config.getMode() == "hermite"){
		tmp.setPath(tmp.HermiteSplines());
	}
	if(config.getMode() == "b"){
		tmp.setPath(tmp.BSplines());
	}
	if(config.getMode() == "bezier"){
		tmp.setPath(tmp.BezierSplines());
	}
	if(config.getMode() == "catmull"){
		//r.setPath(r.CatmullSplines());
		tmp.setPath(tmp.HermiteSplines());
	}

	tmp.setLength(tmp.getPath().size());

	//cout << tmp.toString() << endl;

	return tmp;

	// TODO: updating acceleration

}

Route Route::operator*(float m){
    /*
     * Operator overload multiplies m by each point of route and gradients
     */

    Route tmp = Route();

    vector <Point2D*> tmppoints;
    vector <Point2D*> tmpgradients;
    vector <Point2D*> tmpaccelerations ;

    for(unsigned int i=0; i < size; i++){
	Point2D q = Point2D();
	q = (*points[i])*m;
	Point2D *s = new Point2D(q.x, q.y);
	tmppoints.push_back(s);
    }

    for(unsigned int i=0; i < size; i++){
	Point2D q = Point2D();
	q = (*gradients[i])*m;
	Point2D *s = new Point2D(q.x, q.y);
	tmpgradients.push_back(s);
    }

    tmp.setLength(length);
    tmp.setStart(start);
    tmp.setGoal(goal);
    tmp.setSize(size);
    tmp.setPoints(tmppoints);
    tmp.setGradients(tmpgradients);
    tmp.setAccelerations(tmpaccelerations);

    tmp.setPath(tmp.HermiteSplines());
    tmp.setLength(tmp.getPath().size());

    return tmp;

}


void Route::operator!(){
    cout << this->toString() << endl;
    this->printPath();
}
string Route::toString(){
    std::ostringstream ss;

	//ss << "Route::toString Size:\t\t" << this->size << endl;

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
    /*
    ss << "Route::toString Length:\t\t" << this->length << endl;

	ss << "Route::toString Path:\t\t";
	for(unsigned i=0; i< this->path.size(); i++){
	ss << this->path[i]->toString();
	if (i % 10 == 0 && i > 0)
		ss << endl << "\t\t\t\t";
	}
	*/

    std::string o = ss.str();

    return o;
}

void Route::printPath(){
    Config &config = Config::getInstance();
    Map* map = config.getMap();
    vector < Point2D* > obstacles = map->getObstacles();
    
    int width = config.getMap()->getWidth();
    int height = config.getMap()->getHeight();

    vector < vector <int> > matrix = vector < vector <int> > (height);

    for(unsigned int i = 0; i < width; i++){
	matrix[i] = vector <int> (height);
	for(unsigned int j = 0; j < height; j++){
	    matrix[i][j] = 0;
	}
    }

    for(unsigned int i=0; i< path.size(); i++){
	Point2D *p = path[i];
	 matrix[p->x % width ][p->y % height] = 1;

    }

    for(unsigned int i=0; i< obstacles.size(); i++){
	Point2D *p = obstacles[i];
	 matrix[p->x][p->y] = -2;

    }

    for(unsigned int i=0; i< points.size(); i++){
	Point2D *p = points[i];
	 matrix[p->x % width ][p->y % height] = i+2;
    }

    for(unsigned int i = 0; i < width; i++){
	cout << "\t\t\t\t";
	for(unsigned int j = 0 ; j < height; j++){

	    if(matrix[i][j] > 1){
		cout << matrix[i][j]-2;
		continue;
	    }

	    if(matrix[i][j] < -1) {
		cout << "X";
		continue;
	    }

	    if( matrix[i][j] == 1){
		cout << "." ;
		continue;
	    }

	    if(i == width -1 || i == 0){
		cout << "-";
		continue;
	    }

	    if(j == height -1|| j == 0){
		cout << "|";
		continue;
	    }


	    cout << " ";


	}

	cout << endl;
    }

}

float Route::fitnessEvaluation(Route &r){

	Config &config = Config::getInstance();
	Map *map = config.getMap();
	float alpha = config.getAlpha();


	float fitness;

	int overlaps = 0;
	float length = r.getPath().size();

	/* Getting the collission*/
	//TODO: pregunta: porque no "r.getPath().size()" sea length?
	// es lo mismo :D, es solo notación de código (para que sea más leíble, anuque cuesta más mantenerlo)

	for(unsigned i = 0; i < r.getPath().size(); i++){
		Point2D *p = r.getPath().at(i);
		//cout << "analizando punto " << i << " = " << p->toString() << endl;
		overlaps+=map->getCollision(*p);
	}

	//fitness = length - pow(overlaps, 20); //WTF????????????, no era asi la FO que dije
	fitness = length + overlaps*(1+pow(length, alpha));
	//fitness = length + pow(overlaps, 10);

	//cout << "overlaps ... " << overlaps  << endl;
	//cout << "Route::fitnessEvaluation sqrt(length): " << r.getPath().size() << endl;
	return fitness;
}


void Route::initRandomVelocity(Route &r){

    Config &config = Config::getInstance();
    int n = config.getPivots()+2;
    Map *map = config.getMap();

    /* points, gradients, accelerations casting */
    vector <Point2D*> points (n);
    vector <Point2D*> gradients (n);
    vector <Point2D*> accelerations (n);

    /* setting the bound of route*/
    //r.setGoal(map->getGoal());
    //r.setStart(map->getStart());

    /* setting the attributes of route */
    r.setSize(n);
    r.setPoints(points);
    r.setGradients(gradients);
    r.setAccelerations(accelerations);

    /* setting the points */
    r.initRandomPoints();
    r.initRandomGradients();
    r.setPath(r.BezierSplines());

//    cout << "Route::initRandomVelocity: " << endl;
//    cout << r.toString() << endl;

}

void Route::initRandomRoute(Route& r){

    Config &config = Config::getInstance();
    //es el numero de pivotes+2 (start y goal)
    int n = config.getPivots()+2;
    Map *map = config.getMap();

    /* points, gradients, accelerations casting */
    vector <Point2D*> points (n);
    vector <Point2D*> gradients (n);
    vector <Point2D*> accelerations (n);

    /* setting the bound of route*/
    //r.setStart(map->getStart());
    //r.setGoal(map->getGoal());

    /* setting the attributes of route */
    r.setSize(n);
    r.setPoints(points);
    r.setGradients(gradients);
    r.setAccelerations(accelerations);

    /* setting the points */
    r.initRandomPoints();
    r.initRandomGradients();

    //setear path dependiendo del parametro de entrada
    if(config.getMode() == "hermite"){
		r.setPath(r.HermiteSplines());
	}
	if(config.getMode() == "b"){
		r.setPath(r.BSplines());
	}
	if(config.getMode() == "bezier"){
		r.setPath(r.BezierSplines());
	}
	if(config.getMode() == "catmull"){
		//r.setPath(r.CatmullSplines());
		r.setPath(r.HermiteSplines());
	}

    r.setLength(r.getPath().size());

	//cout << "Route::initRandomRoute: " << endl;
    //cout << r.toString() << endl;
    //r.printPath();
    return;
}

void Route::initRandomGradients(){
	Config &config = Config::getInstance();
    int base = config.getHermiteBase();

    if (gradients.size() < 1) return;
    gradients[0] = Point2D::getRandomPoint(-1, -1, 1, 1);
    for(unsigned int i=1; i<gradients.size()-1; i++){
            Point2D* p = Point2D::getRandomPoint(-1*base, -1*base, base, base);
            p->scaleTo(base);
            gradients[i] = p;
    }
    gradients[gradients.size()-1] = Point2D::getRandomPoint(-1, -1, 1, 1);
    return;
}

void Route::initRandomPoints(){
    if (points.size() < 1) return;

    Config &config = Config::getInstance();
    Map *map = config.getMap();

    points[0] = start;
    for(unsigned int i=1; i<points.size()-1; i++){
	// [TODO] tienen que ser el principio y el final del mapa
	Point2D *p = Point2D::getRandomAbsPoint(0, 0, map->getWidth(), map->getHeight());
	if ( ((*p) == (*start)) || ((*p) == (*goal))){
	    i--;
	    continue;
	}
	points[i] = p;
    }

    points[points.size()-1] = goal;
    return;
}


vector <Point2D*> Route::BezierSplines(){
/*
 * Bezier splines:
 * Bezier splines are used to approach the convex hull propierty of solution.
 * This approximation does not require the gradient vector.
 *
 */
    Config &config = Config::getInstance();
    Map *map = config.getMap();

    int n = this->points.size();
    vector <Point2D*> path;
    vector <Point2D*> tmp;

    //agregar start
    //tmp.push_back(this->start);
    for(unsigned int l, k=0; l <= n/3 ; k+=3, l++){
	Point2D q0 = Point2D();
	Point2D q1 = Point2D();
	Point2D q2 = Point2D();
	Point2D q3 = Point2D();



	q0 = *this->points[k];
	q1 = *this->points[k+1];
	q2 = *this->points[k+2];
	q3 = *this->points[k+3];

	/*
	 * The matrix G =
	 *
	 *     | -1  3 -3  1  |
	 * 1/6*|  3 -6  3  0  |
	 *     | -3  3  0  0  |
	 *     |  1  0  0  0  |
	 *
	 * This interpolation does not ensures
	 * the connection between the start and goal
	 * points. For do this is neccesary to calculate
	 * a line to this points completing the curve.
	 */

	Point2D a = q1*3 - q0*1 - q2*3 + q3*1;
	Point2D b = q0*3 - q1*6 + q2*3;
	Point2D c = q1*3 - q0*3;
	Point2D d = q0*1;

	for(float t=0; t <= 1; t+=0.0001){

	    float xf = (pow(t,3)*a.x + pow(t, 2)*b.x + t*c.x + d.x);
	    float yf = (pow(t,3)*a.y + pow(t, 2)*b.y + t*c.y + d.y);

	    /* El crimen mas grande de la historia*/
	    int x = xf;
	    int y = yf;

	    Point2D* p = new Point2D(x, y);
	    tmp.push_back(p);
	}

    }

    return tmp;
}



vector <Point2D*> Route::BSplines(){
/*
 * Bsplines:
 * B splines are used to maintain convex hull propierty of solution.
 * This approximation does not require the gradient vector.
 *
 */
    Config &config = Config::getInstance();
    Map *map = config.getMap();

    int n = this->points.size();
    vector <Point2D*> line;
    vector <Point2D*> tmp;

    //agregar start
    //tmp.push_back(this->start);

    /*
     * In BSplines, the union of goal and start point
     * with the approximated cruve is not explicit,
     * is by that reason that whe need to join the segments
     * by a line.
     */


    for(unsigned int k=1; k <= n-2; k++){
    //for(unsigned int l = 0, k=1; l <= n/3 ; k+=3, l++){
	Point2D q0 = Point2D();
	Point2D q1 = Point2D();
	Point2D q2 = Point2D();
	Point2D q3 = Point2D();

	q0 = *this->points[k-1];
	q1 = *this->points[k];
	q2 = *this->points[k+1];
	q3 = *this->points[k+2];

	/*
	 * The matrix G =
	 *
	 *     | -1  3 -3  1  |
	 * 1/6*|  3 -6  3  0  |
	 *     | -3  0  3  0  |
	 *     |  1  4  1  0  |
	 *
	 * This interpolation does not ensures
	 * the connection between the start and goal
	 * points. For do this is neccesary to calculate
	 * a line to this points completing the curve.
	 */

	Point2D a = q1*3 - q0*1 - q2*3 + q3*1;
	Point2D b = q0*3 - q1*6 + q2*3;
	Point2D c = q2*3 - q0*3;
	Point2D d = q0*1 + q1*4 + q2*1;

	for(float t=0; t <= 1; t+=0.0001){

	    float xf = (pow(t,3)*a.x + pow(t, 2)*b.x + t*c.x + d.x);
	    float yf = (pow(t,3)*a.y + pow(t, 2)*b.y + t*c.y + d.y);

	    xf/=6;
	    yf/=6;

	    int x = xf;
	    int y = yf;

	    Point2D* p = new Point2D(x, y);
	    tmp.push_back(p);
	}

    }

    // get the last element in Point2D *end;
    // get the goal element in goal;
    // construct a rect between this two points

    int m = tmp.size();

    Point2D p0 = Point2D();
    Point2D p1 = Point2D();

    Point2D p2 = Point2D();
    Point2D p3 = Point2D();

    p0 = *(this->start);
    p1 = *(tmp[0]);

    Point2D as = p1*1 - p0*1;
    Point2D bs = p0*1;

    for(float t=0; t <= 1; t+=0.0001){
	float xf = t*as.x + bs.x;
	float yf = t*as.y + bs.y;

	int x = xf;
	int y = yf;

	Point2D* p = new Point2D(x, y);
	line.insert(line.begin(), p);
    }

    for(unsigned int i = 0; i < line.size(); i++){
	tmp.insert(tmp.begin(), line[i]);
    }


    p2 = *(this->goal);;
    p3 = *(tmp[m]);


    Point2D ag = p3*1 - p2*1 ;
    Point2D bg = p2*1;

    for(float t=0; t <= 1; t+=0.0001){
	float xf = t*ag.x + bg.x;
	float yf = t*ag.y + bg.y;

	int x = xf;
	int y = yf;
	Point2D* p = new Point2D(x, y);
	//tmp.push_back(p);
    }

    return tmp;
}


vector <Point2D*> Route::HermiteSplines()
{
/* HERMITE SPLINES:
 * This splines requieres a random gradient vector for build a curve
 * interpolating the control points.
 *
 * His general form is [x,y] = [t^3 t^2 t 1] [M][G]
 * where M is a 4x4 matrix with constants coefficients,
 * and G is a [x1 y1; x2 y2; x1' y1'; x2' y2']^T 4x2 matrix.
 */
    //map needed for bound overflow verification
    Config &config = Config::getInstance();
    Map *map = config.getMap();

    int n = this->points.size();
    vector <Point2D*> path;
    vector <Point2D*> tmp;

	//agregar start
	tmp.push_back(this->start);

    /* aqui está la cuestion...: 1->2; 2->3; 3->4;  */
    for (unsigned int i=0, j=i+1; i<n-1; i++, j=i+1 ) {

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

	for (float t = 0; t <= 1; t+=0.001)
	{

	    float xf = pow(t,3)*a.x + pow(t, 2)*b.x + t*c.x + d.x;
	    float yf = pow(t,3)*a.y + pow(t, 2)*b.y + t*c.y + d.y;

	    int x = xf;
	    int y = yf;

	    x = (x < 0) ? 0 : ( (x >= map->getWidth()) ? map->getWidth()-1 : x );
	    y = (y < 0) ? 0 : ( (y >= map->getHeight()) ? map->getHeight()-1 : y);

	    // p = a*pow(t,3) + b*pow(t, 2)+ c*t + d;
	    Point2D *point = new Point2D(x, y);
	    tmp.push_back(point);
	}
    }

    Point2D *t = new Point2D(-1,-1);

    for(unsigned int i = 0; i < tmp.size(); i++){
	if ( !((*tmp[i]) == (*t))){
	    path.push_back(tmp[i]);
	    t = tmp[i];
	}
    }

	//slice
	for(unsigned int i=0; i<path.size(); i++){
		for(unsigned int j=i+1; j<path.size(); j++){
			if( *(path[i]) == *(path[j]) ){
				//this->slice(&path);
			}
		}
	}

    return path;
}

void Route::slice(vector<Point2D*> *ruta){
	//obtener los indices
    unsigned int indice_inicial = 0;
    unsigned int indice_final = 0;

//    cout << "Route::slice(): ruta->at(" << 0 << ") = " << ruta->at(0)->toString() << endl;

    for(unsigned int i = 0; i < ruta->size(); i++){
	indice_inicial = i;
	Point2D* valor_a_buscar = ruta->at(i);

	for(unsigned int j=ruta->size()-1; j>0; j--){
	    if( (j != i) && (*(ruta->at(j)) == *valor_a_buscar) ){
		indice_final = j;
		break;
	    }
	}

	if(indice_final != 0){
	    break;
	}
    }

    //debug
//    cout << "Route::slice(): indice_inicial = " << indice_inicial << endl;
//    cout << "Route::slice(): indice_final = " << indice_final << endl;
//
//    cout << "Route::slice(): ruta->at(" << indice_inicial << ") = " << ruta->at(indice_inicial)->toString() << endl;
//    cout << "Route::slice(): ruta->at(" << indice_final << ") = " << ruta->at(indice_final)->toString() << endl;

    vector<Point2D*> f;

    for(unsigned int i = 0; i < ruta->size(); i++){
	if( (indice_inicial < i) && (i <= indice_final) ){
	    continue;
	}
	f.push_back(ruta->at(i));
    }

    *ruta = f;
}
