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

	

	Community firstCommunity(7);

    int time(0);


    ofstream outPlot("SIRPlotBase.txt");

    int numOfStates(3);

    do{
		vector<int> currentStateCount(3,0);
		for(int i=0;i<(int)firstCommunity.communityList.size();i++){
			vector<int> communityStateCount=basicInfectionStep(firstCommunity.communityList[i],time,generator);
			transform(currentStateCount.begin(),currentStateCount.end(),communityStateCount.begin(),currentStateCount.begin(),plus<int>());
		}

        //firstCommunity.updateConnections(2+time/30.);

        outPlot<<time<<" ";
        for(int i=0;i<(int)currentStateCount.size();i++){
            outPlot<<currentStateCount[i]<<" ";
        }
        outPlot<<endl;
        time++;
    }while(time<100);

    outPlot.close();
    return 0;
}