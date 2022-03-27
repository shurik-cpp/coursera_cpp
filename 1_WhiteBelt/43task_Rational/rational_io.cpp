#include <iostream>
#include <iomanip>
#include <sstream>
#include <ostream>
#include <string>


using namespace std;

class Rational {
public:
  // Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
  Rational() {
    num = 0;
    denom = 1;
  }

  Rational(int numerator, int denominator) {
    Reduce(numerator, denominator);
  }

  int Numerator() const {
    return num;
  };
  int Denominator() const {
    return denom;
  };

  void Reduce(const int& numerator, const int& denominator){
    // При конструировании объека класса Rational с параметрами p и q
    // должно выполняться сокращение дроби p/q
    // (здесь вам может пригодиться решение задачи «Наибольший общий делитель»).
    // пока оба числа положительны, будем их уменьшать, не меняя их НОД
    int a = abs(numerator), b = abs(denominator), nod;
    while (a > 0 && b > 0) {
      // возьмём большее из чисел и заменим его остатком от деления на второе
      // действительно, если a и b делятся на x, то a - b и b делятся на x
      // тогда и a % b и b делятся на x, так что можно a заменить на a % b
      if (a > b) {
        a %= b;
      } else {
        b %= a;
      }
    }
    nod = a + b; // наибольший общий делитель

    // Если дробь p/q отрицательная, то объект Rational(p, q) должен
    // иметь отрицательный числитель и положительный знаменатель
    if (numerator > 0 && denominator < 0) num = -(numerator / nod);
    else num = numerator / nod;
    // Если дробь p/q положительная, то объект Rational(p, q) должен
    // иметь положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
    if (numerator < 0 && denominator < 0) num = abs(numerator / nod);

    //Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
    if (num == 0) denom = 1;
    else denom = abs(denominator / nod); // а знаменатель всегда положительный

    //cout << "nod = " << nod << ", n/d = " << num << '/' << denom << endl;
  }

private:
  int num;
  int denom;

};

// перегрузка оператора сравнения на равность
bool operator==(const Rational& r1, const Rational& r2) {
  if ((r1.Numerator() == r2.Numerator()) &&
      (r1.Denominator() == r2.Denominator())) return true;
  return false;
}
// перегрузка оператора +
Rational operator+(const Rational& r1, const Rational& r2){
  // если знаменатели равны:
  if (r1.Denominator() == r2.Denominator()) return Rational(r1.Numerator() + r2.Numerator(), r2.Denominator());
  // приводим к общему знаминателю:
  int commonNum1 = r1.Numerator() * r2.Denominator();
  int commonNum2 = r2.Numerator() * r1.Denominator();
  int commonDenom = r1.Denominator() * r2.Denominator();

  return Rational(commonNum1 + commonNum2, commonDenom);
}
// перегрузка оператора -
Rational operator-(const Rational& r1, const Rational& r2){
  // если знаменатели равны:rational
  if (r1.Denominator() == r2.Denominator()) return Rational(r1.Numerator() - r2.Numerator(), r2.Denominator());
  // приводим к общему знаминателю:
  int commonNum1 = r1.Numerator() * r2.Denominator();
  int commonNum2 = r2.Numerator() * r1.Denominator();
  int commonDenom = r1.Denominator() * r2.Denominator();

  return Rational(commonNum1 - commonNum2, commonDenom);
}
// перегрузка оператора *
Rational operator*(const Rational& r1, const Rational& r2){
  return Rational(r1.Numerator() * r2.Numerator(), r1.Denominator() * r2.Denominator());
}
// перегрузка оператора /
Rational operator/(const Rational& r1, const Rational& r2){
  return Rational(r1.Numerator() * r2.Denominator(), r1.Denominator() * r2.Numerator());
}

// перегрузка оператора вывода в поток <<
ostream& operator<<(ostream& stream, const Rational& r){
  stream << r.Numerator() << '/' << r.Denominator();
  return stream;
}

// перегрузка оператора ввода в поток >>
istream& operator>>(istream& stream, Rational& r){
  int n, d;
  char symbol;
  stream >> n;
  //stream.ignore(1);
  stream >> symbol;
  stream >> d;
  if (stream.fail() == false && symbol == '/') r.Reduce(n, d);
  return stream;
}

int main() {
  {
    ostringstream output;
    output << Rational(-6, 8);
    if (output.str() != "-3/4") {
      cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
      return 1;
    }
  }

  {
    istringstream input("5/7");
    Rational r;
    input >> r;
    bool equal = r == Rational(5, 7);
    if (!equal) {
      cout << "5/7 is incorrectly read as " << r << endl;
      return 2;
    }
  }

  {
    istringstream input("");
    Rational r;
    bool correct = !(input >> r);
    if (!correct) {
      cout << "Read from empty stream works incorrectly" << endl;
      return 3;
    }
  }

  {
    istringstream input("5/7 10/8");
    Rational r1, r2;
    input >> r1 >> r2;
    bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
      return 4;
    }

    input >> r1;
    input >> r2;
    correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
      return 5;
    }
  }

  {
    istringstream input1("1*2"), input2("1/"), input3("/4");
    Rational r1, r2, r3;
    input1 >> r1;
    input2 >> r2;
    input3 >> r3;
    bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
    if (!correct) {
      cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
           << r1 << " " << r2 << " " << r3 << endl;

      return 6;
    }
  }

  cout << "OK" << endl;
  return 0;
}
