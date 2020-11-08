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

	vector<vector<Agent> > communityList;

	const int numOfCommunities(7);

	for(int j=0;j<numOfCommunities;j++){

		int agentNumber(1000);
		vector<Agent> agentList(agentNumber);

		int initialDegree(2);

		for(int i=0;i<(int)agentList.size();i++){
			for(int j=0;j<initialDegree;j++){
				int target(randSite(generator,agentList.size()));
				agentList[i].connections.push_back(make_tuple(target,1));
				agentList[target].connections.push_back(make_tuple(i,1));
				agentList[i].state=0;
			}
		}

		double initialInfection(0.01);
		int initialInfectedNumber(initialInfection*agentList.size());

		for(int i=0;i<initialInfectedNumber;i++){
			int infectionTarget(randSite(generator,agentList.size()));
			agentList[infectionTarget].state=1;
			agentList[infectionTarget].recoveryTime=1+randSite(generator,8);
		}

		communityList.push_back(agentList);
	}

    int time(0);


    ofstream outPlot("SIRPlot.txt");

    int numOfStates(3);

    do{
		vector<int> currentStateCount(3,0);
		for(int i=0;i<(int)communityList.size();i++){
			vector<int> communityStateCount=basicInfectionStep(communityList[i],time,generator);
			transform(currentStateCount.begin(),currentStateCount.end(),communityStateCount.begin(),currentStateCount.begin(),plus<int>());
		}
        

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