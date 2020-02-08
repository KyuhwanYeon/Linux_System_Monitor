#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                 // Accessor             
  std::string User();                    
  std::string Command();                  
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  

  void Pid(int numPID);   //Mutator
  void User(int numPID);
  void Command(int numPID);
  void CpuUtilization(int numPID);
  void Ram(int numPID);
  void UpTime(int numPID);


 private:
 int pid;
 std::string user;
 std::string command;
 float cpuutilization;
 std::string ram;
 long int uptime;

};

#endif