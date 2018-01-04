/**
 * забирает исторические данные с сайта вебмани
 * необходима для тренировки нейросети
 * 
 **/

#include <string>
#include <iostream>
#include "curl/curl.h"
#include <sstream>
#include <regex>
#include <fstream>

using namespace std;

// буфер, для хранения возможной ошибки, размер определяется в самой библиотеке
static char errorBuffer[CURL_ERROR_SIZE];
static string buffer;


// функция обратного вызова
static int writer (char *data, size_t size, size_t nmemb, string *buffer)
{
   if (buffer != NULL) {
      buffer->append(data, size * nmemb);
      return size * nmemb;
   }
   return 0;
}


int main(void)
{
   fstream fout;
   fout.open("2016.txt");
   cmatch res;
   regex regular ( "(avgrate=\")"
                   "([.]*[^\"]+)"
                   "(\")"
                   "( maxrate=\")"
                   "([.]*[^\"]+)"
                   "(\")"
                   "( minrate=\")"
                   "([.]*[^\"]+)"
                   "(\")"
                   "( cntall=\")"
                   "([.]*[^\"]+)"
                   "(\")"
                   "( sumall=\")"
                   "([.]*[^\"]+)"
                   "(\")"
   );
   CURL *curl;
   CURLcode result;

   curl = curl_easy_init();
   if (curl) {
      curl_easy_setopt (curl, CURLOPT_ERRORBUFFER, errorBuffer);
      string url = "https://wm.exchanger.ru/asp/XMLQuerysStats.asp?exchtype=33&grouptype=3&yearstats=2016";
      curl_easy_setopt (curl, CURLOPT_URL, url.c_str());
      // указываем функцию обратного вызова для записи получаемых данных
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writer);
      // указываем куда записывать принимаемые данные
      curl_easy_setopt (curl, CURLOPT_WRITEDATA, &buffer);
      // запускаем выполнение задачи
      result = curl_easy_perform (curl);
      if (result == CURLE_OK) {
         cout << buffer << "\n";
         while (regex_search (buffer.c_str(), res, regular)) {
            // double n = stod (res[2]);
            fout << res[2] << " ";
            fout << res[5] << " ";
            fout << res[8] << " ";
            fout << res[11] << " ";
            fout << res[14] << endl;
            buffer = res.suffix().str();
         }
      } else {    
         cout << "Ошибка! " << errorBuffer << endl;
      }      
   }
   curl_easy_cleanup (curl);
   fout.close();
   return 0;
}