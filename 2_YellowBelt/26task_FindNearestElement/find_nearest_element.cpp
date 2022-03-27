#include <iostream>
#include <set>

using namespace std;

// Напишите функцию FindNearestElement, для множества целых чисел numbers
// и данного числа border возвращающую итератор на элемент множества,
// ближайший к border.
// Если ближайших элементов несколько, верните итератор на наименьший из них.
set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
  // set<int>::const_iterator — тип итераторов для константного множества целых чисел
  if (numbers.count(border)) return numbers.lower_bound(border);
  auto result = numbers.lower_bound(border);
  if (result == begin(numbers)) return result;
  else if (result == end(numbers)) return prev(result);
  else {
    if (border - *prev(result) > *result - border) return result;
  }
  return prev(result);
}

int main() {
  set<int> numbers = {1, 4, 6};
  // ожидаемый вывод:
  // 1 4 4 6 6
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;
  // ожидаемый вывод:
  // 1
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
