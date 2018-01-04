/**
 * источник
 * https://github.com/Winderton/nerualnet
 * 
 **/

#pragma once

#include <vector>
#include "trainingSet.h"
#include "neuron.h"



class NeuralNet
{
public:
   // topology вектор с количеством нейронов в каждом слое
   NeuralNet (const std::vector<unsigned> &topology);

   void feedForward (const std::vector<double> &inputVals);

   void backProp (const std::vector<double> &targetVals);

   void getResults (std::vector<double> &resultVals) const;

   double getRecentAverageError() const { return recentAverageError; }

   
private:

   std::vector<Layer> layers; // layers[layerNumber][NeuronNumber]

   double error;

   double recentAverageError;

   static double recentAverageSmoothingFactor;
};
