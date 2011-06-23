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
    position = this->population[index].getPosition();
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

    // Particle propierties
    T v = T(); /* current velocity */
    T p = T(); /* best position of particle */
    T x = T(); /* current position */
    T g = T(); /* global best position */

    float rhop = (float)rand()/(float)RAND_MAX;
    float rhog = (float)rand()/(float)RAND_MAX;

//    rhop = (rhop < 0) ? rhop : -1*rhop;
//    rhog = (rhog < 0) ? rhog : -1*rhog;

	v = particle.getVelocity();
	p = particle.getBestPosition();
	x = particle.getPosition();
	g = this->population[this->getBestParticleIndex()].getBestPosition();

	/* Setting particle return value for descomposition */
	T w = T();
	//w = v + (p-x)*rhop + (g-x)*rhog;

	/*
	cout << "Swarm<T>::updateParticleVelocity(): rhop = " << rhop << endl;
	cout << "Swarm<T>::updateParticleVelocity(): rhog = " << rhog << endl;
	cout << "Swarm<T>::updateParticleVelocity(): v = " << endl << v.toString() << endl;
	cout << "Swarm<T>::updateParticleVelocity(): p = " << endl << p.toString() << endl;
	cout << "Swarm<T>::updateParticleVelocity(): g = " << endl << g.toString() << endl;
	cout << "Swarm<T>::updateParticleVelocity(): x = " << endl << x.toString() << endl;
	*/
	w = v*0 + (p-x)*rhop + (g-x)*rhog;

	//cout << "Swarm<T>::updateParticleVelocity(): w.toString():" << endl;
	//cout << w.toString() << endl;

    /* updating the velocity of particle */
    particle.setVelocity(w);

    return;
}

/* Concrete Methods */
template <class T> void Swarm<T>::initialize(){

    cout << "Swarm::initialize(): inicializando particulas..." << endl;

    //inicializar cada particula de la poblacion
    for(unsigned int i=0; i < this->population.size(); i++){

        cout << "Swarm::initialize(): inicializando la particula: " << i << endl;

        Particle<T> &p = this->population[i];

        /* Particle Initialization */
        T position = T();
        T velocity = T();
        float fitness;

        /* Particle inictializacion of position and velocity */
        this->evaluateInitPosition(position);
        this->evaluateInitVelocity(velocity);

        /* Fitness evaluation*/
        fitness = this->evaluateFitness(position);

        p.setPosition(position);
        p.setVelocity(velocity);
        p.setFitness(fitness);

        p.setBestPosition(position);
        p.setBestVelocity(velocity);
        p.setBestFitness(fitness);

        cout << "Swarm::initialize(): particula " << i << ", fitness: "<< p.getFitness() << endl;

		cout << "Swarm::initialize(): data:" << endl;
		cout << p.toString() << endl;

        //actualizar la mejor solucion conocida
        if(fitness <= this->fitness) {
            //actualizar la mejor solucion de la poblacion
            this->setFitness(fitness);
            this->bestParticleIndex = i;
        }
    }

}



template <class T> void Swarm<T>::iterate()
{
	//criterio de parada: numero de iteraciones.
	int iteration = 0;

	while (iteration < this->iterations)
	{
		// debug
		cout << "Swarm::iterate(): iteracion " << iteration << " ";

		// para cada partícula, hacer:
		for (unsigned int i = 0; i < this -> population.size(); i++) {

			//cout << "Swarm::iterate(): iterando sobre particula " << i << endl;

			Particle<T> &p = this -> population[i];

			T position = T();
			T bestVelocity = T();
			float particleFitness;

			position = p.getPosition();
			bestVelocity = p.getBestVelocity();

			this->updateParticleVelocity(p);
			p.updatePosition();

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
				this->setFitness(particleFitness);
				this->setBestParticleIndex(i);
			}
		}

		//debug
		cout << "mejor particula: " << this->getBestParticleIndex() << " mejor fitness: " << this->fitness << endl;

		//next iteration
		iteration++;
	}
}




#endif	/* SWARM_TEMPLATE_H */

