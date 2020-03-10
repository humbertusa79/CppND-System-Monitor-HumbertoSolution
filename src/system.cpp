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
using namespace std;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() {
  vector<int> processesIds = LinuxParser::Pids();
  processes_.clear();
  for (unsigned index = 0; index < processesIds.size(); ++index) {
    int id = processesIds[index];
    Process process(id);
    processes_.emplace_back(process);
  }
  sortProcesses();
  return processes_;
}

bool compare(Process p1, Process p2) {
  return p1 > p2;
}

void System::sortProcesses() {
  sort(processes_.begin(), processes_.end(), compare);
}

string System::Kernel() { 
  return LinuxParser::Kernel();
}

float System::MemoryUtilization() { 
  return LinuxParser::MemoryUtilization();
}

string System::OperatingSystem() { 
  return LinuxParser::OperatingSystem();
}

int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

long int System::UpTime() { 
  return LinuxParser::UpTime();
}