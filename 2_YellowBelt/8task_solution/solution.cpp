#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string operation_code;
  is >> operation_code;
  if (operation_code == "NEW_BUS") {
    q.type = static_cast<QueryType>(QueryType::NewBus);
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    vector<string>& stops = q.stops;
    stops.resize(stop_count);
    for (string& stop : stops) {
      is >> stop;
    }
  }
  else if (operation_code == "BUSES_FOR_STOP") {
    q.type = static_cast<QueryType>(QueryType::BusesForStop);
    is >> q.stop;
  }
  else if (operation_code == "STOPS_FOR_BUS") {
    q.type = static_cast<QueryType>(QueryType::StopsForBus);
    is >> q.bus;
  }
  else if (operation_code == "ALL_BUSES") {
    q.type = static_cast<QueryType>(QueryType::AllBuses);
  }

  return is;
}
//==========================================================
struct BusesForStopResponse {
  vector<string> buses_for_stop;
};
//-------------------------
ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses_for_stop.size() == 0) {
    os << "No stop" << endl;
  }
  else {
    for (const string& bus : r.buses_for_stop) {
      os << bus << " ";
    }
    os << endl;
  }
  return os;
}
//==========================================================
struct StopsForBusResponse {
  string bus;
  vector<string> stops_for_bus; // названия всех остановок автобуса
  map<string, vector<string>> buses_to_stops; // названия всех автобусов, проходящих через остановку (остановка, автобусы)
};
//-------------------------
ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_bus.size() == 0) {
    os << "No bus" << endl;
  }
  else {
    for (const string& stop : r.stops_for_bus) {
      os << "Stop " << stop << ": ";
      if (r.buses_to_stops.at(stop).size() == 1) {
        os << "no interchange";
      }
      else {
        for (const string& other_bus : r.buses_to_stops.at(stop)) {
          if (r.bus != other_bus) {
            os << other_bus << " ";
          }
        }
      }
      os << endl;
    }
  }
  return os;
}
//==========================================================
struct AllBusesResponse {
  map<string, vector<string>> stops_for_bus;
};
//-------------------------
ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.stops_for_bus.empty()) {
    os << "No buses" << endl;
  }
  else {
    for (const auto& bus_item : r.stops_for_bus) {
      os << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) {
        os << stop << " ";
      }
      os << endl;
    }
  }
  return os;
}
//==========================================================

class BusManager {
private:
  map<string, vector<string>>
      buses_to_stops, // названия всех автобусов, проходящих через остановку
      stops_for_bus; // названия всех остановок автобуса

public:
//--------------------
  void AddBus(const string& bus, const vector<string>& stops) {
    for (auto& it : stops) { // закидываем в каждую остановку название автобуса
      buses_to_stops[it].push_back(bus);
    }
    stops_for_bus[bus] = stops; // запоминаем остановки для этого автобуса
  }
//--------------------
  BusesForStopResponse GetBusesForStop(const string& stop) {
    BusesForStopResponse result;
    if (buses_to_stops.count(stop)) {
      result.buses_for_stop = buses_to_stops[stop];
    }
    else buses_to_stops.erase(stop);
    return result;
  }
//--------------------
  StopsForBusResponse GetStopsForBus(const string& bus) {
    StopsForBusResponse result;
    if (stops_for_bus.count(bus)) {
      result.stops_for_bus = stops_for_bus[bus];
      result.buses_to_stops = buses_to_stops;
    }
    else {
      stops_for_bus.erase(bus);
    }
    result.bus = bus;
    return result;
  }
//--------------------
  AllBusesResponse GetAllBuses() const {
    AllBusesResponse result;
    result.stops_for_bus = stops_for_bus;
    return result;
  }
};


int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
