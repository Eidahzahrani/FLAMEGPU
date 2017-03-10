
#ifndef MASTER_H_
#define MASTER_H_

#include<string>
#include<iostream>
#include<vector>
#include"FileAgent.h"
#include"ModelDescription.h"

using namespace std;

void addMaster(std::string master, std::vector<FileAgent> slaves, std::vector<FileAgent>combinds, ModelDescription &model);
void addSlave(vector<FileAgent> slaves, ModelDescription &model);
void addCombind(std::vector<FileAgent>combinds, ModelDescription &model);
void addlayer(int line, string master, vector<FileAgent> slaves, vector<FileAgent>combinds, ModelDescription &model);
#endif