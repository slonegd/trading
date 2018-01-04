/**
 * https://github.com/Winderton/nerualnet
 * 
 **/

#include "trainingSet.h"

using namespace std;

trainingSet::trainingSet(const string filename)
{
   ifstream trainingDataFile;
   trainingDataFile.open (filename.c_str());
   do {
      Data tmp;
      string line;
      getline (trainingDataFile, line);
      stringstream ss(line);
      double val = 0;
      unsigned int i;
      i = 0;
      while ( ss >> val )
         tmp.arr.at (i++) = val;
      data.push_back (tmp);
   } while ( !trainingDataFile.eof() );
}


void trainingSet::getVals (vector<double> &inputVals, vector<double> &targetVals)
{
   inputVals.clear();
   targetVals.clear();

   normalizeData ( rand() % (data.size() - 25) );

   for (unsigned i = 0; i < 24; i++)
      for (unsigned j = 0; j < 5; j++)
         inputVals.push_back (normData.at(i).arr.at(j));
   for (unsigned j = 0; j < 5; j++)
      targetVals.push_back (normData.at(24).arr.at(j));
}

void trainingSet::abnormilize (vector<double> &targetVals, vector<double> &outputVals)
{
   for (unsigned i = 0; i < 3; i++) {
      targetVals[i] = targetVals[i] * normK.avg + normK.avg;
      outputVals[i] = outputVals[i] * normK.avg + normK.avg;
   }
   for (unsigned i = 3; i < 5; i++) {
      targetVals[i] = 1 / targetVals[i];
      outputVals[i] = 1 / outputVals[i];
   }
}


///////////////////////////////////////////////////////////////////////////////
//
// PRIVATE
//
///////////////////////////////////////////////////////////////////////////////

void trainingSet::normalizeData (unsigned rndDay)
{
   unsigned normDay = rndDay + 23;
   for (unsigned i = 0; i < 5; i++)
      normK.arr.at(i) = data.at(normDay).arr.at(i);

   for (unsigned i = 0; i < 25; i++) {
      normData.at(i).avg = (data.at(i + rndDay).avg - normK.avg) / normK.avg;
      normData.at(i).max = (data.at(i + rndDay).max - normK.avg) / normK.avg;
      normData.at(i).min = (data.at(i + rndDay).min - normK.avg) / normK.avg;
      normData.at(i).cnt = 1 / data.at(i + rndDay).cnt;
      normData.at(i).vol = 1 / data.at(i + rndDay).vol;
   }
}