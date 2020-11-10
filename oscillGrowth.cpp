#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <chrono>

#include <boost/random/mersenne_twister.hpp>
	boost::mt19937 generator;

#include "growthFunctions.h"

using namespace std;


int main(){
    generator.seed(time(NULL));

	
	vector<string> plotBases={"Base","Slow","Medium","Fast"};
	vector<double> muDivisors={3000.,60.,45.,25};
	int numOfSimulations(plotBases.size());

	for(int sim=0;sim<numOfSimulations;sim++){


		Community firstCommunity(7);

		


		ofstream outPlot("SIRPlot"+plotBases[sim]+".txt");
		

		int numOfStates(3);
		int time(0);
		do{
			vector<int> currentStateCount(3,0);
			for(int i=0;i<(int)firstCommunity.communityList.size();i++){
				vector<int> communityStateCount=basicInfectionStep(firstCommunity.communityList[i],time,generator);
				transform(currentStateCount.begin(),currentStateCount.end(),communityStateCount.begin(),currentStateCount.begin(),plus<int>());
			}

			if(time<100){
				firstCommunity.updateConnections(2.+(double)time/muDivisors[sim]);
			}

			outPlot<<time<<" ";
			for(int i=0;i<(int)currentStateCount.size();i++){
				outPlot<<currentStateCount[i]<<" ";
			}
			outPlot<<endl;
			time++;
		}while(time<150);

		outPlot.close();

	}
    return 0;
}