#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return id; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUtilization; }

// TODO: Return the command that generated this process
string Process::Command() { 
  if(command.size() > 50){
    string command_sub_str = command.substr(0,49);
    command_sub_str.append("...");
    return command_sub_str;
  }
  return command; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { return ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return upTime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(Process const& a) const { 
  double cpu1 = this->cpuUtilization;
  double cpu2 = a.cpuUtilization;
  return  cpu1 > cpu2;
}