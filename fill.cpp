/**
 * генерирует текстовый файл для тренировки нейросети
 * отсюда https://github.com/Winderton/nerualnet
 * 
 **/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>


int main()
{
   std::fstream fout;
   fout.open("testData.txt");
   fout << "topology: 2 2 1" << std::endl;
   for (int i = 100000; i >= 0; i--) {
      double n1 = rand() / double(RAND_MAX);
      double n2 = rand() / double(RAND_MAX);
      double t = n1 * n2;

      fout << "in: " << n1 << " " << n2 << std::endl;
      fout << "out: " << t << std::endl;
   }
   fout.close();
}