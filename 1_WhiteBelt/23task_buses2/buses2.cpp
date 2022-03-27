/* В этой задаче вам нужно присваивать номера автобусным маршрутам.
 * А именно, для каждого маршрута, заданного набором названий остановок,
 * нужно либо выдать новый номер (первому маршруту — 1, второму — 2 и т. д.),
 * либо вернуть номер существующего маршрута, которому соответствует такой набор остановок.
 *
 * Наборы остановок, полученные друг из друга перестановкой остановок, считаются различными (см. пример).
 *
 * Указание
 * В C++ ключом словаря может быть не только число или строка, но и другой контейнер, например, vector.
 *
 * Формат ввода
 * Сначала вводится количество запросов Q, затем Q описаний запросов.
 *
 * Каждый запрос представляет собой положительное количество остановок N,
 * за которым следуют разделённые пробелом N различных названий остановок соответствующего маршрута.
 * Названия остановок состоят лишь из латинских букв и символов подчёркивания.
 *
 * Формат вывода
 * Выведите ответ на каждый запрос в отдельной строке.
 *
 * Если маршрут с данным набором остановок уже существует,
 * в ответ на соответствующий запрос выведите Already exists for i,
 * где i — номер маршрута с таким набором остановок.
 * В противном случае нужно выделить введённому набору остановок новый номер i и вывести его в формате New bus i.
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int checkForAvailability(const vector<string>& item, const map<int, vector<string>>& routesForReverse) {
  map<vector<string>, int> reversedMap;

  for (auto i : routesForReverse){
    reversedMap[i.second] = i.first;
  }
  // проверка на совпадение
  if (reversedMap.count(item)){
    return reversedMap[item];
  }
  else {
    return 0;
  }
}

int main(){
  // словарь <номер маршрута, остановки>
  map<int, vector<string>> routes;

  int q;
  cin >> q; // вводим количество будущих запросов
  int routeCounter = 1;

  for (int iRequest = 0; iRequest < q; ++iRequest){ // обработка запросов
    int numberOfStops;
    cin >> numberOfStops; // вводим количество будущих остановок
    vector<string> stops;
    string currentStop;

    for (int qStops = 0; qStops < numberOfStops; ++qStops) { // обработка количества остановок
      cin >> currentStop;
      stops.push_back(currentStop);
    }
    //проверка на наличие уже существующего маршрута
    int routeNumber = checkForAvailability(stops, routes); // переменная для расчета номера маршрута
    if (routeNumber) { // если функция checkForAvailability вернет отличное от 0 число
      cout << "Already exists for " << routeNumber << endl;
    }
    else { // если вернула 0, то добавляем маршрут
      routes[routeCounter] = stops;
      cout << "New bus " << routeCounter << endl;
      ++routeCounter;
    }
  }

  return 0;
}


/*
int main() {
  int q;
  cin >> q;

map<vector<string>, int> buses;

for (int i = 0; i < q; ++i) {
  int n;
  cin >> n;
  vector<string> stops(n);
  for (string& stop : stops) {
    cin >> stop;
  }

  // проверяем, не существует ли уже маршрут с таким набором остановок
  if (buses.count(stops) == 0) {

    // если не существует, нужно сохранить новый маршрут;
    // его номер на единицу больше текущего количества маршрутов
    const int new_number = buses.size() + 1;
    buses[stops] = new_number;
    cout << "New bus " << new_number << endl;

  } else {
    cout << "Already exists for " << buses[stops] << endl;
  }
}

return 0;
}
*/
