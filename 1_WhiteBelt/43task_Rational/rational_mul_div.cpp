#include <iostream>

using namespace std;

class Rational {
public:
  // Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
  Rational() {
    num = 0;
    denom = 1;
  }

  Rational(int numerator, int denominator) {
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

  int Numerator() const {
    return num;
  };
  int Denominator() const {
    return denom;
  };

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
  // если знаменатели равны:
  if (r1.Denominator() == r2.Denominator()) return Rational(r1.Numerator() - r2.Numerator(), r2.Denominator());
  // приводим к общему знаминателю:
  int commonNum1 = r1.Numerator() * r2.Denominator();
  int commonNum2 = r2.Numerator() * r1.Denominator();
  int commonDenom = r1.Denominator() * r2.Denominator();

  return Rational(commonNum1 - commonNum2, commonDenom);
}

Rational operator*(const Rational& r1, const Rational& r2){
  return Rational(r1.Numerator() * r2.Numerator(), r1.Denominator() * r2.Denominator());
}

Rational operator/(const Rational& r1, const Rational& r2){
  return Rational(r1.Numerator() * r2.Denominator(), r1.Denominator() * r2.Numerator());
}

int main() {
  {
    Rational a(2, 3);
    Rational b(4, 3);
    Rational c = a * b;
    bool equal = c == Rational(8, 9);
    if (!equal) {
      cout << "2/3 * 4/3 != 8/9" << endl;
      return 1;
    }
  }

  {
    Rational a(5, 4);
    Rational b(15, 8);
    Rational c = a / b;
    bool equal = c == Rational(2, 3);
    if (!equal) {
      cout << "5/4 / 15/8 != 2/3" << endl;
      return 2;
    }
  }

  cout << "OK" << endl;
  return 0;
}
