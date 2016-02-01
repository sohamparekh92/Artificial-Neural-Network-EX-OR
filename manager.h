#include "net.h"
#include<cstdlib>
#include<iostream>
#include<vector>

class Manager
{
 public:
 Manager();
 ~Manager() {}
 void Run();

 private:
 std::vector<unsigned> topology;

 Net myNet;

 std::vector<double> inputVals;
 std::vector<double> targetVals;
 std::vector<double> resultVals;
};
