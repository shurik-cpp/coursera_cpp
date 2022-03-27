#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

class RouteManager {
private:
  map<int, set<int>> reachable_lists_;

public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }

  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    // .at() возвращает ссылку на соответствующее значение элемента с ключом, эквивалентным key.
    // пробуем взять ее в reachable_stations (ищем точку start)
    try {
      const set<int>& reachable_stations = reachable_lists_.at(start);
      // ставим итератор равное finish или на первое большее
      auto it = reachable_stations.lower_bound(finish);

      if (it != end(reachable_stations)) result = min(result, abs(finish - *it));
      if (it != begin(reachable_stations)) result = min(result, abs(finish - *prev(it)));
    }
    // Если такого элемента не существует, .at() бросает исключение типа std::out_of_range.
    // тут же ловим это исключение и возвращаем abs(start - finish)
    catch (out_of_range) {
      return result;
    }
    return result;
  }
};


int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    }
    else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
