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




void TestDefault() {
  Rational r;
  // Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
  AssertEqual(r.Numerator(), 0, "default num");
  AssertEqual(r.Denominator(), 1, "default den");
}
void TestWithParam() {
  Rational r(1, 2);
  // При конструировании объекта класса Rational с параметрами p и q
  AssertEqual(r.Numerator(), 1, "with param num");
  AssertEqual(r.Denominator(), 2, "with param den");

  Rational r2(2, 4);
  // должно выполняться сокращение дроби p/q.
  AssertEqual(r2.Numerator(), 1, "with param num, reduction");
  AssertEqual(r2.Denominator(), 2, "with param den, reduction");
}
void TestNegative() {
  Rational r(-1, 2);
  // Если дробь p/q отрицательная, то объект Rational(p, q)
  // должен иметь отрицательный числитель и положительный знаменатель.
  AssertEqual(r.Numerator(), -1, "with param num, negative_1");
  AssertEqual(r.Denominator(), 2, "with param den, negative_1");

  Rational r2(1, -2);
  // Если дробь p/q отрицательная, то объект Rational(p, q)
  // должен иметь отрицательный числитель и положительный знаменатель.
  AssertEqual(r2.Numerator(), -1, "with param num, negative_2");
  AssertEqual(r2.Denominator(), 2, "with param den, negative_2");

  Rational r3(-2, 4);
  // должно выполняться сокращение дроби p/q.
  AssertEqual(r3.Numerator(), -1, "with param num, negative_reduction_1");
  AssertEqual(r3.Denominator(), 2, "with param den, negative_reduction_1");

  Rational r4(2, -4);
  // должно выполняться сокращение дроби p/q.
  AssertEqual(r4.Numerator(), -1, "with param num, negative_reduction_2");
  AssertEqual(r4.Denominator(), 2, "with param den, negative_reduction_2");
}

void TestPositive() {
  Rational r(-1, -2);
  // Если дробь p/q положительная, то объект Rational(p, q)
  // должен иметь положительные числитель и знаменатель
  // (обратите внимание на случай Rational(-2, -3)).
  AssertEqual(r.Numerator(), 1, "with param num, positive");
  AssertEqual(r.Denominator(), 2, "with param den, positive");

  Rational r2(-2, -4);
  // должно выполняться сокращение дроби p/q.
  AssertEqual(r2.Numerator(), 1, "with param num, positive_reduction");
  AssertEqual(r2.Denominator(), 2, "with param den, positive_reduction");
}

void TestNumZero() {
  Rational r(0, 5);
  // Если числитель дроби равен нулю, то знаменатель должен быть равен 1
  AssertEqual(r.Numerator(), 0, "with param num = 0");
  AssertEqual(r.Denominator(), 1, "den with param num = 0");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefault, "TestDefault");
  runner.RunTest(TestWithParam, "TestWithParam");
  runner.RunTest(TestNegative, "TestNegative");
  runner.RunTest(TestPositive, "TestPositive");
  runner.RunTest(TestNumZero, "TestNumZero");

  return 0;
}
