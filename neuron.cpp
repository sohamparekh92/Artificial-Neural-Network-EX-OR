#include"neuron.h"
#include<iostream>
#include<cstdlib>
#include<cmath>

double Neuron::alpha =0.3;
double Neuron::eta =0.02;

double Neuron::getWeightInRange()
{
 return rand()/double(RAND_MAX);
}

Neuron::Neuron(unsigned n, unsigned i): outputs(n),
index(i),
outputVal(0),
gradient(0.0),

connections()
{
// std::cout<<"Made a Neuron with no. of outputs:"<<outputs<<std::endl;
 for(unsigned c=0; c<outputs; ++c)
 {
  connections.push_back(Connection());
  connections.back().weights = getWeightInRange();
 }
}

double Neuron::transferFunction(double sum) 
{
  return tanh(sum);
}

double Neuron::transferFunctionDerivative(double x) 
{
 return 1.0-x*x;
}

void Neuron::feedForward(const std::vector<Neuron> &prevLayer)
{
 double sum = 0.0;
 for(unsigned i=0; i<prevLayer.size(); ++i)
 sum+=prevLayer[i].outputVal*prevLayer[i].connections[index].weights; 
 outputVal = Neuron::transferFunction(sum);

}

void Neuron::calcOutputGradient(double targetVal)
{

 double delta = outputVal - targetVal;
 gradient = delta*Neuron::transferFunctionDerivative(outputVal);

}

void Neuron::calcHiddenGradient(const std::vector<Neuron> &nextLayer)
{
 double sum_DOW = Neuron::sumDOW(nextLayer);
 gradient = sum_DOW*Neuron::transferFunctionDerivative(outputVal);

}

 void Neuron::updateInputWeight( std::vector<Neuron> &prevLayer)
{
 for(unsigned n=0; n<prevLayer.size(); ++n)
 {
  Neuron &ne = prevLayer[n];
  double oldDeltaWeight = ne.connections[index].deltaWeights;
  double newDeltaWeight = eta*ne.getOutputVal()*gradient+alpha*oldDeltaWeight;
  ne.connections[index].deltaWeights = newDeltaWeight;
  ne.connections[index].weights+= newDeltaWeight;
 }
}
double Neuron::sumDOW(const std::vector<Neuron> &nextLayer) const
 double sum = 0.0;
 for(unsigned n=0; n<nextLayer.size()-1; ++n)
 sum+= connections[n].weights*nextLayer[n].gradient;

 return sum;
}


