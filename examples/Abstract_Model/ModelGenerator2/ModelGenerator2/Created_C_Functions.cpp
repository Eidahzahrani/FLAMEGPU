
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileModel.h"
#include "FileLine.h"
#include "FileAgent.h"
#include "AgentDescription.h"
#include "AgentFunctionDescription.h"
#include "AgentFunctionInput.h"
#include "AgentFunctionOutput.h"
#include "AgentStateDescription.h"
#include "MessageDescription.h"
#include "ModelDescription.h"
#include "General_Functions.h"
#include"TreeNode.h"
#include "Created_C_Functions.h"



using namespace std;


ofstream file;
FileLine l;
vector<FileLine>lines;
vector<FileAgent>Slaveagent;
vector<FileAgent>Combindagent;
FileAgent agent("E");
string master;
string slave;
string combind;
int state = 0;


//-------------------------------------------------------------
//== Function Name  : 

void addModel_Functions(FileModel m){

	string s;
	file.open("C:\\FLAMEGPU\\examples\\Abstract_Model\\src\\model\\functions.c");
	if (!file.is_open()) {
		// The file could not be opened
	}
	else {
		define_state(m);
		initfunction(m);
		stepfunction(m);
		exitfunction(m);
		lines = m.getlines();
		int size = lines.size();
		cout<< "size lines:" << size;
		for (int i = 0; i < size; i++){
			cout << "here";
			cout << "line number" << i + 1 << ":";
			l = lines[i];
			agent = l.getMaster();
			master = agent.getName();
			Slaveagent = l.getSlaves();
			int size_S = Slaveagent.size();
			move_function(master);
			death_function(master);
			Combindagent = l.getCombined();
			for (int i = 0; i < size_S; i++){
				s = Slaveagent[i].getName();
				move_function(s);
				send_location_function(s);
				receive_bind_function(s);
				send_combined_function(s);
				need_location_function(s, master);
				send_bind_function(s, master);
				created_function(Combindagent[0].getName(), master, s, i);

			}
			
		
		
				s = Combindagent[0].getName();
				move_function(s);
				
		
			cout << "exit from here" << endl;
		}
		cout << "exit"<<endl;
	}
	cout << "exit2";
	file << "#endif //_FLAMEGPU_FUNCTIONS" << endl;
	file.close();// close the file 


}
//-------------------------------------------------------------
//== Function Name  : 

void define_state(FileModel m){
	std::vector<string>agents;
	file << "#ifndef _FLAMEGPU_FUNCTIONS" << endl;
	file << "#define _FLAMEGPU_FUNCTIONS" << endl;
	file << "#include <header.h>" << endl;
	file << "#include <vector>" << endl;
	file << "#define AGENT_STATE_DEAD 3" << endl;
	file << "#define AGENT_STATE_BIND 2" << endl;

	file << "#define XMAX 		10.0f" << endl;
	file << "#define YMAX		  	10.0f" << endl;
	file << "#define ZMAX		  	10.0f" << endl;
	file << "//Interaction radius" << endl;
	file << "#define radius 1.0f" << endl;
	file << "#define SPEED 0.005f" << endl << endl;;
	
	agents = m.getUniqueAgents();
	int size = agents.size();
	for (int i = 0; i < size; i++){
		file << "std::vector<int>" << agents[i] << "counter;" << endl;
	}
	file << "std::vector<int>iteration;" << endl;
	file << "unsigned int h_iteration = 0;" << endl;
	lines = m.getlines();
	int size1 = lines.size();
	
	for (int i = 0; i < size1; i++){
		cout << "line number" << i + 1 << ":";
		l = lines[i];
		agent = l.getMaster();
		master = agent.getName();
		Slaveagent = l.getSlaves();
		file << "#define AGENT_STATE_" << master << "_DEFAULT" << " 1" << endl;
		int size_S = Slaveagent.size();
		for (int j = 0; j < size_S; j++){
			slave = Slaveagent[j].getName();
			state = j + 4;
			file << "#define AGENT_STATE_" << slave << "_DEFAULT " << state << endl;

		}
		Combindagent = l.getCombined();
		size_S = Combindagent.size();
		for (int j = 0; j < size_S; j++){
			slave = Combindagent[j].getName();

			file << "#define AGENT_STATE_" << slave << "_DEFAULT " << state + j + 1 << endl;

		}
	}

}



//-------------------------------------------------------------
//== Function Name  : 

void initfunction(FileModel m){
	vector<string>s;
	s = m.getUniqueAgents();
	int size = s.size();
	file << "/*" << endl;
	file << " *init_Function....." << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_INIT_FUNC__ void initFunction(){" << endl << endl;
	for (int i = 0; i<size; i++){

		//file << "printf(\"FLAME GPU Init function." << s[i] << " population is (%d)\n\"" << ", get_agent_" << s[i] << "_moving_" << s[i] << "_count());" << endl;
		file << s[i] << "counter.push_back(get_agent_" << s[i] << "_moving_" << s[i] << "_count());" << endl;
		 }
		file << "iteration.push_back(0);" << endl;
		file << "fflush(stdout);" << endl;
		file << " }" << endl;
	
}
//-------------------------------------------------------------
//== Function Name  : 

void stepfunction(FileModel m){
	vector<string>s;
	s = m.getUniqueAgents();
	int size = s.size();
	file << "/*" << endl;
	file << " *step_Function....." << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_STEP_FUNC__ void stepFunction(){" << endl << endl;
	file << "h_iteration++;" << endl;
	file << "iteration.push_back(h_iteration);" << endl;
	for (int i = 0; i<size; i++){
		
		file << s[i]<<"counter.push_back(get_agent_" << s[i] << "_moving_" << s[i] << "_count());" << endl;
	}
	file << "fflush(stdout);" << endl;
	file << "}" << endl;
}

//-------------------------------------------------------------
//== Function Name  : 
void exitfunction(FileModel m){
	file << "/*" << endl;
	file << " *Exit_Function....." << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_EXIT_FUNC__ void exitFunction(){" << endl << endl;
	file << "FILE *output = fopen(""\"C:\\"<<"\\FLAMEGPU\\"<<"\\examples\\"<<"\\Abstract_Model\\"<<"\\output.dat""\",  ""\"w""\");" << endl << endl;

	file << "fprintf(output, ""\"#I";
	vector<string>s;
	s = m.getUniqueAgents();
	int size = s.size();
	for (int i = 0; i < size; i++){
		file << s[i] << " "; 
	}
	file<<"\\n ""\");" << endl << endl;
	file << "for (int i = 0; i < h_iteration; i++){" << endl;

	file << "fprintf(output, ""\"%u ";
	for (int i = 0; i < size; i++){
		file << "%d" << " ";
	}
		file << "\\n ""\", iteration[i],";
		for (int i = 0; i < size; i++){
			cout << i << "--" << size;
			if (i == size-1)file << s[i] << "counter[i]";
			else
			file <<s[i]<< "counter[i]" << ", ";
		}

		file<<");" << endl;
	file << "}" << endl;
	file << "fclose(output);" << endl;
	file << "}" << endl;
}
//-------------------------------------------------------------
//== Function Name  : 

void move_function(string agent){
	file << "/*" << endl;
	file << " * move_" << agent << " FLAMEGPU Agent Function" << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_FUNC__ int move_" << agent << "(xmachine_memory_" << agent << "* agent, RNG_rand48* rand48){" << endl << endl;
	file << "  float x1 = agent->x;" << endl;
	file << "  float y1 = agent->y;" << endl;
	file << "  float z1 = agent->z;" << endl;
	file << "  float random = rnd(rand48);" << endl;
	file << "   if (random < 0.1f) {" << endl;
	file << "		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;" << endl;
	file << " }" << endl;
	file << "	else if (random < 0.2f) {" << endl;
	file << "      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;" << endl;
	file << " }" << endl;
	file << "	else if (random < 0.3f) {" << endl;
	file << "      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;" << endl;
	file << " }" << endl;
	file << "	else if (random < 0.4f){" << endl;
	file << "      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;" << endl;
	file << " }" << endl;
	file << "   else if (random < 0.5f) {" << endl;
	file << "	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;" << endl;
	file << " }" << endl;
	file << "   else  if (random < 0.6f){" << endl;
	file << "    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;" << endl;
	file << " }" << endl;
	file << "/* update memory with new parameters*/" << endl;
	file << "		agent->x = x1;" << endl;
	file << "       agent->y = y1;" << endl;
	file << "       agent->z = z1;" << endl;
	file << "       agent->state = AGENT_STATE_" << agent << "_DEFAULT;" << endl;
	file << endl << "return 0;" << endl;

	file << "}" << endl;

	cout << "move:" << agent << endl;
}
//-------------------------------------------------------------
//== Function Name  : 
void send_location_function(string agent){
	file << "/*" << endl;
	file << " * send_location" << agent << " FLAMEGPU Agent Function" << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_FUNC__ int send_location" << agent << "(xmachine_memory_" << agent << "* agent, xmachine_message_location" << agent << "_list* location" << agent << "_messages){" << endl << endl;
	file << "    int id, s, t, c_id;" << endl;
	file << "    float x, y, z, c_point;" << endl;
	file << "    id = agent->id;" << endl;
	file << "    x = agent->x;" << endl;
	file << "	 y = agent->y;" << endl;
	file << "    z = agent->z;" << endl;
	file << "    s = agent->state;" << endl;
	file << "	 t = agent->type;" << endl;
	file << "	c_point = agent->closest_point;" << endl;
	file << "c_id = agent->closest_id;" << endl;
	file << "add_location" << agent << "_message(location" << agent << "_messages, c_id ,c_point , id, s,t, x, y, z );" << endl;
	file << endl << "return 0;" << endl;
	file << "}" << endl << endl;

	cout << "sendLocation:" << agent << endl;
}
//-------------------------------------------------------------
//== Function Name  : 

void receive_bind_function(string agent){
	file << "/*" << endl;
	file << " * receive_bind" << agent << " FLAMEGPU Agent Function" << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_FUNC__ int receive_bind" << agent << "(xmachine_memory_" << agent << "* agent, xmachine_message_bind" << agent << "_list* bind" << agent << "_messages, xmachine_message_bind" << agent << "_PBM* partition_matrix){" << endl;
	file << "   int c = 0, nearest_id = 0;" << endl;
	file << "	float nearest_distance = 0.0f;" << endl;
	file << " xmachine_message_bind" << agent << "* current_message = get_first_bind" << agent << "_message(bind" << agent << "_messages, partition_matrix, agent->x, agent->y, agent->z);" << endl << endl;
	file << "  while (current_message)" << endl;
	file << "   {" << endl;
	file << "     if (current_message->id != agent->id){" << endl;
	file << "        if (agent->id == current_message->closest_id){" << endl;
	file << "           if (c == 0){" << endl;
	file << "               c++;" << endl;
	file << "               nearest_distance = current_message->closest_point;" << endl;
	file << "               nearest_id = current_message->id;" << endl;
	file << "             }" << endl;
	file << "             else if (nearest_distance > current_message->closest_point){" << endl;
	file << "                 nearest_distance = current_message->closest_point;" << endl;
	file << "                 nearest_id = current_message->id;" << endl;
	file << "             }" << endl;
	file << "         }" << endl;
	file << "      }" << endl;
	file << "   current_message = get_next_bind" << agent << "_message(current_message, bind" << agent << "_messages, partition_matrix);" << endl << endl;
	file << "   }" << endl;
	file << " if (c == 1) {" << endl;
	file << "agent->state = AGENT_STATE_DEAD;" << endl;
	file << "agent->closest_point = nearest_distance;" << endl;
	file << "agent->closest_id = nearest_id;" << endl;
	file << "}" << endl;
	file << "  else{" << endl;
	file << "     agent->closest_id = -1;" << endl;
	file << "   }" << endl << endl;
	file << "return 0;" << endl;
	file << "}" << endl;

	cout << "receveBined:" << agent << endl;


}
//-------------------------------------------------------------
//== Function Name  : 

void send_combined_function(string agent){

	file << "/*" << endl;
	file << " * send_combined" << agent << " FLAMEGPU Agent Function" << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_FUNC__ int send_combined" << agent << "(xmachine_memory_" << agent << "*  agent ,xmachine_message_combined"<<agent<<"_list* combined"<<agent<<"_messages){" << endl << endl;
	

	file << "int id, s, t, c_id;" << endl;
	file << "float x, y, z, c_point;" << endl;
	file << "id = agent->id;" << endl;
	file << "x = agent->x;" << endl;
	file << "y = agent->y;"<< endl;
	file << "z = agent->z;" << endl;
	file << "s = agent->state;" << endl;
	file << "t = agent->type;" << endl;
	file << "c_point = agent->closest_point;" << endl;
	file << "c_id = agent->closest_id;" << endl;

	file << "add_combined" << agent << "_message(combined" << agent <<"_messages, c_id ,c_point , id, s,t, x, y, z );" << endl;
	file << "return 1;" << endl;
	file << "}" << endl;
	cout << "send combined:" << agent << endl;
}

//-------------------------------------------------------------
//== Function Name  : 

void need_location_function(string agent, string master){


	file << "/*" << endl;
	file << " * need_location" << agent << " FLAMEGPU Agent Function" << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_FUNC__ int need_location" << agent << "(xmachine_memory_" << master << "* agent, xmachine_message_location" << agent << "_list* location" << agent << "_messages, xmachine_message_location" << agent << "_PBM* partition_matrix){" << endl << endl;
	file << "    int c = 0, nearest_id;" << endl;
	file << "    float distance_check, x1, x2, y1, y2, z1, z2;" << endl;
	file << "    float nearest_distance = 0.0f;" << endl;
	file << "    x1 = agent->x;" << endl;
	file << "	 y1 = agent->y;" << endl;
	file << "    z1 = agent->z;" << endl << endl;
	file << "xmachine_message_location" << agent << "* current_message = get_first_location" << agent << "_message(location" << agent << "_messages, partition_matrix, agent->x, agent->y, agent->z);" << endl << endl;

	file << "  while (current_message)" << endl;
	file << "   {" << endl;
	file << "     if (current_message->id != agent->id){" << endl;

	file << "           x2 = current_message->x;" << endl;
	file << "	        y2 = current_message->y;" << endl;
	file << "	        z2 = current_message->z;" << endl;
	file << "           distance_check = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2));" << endl;
	file << "               if (distance_check <= radius) {" << endl;
	file << "                     if (c == 0) {" << endl;
	file << "                           c++;" << endl;
	file << "                           nearest_distance = distance_check;" << endl;
	file << "                           nearest_id = current_message->id;" << endl;
	file << "                      }" << endl;
	file << "                 else if (nearest_distance > distance_check){" << endl;
	file << "                        nearest_distance = distance_check;" << endl;
	file << "                        nearest_id = current_message->id;" << endl;
	file << "                     }" << endl;
	file << "                  }" << endl;
	
	file << "             }" << endl;
	file << "   current_message = get_next_location" << agent << "_message(current_message, location" << agent << "_messages, partition_matrix);" << endl << endl;
	file << "   }" << endl;
	file << " if (c == 1) {" << endl;
	file << "agent->state = AGENT_STATE_BIND;" << endl;
	file << "agent->closest_point = nearest_distance;" << endl;
	file << "agent->closest_id = nearest_id;" << endl;
	file << "}" << endl;
	file << "  else{" << endl;
	file << "     agent->closest_id = -1;" << endl;
	file << "   }" << endl << endl;
	file << "return 0;" << endl;
	file << "}" << endl;

	cout << "needLocation:" << agent << endl;
}
//-------------------------------------------------------------
//== Function Name  : 
void send_bind_function(string agent, string master){

	file << "/*" << endl;
	file << " * send_bind" << agent << " FLAMEGPU Agent Function" << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_FUNC__ int send_bind" << agent << "(xmachine_memory_" << master << "* agent, xmachine_message_bind" << agent << "_list* bind" << agent << "_messages){" << endl << endl;
	file << "int id, s, t, c_id;" << endl;
	file << "	float x, y, z, c_point;" << endl;
	file << "id = agent->id;" << endl;
	file << "	x = agent->x;" << endl;
	file << "y = agent->y;" << endl;
	file << "z = agent->z;" << endl;
	file << "t = agent->type;" << endl;
	file << "	s = agent->state;" << endl;
	file << "	c_point = agent->closest_point;" << endl;
	file << "c_id = agent->closest_id;" << endl;
	file << "add_bind" << agent << "_message(bind" << agent << "_messages, c_id ,c_point , id, s,t, x, y, z );" << endl;
	file << "return 0;" << endl;
	file << "}" << endl;
	cout << "send bind:" << agent << endl;

}//-------------------------------------------------------------

//-------------------------------------------------------------
//== Function Name  : 
void created_function(string agent, string master, string slave, int Slave_Number){
	file << "/*" << endl;
	file << " * created_" << agent << " FLAMEGPU Agent Function" << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_FUNC__ int created_" << agent << Slave_Number << "(xmachine_memory_" << master << "* agent, xmachine_memory_" << agent << "_list* " << agent << "_agents, xmachine_message_combined" << slave << "_list* combined" << slave << "_messages, xmachine_message_combined" << slave << "_PBM* partition_matrix, RNG_rand48* rand48){" << endl;
	
	file << "int c = 0;" << endl<<endl;
	file << "  xmachine_message_combined" << slave << "* current_message = get_first_combined" << slave << "_message(combined" << slave << "_messages, partition_matrix, agent->x, agent->y, agent->z);" << endl << endl;

	file << "  while (current_message)" << endl;
		file << "  {" << endl;
		file << "      if (current_message->id != agent->id){" << endl;

			file << "      if (current_message->closest_id == agent->id) {" <<endl;	

				file <<         "c++;" << endl; 

				file << "     }" << endl;
			file << "    else" << endl;
				file << "    {" << endl;
				file << "        current_message->state = AGENT_STATE_DEAD;" << endl;

				file << "    }" << endl;

			file << "    }" << endl;
			file << "      current_message = get_next_combined" << slave << "_message(current_message, combined" << slave << "_messages, partition_matrix);" << endl;

		file << "         }" << endl;
	file << "         if(c >= 1) {" << endl;
		file << "        agent->state = 6;" << endl;
		file << "        add_" << agent << "_agent(" << agent << "_agents, 0.0, 0, agent->id,  AGENT_STATE_" << agent << "_DEFAULT, 1 ,agent->x, agent->y, agent->z );" << endl;
		file << "    }" << endl;
		file << "     return 0;" << endl;
		file << "  }" << endl;
		cout << "created:" << agent << "for slave"<<slave<<endl;
}//-------------------------------------------------------------

//-------------------------------------------------------------
//== Function Name  : 
void death_function(string master){
	file << "/*" << endl;
	file << " * death_" << agent << " FLAMEGPU Agent Function" << endl;
	file << "*/" << endl;
	file << "__FLAME_GPU_FUNC__ int death_" << master << "(xmachine_memory_" << master << "* agent){" << endl << endl;
	file << "  return 1;" << endl << endl;
	file << "}" << endl;


	cout << "death:" << master << endl;

}//-------------------------------------------------------------