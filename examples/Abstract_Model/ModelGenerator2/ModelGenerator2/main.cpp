#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileModel.h"
#include "FileLine.h"
#include "FileAgent.h"
#include "ModelDescription.h"
#include "General_Functions.h"
#include "Created_C_Functions.h"
#include"TreeNode.h"
#include"Iterator.h"
#include "Create_Plot_File.h"



using namespace std;

int main()
{
	int eidah = 0;
	
	string line;;
	FileModel m;
	int size = 0;
	ifstream inputfile;
	inputfile.open("program.txt");
	
	if (inputfile.is_open()) {//open the file 
		while (getline(inputfile, line)) {
			string str;
			FileLine l;
			cout << "dd*";
			//-----------New code--------//
			int mark = 0;
			size = line.length();
			//----------find equal sgin -------//
			for (int i = 0; i < size; i++){
				if (line[i] == '=') mark = i;
			}
			for (int i = 0; i < size; i++){

				if (i == 0) {
				str = line[0];
				FileAgent agent(str);
				l.addMaster(agent);
				m.addagent(str);
				}
				else if ((i < mark) && (isalpha(line[i]))){ str = line[i]; FileAgent agent2(str); l.addSlaves(agent2); m.addagent(str); }
				else if ((i > mark) && (isalpha(line[i]))){ str = line[i]; FileAgent agent1(str); l.addCombind(agent1); m.addagent(str); }
			}
			eidah++;
			m.addLine(l);

		}
	}
	inputfile.close();//close the file===================================================================================================

	//=========================================Get_lines=================================================================================//
	cout << "eidah:" << eidah;
		vector<FileLine>lines;
		FileLine l;
		vector<FileAgent>Slaveagent;
		vector<FileAgent>Combindagent;
		ModelDescription flame_model("Benchmark Model");
		FileAgent agent("str");
		string agent_name;
		lines = m.getlines();
		size = lines.size();
		cout << "the number of lines :" << size;
		for (int i = 0; i < size; i++){
			cout << "line number" << i + 1 << ":";
			l = lines[i];
			agent = l.getMaster();
			agent_name = agent.getName();
			cout << "agent_name" << agent_name;
			Slaveagent = l.getSlaves();
			cout << "the slaves are :";
			for (int i = 0; i < Slaveagent.size(); i++){
				cout << Slaveagent[i] << ",";
			}
			Combindagent = l.getCombined();
			cout << "the Combined are :";
			for (int i = 0; i < Combindagent.size(); i++){
				
				cout << Combindagent[i] << ",";
			}
			cout << endl;
			addMaster(agent_name, Slaveagent, Combindagent, flame_model);
			addSlave(Slaveagent, flame_model);
			addCombind(Combindagent, flame_model);
			addlayer(i, agent_name, Slaveagent, Combindagent, flame_model);
			
			
		}
	//==========================================OutPut FlameGPU XML File===========================================//
		iterations(m);
		ofstream outfile;
		XmlWriter xml;
		outfile.open("..\\..\\src\\model\\XMLModelFile.xml");
		flame_model.outputXML(outfile, xml);
		outfile.close(); 
		addModel_Functions(m);
		Create_Plot(m);
	system("pause");

	return 0;
}

//what should happen in main

//1) read in the files and create a FileModel object
//2) close file forget about the file

//3) for each unique agent name in a vector
//		create a FLAMEGPU Agent
//		add any agent variables and functions that are the same regardless of master/slave/combined
//		if agent is ONLY a combined
//			then add the functions (and variables) required for a combined agent (move)
//		if agent is a slave
//			then add the functions (and variables/messages) required for binding with a master
//		if agent is a master
//			then add the functions (and variables/messages) required for binding with ALL of the slaves. This will require a variable number of functions based on the file input.
//		//add FLAMEGPU agent to FLAMEGPUModel
//	Open a file for writing
//4) call FLAMEGPUModel outputXML(file *);
//		