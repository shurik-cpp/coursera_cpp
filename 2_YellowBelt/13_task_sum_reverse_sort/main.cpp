#include <iostream>
#include "sum_reverse_sort.h"
#include "test_runner.h"

using namespace std;

void TestAll() {
  AssertEqual(Sum(3, 2), 5, "Sum()");
  AssertEqual(Reverse("ytrewq"), "qwerty", "Reverse()");
  vector<int> nums = {2, 4, 5, 3, 1};
  Sort(nums);
  AssertEqual(nums, vector<int>{1, 2, 3, 4, 5}, "Sort()");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestAll, "Test all");
  return 0;
}
