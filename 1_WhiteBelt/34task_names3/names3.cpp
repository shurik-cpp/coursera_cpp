#include <iostream>

#include <map>
#include <vector>
#include <algorithm>

using namespace std;


class Person {
public:
  Person(const string& newFirstName, const string& newLastName, const int& newYearOfBorn){
    yearOfBirth = newYearOfBorn;
    ChangeFirstName(newYearOfBorn, newFirstName);
    ChangeLastName(newYearOfBorn, newLastName);
  }

  void ChangeFirstName(int year, const string& first_name) {
    if (year >= yearOfBirth) first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    if (year >= yearOfBirth) last_names[year] = last_name;
  }
  string GetFullName(int year) const {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    return BuildAnswer(first_name, last_name);
  }

  string GetFullNameWithHistory(int year) const {
    // получаем имена и фамилии по состоянию на год year
    const string all_first_names = FindAllNamesByYear(first_names, year);
    const string all_last_names = FindAllNamesByYear(last_names, year);

    return BuildAnswer(all_first_names, all_last_names);
  }
private:
  map<int, string> first_names;
  map<int, string> last_names;
  int yearOfBirth;

  // если имя неизвестно, возвращает пустую строку
  string FindNameByYear(const map<int, string>& names, int year) const {
    string name;  // изначально имя неизвестно

    // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
    for (const auto& item : names) {
      // если очередной год не больше данного, обновляем имя
      if (item.first <= year) name = item.second;
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      else break;
    }

    return name;
  }

  string FindAllNamesByYear(const map<int, string>& names, int year) const {
    string allNames;
    vector<string> namesReversedChronolygy;

    // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
    for (const auto& item : names) {
      // если очередной год не больше данного, закидываем имена по порядку в вектор
      if (item.first <= year) namesReversedChronolygy.push_back(item.second);
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      else break;
      //cout << item << endl;
    }
    // развернем вектор задом наперед
    reverse(namesReversedChronolygy.begin(), namesReversedChronolygy.end());

    // если пусто, возвращаем пустую строку
    if (namesReversedChronolygy.empty()) return "";
    // если всего одно имя возвращаем только его
    else if (namesReversedChronolygy.size() == 1) return namesReversedChronolygy[0];
    // иначе занимаемся построением строки
    else {
      // присвоим результату первое в списке имя
      allNames = namesReversedChronolygy[0];
      bool openBracket = false;
      for (unsigned int i = 1; i < namesReversedChronolygy.size(); ++i) {
        if (namesReversedChronolygy[i] != namesReversedChronolygy[i - 1]) {
          if (!openBracket) {
            openBracket = true;
            allNames += " (";
          }
          allNames += namesReversedChronolygy[i];
          if (i < namesReversedChronolygy.size() -1) allNames += ", ";
        }
      }
      if (openBracket) allNames += ')';
    }

    return allNames;
  }

  string BuildAnswer(string first, string last) const {
    // если и имя, и фамилия неизвестны
    if (first.empty() && last.empty()) return "No person";
    // если неизвестно только имя
    //else if (first.empty()) return last + " with unknown first name";
    // если неизвестно только фамилия
    //else if (last.empty()) return first + " with unknown last name";
    // если известны и имя, и фамилия
    else return first + " " + last;
  }
};

int main() {
  Person person("Polina", "Sergeeva", 1960);

  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

//  person.ChangeFirstName(1970, "Anna");
//  person.ChangeLastName(1955, "Nobody");
//  cout << person.GetFullNameWithHistory(2000) << endl;

  return 0;
}

/*
#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;

vector<string> FindNamesHistory(const map<int, string>& names_by_year,
                                int year) {
  vector<string> names;
  for (const auto& item : names_by_year) {
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  reverse(begin(names), end(names));
  string joined_name = names[0];
  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      joined_name += " (";
    } else {
      joined_name += ", ";
    }
    joined_name += names[i];
  }
  if (names.size() > 1) {
    joined_name += ")";
  }
  return joined_name;
}

class Person {
public:
  // конструктор
  Person(const string& first_name, const string& last_name,
         int new_birth_year) {
    birth_year = new_birth_year;
    first_names[birth_year] = first_name;
    last_names[birth_year] = last_name;
  }
  void ChangeFirstName(int year, const string& first_name) {
    // игнорируем запись, если год меньше года рождения
    if (year >= birth_year) {
      first_names[year] = first_name;
    }
  }
  void ChangeLastName(int year, const string& last_name) {
    if (year >= birth_year) {
      last_names[year] = last_name;
    }
  }
  string GetFullName(int year) const {
    // обрабатываем случай, когда год меньше года рождения
    if (year < birth_year) {
      return "No person";
    }
    const vector<string> first_names = FindFirstNamesHistory(year);
    const vector<string> last_names = FindLastNamesHistory(year);
    // объединяем имя и фамилию через пробел
    return first_names.back() + " " + last_names.back();
  }
  string GetFullNameWithHistory(int year) const {
    if (year < birth_year) {
      return "No person";
    }
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
    return first_name + " " + last_name;
  }
private:
  vector<string> FindFirstNamesHistory(int year) const {
    return FindNamesHistory(first_names, year);
  }
  vector<string> FindLastNamesHistory(int year) const {
    return FindNamesHistory(last_names, year);
  }

  int birth_year;
  map<int, string> first_names;
  map<int, string> last_names;
};

*/


