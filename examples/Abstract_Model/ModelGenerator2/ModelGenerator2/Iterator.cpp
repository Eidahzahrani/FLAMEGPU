

#include "Iterator.h"
#include <fstream>
#include <iostream>
#include <string>
#include "FileModel.h"
#include"FileLine.h"
#include"FileAgent.h"

using namespace std;


ofstream a_file;

//string combind;
int starter;
int S_S;
int s = 0;
int size_S = 0, size_C = 0, num = 0, itt = 0;
float a, b, c;
float x = 10.0;
int size = 0;
void iterations(FileModel m){

	FileLine l;
	vector<FileLine>lines;
	vector<FileAgent>Slaveagent;
	vector<FileAgent>Combindagent;
	FileAgent agent("E");
	string master;
	string slave;
	a_file.open("..\\..\\iterations\\0.xml");
	if (!a_file.is_open()) {
		// The file could not be opened
	}
	else {
		a_file << "<states><itno>0</itno><environment></environment>" << endl;
		lines = m.getlines();
		size = lines.size();
		//cout << "the size of all lines:" << size;
		for (int i = 0; i < size; i++){

			//cout << "line number" << i << ":";
			l = lines[i];
			agent = l.getMaster();
			master = agent.getName();
			Slaveagent = l.getSlaves();
			S_S = Slaveagent.size();
			//cout << "master:" << master << "slave size:" << S_S;
			num = writer(master, num, S_S, 1);
			S_S = 0;
			size_S = Slaveagent.size();
			for (int j = 0; j < size_S; j++){

				slave = Slaveagent[j].getName();
				num = writer(slave, num, S_S, j + i + 4);
				//cout << slave;
			}

		}
		a_file << "</states>" << endl;
	}
	a_file.close();
	cout << "0.xml File was Created.." << endl;
}

int writer(std::string s, int num, int itt, int state){
	int i = num;
	int size1 = num;

	if (itt != 0){
		itt = 4000* itt;
		size1 = size1 + itt;
		
	}
	else 	size1 = 4000 + size1;
	for (i; i <= size1-1; i++){

		a_file << "<xagent>" << endl;
		a_file << "<name>" << s << "</name>" << endl;
		a_file << "<id>" << i << "</id>" << endl;
		a = ((float)rand() / (float)(RAND_MAX))* x;
		a_file << "<x>" << a << "</x>" << endl;
		b = ((float)rand() / (float)(RAND_MAX))* x;
		a_file << "<y>" << b << "</y>" << endl;
		c = ((float)rand() / (float)(RAND_MAX)) * 1;
		a_file << "<z>" << c << "</z>" << endl;
		a_file << "<vx>0.0</vx>" << endl;
		a_file << "<vy>0.0</vy>" << endl;
		a_file << "<vz>0.0</vz>" << endl;
		a_file << "<count>0</count>" << endl;
		a_file << "<type>1</type>" << endl;
		a_file << "<state>" << state << "</state>" << endl;
		a_file << "<closest_point>" << "0.0" << "</closest_point>" << endl;
		a_file << "<closest_id>" << "0" << "</closest_id>" << endl;

		a_file << "</xagent>" << endl;
	}

	return i;

}


