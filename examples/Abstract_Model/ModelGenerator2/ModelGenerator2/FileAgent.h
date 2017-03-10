
//FileAgent

#ifndef FILEAGENT_H_
#define FILEAGENT_H_

#include<string>
#include<iostream>

using namespace std;
class FileAgent{
	
public:
	FileAgent(std::string name);
	virtual ~FileAgent();
	std::string getName();
	friend bool operator== (const FileAgent &agent1, const FileAgent &agent2 );
	
	friend ostream &operator<<(ostream &output, const FileAgent &D);
	//std::string operator= ( const FileAgent &agent);
private:
	std::string name;
};

#endif