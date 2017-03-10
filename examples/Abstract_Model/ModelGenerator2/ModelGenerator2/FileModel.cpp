
//FileModel.cpp

#include"FileModel.h"
#include <vector>

FileModel::FileModel() : lines(){}
FileModel::~FileModel(){}


void FileModel::addLine(const FileLine &line) { lines.push_back(line); }

void FileModel::addagent(const std::string name){ AllAgent.push_back(name); }

std::vector<std::string> FileModel::getUniqueAgents(){
	return AllAgent;

}


bool FileModel::isMasterAgent(std::string agent_name){
	bool x = false;
	FileAgent agent(agent_name);
	FileAgent s(agent_name);
	FileLine l;
	unsigned size = lines.size();
	for (unsigned i = 0; i < size; i++){
		l = lines[i];
		s = l.getMaster();
			if ( s== agent){ cout << "true"; x = true; goto LL; }
	}

LL:return x;
}

bool FileModel::isSlaveAgent(std::string agent_name){

	bool x = false;
	FileAgent agent(agent_name);
	std::vector<FileAgent> s;
	FileLine l;
	unsigned size = lines.size();
	for (unsigned i = 0; i < size; i++){
		l = lines[i];
		s = l.getSlaves();
		unsigned size = s.size();
		for (unsigned i = 0; i<size; i++){

			if (s[i] == agent){ cout << "true"; x = true; goto LL; }

		}


	}

LL:return x;
}

bool FileModel::isCombinedAgent(std::string agent_name){

	bool x = false;
	FileAgent agent(agent_name);
	std::vector<FileAgent> s;
	FileLine l;
	unsigned size = lines.size();
	for (unsigned i = 0; i < size; i++){
		l = lines[i];
		s = l.getCombined();
		unsigned size = s.size();
		for (unsigned i = 0; i<size; i++){

			if (s[i] == agent){ cout << "true"; x = true; goto LL; }

		}


	}
	
	LL:return x;
}

const FileAgent FileModel::getMaster(std::string slave)const{
	
	FileAgent agent(slave);
	FileAgent master(slave);
	std::vector<FileAgent> s;
	FileLine l;
	unsigned size = lines.size();
	for (unsigned i = 0; i < size; i++){
		l = lines[i];
	 s=l.getSlaves();
	 unsigned size = s.size();
	 for (unsigned i = 0; i<size; i++){

		 if (s[i] == agent) master=l.getMaster();

	 }
		

	}
	return master;
}
std::vector<FileLine> FileModel::getlines(){

	return lines;
}



