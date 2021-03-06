#ifndef GROWTHFUNCTIONS_H
#define GROWTHFUNCTIONS_H

#include <vector>
#include <tuple>
#include <boost/random/mersenne_twister.hpp>

double randPull(boost::mt19937& generator);
int randSite(boost::mt19937& generator, int size);


typedef struct{
    std::vector<std::tuple<int,double> > connections;
    int state;
    int recoveryTime;
	int resusTime;
} Agent;

class Community{

	public:
	Community(int numberOfCommunities);
	std::vector<std::vector<Agent> > communityList;
	void updateConnections(double mu);
	void updateAgentConnectionList(int currentGroup,std::vector<int> newDivisions);

	private:

};

std::vector<int> basicInfectionStep(std::vector<Agent>& inAgents,int time,boost::mt19937& generator);

std::vector<int> testDivisions(double mu, int agentListLength);



#endif