/*
 * AgentFunctionDescription.cpp
 *
 *  Created on: 20 Feb 2014
 *      Author: paul
 */

#include "AgentFunctionDescription.h"
#include <fstream>
#include<iostream>
#include <string>
#include"TreeNode.h"

AgentFunctionDescription::AgentFunctionDescription(const std::string function_name, const std::string state) : function_name(function_name), initial_state(state), end_state("default"), value(0), xagentOutput("default"), reallocate("false"), RNG("false"){

}

AgentFunctionDescription::~AgentFunctionDescription() {}

const std::string AgentFunctionDescription::getEndState() const {
	return end_state;
}

void AgentFunctionDescription::setEndState(const std::string end_state) {
	this->end_state = end_state;
}

const std::string AgentFunctionDescription::getIntialState() const {
	return initial_state;
}

void AgentFunctionDescription::setIntialState(const std::string intial_state) {
	this->initial_state = initial_state;
}

const std::string AgentFunctionDescription::getName() const{
	return function_name;
}

void AgentFunctionDescription::addInput(const AgentFunctionInput &input) {
	if (inputs.size() == 0)
		inputs.insert(InputsMap::value_type(input.getMessageName(), input));
	//else TODO: raise error
}

void AgentFunctionDescription::addOutput(const AgentFunctionOutput &output) {
	if (inputs.size() == 0)
		outputs.insert(OutputsMap::value_type(output.getMessageName(), output));
	//else TODO: raise error
}


//-------------------------------------------------------------
//== Function Name  :   AgentFunctionDescription::addCondition

void AgentFunctionDescription::addCondition(const std::string agentVariable, int value){

	this->agentVariable = agentVariable;
	this->value = value;
}

//-------------------------------------------------------------
//== Function Name  :   AgentFunctionDescription::addxagentOutput

void AgentFunctionDescription::addxagentOutput(const std::string xagentOutput, const std::string xagentOutput_state){
	this->xagentOutput = xagentOutput;
	this->xagentOutput_state = xagentOutput_state;
}

void AgentFunctionDescription::setRealocate(std::string x){

	reallocate = x;

}

void AgentFunctionDescription::setRNG(std::string x){
	RNG = x;

}

//-------------------------------------------------------------
//== Function Name  :   AgentFunctionDescription::outputXML

void AgentFunctionDescription::outputXML(std::ofstream &outfile, XmlWriter &xml){
	
	xml.writeOpenTag(outfile, "gpu:function");
	xml.writeStartElementTag(outfile, "name");
	xml.writeString(outfile, function_name);
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "currentState");
	xml.writeString(outfile, initial_state);
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "nextState");
	xml.writeString(outfile, end_state);
	xml.writeEndElementTag(outfile);

	// =============Iterate over the Inputs_map using Iterator till end.=============//

	for (InputsMap::iterator it = inputs.begin(); it != inputs.end(); ++it){
		
		xml.writeOpenTag(outfile, "inputs");
		xml.writeOpenTag(outfile, "gpu:input");
		//outfile << "<type>" << (*it).second << "<type>"<<std::endl;
		xml.writeStartElementTag(outfile, "messageName");
		xml.writeString(outfile, (*it).first);
		xml.writeEndElementTag(outfile);
		xml.writeCloseTag(outfile);
		xml.writeCloseTag(outfile);
	}
	// =============Iterate over the Outputs_map using Iterator till end.=============//
	for (OutputsMap::iterator it = outputs.begin(); it != outputs.end(); ++it){
		xml.writeOpenTag(outfile, "outputs");
		xml.writeOpenTag(outfile, "gpu:output");
		xml.writeStartElementTag(outfile, "messageName");
		xml.writeString(outfile, (*it).first);
		xml.writeEndElementTag(outfile);
		xml.writeStartElementTag(outfile, "gpu:type");
		xml.writeString(outfile, "single_message");
		xml.writeEndElementTag(outfile);
		xml.writeCloseTag(outfile);
		xml.writeCloseTag(outfile);
	}
	if (xagentOutput != "default"){
		xml.writeOpenTag(outfile, "xagentOutputs");
		xml.writeOpenTag(outfile, "gpu:xagentOutput");
		xml.writeStartElementTag(outfile, "xagentName");
		xml.writeString(outfile, xagentOutput);
		xml.writeEndElementTag(outfile);
		xml.writeStartElementTag(outfile, "state");
		xml.writeString(outfile, xagentOutput_state);
		xml.writeEndElementTag(outfile);
		xml.writeCloseTag(outfile);
		xml.writeCloseTag(outfile);
	}
	if (value > 0){
		xml.writeOpenTag(outfile, "condition");
		xml.writeOpenTag(outfile, "lhs");
		xml.writeStartElementTag(outfile, "agentVariable");
		xml.writeString(outfile, agentVariable);
		xml.writeEndElementTag(outfile);
		xml.writeCloseTag(outfile);
		xml.writeStartElementTag(outfile, "operator");
		xml.writeString(outfile, "==");
		xml.writeEndElementTag(outfile);
		xml.writeOpenTag(outfile, "rhs");
		xml.writeStartElementTag(outfile, "value");
		xml.writeString(outfile, std::to_string(value));
		xml.writeEndElementTag(outfile);
		xml.writeCloseTag(outfile);
		xml.writeCloseTag(outfile);
	}
	xml.writeStartElementTag(outfile, "gpu:reallocate");
	xml.writeString(outfile, reallocate);
	xml.writeEndElementTag(outfile);
	xml.writeStartElementTag(outfile, "gpu:RNG");
	xml.writeString(outfile, RNG);
	xml.writeEndElementTag(outfile);
	
	xml.writeCloseTag(outfile);//close gpu:function tag
}

//=================================================================================
