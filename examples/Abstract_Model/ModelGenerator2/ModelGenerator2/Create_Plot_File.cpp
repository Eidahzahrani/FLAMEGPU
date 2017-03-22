

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include"Create_Plot_File.h"
#include"FileModel.h"
#include"FileLine.h"
#include"FileAgent.h"

using namespace std;

ofstream File;
//FileLine l1;
vector<FileLine>Lines;
vector<FileAgent>slaveagent;
vector<FileAgent>combindagent;
vector<string >equation;
vector<string>Masters;
vector<string>Slaves;
vector<string>Combineds;
FileAgent agent1("E");




void Create_Plot(FileModel model){
	int state = 0;
	int z;
	int counter = 2;
	string s;
	File.open("..\\..\\plot_agent_counts.plot.gpl");
	if (!File.is_open()) {
		// The file could not be opened
	}
	else {
		File << "#This is a GNU plot script for agent outputs" << endl;
		File << "set title ""\"Agent population counts for ";
		Lines = model.getlines();
		int size = Lines.size();
		//print out all lines of equation to the plot file 
		for (int i = 0; i < size; i++){
			title(Lines[i]);
		}
		
		File << "\" "<<endl;
		File << "set xlabel ""\"Iteration number" << "\" " << endl;
		File << "set ylabel ""\"Agent Population Count" << "\" " << endl;
		File << "plot ";
		for (int j = 0;j < size; j++){
			agent1 = Lines[j].getMaster();
			File << """\"output.dat" << "\" " << "using 1:" << counter << " title '" << agent1.getName()<< "', \\" << endl;
			counter++;
			slaveagent = Lines[j].getSlaves();
			 int z1 = slaveagent.size();
			 cout << z1;
		for (int i = 0; i < z1; i++){
			
			File << "    ""\"output.dat" << "\" " << "using 1:" << counter << " title '" << slaveagent[i] << "', \\" << endl;
			counter++;
		}
		combindagent = Lines[j].getCombined();
		int z2 = combindagent.size();
		cout << "z2" << z2;
		for (int i = 0; i < z2; i++){
			if (j==Lines.size()-1)
				File << "    ""\"output.dat" << "\" " << "using 1:" << counter << " title '" << combindagent[i] << "'," << endl;
			else
				File << "    ""\"output.dat" << "\" " << "using 1:" << counter << " title '" << combindagent[i] << "', \\" << endl;
			counter++;
		}
	
		}

	}

	File.close();// close the file 

}

void title(FileLine line){
	int size = 0;
	agent1 = line.getMaster();
	equation.push_back(agent1.getName());
	Masters.push_back(agent1.getName());
	equation.push_back("+");
	slaveagent = line.getSlaves();
	int size_S = slaveagent.size();
	size = size_S - 1;
	for (int i = 0; i < size_S; i++){
		equation.push_back(slaveagent[i].getName());//stor slaves for printing out equation
		Slaves.push_back(slaveagent[i].getName());
		if (i<size)equation.push_back("+");
		else equation.push_back("=");
	}
	combindagent = line.getCombined();
	equation.push_back(combindagent[0].getName());
	Combineds.push_back(combindagent[0].getName());

	size = equation.size();
	for (int i = 0; i < size; i++){
		File << equation[i]; //print out all inserted equations 
	}
	File << ",";
	equation.clear();
}