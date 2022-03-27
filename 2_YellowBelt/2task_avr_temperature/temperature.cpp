#include <iostream>
#include <vector>

using namespace std;

int main() {

  int days;
  cin >> days;

  vector<int> tempers(days);
  int64_t sum = 0;

  for (int i = 0; i < days; ++i) {
    cin >> tempers[i];
    sum += tempers[i];
  }

  int average_temper = sum / days;

  vector<int> hot_days;

  for (int i = 0; i < days; ++i) {
    if (tempers[i] > average_temper) {
      hot_days.push_back(i);
    }
  }

  cout << hot_days.size() << endl;
  for (auto& it : hot_days) {
    cout << it << ' ';
  }
  cout << endl;

  return 0;
}
