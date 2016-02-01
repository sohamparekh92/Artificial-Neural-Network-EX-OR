#include<iostream>
#include<vector>

struct Connection
{
 double weights;
 double deltaWeights;
};

class Neuron
{
 public:
 Neuron(unsigned n, unsigned i);
 void setOutputVal(const double out) { outputVal = out; }
 double getOutputVal() const { return outputVal; }

 void feedForward(const std::vector<Neuron> &prevLayer);
 void calcOutputGradient(double targetVal);
 void calcHiddenGradient(const std::vector<Neuron> &nextLayer);
 void updateInputWeight( std::vector<Neuron> &prevLayer);

 private:
 Neuron();
 double sumDOW(const std::vector<Neuron> &nextLayer) const;

 static double transferFunction(double sum) ;
 static double transferFunctionDerivative(double x) ;
 static double getWeightInRange();

 unsigned outputs;
 unsigned index;

 double outputVal;
 double gradient;
 static double alpha; //momentum
 static double eta; //learning rate

 std::vector<Connection> connections;
};


