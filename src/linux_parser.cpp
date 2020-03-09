#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> version;
  }
  return kernel+ " "+ version ;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::ifstream fileStream(kProcDirectory + kMeminfoFilename);
  float totalMemoryUsage = 0;
  if(fileStream.is_open()){
	std::string line;
    std::string memTitle; 
    float memValue = 0;
    std::vector<double> memValues;
    while(getline(fileStream, line) && memValues.size() < 5) {
      std::istringstream stringStream(line);
      stringStream >> memTitle >> memValue;
      memValues.push_back(memValue);
    }
    if(memValues.empty()){ return 0; }
    float memTotal =  memValues[0];
    float memFree = memValues[1];
    float totalUsedMemory = memTotal - memFree;
    float total = totalUsedMemory - (memValues[3] + memValues[4]);
  	float totalPercentage = (total * 100.0) / totalUsedMemory;
    totalMemoryUsage = totalPercentage/100;
    return totalMemoryUsage;
  }
  return totalMemoryUsage;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::ifstream fileStream(kProcDirectory + kUptimeFilename);
  long upTime = 0;
  long idle = 0;
  if(fileStream.is_open()){
    std::string line;
    getline(fileStream, line);
    std::istringstream stringStream(line);
    stringStream >> upTime >> idle;
    return upTime;
  }
  return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { return pid; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  std::ifstream fileStream(kProcDirectory + kStatFilename);
  vector<string> cpuInformation{};
  if(fileStream.is_open()){
    std::string line;
    while(getline(fileStream, line)) {
      std::string title = "";
      std::istringstream stringStream(line);
      stringStream >> title;
      if(title == "cpu") {
        string value = "";
        while(stringStream >> value) {
          cpuInformation.push_back(value);
        }
        return cpuInformation;
      }
    }
  }
  return cpuInformation;
}

float LinuxParser::CpuUsage(int pid) {
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatFilename);
  vector<float> cpuInformation{};
  float  cpuTotalUsage = 0;
  if(fileStream.is_open()){
    std::string line;
    while(getline(fileStream, line)) {
      string value = "";
      std::istringstream stringStream(line);
      stringStream >> value;
      int index = 0;
      while(stringStream >> value) {
        if((index >= 14 && index<= 17 ) || index == 22)
        {
        	cpuInformation.push_back(stof(value));
        }
        ++index;
      }
    }
    float totalTime = cpuInformation[CPUKeys::kUTime] +  cpuInformation[CPUKeys::kSTime] + cpuInformation[CPUKeys::kCUTime] + cpuInformation[CPUKeys::kCSTime];
    float clockTicks = sysconf(_SC_CLK_TCK);
    float elapsedTime = LinuxParser::UpTime() - (cpuInformation[CPUKeys::kStartTime] / clockTicks);
    cpuTotalUsage = 100 * ((totalTime / clockTicks) / elapsedTime);
    return cpuTotalUsage;
  }
  return cpuTotalUsage;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::ifstream fileStream(kProcDirectory + kStatFilename);
  if(fileStream.is_open()){
      std::string line;
      while(getline(fileStream, line)) {
        std::string title = "";
        int value = 0;
        std::istringstream stringStream(line);
        stringStream >> title >> value;
        if(title == "processes") {
          return value;
        }
      }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
   std::ifstream fileStream(kProcDirectory + kStatFilename);
  if(fileStream.is_open()){
      std::string line;
      while(getline(fileStream, line)) {
        std::string title = "";
        int value = 0;
        std::istringstream stringStream(line);
        stringStream >> title >> value;
        if(title == "procs_running") {
          return value;
        }
      }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream fileStream(kProcDirectory + std::to_string(pid)  + kCmdlineFilename);
  std::string cmd = "";
  if(fileStream.is_open()){
	std::string line;
    getline(fileStream, line);
    std::istringstream stringStream(line);
    stringStream >> cmd;
  }
  return "  "+ cmd;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::ifstream fileStream(kProcDirectory + std::to_string(pid)  + kStatusFilename);
  float memValue = 0;
  if(fileStream.is_open()){
	std::string line;
    std::string memTitle; 
    while(getline(fileStream, line)) {
      std::istringstream stringStream(line);
      stringStream >> memTitle >> memValue;
      //Using VmData instead of VmSize per review comment because as explained  VmData  gives the exact physical memory being used as a part of Physical RAM. i.e. the Code, Data and Stack segments, explained in the man pages.
      if(memTitle == "VmData:") {
        break;
      }
    }
  }
  float result = memValue / 1024.0;
  char value[6];
  sprintf(value,"%.2f",result);
  return value;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(fileStream.is_open()){
      std::string line;
      while(getline(fileStream, line)) {
        std::string title = "";
        std::string value = "";
        std::istringstream stringStream(line);
        stringStream >> title >> value;
        if(title == "Uid:") {
          return value;
        }
      }
  }
  return "";
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::string userId = LinuxParser::Uid(pid);
  std::ifstream fileStream(kPasswordPath);
  if(fileStream.is_open()){
      std::string line;
      while(getline(fileStream, line)) {
        std::istringstream stringStream(line);
        std::string value = "";
        std::vector<string> values;
        while(std::getline(stringStream, value, ':'))
        {
          values.push_back(value);
        }
        if(userId.compare(values[2]) == 0) {
          return values[0];
        }
        values.clear();
      }
  }
  return NULL;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) {
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatFilename);
  long int upTime = 0;
  int index = 0;
  if(fileStream.is_open()){
    std::string line;
    getline(fileStream, line);
    std::istringstream stringStream(line);
    std::string value = "";
    while(std::getline(stringStream, value, ' '))
    {
      if(index == 21) {
        upTime = stol(value) / sysconf(_SC_CLK_TCK);
        return upTime;
      }
      ++index;
    }  
  }
  return upTime;
}