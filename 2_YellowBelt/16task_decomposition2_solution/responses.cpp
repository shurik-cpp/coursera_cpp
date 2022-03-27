#include "responses.h"

// определение всего, что объявлено в responses.h

// struct BusesForStopResponse
// ostream& operator << (ostream& os, const BusesForStopResponse& r)
// struct StopsForBusResponse
// ostream& operator << (ostream& os, const StopsForBusResponse& r)
// struct AllBusesResponse
// ostream& operator << (ostream& os, const AllBusesResponse& r)

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
  if (r.buses_for_stop.size() == 0) {
    os << "No stop" << std::endl;
  }
  else {
    for (const std::string& bus : r.buses_for_stop) {
      os << bus << " ";
    }
    os << std::endl;
  }
  return os;
}
//==========================================================
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_bus.size() == 0) {
    os << "No bus" << std::endl;
  }
  else {
    for (const std::string& stop : r.stops_for_bus) {
      os << "Stop " << stop << ": ";
      if (r.buses_to_stops.at(stop).size() == 1) {
        os << "no interchange";
      }
      else {
        for (const std::string& other_bus : r.buses_to_stops.at(stop)) {
          if (r.bus != other_bus) {
            os << other_bus << " ";
          }
        }
      }
      os << std::endl;
    }
  }
  return os;
}
//==========================================================
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
  if (r.stops_for_bus.empty()) {
    os << "No buses" << std::endl;
  }
  else {
    for (const auto& bus_item : r.stops_for_bus) {
      os << "Bus " << bus_item.first << ": ";
      for (const std::string& stop : bus_item.second) {
        os << stop << " ";
      }
      os << std::endl;
    }
  }
  return os;
}
