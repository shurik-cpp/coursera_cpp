#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

struct BusesForStopResponse {
  std::vector<std::string> buses_for_stop;
};
//-------------------------
std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
//==========================================================
struct StopsForBusResponse {
  std::string bus;
  std::vector<std::string> stops_for_bus; // названия всех остановок автобуса
  std::map<std::string, std::vector<std::string>> buses_to_stops; // названия всех автобусов, проходящих через остановку (остановка, автобусы)
};
//-------------------------
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
//==========================================================
struct AllBusesResponse {
  std::map<std::string, std::vector<std::string>> stops_for_bus;
};
//-------------------------
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
