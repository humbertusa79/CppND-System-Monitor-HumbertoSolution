#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return id; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::CpuUsage(Pid()); }

// TODO: Return the command that generated this process
string Process::Command() { 
  std::string command = LinuxParser::Command(Pid());
  if(command.size() > 50){
    string command_sub_str = command.substr(0,49);
    command_sub_str.append("...");
    return command_sub_str;
  }
  return command; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(Process a) { 
  double cpu1 = this->CpuUtilization();
  double cpu2 = a.CpuUtilization();
  return  cpu1 > cpu2;
}