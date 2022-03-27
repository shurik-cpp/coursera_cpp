#include <iostream>
#include <iomanip>
#include <sstream>
#include <ostream>
#include <string>
#include <set>
#include <map>


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

bool operator<(const Rational& r1, const Rational r2){
  if (r1.Denominator() != r2.Denominator()) {
    // приводим к общему знаминателю:
    int commonNum1 = r1.Numerator() * r2.Denominator();
    int commonNum2 = r2.Numerator() * r1.Denominator();
    //int commonDenom = r1.Denominator() * r2.Denominator();
    return commonNum1 < commonNum2;
  }
  return r1.Denominator() < r2.Denominator();
}

int main() {
  set<Rational> rationals;
  rationals.insert(Rational(1, 2));
  rationals.insert(Rational(1, 3));
  rationals.insert(Rational(1, 8));

  //  cout << "set test:" << endl;
  //  for (auto& it : rationals) {
  //    cout << it << ' ';
  //  }
  //  cout << endl << endl << "map test:" << endl;

  map<Rational, string> name;
  name[Rational(1, 2)] = "a half";
  name[Rational(1, 3)] = "one third";

  //  for (auto& it : name) {
  //    cout << it.first << " - " << it.second << endl;
  //  }

  return 0;
}