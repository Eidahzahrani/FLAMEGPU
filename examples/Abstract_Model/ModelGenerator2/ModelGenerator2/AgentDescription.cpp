/*
 * AgentDescription.cpp
 *
 *  Created on: 20 Feb 2014
 *      Author: paul
 */

#include "AgentDescription.h"
#include"TreeNode.h"
#include <fstream>
#include<iostream>
#include <string>
#include"TreeNode.h"

AgentDescription::AgentDescription(std::string name) : states(), functions(), memory(), sizes(){
	stateless = false;
	this->name = name;

}

AgentDescription::~AgentDescription() {

}


void AgentDescription::setName(std::string name) {
}

std::string AgentDescription::getName() const{
	return name;
}
std::ostream &operator<<(std::ostream &output, const AgentDescription &D) {
	output << D.name;
	return output;
}

void AgentDescription::addState(const AgentStateDescription& state, bool initial_state) {

	//check if this is a stateless system
	if (stateless){
		stateless = false;
	}

	states.insert(StateMap::value_type(state.getName(), state));
	if (initial_state)
		setInitialState(state.getName());
}

void AgentDescription::setInitialState(const std::string initial_state) {
	this->initial_state = initial_state;
}

void AgentDescription::addAgentFunction(const AgentFunctionDescription& function) {

	functions.insert(FunctionMap::value_type(function.getName(), function));
}

MemoryMap& AgentDescription::getMemoryMap() {
	return memory;
}


const MemoryMap& AgentDescription::getMemoryMap() const {
	return memory;
}

const StateMap& AgentDescription::getStateMap() const {
	return states;
}

unsigned int AgentDescription::getMemorySize() const {
	unsigned int size = 0;
	for (TypeSizeMap::const_iterator it = sizes.begin(); it != sizes.end(); it++){
		size += it->second;
	}
	return size;
}

unsigned int AgentDescription::getNumberAgentVariables() const{
	return memory.size();
}

const unsigned int AgentDescription::getAgentVariableSize(const std::string variable_name) const{
	//get the variable name type
	MemoryMap::const_iterator mm = memory.find(variable_name);
	if (mm == memory.end())
		throw std::runtime_error("Invalid agent memory variable");
	const std::type_info *t = &(mm->second);
	//get the type size
	TypeSizeMap::const_iterator tsm = sizes.find(t);
	if (tsm == sizes.end())
		throw std::runtime_error("Missing entry in type sizes map. Something went bad.");
	return tsm->second;
}

bool AgentDescription::requiresAgentCreation() const{
	
	//needs to search entire model for any functions with an agent output for this agent
	for (FunctionMap::const_iterator it= functions.begin(); it != functions.end(); it++){
		//if (*it->second()->)
	}

	return false;
}

const std::type_info& AgentDescription::getVariableType(const std::string variable_name) const{
	MemoryMap::const_iterator iter;
	iter = memory.find(variable_name);

	if (iter == memory.end())
		throw std::runtime_error("Invalid agent memory variable");

	return iter->second;

}

bool AgentDescription::hasAgentFunction(const std::string function_name) const {
	FunctionMap::const_iterator f;
	f = functions.find(function_name);
	return (f != functions.end());
}
///////////////////////outputXML////////////////////////////
void AgentDescription::outputXML(std::ofstream &outfile, XmlWriter &xml){


	xml.writeOpenTag(outfile, "gpu:xagent");
	xml.writeStartElementTag(outfile, "name");
	xml.writeString(outfile, name);
	xml.writeEndElementTag(outfile);
	xml.writeOpenTag(outfile, "memory");
	
	// =============Iterate over the Memory_map using Iterator till end.=============//

	for (MemoryMap::iterator it = memory.begin(); it != memory.end(); ++it){
		xml.writeOpenTag(outfile, "gpu:variable");
		xml.writeStartElementTag(outfile, "type");
		xml.writeString(outfile, (*it).second.name());
		xml.writeEndElementTag(outfile);
		xml.writeStartElementTag(outfile, "name");
		xml.writeString(outfile, (*it).first);
		xml.writeEndElementTag(outfile);
		xml.writeCloseTag(outfile);
	}
	xml.writeCloseTag(outfile);
	
	//end memory
	//start function

	// =============Iterate over the Function_map using Iterator till end.=============//

	xml.writeOpenTag(outfile, "functions");//open functions tag
	for (FunctionMap::iterator it = functions.begin(); it != functions.end(); ++it){
		auto function= it->second;
		function.outputXML(outfile, xml);
	}
	xml.writeCloseTag(outfile);//close functions tag
	xml.writeOpenTag(outfile, "states");//open states tag

	// =============Iterate over the State_map using Iterator till end.=============//

	for (StateMap::iterator it = states.begin(); it != states.end(); ++it){
		auto state= it->second;
		state.outputXML(outfile, xml);
	}
	xml.writeStartElementTag(outfile, "initialState");
	xml.writeString(outfile, initial_state);
	xml.writeEndElementTag(outfile);
	xml.writeCloseTag(outfile);//close states tag
	
	xml.writeStartElementTag(outfile, "gpu:type");
	xml.writeString(outfile, "continuous");
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "gpu:bufferSize");
	xml.writeString(outfile, "1024");
	xml.writeEndElementTag(outfile);	
	xml.writeCloseTag(outfile);//close gpu:xagent tag

}