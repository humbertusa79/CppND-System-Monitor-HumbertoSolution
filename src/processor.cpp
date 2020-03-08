#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  vector<string> cpuInformation = LinuxParser::CpuUtilization();
  float previdle = prevIdle + prevIOWait;
  float idle = stof(cpuInformation[CPUStates::kIdle_]) + stof(cpuInformation[CPUStates::kIOwait_]);
  float prevNonIdle = prevUser + prevNice + prevSystem + prevIrq + prevSoftIrq + prevSteal;
  float nonIdle = stof(cpuInformation[CPUStates::kUser_]) + stof(cpuInformation[CPUStates::kNice_]) + stof(cpuInformation[CPUStates::kSystem_]) + stof(cpuInformation[CPUStates::kIRQ_]) + stof(cpuInformation[CPUStates::kSoftIRQ_]) + stof(cpuInformation[CPUStates::kSteal_]);
  float prevTotal = previdle + prevNonIdle;
  float total = idle + nonIdle;
  float totald = total - prevTotal;
  float idled = idle + prevIdle;
  return (totald - idled)/totald;
}