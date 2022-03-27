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

// Комментарии, которые говорят, что именно нужно реализовать в этой программе

int main() {
  {
    const Rational r(3, 10);
    if (r.Numerator() != 3 || r.Denominator() != 10) {
      cout << "Rational(3, 10) != 3/10" << endl;
      return 1;
    }
  }

  {
    const Rational r(8, 12);
    if (r.Numerator() != 2 || r.Denominator() != 3) {
      cout << "Rational(8, 12) != 2/3" << endl;
      return 2;
    }
  }

  {
    const Rational r(-4, 6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(-4, 6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(4, -6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(4, -6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(0, 15);
    if (r.Numerator() != 0 || r.Denominator() != 1) {
      cout << "Rational(0, 15) != 0/1" << endl;
      return 4;
    }
  }

  {
    const Rational defaultConstructed;
    if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
      cout << "Rational() != 0/1" << endl;
      return 5;
    }
  }

  cout << "OK" << endl;
  return 0;
}
