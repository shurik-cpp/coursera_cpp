#include "database.h"

void Database::Add(const Date& date, const string& event) {
  // делаем быстрый поиск по отсортированной версии базы
  // если не обнаружилось событие в указанной дате,
  // добавляем его в хронологическую и сортированную базы
  if (!db_sorted[date].count(event)) {
      db[date].push_back(event);
      db_sorted[date].insert(event);
  }
}

void Database::Print(ostream& os) const {
  for (const auto& it_date : db) {
    for (const auto& it_event : it_date.second) {
      os << it_date.first << " " << it_event << endl;
    }
  }
}

ostream& operator<<(ostream& os, const pair<Date, string>& to_print) {
  os << to_print.first << " " << to_print.second;
  return os;
}

int Database::RemoveIf(function<bool(const Date&, const string&)> predic) {
  int counter = 0;
  set<Date> dates_to_del;
  // полностью очищаем сортированную базу
  db_sorted.clear();

  for (auto& it_date : db) {
    auto del_itr = begin(it_date.second);
    // перемещаем найденные, удовлетворяющие, события в начало вектора
    del_itr = stable_partition(begin(it_date.second), end(it_date.second),
                               [it_date, predic](string& event) {
                                 return predic(it_date.first, event);
                               });
    // посчитаем сколько событий будет удалено
    counter += del_itr - begin(it_date.second);
    // подчищаем вектор(дек) с начала до установленного итератора
    it_date.second.erase(begin(it_date.second), del_itr);
    // если событий в текущей дате не осталось, сохраняем дату, чтоб потом ее удалить
    if (it_date.second.empty()) {
      dates_to_del.insert(it_date.first);
      //db.erase(it_date.first);
    }
    else { // если в дате остались события
      // создаем set из оставшихся событий
      set<string> refreshed_events(begin(it_date.second), end(it_date.second));
      // и добавим дату с этими событиями в сортированную мапу
      db_sorted[it_date.first] = refreshed_events;
    }
  }
  // стираем пустые ключи из базы
  for (auto& it : dates_to_del) {
    db.erase(it);
  }
  return counter;
}

//string Database::Last(const Date& date) const {
//  if (db.empty() || date < db.begin()->first) {
//    throw invalid_argument("No entries");
//  }
//  // берем итераторы lower_bound upper_bound на элемент c искомой датой
//  auto lowUppBounds = db.equal_range(date);
//  // если lower_bound стоит на end, значит искомая дата больше тех, что есть в базе
//  // поэтому, шагнем назад, на последнюю существующуу дату
//  if (lowUppBounds.first == end(db)) lowUppBounds.first--;
//  // создадим константную ссылку на события vector внутри map
//  const auto& _events = lowUppBounds.first->second;
//  // конвертируем Data в string
//  stringstream ss;
//  ss << lowUppBounds.first->first;
//  string current_date;
//  ss >> current_date;
//  // вернем дату и разыменованную последнюю запись
//  return current_date + " " + _events.back();
//}
pair<Date, string> Database::Last(const Date& date) const {
  if (db.empty() || date < db.begin()->first) {
    throw invalid_argument("No entries");
  }
  // создаем и ставим итератор на нужную дату
  auto it = prev(db.upper_bound(date));
  // вернем пару из даты и последней записи событий
  return make_pair(it->first, it->second.back());
}
