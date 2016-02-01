#include <iostream>
#include <fstream>
#include<cstdlib>
using namespace std;

int main () {
  ofstream myfile;
  int topology;
  myfile.open ("trainingData.xml");
  myfile << "<Data>\n";
  myfile << " <Topology>";
  std::cout<<"Enter Topology: "<<std::endl;
  std::cin>> topology;
  myfile <<topology;
  myfile <<"</Topology>\n";
  for(int i=0; i<200; i++)
  { 
   int input1 = rand()%2;
   int input2 = rand()%2;
   int output;
   if(input1 == input2) output = 0;
   else output = 1;
   myfile << " <Pass"<<i<<">\n";
   myfile << "  <Input"<<i<<"1>";
   myfile <<input1;
   myfile <<"</Input"<<i<<"1>\n";
   myfile <<"  <Input"<<i<<"2>";
   myfile <<input2;
   myfile <<"</Input"<<i<<"2>\n";
   myfile << "  <targetOutput"<<i<<">";
   myfile <<output;
   myfile <<"</targetOutput"<<i<<">\n";
   myfile <<" </Pass"<<i<<">\n";
  }
  myfile << "</Data>\n";
  myfile.close();
  return 0;
}
