
//FileLine
#include"FileLine.h"
#include"FileAgent.h"
#include<string>


FileLine::FileLine() :input_agents(), output_agents(), master("name"){}
FileLine::~FileLine(){}



void FileLine::addSlaves(const FileAgent& agent){
	input_agents.push_back(agent);

}

void FileLine::addCombind(const FileAgent& agent){
	output_agents.push_back(agent);
}

void FileLine::addMaster(const FileAgent& agent){
	master = agent;
}


//return any slave agents in the line (every agent except for first and last)
const std::vector<FileAgent> FileLine::getSlaves() {
	return input_agents;
}

// return the first item in the line
const FileAgent& FileLine::getMaster(){
	return master;
}

//return the last item in the line
const std::vector<FileAgent> FileLine::getCombined(){
	return output_agents;
}