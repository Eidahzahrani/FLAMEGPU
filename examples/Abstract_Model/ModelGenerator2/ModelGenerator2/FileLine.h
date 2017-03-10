
//FileLine.h

#ifndef FILELINE_H_
#define FILELINE_H_

#include "FileAgent.h"
#include <list>
#include <vector>


class FileLine{
public:
	FileLine();
	virtual ~FileLine();
	void addSlaves(const FileAgent& agent);
	void addCombind(const FileAgent& agent);
	void addMaster(const FileAgent& agent);

	const std::vector<FileAgent> getSlaves();	//return any slave agents in the line (every agent except for first and last)

	const FileAgent& getMaster(); // return the first item in the line

	const std::vector<FileAgent> getCombined(); //return the last item in the line

private:
	std::vector<FileAgent> input_agents;	//must be ordered
	std::vector<FileAgent> output_agents;	//must be ordered
	FileAgent master;
	
};

#endif /* FILELINE_H_ */