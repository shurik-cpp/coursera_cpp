#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

// Предварительное объявление шаблонных функций
template <typename T>
T Sqr(T x);

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p); // для пар

template <typename Key, typename Val>
map<Key, Val> Sqr(map<Key, Val> m); // для словарей

template <typename T>
vector<T> Sqr(vector<T> v); // для векторов


// Объявляем шаблонные функции
template <typename T>
T Sqr(T x) {
  return x * x;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) { // для пар
  return make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename Key, typename Val>
map<Key, Val> Sqr(map<Key, Val> m) { // для словарей
  for (auto& it : m) {
    it.second = Sqr(it.second);
  }
  return m;
}

template <typename T>
vector<T> Sqr(vector<T> v) { // для векторов
  for (auto& it : v) {
    it = Sqr(it);
  }
  return v;
}


int main() {
  // Пример вызова функции
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }

  return 0;
}
