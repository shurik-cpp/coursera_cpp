#pragma once

#include <iostream>
#include <map>

using namespace std;

struct Student {
  string first_name;         // {"Sidor",
  string last_name;          //  "Sidorov",
  map<string, double> marks; //  {{"maths", 2.7}},
  // Рейтинг студента записан в поле rating
  double rating;             //  2.7},

  // для сортировки по алфавиту - sort(students.begin(), students.end(), []());
  bool operator < (const Student& other) const {
    return GetName() < other.GetName();
  }

  // true, если рейтинг студента this выше рейтинга студента other
  inline bool Less(const Student& other) const {
    return rating > other.rating;
  }

  string GetName() const {
    return first_name + " " + last_name;
  }
};

//----------------------
ostream& operator <<(ostream& os, const Student& student) {
  os << student.GetName() << ": " << student.rating;
  return os;
}
