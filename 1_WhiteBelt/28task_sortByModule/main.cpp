#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool module(int x, int y) {
  return (abs(x) < abs(y)); // возвращает true, если условие выполняется и false если нет
}

int main(){
  vector<int> v;

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    int temp;
    cin >> temp;
    v.push_back(temp);
  }

  sort(begin(v), end(v), module);

  for (const auto& k : v) {
    cout << k << ' ';
  }

  return 0;
}

/*
  // сортируем
  sort(begin(v), end(v), [](int l, int r) { // функция, сравнивающая abs(l) и abs(r) — модули чисел l и r
         return abs(l) < abs(r);
       }
  );
*/
