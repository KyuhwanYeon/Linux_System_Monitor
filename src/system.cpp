#include "system.h"
#include <unistd.h>
#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include <algorithm>

using namespace std;
using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

bool CompareCpuUtilization(Process p1, Process p2) 
{ 
    return p1.CpuUtilization() > p2.CpuUtilization(); 
} 

vector<Process>& System::Processes() {
  int PID;
  vector<int> vecPID = LinuxParser::Pids();
  int numProcess = vecPID.size();
  vector<Process> Tmp(numProcess);
  processes_ = Tmp;
  
  for (int idxPID = 0; idxPID < numProcess; idxPID++) {
    PID =vecPID[idxPID];
    processes_[idxPID].Pid(PID);
    processes_[idxPID].User(PID);
    processes_[idxPID].Command(PID);
    processes_[idxPID].Ram(PID);
    processes_[idxPID].CpuUtilization(PID);
    processes_[idxPID].UpTime(PID);

  }
  sort(processes_.begin(),processes_.end(),CompareCpuUtilization); // sort the process according to the usage of CPU to show up first which will be having hiest CPU usage

  return processes_;
}


std::string System::Kernel() {
  std::string s = LinuxParser::Kernel();
  return s;
}


float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }


std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }


int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }


int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }