#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<vector>
#include<string>
#include<iostream>
#include "linux_parser.h"

using std::vector;
using std::string;
using std::stol;
using LinuxParser::CPUStates;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  long prevIdle{0};
  long prevIOWait{0};
  long prevUser{0};
  long prevNice{0};
  long prevSystem{0};
  long prevIrq{0};
  long prevSoftIrq{0};
  long prevSteal{0};
};

#endif