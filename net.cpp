#include"net.h"
#include<cassert>
#include <cmath>
Net::Net(): numLayers(0),
layers(),
error(0.0)
{

}

void Net::setNetwork(std::vector<unsigned> &topology)
{
 //std::cout<<"Made a Network!"<<std::endl;
 numLayers = topology.size();
 for(unsigned int i=0;i<numLayers; ++i)
 {
  layers.push_back(Layer());
 // std::cout<<"Made Layer:"<<i+1<<std::endl;
  for(unsigned int j=0; j<=topology[i]; ++j)
  {
   if(i+1!= topology.size())
    layers.back().push_back(Neuron(topology[i+1], j));
   else
    layers.back().push_back(Neuron(0, j));
  }
 }
 layers.back().back().setOutputVal(0.1);
 //for(unsigned layerNum=0; layerNum<layers.size()-1 ;layerNum++)
 //layers[layerNum].back().setOutputVal(1.0);
}

void Net::feedForward(const std::vector<double> &inputVals)
{
 assert(inputVals.size() == layers[0].size()-1);
 //Set input
 for(unsigned inputNode = 0; inputNode<inputVals.size(); ++inputNode)
 layers[0][inputNode].setOutputVal(inputVals[inputNode]);
 //Feed propagate
 for(unsigned layerNum=1; layerNum<numLayers; ++layerNum)
 {
  std::vector<Neuron> &prevLayer = layers[layerNum-1];
  for(unsigned n=0; n<layers[layerNum].size()-1; ++n)
  layers[layerNum][n].feedForward(prevLayer);
 }
}

void Net::backProp(const std::vector<double> &targetVals)
{

 //Calculate net error e.g RMS
 Layer &outputLayer = layers.back();
 error=0.0;
 for(unsigned i=0; i<outputLayer.size()-1; ++i)
 {
  double delta = targetVals[i]-outputLayer[i].getOutputVal();
  error += delta*delta;
 }
 error = error/(outputLayer.size()-1);
 error = sqrt(error);
 //Calculate output layer gradient
 for(unsigned n=0; n< outputLayer.size() -1; ++n)
 outputLayer[n].calcOutputGradient(targetVals[n]);
 //Calculate hidden layer gradients
 for(unsigned layerNum = layers.size()-2; layerNum>0; --layerNum)
 {

  Layer &hiddenLayer = layers[layerNum];
  Layer &nextLayer = layers[layerNum+1];
  for(unsigned n = 0; n<hiddenLayer.size(); ++n )
  hiddenLayer[n].calcHiddenGradient(nextLayer);
  
 }

 //for all the layers from output to first hidden layer, update connection weights
 for(unsigned layerNum = layers.size()-1; layerNum>0; --layerNum)
 {
  Layer &currentLayer = layers[layerNum];
  Layer &prevLayer = layers[layerNum-1];
  for(unsigned n=0; n<currentLayer.size()-1; ++n )
  currentLayer[n].updateInputWeight(prevLayer);
 }
} 

void Net::getResults(std::vector<double> &resultVals) 
{
 resultVals.clear();
 for(unsigned i=0; i<layers.back().size(); ++i)
 resultVals.push_back(layers.back()[i].getOutputVal()); 
}







