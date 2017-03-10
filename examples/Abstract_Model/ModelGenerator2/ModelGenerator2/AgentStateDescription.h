/*
 * AgentStateDescription.h
 *
 *  Created on: 20 Feb 2014
 *      Author: paul
 */

#ifndef AGENTSTATEDESCRIPTION_H_
#define AGENTSTATEDESCRIPTION_H_

#include <string>
#include"TreeNode.h"

class AgentStateDescription {
public:
	AgentStateDescription(const std::string name);
	virtual ~AgentStateDescription();

	const std::string getName() const;

	//friend std::ostream& operator<<(std::ostream& os, const AgentStateDescription& state);

	void outputXML(std::ofstream &outfile, XmlWriter &xml);


private:

	const std::string name;
};

#endif /* AGENTSTATEDESCRIPTION_H_ */
