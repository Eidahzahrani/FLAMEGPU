


#ifndef CREATED_C_FUNCTIONS_H_
#define CREATED_C_FUNCTIONS_H_


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



void addModel_Functions( FileModel m);
void define_state(FileModel m);
void move_function(string agent);
void send_location_function(string agent);
void receive_bind_function(string agent);
void send_combined_function(string agent);
void need_location_function(string agent, string master);
void send_bind_function(string agent, string master);
void created_function(string agent, string master, string slave, int Slave_Number);
void death_function(string master);
void initfunction(FileModel m);
void stepfunction(FileModel m);
void exitfunction(FileModel m);

#endif