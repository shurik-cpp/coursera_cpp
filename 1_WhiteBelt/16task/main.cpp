/* Реализуйте функцию vector<int> Reversed(const vector<int>& v),
 * возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
*/
#include <iostream>
#include <vector>
#include <reversed.cpp>

using namespace std;

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};

  for (auto i : nums) {
    cout << i << " ";
  }
  cout << endl;
  vector<int> rev_nums = Reversed(nums);

  for (auto i : rev_nums) {
    cout << i << " ";
  }

  return 0;
}
