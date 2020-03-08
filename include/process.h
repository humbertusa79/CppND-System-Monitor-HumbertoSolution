#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator>(Process const& a) const;  // TODO: See src/process.cpp
  
  Process(int id, std::string userName, float cpu, std::string ram, std::string cmd, long int upTime) {
    this->id = id;
    this->user = userName;
    this-> cpuUtilization = cpu;
    this->ram = ram;
    this->command = cmd;
    this->upTime = upTime;
  }

  // TODO: Declare any necessary private members
 private:
  int id;
  std::string user;
  std::string command;
  float cpuUtilization;
  std::string ram;
  long int upTime;
};

#endif