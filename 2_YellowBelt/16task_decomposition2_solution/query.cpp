#include "query.h"

// определение istream& operator >> (istream& is, Query& q);

// enum class QueryType
// struct Query
// объявление istream& operator >> (istream& is, Query& q)

std::istream& operator >> (std::istream& is, Query& q) {
  std::string operation_code;
  is >> operation_code;
  if (operation_code == "NEW_BUS") {
    q.type = static_cast<QueryType>(QueryType::NewBus);
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    std::vector<std::string>& stops = q.stops;
    stops.resize(stop_count);
    for (std::string& stop : stops) {
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
