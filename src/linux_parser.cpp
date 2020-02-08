#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}


string LinuxParser::Kernel() {
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel>> version;
  }
  stream.close();
  return kernel;
}


vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  float MemTotal = 0;
  float MemFree = 0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          MemTotal = std::stof(value);
        }
        if (key == "MemFree") {
          MemFree = std::stof(value);
        }
        if (MemTotal > 0 && MemFree > 0) {
          return MemFree / MemTotal;
        }
      }
    }
  }

  return 1;
}

long LinuxParser::UpTime() {
  string line;
  string Uptime1;
  string Uptime2;
  long lnUptime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> Uptime1 >> Uptime2) {
       
        lnUptime=stol(Uptime1);
       // std::cout<<lnUptime<<std::endl;
        return lnUptime;
        
      }
    }
  }
  return lnUptime;
}

long LinuxParser::Jiffies() { return 0; }


long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }


long LinuxParser::ActiveJiffies() { return 0; }

long LinuxParser::IdleJiffies() { return 0; }


vector<string> LinuxParser::CpuUtilization() { return {}; }


int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  int numprocesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          numprocesses = std::stoi(value);
          return numprocesses;
        }
      }
    }
  }
  return NULL;
}

int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  int numprocesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          numprocesses = std::stoi(value);
          return numprocesses;
        }
      }
    }
  }
  return NULL;
}

string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }