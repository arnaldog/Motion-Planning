
/*
 * File:   Swarm_Template.h
 * Author: alejandrasuarez
 *
 * Created on 3 de junio de 2011, 1:10
 */

#ifndef SWARM_TEMPLATE_H
#define	SWARM_TEMPLATE_H

#include "Swarm.h"

/*
 * Templating functions
 */
template <class T> Swarm<T>::Swarm(){
}

template <class T> Swarm<T>::Swarm(int size, int iterations, float fitness){
    this->size = size;
    this->iterations = iterations;
    this->fitness = fitness;
    this->population = vector < Particle<T> > (size);
}

template <class T> Swarm<T>::~Swarm(){

}
template <class T> void Swarm<T>::setBestParticleIndex(int bestParticleIndex) {
    this->bestParticleIndex = bestParticleIndex;
}
template <class T> int Swarm<T>::getBestParticleIndex() const {
    return bestParticleIndex;
}
template <class T> void Swarm<T>::setFitness(float fitness) {
    this->fitness = fitness;
}
template <class T> float Swarm<T>::getFitness() const {
    return fitness;
}
template <class T> void Swarm<T>::setIterations(int iterations) {
    this->iterations = iterations;
}
template <class T> int Swarm<T>::getIterations() const {
    return iterations;
}
template <class T> void Swarm<T>::setPopulation(vector< Particle<T> > population) {
    this->population = population;
}
template <class T> vector<Particle<T> > const& Swarm<T>::getPopulation() {
    return population;
}
template <class T> void Swarm<T>::setSize(int size) {
    this->size = size;
}
template <class T> int Swarm<T>::getSize() const {
    return size;
}

template <class T> Swarm<T>::Swarm(const Swarm& orig){

}

template <class T> void Swarm<T>::setFitnessFunction(float (T::*f)(T&)){
    this->fitnessFunction = f;
}

template <class T> float Swarm<T>::evaluateFitness(T &position){
    return ((position).*(this->fitnessFunction))(position);
}

/* Evaluation functions callers */
template <class T> void Swarm<T>::evaluateInitPosition(T &position){
    return ((position).*(this->initPositionFunction))(position);
}
template <class T> void Swarm<T>::evaluateInitVelocity(T &velocity){
    return ((velocity).*(this->initVelocityFunction))(velocity);
}

template <class T> void Swarm<T>::setParticleSize(int particleSize) {
    this->particleSize = particleSize;
}
template <class T> int Swarm<T>::getParticleSize() const {
    return particleSize;
}

template <class T> void Swarm<T>::setRhog(float rhog) {
    this->rhog = rhog;
}
template <class T> void Swarm<T>::setRhop(float rhop) {
    this->rhop = rhop;
}
template <class T> void Swarm<T>::setPhig(float phig) {
    this->phig = phig;
}
template <class T> void Swarm<T>::setPhip(float phip) {
    this->phip = phip;
}
template <class T> void Swarm<T>::setOmega(float omega) {
    this->omega = omega;
}

template <class T> void Swarm<T>::printBestParticle(){
	int index = this->bestParticleIndex;
	T position = T();
	position = this->population[index].getBestPosition();
	!position;
}

/* setters for initializer functions */
template <class T> void Swarm<T>::setInitPositionFunction(void (T::*f)(T&)){
    this->initPositionFunction = f;
}

template <class T> void Swarm<T>::setInitVelocityFunction(void (T::*f)(T&)){
    this->initVelocityFunction = f;
}


template <class T> void Swarm<T>::updateParticleVelocity(Particle<T> &particle){

    Config &config = Config::getInstance();
    float omega = config.getOmega();
    float phip = config.getPhi_p();
    float phig = config.getPhi_g();

    // Particle propierties
    T v = T(); /* current velocity */
    T p = T(); /* best position of particle */
    T x = T(); /* current position */
    T g = T(); /* global best position */

    float rhop = (float)rand()/(float)RAND_MAX;
    float rhog = (float)rand()/(float)RAND_MAX;
    float omeg = (float)rand()/(float)RAND_MAX;

    v = particle.getVelocity();
    p = particle.getBestPosition();
    x = particle.getPosition();
    g = this->population[this->getBestParticleIndex()].getBestPosition();

    /* Setting particle return value for descomposition */


//    cout << endl;
//    cout << "Posición inicial\t\t:";
//    cout << x.toString() << endl ;
//    cout << "Velocidad inicial\t\t:";
//    cout << v.toString() << endl ;


    T w = T();
    //T w1 = T();
    //T w2 = T();
    //T w3 = T();

	//cout << "Swarm<T>::updateParticleVelocity(): rhop = " << rhop << endl;
	//cout << "Swarm<T>::updateParticleVelocity(): rhog = " << rhog << endl;
	//cout << "Swarm<T>::updateParticleVelocity(): v = " << endl << v.toString() << endl;
	//cout << "Swarm<T>::updateParticleVelocity(): p = " << endl << p.toString() << endl;
	//cout << "Swarm<T>::updateParticleVelocity(): g = " << endl << g.toString() << endl;
	//cout << "Swarm<T>::updateParticleVelocity(): x = " << endl << x.toString() << endl;

	w = v*omega + (p-x)*(rhop*phip) + (g-x)*(rhog*phig);

	/*
	w1 = v*omega;
	cout << "Swarm<T>::updateParticleVelocity(): v*omega = \t\t" << endl;
	cout << w1.toString() << endl;

	w2 = (p-x)*(rhop*phip);
	cout << "Swarm<T>::updateParticleVelocity(): (p-x)*(rhop*phip) = " << endl;
	cout << w2.toString() << endl;

	w3 = (g-x)*(rhog*phig);
	cout << "Swarm<T>::updateParticleVelocity(): (g-x)*(rhog*phig) = " << endl;
	cout << w3.toString() << endl;

	cout << "Swarm<T>::updateParticleVelocity(): w.toString():" << endl;
	cout << w.toString() << endl;
	*/

    /* updating the velocity of particle */
    particle.setVelocity(w);

    return;
}

/* Concrete Methods */
template <class T> void Swarm<T>::initialize(){

    //cout << "Swarm::initialize(): inicializando particulas..." << endl;

	std::ostringstream ss;

	//debug informe CSV
    ss << "particle,fitness" << endl;

    //inicializar cada particula de la poblacion
    for(unsigned int i=0; i < this->population.size(); i++){

        //cout << "Swarm::initialize(): inicializando la particula: " << i << endl;

        Particle<T> &p = this->population[i];

        /* Particle Initialization */
        T position = T();
        T velocity = T();
        float fitness;

        /* Particle inictialization of position and velocity */
		//cout << "Swarm::initialize(): PRE evaluateInitPosition..." << endl;
        this->evaluateInitPosition(position);
        //cout << "Swarm::initialize(): POST evaluateInitPosition..." << endl;

        //cout << "Swarm::initialize(): PRE evaluateInitVelocity..." << endl;
        this->evaluateInitVelocity(velocity);
        //cout << "Swarm::initialize(): POST evaluateInitVelocity..." << endl;

        /* Fitness evaluation*/
        fitness = this->evaluateFitness(position);

        /* particle position, velocity and fitness setting*/
        p.setPosition(position);
        p.setVelocity(velocity);
        p.setFitness(fitness);

        p.setBestPosition(position);
        p.setBestVelocity(velocity);
        p.setBestFitness(fitness);

		//imprimir posicion
        //!position;

		//cout << "Swarm::initialize(): particula " << i << ", fitness: "<< p.getFitness() << endl;

		//debug para informe CSV
		ss << i << "," << p.getFitness() << endl;

		//cout << "Swarm::initialize(): data:" << endl;
		//cout << p.toString() << endl;

        //actualizar la mejor solucion conocida
        if(fitness < this->fitness) {
            //actualizar la mejor solucion de la poblacion
            this->setFitness(fitness);
            this->bestParticleIndex = i;
        }
    }

    string filename = "initialization";
    string input = ss.str();
    Config &config = Config::getInstance();
	config.writeCsv(filename, input);

}



template <class T> void Swarm<T>::iterate()
{
	//criterio de parada: numero de iteraciones.
	int iteration = 0;

	std::ostringstream ss;

	//debug informe CSV
    ss << "iteration,particle,fitness" << endl;

	while (iteration < this->iterations)
	{
		// para cada partícula, hacer:
		for (unsigned int i = 0; i < this -> population.size(); i++) {

			//cout << "Swarm::iterate(): iterando sobre particula " << i << endl;

			Particle<T> &p = this -> population[i];

			T position = T();
			position = p.getPosition();

			T bestVelocity = T();
			bestVelocity = p.getBestVelocity();

			//cout << "Swarm::iterate(): PRE updateParticleVelocity " << i << endl;
			this->updateParticleVelocity(p);
			//cout << "Swarm::iterate(): POST updateParticleVelocity " << i << endl;

			//cout << "Swarm::iterate(): PRE updatePosition" << i << endl;
			p.updatePosition();
			//cout << "Swarm::iterate(): POST updatePosition" << i << endl;

			float particleFitness;
			particleFitness = this->evaluateFitness(position);
			p.setFitness(particleFitness);

			//if (f(xi) < f(pi)) do:
			if (p.getFitness() < p.getBestFitness()) {
				p.setBestPosition(position);
				p.setBestVelocity(bestVelocity);
				p.setFitness(particleFitness);
			}

			//if (f(pi) < f(g)) update the swarm's best known position:
			//g ← pi
			if (particleFitness < this->fitness) {
				// cout << "Swarm::iterate: Updating best particle:" << i << endl;
				this->setFitness(particleFitness);
				this->setBestParticleIndex(i);
			}

			//debug
			//cout << "Swarm::iterate(): finalmente la particula en esta iteracion quedo como: " << endl;
			//cout << p.toString();
		}

		// debug
		//cout << "Swarm::iterate(): resumen de iteracion " << iteration << ":";
		//cout << " mejor particula: " << this->getBestParticleIndex();
		//cout << " mejor fitness: " << this->fitness << endl;

		//debug para informe CSV
		ss << iteration << ","  << this->getBestParticleIndex() << "," << this->fitness << endl;

		//next iteration
		iteration++;
	}

	string filename = "iteration";
    string input = ss.str();
    Config &config = Config::getInstance();
	config.writeCsv(filename, input);

}




#endif	/* SWARM_TEMPLATE_H */

