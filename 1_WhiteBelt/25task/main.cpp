/*
 * Напишите функцию BuildMapValuesSet, принимающую на вход словарь map<int, string>
 * и возвращающую множество значений этого словаря
*/

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <map_values.cpp>

using namespace std;

//set<string> BuildMapValuesSet(const map<int, string>& m){
//  set<string> result;
//  for (auto i : m){
//    result.insert(i.second);
//  }
//  return result;
//}


int main(){
  set<string> values = BuildMapValuesSet({
      {1, "odd"},
      {2, "even"},
      {3, "odd"},
      {4, "even"},
      {5, "odd"}
  });

  for (const string& value : values) {
    cout << value << endl;
  }

  return 0;
}
