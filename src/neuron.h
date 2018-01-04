/**
 * https://github.com/Winderton/nerualnet
 * 
 **/

#pragma once

#include <vector>
#include <cstdlib>
#include <cmath>

class neuron;

using Layer = std::vector<neuron>;

struct Connection {
   double weight;
   double deltaWeight;
};

class neuron {
public:
   // numOutputs для определения вектора выходных весов
   // myIndex ??
   neuron (unsigned numOutputs, unsigned myIndex);

   void setOutputVal (double val) { outputVal = val; }

   double getOutputVal() const { return outputVal; }

   void feedForward (const Layer &prevLayer);

   void calcOutputGradients (double targetVals);

   void calcHiddenGradients (const Layer &nextLayer);

   void updateInputWeights (Layer &prevLayer);


private:
   static double eta;

   static double alpha;

   static double randomWeight() { return rand() / double(RAND_MAX) / 1000; }

   static double activationFunction (double x);

   static double activationFunctionDerivative (double x);

   double sumDOW (const Layer &nextLayer) const;

   double outputVal;

   // выходные веса для следующего слоя
   // входные беруться с предыдущего
   std::vector<Connection> outputWeights;

   unsigned m_myIndex;

   double gradient;
};