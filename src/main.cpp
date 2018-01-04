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
   cout.precision (3);
   for (unsigned i = 0; i < v.size(); i++)
      std::cout << '\t' << v[i] << " ";
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
   // третий половина второго 40
   // пока без третьего
   std::vector<unsigned> topology;
   topology.push_back(120);
   topology.push_back(160);
   topology.push_back(80);
   topology.push_back(40);
   topology.push_back(5);
   NeuralNet net(topology);

   // тут добавить (или в конструктор сети/нейрона) считывание весов из файла сети

   // тренировка сети по историческим данным
   // задаётся количество проходов
   // проходы беруться рандомно из исторических данных
   // НЕ СДЕЛАНО
   // по окончанию тренировки проходим по всем данным по порядку, считаем среднюю ошибку
   std::vector<double> inputVals, targetVals, resultVals, errors;
   int trainingPass = 0;
   while ( trainingPass < 100000)
   {
      ++trainingPass;
      std::cout << std::endl << "Pass: " << trainingPass << std::endl;

      trainingData.getVals (inputVals, targetVals);
      // showVectorVals("Input:", inputVals);
      net.feedForward (inputVals);
      net.getResults (resultVals);
      net.backProp (targetVals);

      trainingData.abnormilize (targetVals, resultVals);
      showVectorVals("Targets:", targetVals);
      showVectorVals("Outputs:", resultVals);
      errors.clear();
      for (unsigned i = 0; i < 5; i++)
         errors.push_back ( (resultVals[i] - targetVals[i]) / targetVals[i] * 100 );
      showVectorVals("Errors:", errors);

      // std::cout << "Net average error: " << net.getRecentAverageError() << std::endl;

   }

   std::cout << std::endl << "Done" << std::endl;

   system("PAUSE");

   return(0);
}