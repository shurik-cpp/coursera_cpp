#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // Если диапазон содержит меньше 2 элементов, выйти из функции.
  if (range_end - range_begin < 2) {
    //cout << "elements.size() = " << elements.size() << endl;
    return;
  }

  // Создать вектор, содержащий все элементы текущего диапазона
  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  // Разбить вектор на две равные части.
  // Вызвать функцию MergeSort от каждой половины вектора

  MergeSort(begin(elements), begin(elements) + elements.size() / 2);
  MergeSort(begin(elements) + elements.size() / 2, end(elements));

  // С помощью алгоритма std::merge слить отсортированные половины,
  // записав полученный отсортированный диапазон вместо исходного.
  merge(begin(elements), begin(elements) + elements.size() / 2,
        begin(elements) + elements.size() / 2, end(elements),
        range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};

  // ожидаемый вывод: 0 1 4 4 4 6 6 7
  MergeSort(begin(v), end(v));

  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
