std::vector<Person> SortByGender(const std::vector<Person>& p, Gender g) {
  std::vector<Person> result;
  for (auto it : p) {
    if (it.gender == g) {
      result.push_back(it);
    }
  }
  return result;
}

std::vector<Person> SortByEmployed(const std::vector<Person>& p, bool employed) {
  std::vector<Person> result;
  for (auto it : p) {
    if (it.is_employed == employed) {
      result.push_back(it);
    }
  }
  return result;
}

/* Вычисляющую и выводящую медианный возраст для каждой из следующих групп людей:
 *
 * все люди;
 *
 * все женщины;
 * все мужчины;
 *
 * все занятые женщины;
 * все безработные женщины;
 *
 * все занятые мужчины;
 * все безработные мужчины.
*/
void PrintStats(std::vector<Person> persons) {
  using namespace std;
  vector<Person> sorted;
  cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

  sorted = SortByGender(persons, Gender::FEMALE);
  cout << "Median age for females = "
       << ComputeMedianAge(sorted.begin(), sorted.end()) << endl;
  sorted = SortByGender(persons, Gender::MALE);
  cout << "Median age for males = "
       << ComputeMedianAge(sorted.begin(), sorted.end()) << endl;

  sorted = SortByEmployed(SortByGender(persons, Gender::FEMALE), true);
  cout << "Median age for employed females = "
       << ComputeMedianAge(sorted.begin(), sorted.end()) << endl;
  sorted = SortByEmployed(SortByGender(persons, Gender::FEMALE), false);
  cout << "Median age for unemployed females = "
       << ComputeMedianAge(sorted.begin(), sorted.end()) << endl;

  sorted = SortByEmployed(SortByGender(persons, Gender::MALE), true);
  cout << "Median age for employed males = "
       << ComputeMedianAge(sorted.begin(), sorted.end()) << endl;
  sorted = SortByEmployed(SortByGender(persons, Gender::MALE), false);
  cout << "Median age for unemployed males = "
       << ComputeMedianAge(sorted.begin(), sorted.end()) << endl;

}
