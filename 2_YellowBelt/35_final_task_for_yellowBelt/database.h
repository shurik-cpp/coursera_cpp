#pragma once
#include <iostream>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include "date.h"
#include "node.h"
#include <sstream>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;

ostream& operator<<(ostream& os, const pair<Date, string>& to_print);

class Database {
public:
  Database() {}

  void Add(const Date& date, const string& event);

  void Print(ostream& os) const;

  template<typename Tpredicate>
  vector<pair<Date, string>> FindIf(Tpredicate predic) const {
    vector<pair<Date, string>> result;

    for (const auto& it_date : db) {
      for (const auto& it_event : it_date.second) {
        bool isPredicate = predic(it_date.first, it_event);
        if (isPredicate) {
          result.push_back(make_pair(it_date.first, it_event));
        }
      }
    }
    return result;
  }

  //можно так:
  //template<typename Tpredicate>
  //int RemoveIf(Tpredicate predic) const { //... }
  // но я сделал так:
  int RemoveIf(function<bool(const Date&, const string&)> predic);

  pair<Date, string> Last(const Date& date) const;


private:
  map<Date, deque<string>> db;
  map<Date, set<string>> db_sorted; // вспомогательная мапа для быстрого поиска в функции Add
};


