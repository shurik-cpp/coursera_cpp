/* Реализуйте функцию void Reverse(vector<int>& v),
 * которая переставляет элементы вектора в обратном порядке.
*/
#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector<int>& v) {
  vector<int> temp = v;

  v.clear();

  for (int i = temp.size() - 1; i >= 0; i--) {
    v.push_back(temp[i]);
    //cout << "i = " << i << endl;
  }
 // cout << "=============" << endl;
}

/*
void Reverse(vector<int>& v) {
  int n = v.size();  // для удобства сохраним размер вектора в переменную n
  for (int i = 0; i < n / 2; ++i) {
    // элемент с индексом i симметричен элементу с индексом n - 1 - i
    // поменяем их местами с помощью временной переменной tmp
    int tmp = v[i];
    v[i] = v[n - 1 - i];
    v[n - 1 - i] = tmp;
  }
}
*/
