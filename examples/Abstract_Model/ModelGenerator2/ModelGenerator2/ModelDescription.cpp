/*
 * ModelDescription.cpp
 *
 *  Created on: 20 Feb 2014
 *      Author: paul
 */

#include "ModelDescription.h"
#include"TreeNode.h"
#include <fstream>
#include<iostream>
#include <string>

ModelDescription::ModelDescription(const std::string model_name) : agents(), messages(), name(model_name) {}

ModelDescription::~ModelDescription() {}

const std::string ModelDescription::getName() const {
	return name;
}

void ModelDescription::addAgent(const AgentDescription &agent) {
	agents.insert(AgentMap::value_type(agent.getName(), agent));
}

void ModelDescription::addMessage(const MessageDescription &message) {
	messages.insert(MessageMap::value_type(message.getName(), message));
}

const AgentDescription& ModelDescription::getAgentDescription(const std::string agent_name) const{
	AgentMap::const_iterator iter;
	iter = agents.find(agent_name);
	if (iter == agents.end())
		throw std::runtime_error("Invalid agent memory variable");
	return iter->second;
}

//-------------------------------------------------------------
//== Function Name  :   ModelDescription::addALayer

void ModelDescription::addALayer(const int num, std::vector<std::string> function_name) {
	layers.insert(LayerMap::value_type(num, function_name));
}
//-------------------------------------------------------------
//== Function Name  :    ModelDescription::outputXML

void ModelDescription::outputXML(std::ofstream &outfile, XmlWriter &xml){

	
	xml.open(outfile);
	xml.writeStartElementTag(outfile, "name");
	xml.writeString(outfile, name);
	xml.writeEndElementTag(outfile);
	xml.writeOpenTag(outfile, "gpu:environment");
	xml.writeOpenTag(outfile, "gpu:functionFiles");
	xml.writeStartElementTag(outfile, "file");
	xml.writeString(outfile, "functions.c");
	xml.writeEndElementTag(outfile);
	xml.writeCloseTag(outfile);
	xml.writeOpenTag(outfile, "gpu:initFunctions");
	xml.writeOpenTag(outfile, "gpu:initFunction");
	xml.writeStartElementTag(outfile, "gpu:name");
	xml.writeString(outfile, "initFunction");
	xml.writeEndElementTag(outfile);
	xml.writeCloseTag(outfile);
	xml.writeCloseTag(outfile);

	xml.writeOpenTag(outfile, "gpu:stepFunctions");
	xml.writeOpenTag(outfile, "gpu:stepFunction");
	xml.writeStartElementTag(outfile, "gpu:name");
	xml.writeString(outfile, "stepFunction");
	xml.writeEndElementTag(outfile);
	xml.writeCloseTag(outfile);
	xml.writeCloseTag(outfile);

	xml.writeOpenTag(outfile, "gpu:exitFunctions");
	xml.writeOpenTag(outfile, "gpu:exitFunction");
	xml.writeStartElementTag(outfile, "gpu:name");
	xml.writeString(outfile, "exitFunction");
	xml.writeEndElementTag(outfile);
	xml.writeCloseTag(outfile);
	xml.writeCloseTag(outfile);
	xml.writeCloseTag(outfile);
		//xml.close();
	xml.writeOpenTag(outfile, "xagents");

	//== Iterate over the AgentMap using Iterator till end.==

	for ( AgentMap::iterator it = agents.begin(); it != agents.end(); it++){
	
		auto agent= it->second;
		agent.outputXML(outfile , xml);
	}
	xml.writeCloseTag(outfile);
	xml.writeOpenTag(outfile, "messages");//open messages tag

	// Iterate over the map using Iterator till end.
	for (MessageMap::iterator it = messages.begin(); it != messages.end(); ++it){
		auto message = it->second;
		message.outputXML(outfile, xml);
	}
	xml.writeCloseTag(outfile);//close messages tag
	xml.writeOpenTag(outfile, "layers");
	
	for (LayerMap::iterator it = layers.begin(); it != layers.end(); ++it){
	
		xml.writeOpenTag(outfile, "layer");
		for (int i = 0; i < it->second.size(); ++i){
		
		xml.writeOpenTag(outfile, "gpu:layerFunction");
		xml.writeStartElementTag(outfile, "name");
		xml.writeString(outfile, it->second[i]);
		xml.writeEndElementTag(outfile);
		//outfile << " </gpu:layerFunction>" << std::endl;
		xml.writeCloseTag(outfile);
	}

	xml.writeCloseTag(outfile);
}
	xml.writeCloseTag(outfile);
	xml.close(outfile);
}
//==----------------------------------------------------------------------------
