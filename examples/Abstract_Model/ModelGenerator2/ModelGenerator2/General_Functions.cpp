

#include "General_Functions.h"
#include "FileAgent.h"
#include "AgentDescription.h"
#include "AgentFunctionDescription.h"
#include "AgentFunctionInput.h"
#include "AgentFunctionOutput.h"
#include "AgentStateDescription.h"
#include "MessageDescription.h"
#include "ModelDescription.h"
#include "AgentStateDescription.h"

string message01, message02, message03, function_name , string_counter;
int counter = 1;

void addMaster(string master, vector<FileAgent> slaves, vector<FileAgent>combinds, ModelDescription &model){

	string s, state;
	
	AgentDescription agent(master);
	agent.addAgentVariable<int>("id");
	agent.addAgentVariable<float>("x");
	agent.addAgentVariable<float>("y");
	agent.addAgentVariable<float>("z");
	agent.addAgentVariable<float>("vx");
	agent.addAgentVariable<float>("vy");
	agent.addAgentVariable<float>("vz");
	agent.addAgentVariable<int>("count");
	agent.addAgentVariable<int>("type");
	agent.addAgentVariable<int>("state");
	agent.addAgentVariable<float>("closest_point");
	agent.addAgentVariable<int>("closest_id");

	state = "moving_" + master;
	
	agent.setInitialState(state);
	AgentStateDescription state1(state);
	agent.addState(state1);
	// move function for master agent
	function_name = "move_" + master;
	AgentFunctionDescription move(function_name, state);
	move.setIntialState(state);
	move.setEndState(state);
	move.setRNG("true");
	agent.addAgentFunction(move);
	//creating the messages 
	for (int i = 0; i < slaves.size(); i++){
		s = slaves[i].getName();
		message01 = "location" + s;
		message02 = "bind" + s;
		message03 = "combined" + s;
	
		//The agent messages
	
		
		MessageDescription message(message01);
		message.addVariable<int>("id");
		message.addVariable<float>("x");
		message.addVariable<float>("y");
		message.addVariable<float>("z");
		message.addVariable<int>("type");
		message.addVariable<int>("state");
		message.addVariable<float>("closest_point");
		message.addVariable<int>("closest_id");


		MessageDescription message1(message02);
		message1.addVariable<int>("id");
		message1.addVariable<float>("x");
		message1.addVariable<float>("y");
		message1.addVariable<float>("z");
		message1.addVariable<int>("type");
		message1.addVariable<int>("state");
		message1.addVariable<float>("closest_point");
		message1.addVariable<int>("closest_id");

		MessageDescription message2(message03);
		message2.addVariable<int>("id");
		message2.addVariable<float>("x");
		message2.addVariable<float>("y");
		message2.addVariable<float>("z");
		message2.addVariable<int>("type");
		message2.addVariable<int>("state");
		message2.addVariable<float>("closest_point");
		message2.addVariable<int>("closest_id");
	
		function_name = "need_location" + s;
		//need_location function for the master agent 
		AgentFunctionDescription need_location(function_name, state);
		AgentFunctionInput location(message01);
		need_location.addInput(location);
		need_location.setIntialState(state);
		need_location.setEndState(state);
		agent.addAgentFunction(need_location);

		function_name = "send_bind" + s;
		//send_bind function for the master agent 
		AgentFunctionDescription send_bind(function_name, state);
		AgentFunctionOutput bind(message02);//output message
		send_bind.addOutput(bind);
		send_bind.addCondition("state", 2);
		send_bind.setIntialState(state);
		send_bind.setEndState(state);
		agent.addAgentFunction(send_bind);

		s = combinds[0].getName();
		string_counter = to_string(i);
		function_name = "created_" + s + string_counter;
		//cout << "function name====" << function_name << endl;
		string statee = "moving_" + s;
		//created_ function for the master agent 
		AgentFunctionDescription created_(function_name, state);
		created_.addCondition("state", 2);
		AgentFunctionInput combined(message03);
		created_.addInput(combined);
		created_.addxagentOutput(s, statee);
		created_.setIntialState(state);
		created_.setEndState(state);
		created_.setRNG("true");
		agent.addAgentFunction(created_);
		
		model.addMessage(message);
		model.addMessage(message1);
		model.addMessage(message2);
	}

	//for (int i = 0; i <combinds.size(); i++){
		
	//}
	
	// death function for master agent
	function_name = "death_" + master;
	AgentFunctionDescription death(function_name, state);
	state = "moving_" + master;
	death.setIntialState(state);
	state = "dead" + master;
	death.setEndState(state);
	death.addCondition("state", 6);
	death.setRealocate("true");
	agent.addState(state);
	agent.addAgentFunction(death);
	model.addAgent(agent);

	//cout <<endl<< "done added master agent"<<master<<endl;

}
void addSlave(vector<FileAgent> slaves, ModelDescription &model){

	string s, state;
	for (int i = 0; i < slaves.size(); i++){
		s = slaves[i].getName();
		message01 = "location" + s;
		message02 = "bind" + s;
		message03 = "combined" + s;
	
		//The agent messages

		MessageDescription message(message01);
		message.addVariable<int>("id");
		message.addVariable<float>("x");
		message.addVariable<float>("y");
		message.addVariable<float>("z");
		message.addVariable<int>("type");
		message.addVariable<int>("state");
		message.addVariable<float>("closest_point");
		message.addVariable<int>("closest_id");

		MessageDescription message1(message02);
		message1.addVariable<int>("id");
		message1.addVariable<float>("x");
		message1.addVariable<float>("y");
		message1.addVariable<float>("z");
		message1.addVariable<int>("type");
		message1.addVariable<int>("state");
		message1.addVariable<float>("closest_point");
		message1.addVariable<int>("closest_id");

		MessageDescription message2(message03);
		message2.addVariable<int>("id");
		message2.addVariable<float>("x");
		message2.addVariable<float>("y");
		message2.addVariable<float>("z");
		message2.addVariable<int>("type");
		message2.addVariable<int>("state");
		message2.addVariable<float>("closest_point");
		message2.addVariable<int>("closest_id");


		AgentDescription agent(s);
		agent.addAgentVariable<int>("id");
		agent.addAgentVariable<float>("x");
		agent.addAgentVariable<float>("y");
		agent.addAgentVariable<float>("z");
		agent.addAgentVariable<float>("vx");
		agent.addAgentVariable<float>("vy");
		agent.addAgentVariable<float>("vz");
		agent.addAgentVariable<int>("count");
		agent.addAgentVariable<int>("type");
		agent.addAgentVariable<int>("state");
		agent.addAgentVariable<float>("closest_point");
		agent.addAgentVariable<int>("closest_id");

		//cout << "_____Slave:" << s << "____" << endl;
		state = "moving_" + s;
		AgentStateDescription state1(state);
		agent.addState(state1);
		agent.setInitialState(state);
		function_name = "move_" + s;
		//move function for all L agents 
		AgentFunctionDescription move(function_name, state);
		move.setEndState(state);
		move.setRNG("true");
		agent.addAgentFunction(move);
		//cout << "____the functions are:" << function_name << endl;
		//send_location function 
		function_name = "send_location" + s;
		AgentFunctionDescription send_location(function_name , state);
		AgentFunctionOutput location(message01);
		//FunctionOutputType SINGLE_MESSAG;
		//location.setFunctionOutputType(SINGLE_MESSAG);
		send_location.addOutput(location);
		send_location.setIntialState(state);
		send_location.setEndState(state);
		agent.addAgentFunction(send_location);

		//cout << "--" << function_name;
		//receive_bind function 
		function_name = "receive_bind" + s;
		AgentFunctionDescription receive_bind(function_name, state);
		AgentFunctionInput newAgent(message02);//input message
		receive_bind.addInput(newAgent);
		receive_bind.setIntialState(state);
		receive_bind.setEndState(state);
		agent.addAgentFunction(receive_bind);
		//cout << "--" << function_name;

		//combined function
		function_name = "send_combined" + s;
		state = "moving_" + s;
		AgentFunctionDescription send_combined(function_name, state);
		send_combined.addCondition("state", 3);
		AgentFunctionOutput combined(message03);
		send_combined.addOutput(combined);
		send_combined.setIntialState(state);
		state = "dead" + s;
		agent.addState(state);
		send_combined.setEndState(state);
		send_combined.setRealocate("true");
		agent.addAgentFunction(send_combined);
		//cout << "--" << function_name;

		model.addMessage(message);
		model.addMessage(message1);
		model.addMessage(message2);
		model.addAgent(agent);
		//cout << "the agent is:" << agent.getName();
		//cout << endl << "done added slave agent" << s << endl;
	}
	
}


void addCombind(vector<FileAgent> combind, ModelDescription &model){
	string s, state;
	for (int i = 0; i < combind.size(); i++){
		s = combind[i].getName();
		
		AgentDescription agent(s);
		agent.addAgentVariable<int>("id");
		agent.addAgentVariable<float>("x");
		agent.addAgentVariable<float>("y");
		agent.addAgentVariable<float>("z");
		agent.addAgentVariable<float>("vx");
		agent.addAgentVariable<float>("vy");
		agent.addAgentVariable<float>("vz");
		agent.addAgentVariable<int>("count");
		agent.addAgentVariable<int>("type");
		agent.addAgentVariable<int>("state");
		agent.addAgentVariable<float>("closest_point");
		agent.addAgentVariable<int>("closest_id");

		state = "moving_" + s;

		agent.setInitialState(state);
		AgentStateDescription state1(state);
		agent.addState(state1);
		function_name = "move_" + s;
		//move function for all L agents 
		AgentFunctionDescription move(function_name, state);
		move.setIntialState(state);
		move.setEndState(state);
		move.setRNG("true");
		agent.addAgentFunction(move);
		model.addAgent(agent);
		
		
		//cout << endl << "done added combind agent" << s << endl;

	}


}
void addlayer(int line, string master, vector<FileAgent> slaves, vector<FileAgent>combinds, ModelDescription &model){
	//cout << "add layer*******" << line << endl;

	std::vector<std::string>layerone;
	std::vector<std::string>layer8;
	std::vector<std::string>layer9;
	std::vector<std::string>layer;
	std::vector<std::string>Maxlayer;
	string s;


	s = "move_" + master;
	layerone.push_back(s);

	//s = "death_" + master;
	//layer8.push_back(s);

	for (int i = 0; i < slaves.size(); i++){

		s = "move_" + slaves[i].getName();
		layerone.push_back(s);

		s = "send_location" + slaves[i].getName();
		Maxlayer.push_back(s);

		s = "need_location" + slaves[i].getName();
		Maxlayer.push_back(s);

		s = "send_bind" + slaves[i].getName();
		Maxlayer.push_back(s);

		s = "receive_bind" + slaves[i].getName();
		Maxlayer.push_back(s);

		s = "send_combined" + slaves[i].getName();
		Maxlayer.push_back(s);
		//cout << "here" << endl;
		s = "created_" + combinds[0].getName() + to_string(i);
		//cout << s << endl;
		Maxlayer.push_back(s);
		s = "death_" + master;
		//cout << s << endl;
		Maxlayer.push_back(s);
	}

	for (int i = 0; i < combinds.size(); i++){

		//cout << "combind____" << combinds[i].getName();
		s = "move_" + combinds[i].getName();
		layer9.push_back(s);
	}
	line = line * 10;
	//cout << "counter:  " << counter + line;
	model.addALayer(counter + line, layerone);
	++counter;
	int l;
	l = slaves.size() * 7;
	//cout << "L" << l << endl;
	for (int i = 0; i<l; i++){
		//cout << "this is model layer:" << i << endl;
		layer.push_back(Maxlayer[i]);
		model.addALayer(line + counter, layer);
		layer.clear();
		++counter;
	}
	//model.addALayer(counter + line, layer8);
	//++counter;
	model.addALayer(counter + line, layer9);


}