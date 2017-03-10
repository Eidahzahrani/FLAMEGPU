/*
 * AgentFunctionDescription.h
 *
 *  Created on: 20 Feb 2014
 *      Author: paul
 */

#ifndef AGENTFUNCTIONDESCRIPTION_H_
#define AGENTFUNCTIONDESCRIPTION_H_

#include <string>
#include <map>
#include <memory>

#include "AgentFunctionInput.h"
#include "AgentFunctionOutput.h"
#include"TreeNode.h"

typedef std::map<std::string, const AgentFunctionInput> InputsMap;
typedef std::map<std::string,  AgentFunctionOutput> OutputsMap;

class AgentFunctionDescription {
public:

	AgentFunctionDescription(const std::string function_nameconst, const std::string state);

	virtual ~AgentFunctionDescription();

	const std::string getEndState() const;

	void setEndState(const std::string end_state);

	const std::string getIntialState() const;

	void setIntialState(const std::string intial_state);

	const std::string getName() const;

	void addInput(const AgentFunctionInput &input);

	void addOutput(const AgentFunctionOutput &output);

	void outputXML(std::ofstream &outfile, XmlWriter &xml);

	void addCondition(const std::string agentVariable, int value);

	void addxagentOutput(const std::string xagentOutput, const std::string xagentOutput_state);

	void setRealocate(std::string x);
	void setRNG(std::string x);


	//todo: add agent output

public:

	const std::string function_name;
	std::string initial_state;
	std::string end_state;
	InputsMap inputs;
	OutputsMap outputs;
	std::string agentVariable;
	int value;
	std::string xagentOutput; 
	std::string xagentOutput_state;
	std::string reallocate;
	std::string RNG;

};

#endif /* AGENTFUNCTIONDESCRIPTION_H_ */
