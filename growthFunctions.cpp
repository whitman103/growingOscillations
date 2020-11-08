#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include "growthFunctions.h"

using namespace std;
#include <boost/random/mersenne_twister.hpp>
extern boost::mt19937 generator;

int randSite(boost::mt19937& generator, int size){
    return generator()%size;
}

double randPull(boost::mt19937& generator){
    return (double)generator()/(double)generator.max();
}

Community::Community(int numOfCommunities){

	for(int j=0;j<numOfCommunities;j++){

		int agentNumber(1000);
		vector<Agent> agentList(agentNumber);

		int initialDegree(2);

		for(int i=0;i<(int)agentList.size();i++){
			for(int j=0;j<initialDegree;j++){
				int target(randSite(generator,agentList.size()));
				agentList[i].connections.push_back(make_tuple(target,1));
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

}


void Community::updateConnections(double mu){
	vector<int> newDivision=testDivisions(mu,communityList[0].size());
	for(int i=0;i<(int)communityList.size();i++){
		updateAgentConnectionList(i,newDivision);
	}
}

void Community::updateAgentConnectionList(int currentGroup, vector<int> newDivisions){
	for(int i=0;i<(int)communityList[currentGroup].size();i++){
		int updatedNumberOfConnections(newDivisions[i]);
		if(updatedNumberOfConnections!=communityList[currentGroup][i].connections.size()){
			while(updatedNumberOfConnections>communityList[currentGroup][i].connections.size()){
				int checkConnection(randSite(generator,communityList[currentGroup].size()));
				do{
					checkConnection=randSite(generator,communityList[currentGroup].size());
				}while(find_if(communityList[currentGroup][i].connections.begin(),communityList[currentGroup][i].connections.end(),[&checkConnection](const tuple<int,double>& test){return checkConnection==get<0>(test);})!=communityList[currentGroup][i].connections.end());
				
				communityList[currentGroup][i].connections.push_back(make_tuple(checkConnection,1.));
			}
			while(updatedNumberOfConnections<communityList[currentGroup][i].connections.size()){
				int removal(randSite(generator,communityList[currentGroup][i].connections.size()));
				communityList[currentGroup][i].connections.erase(communityList[currentGroup][i].connections.begin()+removal);
			}
		}
	}
}

vector<int> basicInfectionStep(vector<Agent>& agentList, int time, boost::mt19937& generator){
    vector<int> currentStateCount(3,0);
    double infectionProb(0.1);
    for(int i=0;i<(int)agentList.size();i++){
        currentStateCount[agentList[i].state]++;
        if(agentList[i].state==1){
            if(time>agentList[i].recoveryTime){
                agentList[i].state=2;
            }
            else{
                for(int j=0;j<(int)agentList[i].connections.size();j++){
                    int infectionTarget=get<0>(agentList[i].connections[j]);
                    if(agentList[infectionTarget].state==0){
                        if(randPull(generator)<infectionProb){
                            agentList[infectionTarget].state=1;
                            agentList[infectionTarget].recoveryTime=time+1+randSite(generator,8);
                        }
                    }
                }
            }
        }
    }
    return currentStateCount;
}

vector<int> testDivisions(double mu, int agentListLength){
	int nLevels(floor(2*mu-1));
	vector<int> connectionNum(agentListLength,0);
	int interNumber(connectionNum.size()/nLevels);
	for(int i=0;i<nLevels;i++){
		for(int j=0;j<interNumber;j++){
			connectionNum[i*interNumber+j]=i+2;
		}
	}
	for(int i=(nLevels-1)*interNumber;i<connectionNum.size();i++){
		if(connectionNum[i]==0){
			connectionNum[i]=nLevels+2;
		}
	}
	return connectionNum;
}