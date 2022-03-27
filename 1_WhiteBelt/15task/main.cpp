/* Реализуйте функцию void Reverse(vector<int>& v),
 * которая переставляет элементы вектора в обратном порядке.
*/
#include <iostream>
#include <vector>
#include <reverse.cpp>

using namespace std;

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};

  for (auto i : nums) {
    cout << i << " ";
  }
  cout << endl;
  Reverse(nums);

  for (auto i : nums) {
    cout << i << " ";
  }
  return 0;
}
