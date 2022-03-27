#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <iomanip>
#include <ostream>

using namespace std;

struct Date {
  int year;
  int month;
  int day;
};

void DateSeparatorCheck(stringstream& stream, const string& val) {
  if (stream.peek() != '-') { // проверка разделителя даты
    throw runtime_error("Wrong date format: " + val);
  }
  else stream.ignore(1);
}

Date ParseDate(const string& s) {
  stringstream stream(s); // создаем поток из строки s
  Date date;
  string garbige;

  // парсим поток
  stream >> date.year;
  DateSeparatorCheck(stream, s);
  if (stream >> date.month) DateSeparatorCheck(stream, s);
  if (stream >> date.day);
  else throw runtime_error("Wrong date format: " + s);

  // собираем остатки строки:
  stream >> garbige;
  if (garbige.size() != 0) throw runtime_error("Wrong date format: " + s);

  if (date.month < 1 || date.month > 12) {
    throw runtime_error("Month value is invalid: " + to_string(date.month));
  }
  else if (date.day < 1 || date.day > 31) {
    throw runtime_error("Day value is invalid: " + to_string(date.day));
  }

  return date;
}

//------------------------------------
bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.year == rhs.year) {
    if (lhs.month == rhs.month){
      return lhs.day < rhs.day; // если год и месяц совпадают, сортируем по дням
    }
    return lhs.month < rhs.month; // если месяцы не равны, сортируем по месяцу
  }
  return lhs.year < rhs.year; // если года не равны, сортируем по году
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setfill('0');
  stream << setw(4) << date.year << '-'
         << setw(2) << date.month << '-'
         << setw(2) << date.day;
  return stream;
}

//===============================================================
class Database {
public:
  void AddEvent(const Date& date, const string& event) { // добавляет событие
    data[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event) { // удаляет событие
    bool isFinded = false;
    if (data[date].count(event)) { // если есть такое событие по такой дате
      data[date].erase(event); // удаляем его
      isFinded = true;
    }
    if (data[date].size() == 0) data.erase(date); // если событий на эту дату не осталось, удаляем дату из словаря
    return isFinded; // если нет, возвращаем опущенный флаг
  }

  int DeleteDate(const Date& date) { // удаляет все события на эту дату
    int counterEvents = data[date].size();
    data.erase(date);
    return counterEvents;
  }

  set<string> Find(const Date& date) const {
    /* Поиск в константном словаре
     * При реализации данного шаблона вам может понадобится использовать поиск с помощью квадратных скобок для словаря,
     * переданного в функцию по константной ссылке. Как было показано ранее, это сделать не удастся,
     * так как обращение к несуществующему ключу с помощью квадратных скобок добавит его в словарь,
     * что недопустимо для константного словаря.
     *
     * В этом случае вместо квадратных скобок используйте метод at: в случае отсутствия ключа он выбросит исключение
     * и потому может быть использован для константного объекта.
     */
    return data.at(date); // теперь всё хорошо
  }

  void Print() const {
   // cout << "data.size() = " << data.size() << endl;
    for (const auto& it : data) {
      for (const auto& events : it.second) {
        cout << it.first << ' ' << events << endl;
      }
    }
  }

private:
  map<Date, set<string>> data;
};

//=================================================================
int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
    stringstream stream(command);
    string whatDo;

    try {
      stream >> whatDo;
      if (whatDo == "Add") {
        string add_date, add_event;
        stream >> add_date >> add_event;
        // парсим дату для добавления
        Date date = ParseDate(add_date);
        // добавляем в словарь класса Database
        db.AddEvent(date, add_event);
      }
      else if (whatDo == "Del") {
        string del_date, event;
        stream >> del_date;
        // парсим дату для удаления
        Date date = ParseDate(del_date);

        stream >> event;
        if (event.empty()) { // если после считывания даты event остался пуст
          cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
        }
        else {
          if (db.DeleteEvent(date, event)) {
            cout << "Deleted successfully" << endl;
          }
          else {
            cout << "Event not found" << endl;
          }
        }
      }
      else if (whatDo == "Find") {
        string find_date;
        stream >> find_date;
        // парсим дату для удаления
        Date date = ParseDate(find_date);
        // выводим все события этой даты
        try {
          for (const auto& it : db.Find(date)) {
            cout << it << endl;
          }
        }
        catch (const exception&) {
        }
      }
      else if (whatDo == "Print") {
        db.Print();
      }
      else if (!whatDo.empty()) throw runtime_error("Unknown command: " + whatDo);
    }
    catch (const exception& ex) {
      cout << ex.what() << endl;
      return 0;
    }
  }
  return 0;
}

