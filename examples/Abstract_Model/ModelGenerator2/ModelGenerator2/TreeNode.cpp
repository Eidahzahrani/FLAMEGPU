

#include"TreeNode.h"

#include <fstream>
#include<iostream>
#include <string>
#include <sstream>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/xml_parser.hpp>



//---------------------------------------------------------------
//== Function Name  :   XmlWriter::open

void XmlWriter::open(std::ofstream &outFile) {

	outFile << "<gpu:xmodel xmlns:gpu=\"http://www.dcs.shef.ac.uk/~paul/XMMLGPU" << "\"\n";
	outFile << "xmlns=\"http://www.dcs.shef.ac.uk/~paul/XMML" << "\">\n";
		indent = 0;
		openTags = 0;
		openElements = 0;
}
//-------------------------------------------------------------
//== Function Name  :   XmlWriter::close

void XmlWriter::close(std::ofstream &outFile) {
	if (outFile.is_open()) {
		outFile << "</gpu:xmodel>";
		outFile.close();
	}
	else {
		std::cout << "File already closed.\n";
	}

}
//------------------------------------------------------------------------
//== Function Name  :   XmlWriter::writeOpenTag

void XmlWriter::writeOpenTag(std::ofstream &outFile, const std::string openTag) {
	if (outFile.is_open()) {
		for (int i = 0; i < indent; i++) {
			outFile << "\t";
		}
		tempOpenTag.resize(openTags + 1);
		outFile << "<" << openTag << ">\n";
		tempOpenTag[openTags] = openTag;
		indent += 1;
		openTags += 1;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}
//---------------------------------------------------------------
//== Function Name  :   XmlWriter::writeCloseTag

void XmlWriter::writeCloseTag(std::ofstream &outFile) {
	if (outFile.is_open()) {
		indent -= 1;
		for (int i = 0; i < indent; i++) {
			outFile << "\t";
		}
		outFile << "</" << tempOpenTag[openTags - 1] << ">\n";
		tempOpenTag.resize(openTags - 1);
		openTags -= 1;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}
//-----------------------------------------------------------------
//== Function Name  :   XmlWriter::writeStartElementTag

void XmlWriter::writeStartElementTag(std::ofstream &outFile, const std::string elementTag) {
	if (outFile.is_open()) {
		for (int i = 0; i < indent; i++) {
			outFile << "\t";
		}
		tempElementTag.resize(openElements + 1);
		tempElementTag[openElements] = elementTag;
		openElements += 1;
		outFile << "<" << elementTag;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}
//---------------------------------------------------------------------------
//== Function Name  :   XmlWriter::writeEndElementTag

void XmlWriter::writeEndElementTag(std::ofstream &outFile) {
	if (outFile.is_open()) {
		outFile << "</" << tempElementTag[openElements - 1] << ">\n";
		tempElementTag.resize(openElements - 1);
		openElements -= 1;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}

//-----------------------------------------------------------------------------
//== Function Name  :   XmlWriter::writeString

void XmlWriter::writeString(std::ofstream &outFile, const std::string outString) {
	if (outFile.is_open()) {
		outFile << ">" << outString;
	}
	else {
		std::cout << "File is closed. Unable to write to file.\n";
	}
}

	