#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

  vector<vector<string>> tasksOfMonth(31); //создадим вектор векторов заданий первого месяца (январь) с 31 днем
  int counterMonth = 1;
  bool longMonth = true; // true - когда в месяце 31 день
  int Q;
  cin >> Q;

  for (int i = 0; i < Q; ++i) {
    string command, task;
    int day;
    cin >> command;
    if (command == "ADD") {
      cin >> day >> task;
      tasksOfMonth[day -1].push_back(task);
    }
    else if (command == "DUMP") {
      cin >> day;
      cout << tasksOfMonth[day -1].size(); // выводим, сколько заданий на этот день
      for (const auto& t : tasksOfMonth[day -1]) {
        cout << " " << t;
      }
      cout << endl;
    }
    else if (command == "NEXT") {
      if (counterMonth != 7 && counterMonth != 12) longMonth = !longMonth;

      if (counterMonth == 12) counterMonth = 1;
      else ++counterMonth;
      //cout << "counterMonth = " << counterMonth << endl << "longMonth = " << longMonth << endl;

      if (longMonth) {
        tasksOfMonth.resize(31);
        //cout << "tasksOfMonth.size(" << tasksOfMonth.size() << ')' << endl;
      }
      else {
        if (counterMonth == 2) { // проверка на февраль
          for (int t = 28; t <= 30; ++t) {
            for (auto s : tasksOfMonth[t]) {
              tasksOfMonth[27].push_back(s);
            }
          }
          tasksOfMonth.resize(28); // меняем размер оригинального вектора
          //cout << "tasksOfMonth.size(" << tasksOfMonth.size() << ')' << endl;
        }
        else {
          for (auto s : tasksOfMonth[30]) {
            tasksOfMonth[29].push_back(s);
          }
          tasksOfMonth.resize(30); // меняем размер оригинального вектора
          //cout << "tasksOfMonth.size(" << tasksOfMonth.size() << ')' << endl;
        }
      }
    }
  }

  return 0;
}

