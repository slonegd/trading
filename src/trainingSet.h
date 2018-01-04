/**
 * основа
 * https://github.com/Winderton/nerualnet
 * переделал под свои данные
 * 
 * в исторических данных файл в каждой строке которого по порядку
 * расположены данные (средняя/максимальная/минимальная/кол-во заявок/объём)
 * для обучения беруться 24 последовательные строки
 * результат - следующая за ними строка
 * 
 **/

#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>

class trainingSet
{
public:
   trainingSet(const std::string filename);

   bool isEOF() { return trainingDataFile.eof(); }

   void getTopology(std::vector<unsigned> &topology);

   unsigned getNextInputs(std::vector<double> &inputVals);

   unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

   double getAvgAt(unsigned n) { return data.at(n).avg; }


private:
   // исторические данные на 1 день
   union Data {
      struct {
         double avg;
         double max;
         double min;
         double cnt;
         double vol;
      };
      std::array<double, 5> arr;
   };
   // исторические данные за всё время (из файла)
   std::vector<Data> data;
   // нормализованные исторические данные
   // нормализация происходит путём вычетания и последующего деления
   // на среднее последнего (24) дня 
   std::array<Data, 25> normData;
   // рандомный номер с которого ведётся обучение от 0 до data.size()-25
   unsigned rndDay;
   // коэфициент нормализации равен среднему последнего (24) дня 
   Data normK;

   // не нужен будет
   std::ifstream trainingDataFile;

   // считает normK и normData из data, начиная с rndDay
   void normalizeData();
};