#include "manager.h"
#include "traindata.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
Manager::Manager(): topology(),
myNet(),
inputVals(),
targetVals(),
resultVals() 
{
 int n = TrainData::getInstance().getXmlInt("Topology");
 while(n>0)
 {
  topology.push_back(n%10);
  n /= 10;
 }
 std::reverse(topology.begin(), topology.end());
 myNet.setNetwork(topology); 
}

void print(const std::vector<double>& vec, std::ofstream& myfile)
{
 for(unsigned i=0; i<vec.size(); ++i)
{
  std::cout<<vec[i]<<" ";
  myfile<<vec[i];
    myfile<<"\n";
 }
 std::cout<<std::endl;
}
void printResult(const std::vector<double>& vec, std::ofstream& myfile)
{
 for(unsigned i=0; i<vec.size()-1; ++i)
 {
  std::cout<<vec[i]<<" ";
  myfile<<vec[i];
  myfile<<"\n";
 }
 std::cout<<std::endl;
}

void Manager::Run()
{
 std::ofstream myfile;
 myfile.open("Output.txt");
 int input1, input2, targetOutput;
 for(int i=0; i<2000; ++i)
 {
  inputVals.clear();
  targetVals.clear();
  input1=rand()%2;
  input2=rand()%2;
  targetOutput=1;
  if(input1==input2) targetOutput=0;
  inputVals.push_back(input1);
  inputVals.push_back(input2);
  targetVals.push_back(targetOutput);
  myNet.feedForward(inputVals);
  myNet.backProp(targetVals);
  myNet.getResults(resultVals);
  myfile<<"Pass: "<<i<<"\n";
  std::cout<<"Input"<<std::endl;
  myfile<<"Input\n";
  print(inputVals, myfile);
  std::cout<<"TargetVals"<<std::endl;
  myfile<<"TargetVal\n";
  print(targetVals, myfile);
  std::cout<<"resultVals"<<std::endl;
  myfile<<"resultVal\n";
  printResult(resultVals, myfile);
  myfile<<"\n";
 }
 myfile.close();
}
