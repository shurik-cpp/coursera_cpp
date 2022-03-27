#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Date {
  int year;
  int month;
  int day;
};

istream& operator>>(istream& stream, Date& date) {
  stream >> date.year;
  stream.ignore(1);
  stream >> date.month;
  stream.ignore(1);
  stream >> date.day;
  return stream;
}

int operator-(const Date& ld, const Date& rd) {
  int result = 0;
  vector<int> days_of_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  result += ((rd.year - ld.year) * 365) + ((rd.month - ld.month) * 30) + (rd.day - ld.day);

  return result;
}

int main() {

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; ++i) {
    string request;
    Date left_date, right_date;
    cin >> request >> left_date >> right_date;
    int period_days = right_date - left_date;

    if (request == "Earn") {
      int income;
      cin >> income;
    }
    else if (request == "ComputeIncome") {

    }
  }
  return 0;
}
