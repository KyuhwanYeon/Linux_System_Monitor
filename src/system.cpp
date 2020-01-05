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

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
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
    std::cout<<processes_[idxPID].UpTime()<<std::endl;
  }

  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  std::string s = LinuxParser::Kernel();
  return s;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }
// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }