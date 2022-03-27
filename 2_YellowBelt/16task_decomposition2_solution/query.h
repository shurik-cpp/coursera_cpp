#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

// enum class QueryType
// struct Query
// объявление istream& operator >> (istream& is, Query& q)

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  std::string bus;
  std::string stop;
  std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q);
