#include "processor.h"
#include <string>
#include "linux_parser.h"
#include <vector>
using std::string;
using std::vector;
using std::stof;
float Processor::Utilization() {
  string line;
  string key;
  string user;
  string nice;
  string system;
  string idle;
  string iowait;
  string irq;
  string softirq;
  string steal;
  string guest;
  string guest_nice;

  float total_time;
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal>>guest>>guest_nice) {
        if (key == "cpu") {
            total_time = stof(user)+stof(nice)+stof(system)+stof(idle)+stof(iowait)+stof(irq)+stof(softirq)+stof(steal)+stof(guest)+stof(guest_nice);


          return (total_time-stof(idle))/total_time;
        }
      }
    }
  }    
    
    
     return 0.0; }