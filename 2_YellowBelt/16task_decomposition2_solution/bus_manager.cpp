#include "bus_manager.h"

// определения методов класса BusManager

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
  for (auto& it : stops) { // закидываем в каждую остановку название автобуса
    buses_to_stops[it].push_back(bus);
  }
  stops_for_bus[bus] = stops; // запоминаем остановки для этого автобуса
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) {
  BusesForStopResponse result;
  if (buses_to_stops.count(stop)) {
    result.buses_for_stop = buses_to_stops[stop];
  }
  else buses_to_stops.erase(stop);
  return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) {
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

AllBusesResponse BusManager::GetAllBuses() const {
  AllBusesResponse result;
  result.stops_for_bus = stops_for_bus;
  return result;
}


