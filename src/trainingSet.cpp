/**
 * https://github.com/Winderton/nerualnet
 * 
 **/

#include "trainingSet.h"

trainingSet::trainingSet(const std::string filename)
{
   std::ifstream trainingDataFile;
   trainingDataFile.open (filename.c_str());
   do {
      Data tmp;
      std::string line;
      std::getline (trainingDataFile, line);
      std::stringstream ss(line);
      double val = 0;
      unsigned int i;
      i = 0;
      while ( ss >> val )
         tmp.arr.at (i++) = val;
      data.push_back (tmp);
   } while ( !trainingDataFile.eof() );
}

void trainingSet::getTopology(std::vector<unsigned> &topology)
{
   std::string line;
   std::string label;

   std::getline(trainingDataFile, line);
   std::stringstream ss(line);
   ss >> label;
   if (this->isEOF() || label.compare("topology:") != 0)
   {
      abort();
   }

   while (!ss.eof())
   {
      unsigned n;
      ss >> n;
      topology.push_back(n);
   }
   return;
}

unsigned trainingSet::getNextInputs(std::vector<double> &inputVals)
{
   inputVals.clear();

   std::string line;
   std::getline(trainingDataFile, line);
   std::stringstream ss(line);

   std::string label;
   ss >> label;
   if (label.compare("in:") == 0) {
      double oneValue;
      while (ss >> oneValue) {
         inputVals.push_back(oneValue);
      }
   }

   return inputVals.size();
}

unsigned trainingSet::getTargetOutputs(std::vector<double> &targetOutputVals)
{
   targetOutputVals.clear();

   std::string line;
   std::getline(trainingDataFile, line);
   std::stringstream ss(line);

   std::string label;
   ss >> label;
   if (label.compare("out:") == 0) {
      double oneValue;
      while (ss >> oneValue) {
         targetOutputVals.push_back(oneValue);
      }
   }

   return targetOutputVals.size();
}

///////////////////////////////////////////////////////////////////////////////
//
// PRIVATE
//
///////////////////////////////////////////////////////////////////////////////

void trainingSet::normalizeData()
{
   unsigned normDay = rndDay + 24;
   normK.avg = data.at(normDay).avg;
   normK.max = data.at(normDay).max;
   normK.min = data.at(normDay).min;
   normK.cnt = data.at(normDay).cnt;
   normK.vol = data.at(normDay).vol;
   for (auto d : normData)
      for (unsigned i = 0; i < d.arr.size(); i++)
         d.arr.at(i) =  (d.arr.at(i) - normK.arr.at(i)) / normK.arr.at(i);
}