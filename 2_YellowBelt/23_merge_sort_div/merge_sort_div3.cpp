#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

template <typename T>
void PrintVector(const vector<T>& v) {
  for (const auto& it : v) {
    cout << it << ' ';
  }
  cout << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // Если диапазон содержит меньше 2 элементов, выйти из функции.
  if (range_end - range_begin < 2) {
    //cout << "elements.size() = " << elements.size() << endl;
    return;
  }

  // Создать вектор, содержащий все элементы текущего диапазона
  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  // Разбить вектор на 3 равные части.
  // Вызвать функцию MergeSort от каждой части вектора

  MergeSort(begin(elements), begin(elements) + elements.size() / 3);
  MergeSort(begin(elements) + elements.size() / 3, begin(elements) + (elements.size() / 3) * 2);
  MergeSort(begin(elements) + (elements.size() / 3) * 2, end(elements));

  // Слить первые две трети вектора с помощью алгоритма merge,
  // сохранив результат во временный вектор с помощью back_inserter
  vector<typename RandomIt::value_type> temp;
  merge(begin(elements), begin(elements) + elements.size() / 3,
        begin(elements) + elements.size() / 3, begin(elements) + (elements.size() / 3) * 2,
        back_inserter(temp));

  // Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2,
  // записав полученный отсортированный диапазон вместо исходного
  merge(temp.begin(), temp.end(),
        begin(elements) + (elements.size() / 3) * 2, end(elements),
        range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};

  // ожидаемый вывод: 0 1 4 4 4 5 6 6 7
  MergeSort(begin(v), end(v));

  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
