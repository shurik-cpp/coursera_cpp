#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

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
