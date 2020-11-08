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

vector<int> testDivisions(double mu){
	const int N(100);
	int nLevels(floor(2*mu-1));
	vector<int> connectionNum(N,0);
	int interNumber(N/nLevels);
	for(int i=0;i<nLevels;i++){
		for(int j=0;j<interNumber;j++){
			connectionNum[i*interNumber+j]=i+1;
		}
	}
	for(int i=(nLevels-1)*interNumber;i<connectionNum.size();i++){
		if(connectionNum[i]==0){
			connectionNum[i]=nLevels;
		}
	}
	return connectionNum;
}