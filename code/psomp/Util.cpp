#include "Util.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

Util::Util() {
}

Util::~Util() {
}

int Util::getRandomInt(int max){
	return rand()%max + 1;
}
