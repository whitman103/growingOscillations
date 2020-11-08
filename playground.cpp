#include <iostream>
#include <chrono>
#include <fstream>

#include <boost/random/mersenne_twister.hpp>
boost::mt19937 generator;

#include "growthFunctions.h"

using namespace std;

int main(){
	generator.seed(time(NULL));

	vector<int> oneTest=testDivisions(1);
	vector<int> fourTest=testDivisions(4);

	ofstream outTest("outTest.txt");

	for(int i=0;i<(int)oneTest.size();i++){
		outTest<<i<<" "<<oneTest[i]<<" "<<fourTest[i]<<endl;
	}
	outTest.close();


	return 0;
}
