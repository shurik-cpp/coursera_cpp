#include "airline_ticket.h"
#include "test_runner.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <tuple>
#include <map>

using namespace std;

// Функцию UpdateTicket можно было бы реализовать так:
//void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
//  map<string, string>::const_iterator it;

//  it = updates.find("price");
//  if (it != updates.end()) {
//    istringstream is(it->second);
//    is >> ticket.price;
//  }

//  //... UPDATE_FIELD(t, departure_date, updates1);
//}

// Напишите макрос UPDATE_FIELD
#define UPDATE_FIELD(ticket, what_changing, map_values)                 \
{                                                                       \
  auto it = map_values.find(#what_changing);                            \
  if (it != map_values.end()) {                                         \
    istringstream iss(it->second);                                      \
    iss >> ticket.what_changing;                                        \
  }                                                                     \
}

bool operator <(const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) < tie(rhs.year,rhs.month,rhs.day);
}
bool operator !=(const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) != tie(rhs.year,rhs.month,rhs.day);
}
bool operator ==(const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) == tie(rhs.year,rhs.month,rhs.day);
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setfill('0');
  stream << setw(4) << date.year << '-'
         << setw(2) << date.month << '-'
         << setw(2) << date.day;
  return stream;
}

void DateSeparatorCheck(istream& stream) {
  if (stream.peek() != '-') { // проверка разделителя даты
    throw runtime_error("Wrong date format");
  }
  else stream.ignore(1);
}

Date ParseDate(istream& is) {
  Date date;
  string garbige;

  // парсим поток
  is >> date.year;
  DateSeparatorCheck(is);
  if (is >> date.month) DateSeparatorCheck(is);
  if (is >> date.day);
  else throw runtime_error("Wrong date format");

  if (date.month < 1 || date.month > 12) {
    throw runtime_error("Month value is invalid: " + to_string(date.month));
  }
  else if (date.day < 1 || date.day > 31) {
    throw runtime_error("Day value is invalid: " + to_string(date.day));
  }

  return date;
}

istream& operator>>(istream& stream, Date& date) {
  date = ParseDate(stream);
  return stream;
}
//====================================================
bool operator <(const Time& lhs, const Time& rhs) {
  return tie(lhs.hours,lhs.minutes) < tie(rhs.hours,rhs.minutes);
}
bool operator ==(const Time& lhs, const Time& rhs) {
  return tie(lhs.hours,lhs.minutes) == tie(rhs.hours,rhs.minutes);
}
bool operator !=(const Time& lhs, const Time& rhs) {
  return tie(lhs.hours,lhs.minutes) != tie(rhs.hours,rhs.minutes);
}

void TimeSeparatorCheck(istream& stream) {
  if (stream.peek() != ':') { // проверка разделителя даты
    throw runtime_error("Wrong time format");
  }
  else stream.ignore(1);
}

Time ParseTime(istream& is) {
  Time time;
  string garbige;

  // парсим поток
  is >> time.hours;
  TimeSeparatorCheck(is);
  if (is >> time.minutes);
  else throw runtime_error("Wrong time format");

  if (time.hours < 0 || time.hours > 24) {
    throw runtime_error("Time value is invalid: " + to_string(time.hours));
  }
  else if (time.minutes < 0 || time.minutes > 60) {
    throw runtime_error("Time value is invalid: " + to_string(time.minutes));
  }

  return time;
}

istream& operator>>(istream& stream, Time& time) {
  time = ParseTime(stream);
  return stream;
}

ostream& operator<<(ostream& os, const Time& t) {
  return os << t.hours << ':' << t.minutes;
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
      {"departure_date", "2018-2-28"},
      {"departure_time", "17:40"},
      };

  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
      {"price", "12550"},
      {"arrival_time", "20:33"},
      };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
