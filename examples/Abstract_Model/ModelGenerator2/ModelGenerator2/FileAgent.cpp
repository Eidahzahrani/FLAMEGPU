//flieAgent




#include"FileAgent.h"


FileAgent::FileAgent(std::string name){ this->name = name; }
FileAgent::~FileAgent(){}

std::string FileAgent::getName(){
	return name;
}
bool  operator== (const  FileAgent &agent1, const FileAgent &agent2)
{
	
	return (agent1.name == agent2.name);
}
 ostream &operator<<(ostream &output, const FileAgent &D) {
	output << D.name;
	return output;
}