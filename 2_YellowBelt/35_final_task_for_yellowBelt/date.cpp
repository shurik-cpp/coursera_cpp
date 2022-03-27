#include "date.h"
#include <tuple>

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

//------------------------------------
bool operator == (const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) == tie(rhs.year,rhs.month,rhs.day);
}

bool operator != (const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) != tie(rhs.year,rhs.month,rhs.day);
}

bool operator < (const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) < tie(rhs.year,rhs.month,rhs.day);
}

bool operator <= (const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) <= tie(rhs.year,rhs.month,rhs.day);
}

bool operator > (const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) > tie(rhs.year,rhs.month,rhs.day);
}

bool operator >= (const Date& lhs, const Date& rhs) {
  return tie(lhs.year,lhs.month,lhs.day) >= tie(rhs.year,rhs.month,rhs.day);
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setfill('0');
  stream << setw(4) << date.year << '-'
         << setw(2) << date.month << '-'
         << setw(2) << date.day;
  return stream;
}
