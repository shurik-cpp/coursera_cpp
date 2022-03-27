#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {

  auto it = names.equal_range(year);
//  cout << "request: " << year << endl
//       << "lower: " << it.first->first << " " << it.first->second << endl
//       << "upper: " << it.second->first << " " << it.second->second << endl;

  if (it.first == begin(names) && it.second == begin(names)) {
    return "";
  }
  else if (it.first == it.second ||
           (it.first == end(names) && it.second == end(names))) {
    return prev(it.first)->second;
  }

  return it.first->second;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }

  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }

  string GetFullName(int year) {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

      // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

      // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

      // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  //cout << person.GetFullName(1969);

  return 0;
}
