#include "processor.h"

// TODO: Return the aggregate CPU utilization
double Processor::Utilization() { 
  vector<string> cpuInformation = LinuxParser::CpuUtilization();
  double previdle = prevIdle + prevIOWait;
  double idle = stod(cpuInformation[CPUStates::kIdle_]) + stod(cpuInformation[CPUStates::kIOwait_]);
  double prevNonIdle = prevUser + prevNice + prevSystem + prevIrq + prevSoftIrq + prevSteal;
  double nonIdle = stod(cpuInformation[CPUStates::kUser_]) + stod(cpuInformation[CPUStates::kNice_]) + stod(cpuInformation[CPUStates::kSystem_]) + stod(cpuInformation[CPUStates::kIRQ_]) + stod(cpuInformation[CPUStates::kSoftIRQ_]) + stod(cpuInformation[CPUStates::kSteal_]);
  double prevTotal = previdle + prevNonIdle;
  double total = idle + nonIdle;
  double totald = total - prevTotal;
  double idled = idle + prevIdle;
  return (totald - idled)/totald;
}