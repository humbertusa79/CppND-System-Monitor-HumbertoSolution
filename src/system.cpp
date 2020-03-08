#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector; 

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> processesIds = LinuxParser::Pids();
  for (unsigned index = 0; index < processesIds.size(); ++index) {
    int id = processesIds[index];
    std::string userName = LinuxParser::User(id);
    float cpuUsage = LinuxParser::CpuUsage(id);
    std::string ram = LinuxParser::Ram(id);
    std::string cmd =  LinuxParser::Command(id);
    long int upTime = LinuxParser::UpTime(id);
    Process process(id, userName, cpuUsage, ram, cmd, upTime);
    processes_.push_back(process);
  }
  return processes_;
}

bool compare(const Process p1,const Process p2) {
  return p1 > p2;
}

void System::sortProcesses() {
  std::sort(processes_.begin(), processes_.end(), compare);
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
  return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
  return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
  return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
  return LinuxParser::UpTime();
}