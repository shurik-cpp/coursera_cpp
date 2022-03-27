#pragma once

#include <map>
#include <vector>
#include "responses.h"

// объявление класса BusManager
class BusManager {
private:
  std::map<std::string, std::vector<std::string>>
      buses_to_stops, // названия всех автобусов, проходящих через остановку
      stops_for_bus; // названия всех остановок автобуса

public:
  void AddBus(const std::string& bus, const std::vector<std::string>& stops);

  BusesForStopResponse GetBusesForStop(const std::string& stop);

  StopsForBusResponse GetStopsForBus(const std::string& bus);

  AllBusesResponse GetAllBuses() const;
};

