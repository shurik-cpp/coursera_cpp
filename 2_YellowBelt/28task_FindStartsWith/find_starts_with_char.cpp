#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// Напишите функцию FindStartsWith:
//
// принимающую отсортированный набор строк
// в виде итераторов range_begin, range_end и один символ prefix;
//
// возвращающую диапазон строк, начинающихся с символа prefix,
// в виде пары итераторов.
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
                                        RandomIt range_end,
                                        char prefix) {
  /* нужна функция сравнения. Если типы разные, надо будет определить структуру сравнения,
   * как в примере на cppreferece. Но тебе такое рано)
   * Поэтому проще  всего тебе привести префикс из чара к строке
   * и сделать лямбру [](const string& a, const string& b) { return a[0] < b[0]; }
   * Префикс в явном виде в лямбде захватывать не нужно, он передаётся третьим параметром
   * в equal_range как value (см cppreference), а потом уже где-то там внутри он передаётся
   * в лямбду одним из двух параметров (a или b, когда как).
   * Полностью что-то вроде
   * equal_range(begin(v), end(v), prefix, [](const string& a, const string& b) { return a[0] < b[0]; })
   * при условии, что префикс стал строкой из одного символа, а не чаром.*/
  string p;
  p += prefix;
  pair<RandomIt, RandomIt> result = equal_range(range_begin, range_end, p,
                                                [](const string& a, const string& b) {
                                                  return a[0] < b[0];
                                                });
  return result;
}

int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  const auto m_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto p_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " "
       << (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " "
       << (z_result.second - begin(sorted_strings)) << endl;

  return 0;
}
