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

int Process::Pid() { return id; }

float Process::CpuUtilization() { return LinuxParser::CpuUsage(Pid()); }

string Process::Command() { 
  std::string command = LinuxParser::Command(Pid());
  if(command.size() > 50){
    string command_sub_str = command.substr(0,49);
    command_sub_str.append("...");
    return command_sub_str;
  }
  return command; 
}

string Process::Ram() { return LinuxParser::Ram(Pid()); }

string Process::User() { return LinuxParser::User(Pid()); }

long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

bool Process::operator>(Process a) { 
  double cpu1 = this->CpuUtilization();
  double cpu2 = a.CpuUtilization();
  return  cpu1 > cpu2;
}