/* Напишите функцию, которая:
 * называется PalindromFilter
 * возвращает vector<string>
 * принимает vector<string> words и int minLength и возвращает все строки из вектора words,
 * которые являются палиндромами и имеют длину не меньше minLength
 *
 * Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
 *
 * На проверку пришлите файл с реализацией функции PalindromFilter.
 * Ваш файл может содержать и другие функции, если они вам необходимы.
 * В этой задаче ваша программа не обязана что-то считывать из stdin и записывать в stdout —
 * тестирующая система будет вызывать вашу функцию PalindromFilter напрямую
*/

#include <iostream>
#include <PalindromFilter.cpp>
#include <vector>
#include <string>

using namespace std;

int main() {
  cout << "Start" << endl;

  vector<string> given = {"lol" , "kek", "cheburek"};
  //vector<string> given = {"abacaba" , "aba"};
  //vector<string> given = {"weew", "bro", "code"};
  //cout << "vector<string> given = {};" << endl;
  uint16_t minLength = 3;

  cout << "vector<string> filtredVector = PalindromFilter(given, " << minLength << ')' << endl;
  vector<string> filtredVector = PalindromFilter(given, minLength);

  cout << "filtredVector.size() = " << filtredVector.size() << endl;
  for (uint16_t i = 0; i < filtredVector.size(); ++i) {
    cout << filtredVector[i] << ", ";
  }

  return 0;
}
