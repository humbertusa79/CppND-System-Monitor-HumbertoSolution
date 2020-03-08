#include <string>
#include <iostream>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  long time = seconds;
  char buffer[20];
  long hrs = 0;
  long min = 0;
  long sec = 0;
  hrs = time / 3600;
  time = time % 3600;
  min = time / 60;
  time = time % 60;
  sec = time;
  sprintf(buffer,"%.2d : %.2d : %.2d", hrs, min, sec);
  return buffer;
}