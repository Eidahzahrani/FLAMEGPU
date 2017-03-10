/*
 * ModelDescription.h
 *
 *  Created on: 20 Feb 2014
 *      Author: paul
 */

#ifndef MODELDESCRIPTION_H_
#define MODELDESCRIPTION_H_


#include <string>
#include <map>
#include <memory>
#include <vector>
#include <typeinfo>
#include "TreeNode.h"
#include "AgentDescription.h"
#include "MessageDescription.h"

typedef std::map<const std::string, const AgentDescription> AgentMap;
typedef std::map<const std::string,  const MessageDescription> MessageMap;
typedef std::map< const int, const std::vector<std::string>> LayerMap;
class ModelDescription{
public:
	ModelDescription(const std::string model_name);

	virtual ~ModelDescription();

	const std::string getName() const;

	void addAgent(const AgentDescription &agent);

	void addMessage(const MessageDescription &message);

	void ModelDescription::addALayer(const int num, std::vector < std::string> function_name);

	const AgentDescription& getAgentDescription(const std::string agent_name) const;

	const AgentMap& getAgentMap() const;

	void outputXML(std::ofstream &outfile, XmlWriter &xml);

private:
	std::string name;
	AgentMap agents;
	MessageMap messages;
	LayerMap layers;
	
};


#endif /* MODELDESCRIPTION_H_ */
