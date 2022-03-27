#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cmath>

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

// возвращает количество уникальных действительных корней
// уравнения ax² + bx + c = 0.
int GetDistinctRealRootCount(double a, double b, double c) {
  int result = 0;
  if (a == 0 && b == 0) return 0;
  else if (a == 0 && c == 0) return 1;
  if (a == 0 && c == 0) return 1;

  double d = (b * b) - (4 * a * c);
  double x1 = (sqrt(d) - b) / (2 * a);
  double x2 = (-sqrt(d) - b) / (2 * a);

  if (d > 0) result = 2;
  else if (d == 0 || x1 == x2) return 1;

  return result;
}

void Test() {
  //d = (b * b) - (4 * a * c);
  AssertEqual(GetDistinctRealRootCount(0, 0, 0),   0, "a = 0 && b = 0 && c = 0");
  AssertEqual(GetDistinctRealRootCount(0, 0, 1),   0, "a = 0 && b = 0");
  AssertEqual(GetDistinctRealRootCount(1, 0, 1),   0, "D < 0 (1)");
  AssertEqual(GetDistinctRealRootCount(1, 1, 1),   0, "D < 0 (2)");

  AssertEqual(GetDistinctRealRootCount(-1, 2, -1), 1, "for D = 0 (1)");
  AssertEqual(GetDistinctRealRootCount(1, 2, 1),   1, "for D = 0 (2)");
  AssertEqual(GetDistinctRealRootCount(1, 0, 0),   1, "b = 0 && c = 0");
  AssertEqual(GetDistinctRealRootCount(0, 1, 0),   1, "a = 0 && c = 0");

  AssertEqual(GetDistinctRealRootCount(-1, 2, 1),  2, "D > 0 (1)");
  AssertEqual(GetDistinctRealRootCount(1, 2, -1),  2, "D > 0 (2)");

}

int main() {
  TestRunner r;
  r.RunTest(Test, "Test:");

  return 0;
}
