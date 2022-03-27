#include <map>
#include <vector>
#include <tuple>

// функция собирает (связывет) из структуры кортеж
tuple<const string&, const string&, const map<Lang, string>&, int64_t> GetRank(const Region& region) {
  return tie(region.std_name, region.parent_std_name, region.names, region.population);
}

bool operator<(const Region& lhs, const Region& rhs) {
  return GetRank(lhs) < GetRank(rhs);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
  int result = 0;
  map<Region, int> region_counter;

  for (const Region& it : regions) {
    result = max(result, ++region_counter[it]);
  }
  return result;
}
