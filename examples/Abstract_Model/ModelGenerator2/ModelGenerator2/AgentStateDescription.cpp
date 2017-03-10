/*
 * AgentStateDescription.cpp
 *
 *  Created on: 20 Feb 2014
 *      Author: paul
 */

#include "AgentStateDescription.h"
#include "File.h"
#include <fstream>
#include<iostream>
#include"TreeNode.h"


AgentStateDescription::AgentStateDescription(const std::string state_name) : name(state_name){ 
	
}

AgentStateDescription::~AgentStateDescription() {

}

const std::string AgentStateDescription::getName() const {
	return name;
}

/*std::ostream &operator<<(std::ostream &os, const AgentStateDescription& state) {
	os << state.name;
	return os;
}*/

void AgentStateDescription::outputXML(std::ofstream &outfile, XmlWriter &xml){
	xml.writeOpenTag(outfile,"gpu:state");
	xml.writeStartElementTag(outfile,"name");
	xml.writeString(outfile, name);
	xml.writeEndElementTag(outfile);
	xml.writeCloseTag(outfile);
	
}