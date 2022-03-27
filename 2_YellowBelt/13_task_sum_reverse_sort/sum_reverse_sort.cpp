#include "sum_reverse_sort.h"
#include <algorithm>

// складывать два числа
int Sum(int x, int y) {
  return x + y;
}

// обращать строку
std::string Reverse(std::string s) {
  std::reverse(s.begin(), s.end());
  return s;
}
// сортировать вектор чисел по возрастанию
void Sort(std::vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
}
