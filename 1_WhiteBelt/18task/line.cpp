#include <iostream>
#include <vector>
#include <string>



using namespace std;

int main() {
  vector<bool> queue = {}; // вектор очереди. номер ячейки - человек, true - беспокоится, false - спокоен
  int Q;
  cin >> Q; // запомним количество будущих операций
  vector<string> command(Q); // комманда опрерации
  vector<int> value(Q); // значение операции

  for (int i = 0; i < Q; ++i) {
    cin >> command[i];
    if (command[i] == "WORRY_COUNT") value[i] = 0;
    else cin >> value[i];
  }

  for (int i = 0; i < Q; ++i) {
    if (command[i] != "WORRY_COUNT") {
      if (command[i] == "COME") { // добавление или удаление людей в очереди
        if (value[i] > 0) {
          for (int j = abs(value[i]); j > 0; --j) {
            queue.push_back(false);
          }
        }
        else if (value[i] < 0) {
          for (int j = abs(value[i]); j > 0; --j) {
            queue.pop_back();
          }
        }
        //cout << "queue.size() = " << queue.size() << endl;
      }
      else if (command[i] == "WORRY") {
        queue[value[i]] = true;
        /*cout << '[';
        for (auto j : queue){
          cout << j << ' ';
        }
        cout << ']' << endl;*/
      }
      else if (command[i] == "QUIET") {
        queue[value[i]] = false;
      }
    }
    else {
      int counter_worry = 0;
      for (auto k : queue) {
        if (k) counter_worry++;
      }
      cout << counter_worry << endl;
    }
  }
  return 0;
}
