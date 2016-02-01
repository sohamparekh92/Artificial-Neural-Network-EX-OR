#include<iostream>
#include<vector>
#include"neuron.h"

typedef std::vector<Neuron> Layer;

class Net
{
 public:
 Net();

 void setNetwork(std::vector<unsigned> &topology);
 void feedForward(const std::vector<double> &inputVals);
 void backProp(const std::vector<double> &targetVals);
 void getResults(std::vector<double> &resultVals) ;

 private:
 unsigned numLayers;
 std::vector<Layer> layers;
 double error;

};


