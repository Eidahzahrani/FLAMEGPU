/*
 * MessageDescription.cpp
 *
 *  Created on: 20 Feb 2014
 *      Author: paul
 */
#include"TreeNode.h"
#include "MessageDescription.h"
#include <fstream>
#include<iostream>
#include <string>

MessageDescription::MessageDescription(const std::string message_name) : variables(), name(message_name) { }

MessageDescription::~MessageDescription() {}

const std::string MessageDescription::getName() const{
	return name;
}

std::ostream &operator<<(std::ostream &output, const MessageDescription &D) {
	output << D.name;	
	return output;
}

void MessageDescription::outputXML(std::ofstream &outfile, XmlWriter &xml){



	xml.writeOpenTag(outfile, "gpu:message");
	xml.writeStartElementTag(outfile, "name");
	xml.writeString(outfile, name);
	xml.writeEndElementTag(outfile);
	xml.writeOpenTag(outfile, "variables");
	
	// Iterate over the map using Iterator till end.
	
	for (VariableMap::iterator it = variables.begin(); it != variables.end(); ++it){
		xml.writeOpenTag(outfile, "gpu:variable");
		//outfile << "<gpu:variable>" << std::endl;
		xml.writeStartElementTag(outfile, "type");
		xml.writeString(outfile, (*it).second.name());
		xml.writeEndElementTag(outfile);
		//outfile << "<type>" << (*it).second.name() << "<type>"<<std::endl;
		xml.writeStartElementTag(outfile, "name");
		xml.writeString(outfile, (*it).first);
		xml.writeEndElementTag(outfile);
		//outfile << "<name>" << (*it).first << "</name>"<<std::endl;
		xml.writeCloseTag(outfile);
		//outfile << "</gpu:variable>" << std::endl;
		
	}
	xml.writeCloseTag(outfile);

	xml.writeOpenTag(outfile, "gpu:partitioningSpatial");
	xml.writeStartElementTag(outfile, "gpu:radius");
	xml.writeString(outfile, "1.0");
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "gpu:xmin");
	xml.writeString(outfile, "0.0");
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "gpu:xmax");
	xml.writeString(outfile, "10.0");
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "gpu:ymin");
	xml.writeString(outfile, "0.0");
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "gpu:ymax");
	xml.writeString(outfile, "10.0");
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "gpu:zmin");
	xml.writeString(outfile, "0.0");
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "gpu:zmax");
	xml.writeString(outfile, "1.0");
	xml.writeEndElementTag(outfile);
	
		xml.writeCloseTag(outfile);
		xml.writeStartElementTag(outfile, "gpu:bufferSize");
		xml.writeString(outfile, "1048576");
		xml.writeEndElementTag(outfile);
		xml.writeCloseTag(outfile);
	//outfile << "</variables>" << std::endl;

		
}
