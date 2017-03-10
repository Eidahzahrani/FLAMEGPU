


#ifndef TREENODE_H_
#define TREENODE_H_


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class XmlWriter {
public:
	void open(std::ofstream &outFile);
	void close(std::ofstream &outFile);
	void writeOpenTag(std::ofstream &outfile,  const std::string);
	void writeCloseTag(std::ofstream &outfile);
	void writeStartElementTag(std::ofstream &outfile,const std::string);
	void writeEndElementTag(std::ofstream &outfile);
	void writeString(std::ofstream &outfile,const std::string);
private:
	std::ofstream outFile;
	int indent;
	int openTags;
	int openElements;
	std::vector<std::string> tempOpenTag;
	std::vector<std::string> tempElementTag;
};


#endif