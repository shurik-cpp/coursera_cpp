#include <iostream>
#include <map>

using namespace std;

class Person {
private: // приватные поля
  map<int, NameSuname> year_fullName; // год, имя+фамилия+что менялось в этом году
  
  struct NameSuname {
    string name = ""; // хранит текущее имя
    string suname = ""; // хранит текущую фамилию
    //int whatChange = 0; // 1 - меняли name, 2 - меняли suname, 0 - еще ничего не меняли в этом году
    bool isNameChanged = false;
    bool isSunameChanged = false;
  };
  
public:
  void ChangeFirstName(int year, const string& first_name) {
    // добавить факт изменения имени на first_name в год year
    string currentSuname = "";

    // записываем в текущий год новое имя
    year_fullName[year].name = first_name;

    // трясем прошлые и будущие записи
    for (auto& item : year_fullName){
      // проверка прошлых годов (берем прошлую фамилию)
      if (item.first < year) currentSuname = item.second.suname;
      // замена будущих имен до очередной замены
      if (item.first > year){
        // меняем имена в будущем, до очередной смены имени
        if (item.second.isNameChanged == true) break;
        else year_fullName[item.first].name = first_name;
      }
    }
    // записываем в текущий год прошлую фамилию, если фамилия пуста
    if (year_fullName[year].suname.size() == 0) year_fullName[year].suname = currentSuname;
    // запоминаем что меняли в этом году имя
    year_fullName[year].isNameChanged = true;
  }

  void ChangeLastName(int year, const string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
    string currentName = "";

    // записываем в текущий год новую фамилию
    year_fullName[year].suname = last_name;

    // трясем прошлые и будущие записи
    for (auto& item : year_fullName){
      // проверка прошлых годов (берем прошлое имя)
      if (item.first < year) currentName = item.second.name;
      // замена будущих фамилий до очередной замены
      if (item.first > year){
        // если в будущем встретилась смена фамилии, запрещаем менять будущие фамилии
        if (item.second.isSunameChanged == true) break;
        else year_fullName[item.first].suname = last_name;
      }
    }

    //записываем прошлое имя в текущий год, если имя пусто
    if (year_fullName[year].name.size() == 0) year_fullName[year].name = currentName;
    // запоминаем что меняли в этом году фамилию
    year_fullName[year].isSunameChanged = true;
  }
  
  string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year

    // если после всех итераций по множеству result не изменится, функция вернет Инкогнито
    string result = "Incognito";

    for (const auto& item : year_fullName){
      //-------- если запрашиваемый год имеется
      if (year == item.first) {
        // проверка наличия имени
        if (item.second.name.size() == 0) result = item.second.suname + " with unknown first name";
        // проверка наличия фамилии
        else if (item.second.suname.size() == 0) result = item.second.name + " with unknown last name";
        // если имя и фамилия имеется
        else result = item.second.name + " " + item.second.suname;
      }
      //-------- если запрашиваемый год больше текущего в цикле проверки,
      //-------- запоминаем имя и фамилию текущего года, чтобы вернуть его, в случае,
      //-------- если к концу цикла if (year == item.first) так и не настанет
      else if (year > item.first) {
        if (item.second.name.size() == 0) result = item.second.suname + " with unknown first name";
        else if (item.second.suname.size() == 0) result = item.second.name + " with unknown last name";
        else result = item.second.name + " " + item.second.suname;
      }
    }

    // возвращаем результат провеки
    return result;
  }
  
  void PrintAll() {
    cout << endl << "============================" << endl;
    for (const auto& item : year_fullName){
      cout << item.first << ": " << item.second.name << ' ' << item.second.suname << endl;
    }
    cout << "============================" << endl << endl;
  }
  
};

int main(){
  Person person;

//  person.ChangeLastName(1965, "Sergeeva");
//  person.ChangeFirstName(1967, "Polina");

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


//  person.PrintAll();

//  person.ChangeFirstName(1950, "Irina");
//  person.ChangeLastName(1949, "Pozdeeva");
//  person.ChangeFirstName(1945, "Anna");
//  person.ChangeLastName(1945, "Petrova");
//  person.ChangeLastName(1999, "Ivanova");

//  for (int year : {2020, 1700}) {
//    cout << person.GetFullName(year) << endl;
//  }
//  person.PrintAll();
  return 0;
}

