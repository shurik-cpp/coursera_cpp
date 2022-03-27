#include <iostream>

#include <map>
#include <vector>
#include <algorithm>

using namespace std;


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

    return BuildAnswer(first_name, last_name);
  }

  string GetFullNameWithHistory(int year){
    // получаем имена и фамилии по состоянию на год year
    const string all_first_names = FindAllNamesByYear(first_names, year);
    const string all_last_names = FindAllNamesByYear(last_names, year);

    return BuildAnswer(all_first_names, all_last_names);
  }
private:
  map<int, string> first_names;
  map<int, string> last_names;

  // если имя неизвестно, возвращает пустую строку
  string FindNameByYear(const map<int, string>& names, int year) {
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

  string FindAllNamesByYear(const map<int, string>& names, int year){
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

  string BuildAnswer(string first, string last) {
    // если и имя, и фамилия неизвестны
    if (first.empty() && last.empty()) return "Incognito";
    // если неизвестно только имя
    else if (first.empty()) return last + " with unknown first name";
    // если неизвестно только фамилия
    else if (last.empty()) return first + " with unknown last name";
    // если известны и имя, и фамилия
    else return first + " " + last;
  }
};

int main(){
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1965, "Appolinaria");

  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeLastName(1965, "Volkova");
  person.ChangeLastName(1965, "Volkova-Sergeeva");

  for (int year : {1964, 1965, 1966}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

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
  // перебираем всю историю в хронологическом порядке
  for (const auto& item : names_by_year) {
    // если очередное имя не относится к будущему и отличается от предыдущего,
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      // добавляем его в историю
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  // нет истории — имя неизвестно
  if (names.empty()) {
    return "";
  }
  // меняем прямой хронологический порядок на обратный
  reverse(begin(names), end(names));

  // начинаем строить полное имя с самого последнего
  string joined_name = names[0];

  // перебираем все последующие имена
  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      // если это первое «историческое» имя, отделяем его от последнего скобкой
      joined_name += " (";
    } else {
      // если это не первое имя, отделяем от предыдущего запятой
      joined_name += ", ";
    }
    // и добавляем очередное имя
    joined_name += names[i];
  }

  // если в истории было больше одного имени, мы открывали скобку — закроем её
  if (names.size() > 1) {
    joined_name += ")";
  }
  // имя со всей историей готово
  return joined_name;
}

// см. решение предыдущей задачи
string BuildFullName(const string& first_name, const string& last_name) {
  if (first_name.empty() && last_name.empty()) {
    return "Incognito";
  } else if (first_name.empty()) {
    return last_name + " with unknown first name";
  } else if (last_name.empty()) {
    return first_name + " with unknown last name";
  } else {
    return first_name + " " + last_name;
  }
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
    // найдём историю изменений имени и фамилии
    // в данном случае это излишне, так как нам достаточно узнать последние имя и фамилию, но почему бы не использовать готовые функции?
    const vector<string> first_names_history = FindFirstNamesHistory(year);
    const vector<string> last_names_history = FindLastNamesHistory(year);

    // подготовим данные для функции BuildFullName: возьмём последние имя и фамилию или оставим их пустыми, если они неизвестны
    string first_name;
    string last_name;
    if (!first_names_history.empty()) {
      first_name = first_names_history.back();
    }
    if (!last_names_history.empty()) {
      last_name = last_names_history.back();
    }
    return BuildFullName(first_name, last_name);
  }

  string GetFullNameWithHistory(int year) {
    // получим полное имя со всей историей
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    // получим полную фамилию со всей историей
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
    // объединим их с помощью готовой функции
    return BuildFullName(first_name, last_name);
  }

private:
  vector<string> FindFirstNamesHistory(int year) {
    return FindNamesHistory(first_names, year);
  }
  vector<string> FindLastNamesHistory(int year) {
    return FindNamesHistory(last_names, year);
  }

  map<int, string> first_names;
  map<int, string> last_names;
};

*/
