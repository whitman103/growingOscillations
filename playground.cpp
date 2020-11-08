#include <iostream>
#include <chrono>
#include <fstream>

#include <boost/random/mersenne_twister.hpp>
boost::mt19937 generator;

#include "growthFunctions.h"

using namespace std;

int main(){
	generator.seed(time(NULL));

	return 0;
}
