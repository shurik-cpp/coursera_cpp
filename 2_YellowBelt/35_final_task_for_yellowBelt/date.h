#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Date {
  int year;
  int month;
  int day;
};

Date ParseDate(istream& is);

bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& stream, const Date& date);
