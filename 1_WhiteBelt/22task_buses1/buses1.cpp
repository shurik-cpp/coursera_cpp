/* Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:
 *
 * NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками
 * с названиями stop1, stop2, ...
 * BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
 * STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов,
 * на которые можно пересесть на каждой из остановок.
 * ALL_BUSES — вывести список всех маршрутов с остановками.
 *
 * Формат ввода
 *
 * В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.
 * Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.
 * Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует,
 * количество остановок больше 0, а после числа stop_count следует именно такое количество названий остановок,
 * причём все названия в каждом списке различны.
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(){
  map<string, vector<string>> buses; //словарь автобусов (<название автобуса, его остановки>) (каждый автобус имеет несколько остановок)
  vector<string> bus_order; // для хранения, в каком порядке производилась запись NEW_BUS

  // сколько всего будет запросов
  int q;
  cin >> q;

  // обработка запросов
  for (int i = 0; i < q; ++i){
    string command;
    cin >> command;

    if (command == "NEW_BUS"){
      string bus_name;
      int stop_count;
      cin >> bus_name >> stop_count;
      // запоминаем в каком порядке были введены автобусы
      bus_order.push_back(bus_name);

      vector<string> stops; // вектор остановок
      for (int j = 0; j < stop_count; ++j){
        string temp;
        cin >> temp;
        stops.push_back(temp);  // заполняем вектор остановками
      }
      buses[bus_name] = stops; // добавляем элемент в словарь (остановки этого маршрута)
    }
    // BUSES_FOR_STOP stop - все автобусы для остановки stop через пробел,
    // в том порядке, в котором они создавались командами NEW_BUS
    // Если остановка stop не существует, выведите No stop.
    else if (command == "BUSES_FOR_STOP"){
      vector<string> temp_vector;
      string stop;
      cin >> stop;

      for (auto b : buses){ // трясем каждый автобус
        for (auto s : b.second){ // проверяем каждую остановку b-автобуса на совпадение
          // заполняем временный вектор названиями автобусов, если есть совпадение остановок
          if (s == stop) temp_vector.push_back(b.first);
        }
      }
      if (temp_vector.size() == 0){
        cout << "No stop" << endl; // если остановка нигде не встретилась, вектор будет пустой
      }
      else { // если вектор не пустой, выводим его на экран
        for (auto a : bus_order) { // выводим автобусы для пересадки в порядке их заполнения
          for (auto j : temp_vector) { // трясем вектор найденных автобусов
            if (a == j) { // проверка есть ли во временном списке автобусов текущий (по порядку) автобус
              cout << a << ' '; // если есть, печатаем, нет - ничего не делаем
            }
          }
        }
        cout << endl;
      }
    }
    // STOPS_FOR_BUS bus - остановки маршрута bus в отдельных строках
    // в том порядке, в котором они были заданы в соответствующей команде NEW_BUS.
    // Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ...,
    // где bus1 bus2 ... — список автобусов, проезжающих через остановку stop,
    // в порядке, в котором они создавались командами NEW_BUS, за исключением исходного маршрута bus.
    // Если через остановку stop не проезжает ни один автобус, кроме bus,
    // вместо списка автобусов для неё выведите no interchange.
    else if (command == "STOPS_FOR_BUS") {
      string bus;
      cin >> bus;
      // если такой автобус существует, выводим его остановки и для каждой
      // остановки выведем автобусы, которые на ней останавливаются
      if (buses.count(bus)) { // проверка на наличие автобуса
        for (auto currentStop : buses[bus]) { // перебираем вектор остановок этого автобуса
          cout << "Stop " << currentStop << ": "; //  и выводим на экран название остановки
          // ищем автобусы, которые останавливаются на текущей остановке
          vector<string> temp_vector; // сюда будем записывать названия автобусов, которые останавливаются на текущей (currentStop) остановке
          for (auto currentBus : buses) { // перебираем все автобусы в словаре buses
            for (auto s : currentBus.second) { // ищем в текущем автобусе (currentBus) нашу текущуу (currentStop) остановку
              // заполняем временный вектор названиями автобусов, если есть
              // совпадение текущей остановки
              if (s == currentStop) temp_vector.push_back(currentBus.first);
            }
          }
          if (temp_vector.size() == 1) { // если найдено всего одно совпадение, пишем, нет пересадок
            cout << "no interchange" << endl;
          }
          else { // если вектор не пустой, выводим его на экран через пробел
            for (auto a : bus_order) { // выводим автобусы для пересадки в порядке их заполнения
              if (a != bus) { // кроме запрашиваемого автобуса
                for (auto j : temp_vector) { // трясем вектор найденных автобусов
                  if (a == j) { // проверка есть ли во временном списке автобусов текущий (по порядку) автобус
                    cout << a << ' '; // если есть, печатаем, нет - ничего не делаем
                  }
                }
              }
            }
            cout << endl;
          }
        }
      }
      else {
        cout << "No bus" << endl;
        buses.erase(bus);
      }
    }
    // ALL_BUSES - описания всех автобусов в алфавитном порядке.
    // Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ...,
    // где stop1 stop2 ... — список остановок автобуса bus
    // в порядке, в котором они были заданы в соответствующей команде NEW_BUS.
    // Если автобусы отсутствуют, выведите No buses.
    else if (command == "ALL_BUSES"){
      if (buses.size() != 0){  // если есть сохраненные автобусы, выводим все на экран
        for (auto j : buses){
           cout << "Bus " << j.first << ": "; // выводим заголовок и название автобуса
           for (auto k : j.second){
             cout << k << ' '; // выводим список остановок
           }
           cout << endl;
        }
      }
      else {
        cout << "No buses" << endl;
      }
    }
  }
  return 0;
}

/*
// ответ на запрос BUSES_FOR_STOP
void PrintBusesForStop(map<string, vector<string>>& stops_to_buses,
                       const string& stop) {
  if (stops_to_buses.count(stop) == 0) {
    cout << "No stop" << endl;
  } else {
    for (const string& bus : stops_to_buses[stop]) {
      cout << bus << " ";
    }
    cout << endl;
  }
}

// ответ на запрос STOPS_FOR_BUS
void PrintStopsForBus(map<string, vector<string>>& buses_to_stops,
                      map<string, vector<string>>& stops_to_buses,
                      const string& bus) {
  if (buses_to_stops.count(bus) == 0) {
    cout << "No bus" << endl;
  } else {
    for (const string& stop : buses_to_stops[bus]) {
      cout << "Stop " << stop << ": ";

      // если через остановку проходит ровно один автобус,
      // то это наш автобус bus, следовательно, пересадки тут нет
      if (stops_to_buses[stop].size() == 1) {
        cout << "no interchange";
      } else {
        for (const string& other_bus : stops_to_buses[stop]) {
          if (bus != other_bus) {
            cout << other_bus << " ";
          }
        }
      }
      cout << endl;
    }
  }
}

// ответ на запрос ALL_BUSES
void PrintAllBuses(const map<string, vector<string>>& buses_to_stops) {
  if (buses_to_stops.empty()) {
    cout << "No buses" << endl;
  } else {
    for (const auto& bus_item : buses_to_stops) {
      cout << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        cout << stop << " ";
      }
      cout << endl;
    }
  }
}

int main() {
  int q;
  cin >> q;

  map<string, vector<string>> buses_to_stops, stops_to_buses;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "NEW_BUS") {

      string bus;
      cin >> bus;
      int stop_count;
      cin >> stop_count;

      // с помощью ссылки дадим короткое название вектору
      // со списком остановок данного автобуса;
      // ключ bus изначально отсутствовал в словаре, поэтому он автоматически
      // добавится туда с пустым вектором в качестве значения
      vector<string>& stops = buses_to_stops[bus];
      stops.resize(stop_count);

      for (string& stop : stops) {
        cin >> stop;
        // не забудем обновить словарь stops_to_buses
        stops_to_buses[stop].push_back(bus);
      }

    } else if (operation_code == "BUSES_FOR_STOP") {

      string stop;
      cin >> stop;
      PrintBusesForStop(stops_to_buses, stop);

    } else if (operation_code == "STOPS_FOR_BUS") {

      string bus;
      cin >> bus;
      PrintStopsForBus(buses_to_stops, stops_to_buses, bus);

    } else if (operation_code == "ALL_BUSES") {

      PrintAllBuses(buses_to_stops);

    }
  }

  return 0;
}
*/
