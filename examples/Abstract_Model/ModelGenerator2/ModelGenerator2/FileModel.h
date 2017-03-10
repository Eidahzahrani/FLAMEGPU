
//FileMdel.h
#ifndef FILEMODEL_H_
#define FILEMODEL_H_


#include <string>
#include <map>
#include <memory>
#include <vector>
#include <typeinfo>


#include "FileLine.h"
#include "FileAgent.h"



class FileModel{
	
public:
	FileModel();

	virtual ~FileModel();
	void addLine(const FileLine &line);
	void addagent(const std::string);

	std::vector<FileLine> getlines();
	std::vector<std::string> getUniqueAgents();	//vector of agent names

	bool isMasterAgent(std::string agent_name);

	bool isSlaveAgent(std::string agent_name);

	bool isCombinedAgent(std::string agent_name);

	const FileAgent getMaster(std::string slave)const;

	//const FileLine& getLine(const int line_number) const;

private:
	std::vector<FileLine> lines;
	std::vector<std::string>AllAgent;
};

#endif /* FILEMODEL_H_ */