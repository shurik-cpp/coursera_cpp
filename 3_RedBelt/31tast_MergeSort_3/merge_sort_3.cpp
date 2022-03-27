#include "test_runner.h"
#include <algorithm>
#include <iterator>
#include <utility>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // Если диапазон содержит меньше 2 элементов, выйти из функции.
      if (range_end - range_begin < 2) {
        //cout << "elements.size() = " << elements.size() << endl;
        return;
      }

      // Создать вектор, содержащий все элементы текущего диапазона
      vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));

      // Разбить вектор на 3 равные части.
      // Вызвать функцию MergeSort от каждой части вектора

      MergeSort(begin(elements), begin(elements) + elements.size() / 3);
      MergeSort(begin(elements) + elements.size() / 3, begin(elements) + (elements.size() / 3) * 2);
      MergeSort(begin(elements) + (elements.size() / 3) * 2, end(elements));

      // Слить первые две трети вектора с помощью алгоритма merge,
      // сохранив результат во временный вектор с помощью back_inserter
      vector<typename RandomIt::value_type> temp;
      merge(make_move_iterator(begin(elements)),
            make_move_iterator(begin(elements) + elements.size() / 3),
            make_move_iterator(begin(elements) + elements.size() / 3),
            make_move_iterator(begin(elements) + (elements.size() / 3) * 2),
            back_inserter(temp));

      // Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2,
      // записав полученный отсортированный диапазон вместо исходного
      merge(make_move_iterator(temp.begin()),
            make_move_iterator(temp.end()),
            make_move_iterator(begin(elements) + (elements.size() / 3) * 2),
            make_move_iterator(end(elements)),
            range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
