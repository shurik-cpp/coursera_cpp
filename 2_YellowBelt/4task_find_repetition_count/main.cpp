#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

// Здесь Lang — идентификатор языка:
enum class Lang {
  DE, FR, IT
};

// Имеется база регионов, представленная вектором структур Region:
struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

// функция собирает (связывет) из структуры кортеж
tuple<const string&, const string&, const map<Lang, string>&, int64_t> GetRank(const Region& region) {
  return tie(region.std_name, region.parent_std_name, region.names, region.population);
}

bool operator<(const Region& lhs, const Region& rhs) {
  return GetRank(lhs) < GetRank(rhs);
}


/* Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и определяющую,
 * какое максимальное количество повторов (число вхождений одного и того же элемента) она содержит.
 * Две записи (объекты типа Region) считаются различными,
 * если они отличаются хотя бы одним полем.
 *
 * Если все записи уникальны, считайте максимальное количество повторов равным 1.
 * Если записи отсутствуют, верните 0.
 * Гарантируется, что типа int достаточно для хранения ответа.
*/
int FindMaxRepetitionCount(const vector<Region>& regions) {
  int result = 0;
  map<Region, int> region_counter;

  for (const Region& it : regions) {
    result = max(result, ++region_counter[it]);
  }
  return result;
}

int main() {
  cout << FindMaxRepetitionCount({
              {
                  "Moscow",
                  "Russia",
                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                  89
              }, {
                  "Russia",
                  "Eurasia",
                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                  89
              }, {
                  "Moscow",
                  "Russia",
                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                  89
              }, {
                  "Moscow",
                  "Russia",
                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                  89
              }, {
                  "Russia",
                  "Eurasia",
                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                  89
                  },
              }) << endl;

  cout << FindMaxRepetitionCount({
              {
                  "Moscow",
                  "Russia",
                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                  89
              }, {
                  "Russia",
                  "Eurasia",
                  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                  89
              }, {
                  "Moscow",
                  "Russia",
                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
                  89
              }, {
                  "Moscow",
                  "Toulouse",
                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                  89
              }, {
                  "Moscow",
                  "Russia",
                  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                  31
                  },
              }) << endl;

  return 0;
}
