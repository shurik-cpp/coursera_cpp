#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;



// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
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


template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (runtime_error& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


void Test() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  AssertEqual(person.GetFullName(1965), "Polina with unknown last name", "(1965)");
  person.ChangeLastName(1967, "Sergeeva");
  AssertEqual(person.GetFullName(1967), "Polina Sergeeva", "(1967)");
  person.ChangeFirstName(1970, "Appolinaria");
  AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva", "(1970)");
  person.ChangeLastName(1968, "Volkova");
  AssertEqual(person.GetFullName(1968), "Polina Volkova", "(1968)");
  AssertEqual(person.GetFullName(1990), "Appolinaria Volkova", "(1990)");
  AssertEqual(person.GetFullName(1960), "Incognito", "(1960)");

  Person person2;
  person2.ChangeLastName(1967, "Sergeev");
  AssertEqual(person2.GetFullName(1967), "Sergeev with unknown first name", "(1967-p2)");
}

int main() {
  TestRunner r;

  r.RunTest(Test, "Test:");

  return 0;
}
