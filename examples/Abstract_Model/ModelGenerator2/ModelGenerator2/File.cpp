
#include "File.h"
#include <iostream>
#include<fstream>
#include <string>

using namespace std;

void output(std::ofstream &outfile, std::string s){
	string str = s;
	outfile.open("XMLModelFile.xml");
	outfile << str;
}