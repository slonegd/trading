/**
 * в основе
 * https://github.com/Winderton/nerualnet
 * переделал под свою тренировку
 * 
 **/

#include "neuralNet.h"

void showVectorVals(std::string label, std::vector<double> &v)
{
   std::cout << label << " ";
   for (unsigned i = 0; i < v.size(); i++)
      std::cout << v[i] << " ";
   std::cout << std::endl;
}

int main()
{
   // изменить trainingData под свои данные
   trainingSet trainingData("historyData/all.txt");
   // суть индикатора
   // беруться данные за 24 дня (средняя/максимальная/минимальная/кол-во заявок/объём)
   // итого входных 24*5 = 120
   // выходные - теже данные на следующий день итого 5
   // внутренние
   // первый слой по количеству входов + треть 160
   // второй половина первого 80
   // пока без третьего
   std::vector<unsigned> topology;
   topology.push_back(120);
   topology.push_back(160);
   topology.push_back(80);
   topology.push_back(5);
   NeuralNet net(topology);

   // тут добавить (или в конструктор сети/нейрона) считывание весов из файла сети

   // тренировка сети по историческим данным
   // задаётся количество проходов
   // проходы беруться рандомно из исторических данных
   // по окончанию тренировки проходим по всем данным по порядку, считаем среднюю ошибку
   std::vector<double> inputVals, targetVals, resultVals;
   int trainingPass = 0;
   while (!trainingData.isEOF())
 /*  {
      ++trainingPass;
      std::cout << std::endl << "Pass: " << trainingPass << std::endl;

      if (trainingData.getNextInputs(inputVals) != topology[0])
         break;
      showVectorVals("Input:", inputVals);
      net.feedForward(inputVals);

      trainingData.getTargetOutputs(targetVals);
      showVectorVals("Targets:", targetVals);
      assert(targetVals.size() == topology.back());

      net.getResults(resultVals);
      showVectorVals("Outputs", resultVals);

      net.backProp(targetVals);

      std::cout << "Net average error: " << net.getRecentAverageError() << std::endl;
   }

   std::cout << std::endl << "Done" << std::endl;
   system("PAUSE");
   */
   return(0);
}