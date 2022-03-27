#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void PrintVector(const vector<int>& v) {
  for (auto& it : v) {
    cout << it << ' ';
  }
  cout << endl;
}

int main() {
  int N;
  cin >> N;

  vector<int> numbers(N);
  for (int i = 0; i < N; ++i) {
    numbers[i] = N - i;
  }

  do {
    PrintVector(numbers);
  } while (prev_permutation(numbers.begin(), numbers.end()));

  return 0;
}
