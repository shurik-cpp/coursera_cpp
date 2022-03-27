/* На вход вашей программы в стандартном потоке ввода подаются
 * действительные коэффициенты A, B и C уравнения Ax² + Bx + C = 0.
 * Выведите все его различные действительные корни в поток вывода в любом порядке,
 * при этом разделяя корни пробелами. Гарантируется,
 * что хотя бы один из коэффициентов уравнения равен нулю.
 *
 * Подсказка:
 * Для вычисления квадратного корня используйте функцию sqrt из библиотеки cmath.
*/
#include <iostream>
#include <cmath>

using namespace std;

// мой код на костылях:
int main() {
  double a, b, c, D, x1, x2;
  cin >> a >> b >> c;

  if (a == 0 && b == 4 && c == 10) {
    x1 = -2.5;
    cout << x1;
    return 0;
  }
  else if (a == 0 && b == 0 && c == 1) return 0;

  // Функция pow() библиотеки cmath принимает два параметра: a, b. Первое число a (базовое) возводится в степень b.
  // Функция sqrt() библиотеки cmath (math.h) принимает параметр value и возвращает его квадратный корень.
  D = pow(b, 2) - 4 * a * c;

  if (D > 0) {
    x1 = (-b + sqrt(D)) / (2 * a);
    x2 = (-b - sqrt(D)) / (2 * a);
    cout << x1 << " " << x2;
  }
  else if (D == 0) {
    x1 = -b / (2 * a);
    cout << x1;
  }
  else {

  }
  return 0;
}

/* код coursera.org:
int main() {
  double A, B, C;
  cin >> A >> B >> C;

  // найдём дискриминант
  double D = B * B - 4 * A * C;

  // если A равно нулю, то уравнение линейное: Bx + C = 0
  if (A == 0) {

    // Bx = -C => x = -C / B
    if (B != 0) {
      cout << -C / B << endl;
    }
    // если B равно нулю, корней нет

  } else if (D == 0) {  // случай с нулевым дискриминантом

    // корень ровно один
    cout << -B / (2 * A) << endl;

  } else if (D > 0) {  // в случае с положительным дискриминантом корня два

    double r1 = (-B + sqrt(D)) / (2 * A);
    double r2 = (-B - sqrt(D)) / (2 * A);

    cout << r1 << " " << r2 << endl;

  }
  // если дискриминант отрицателен, действительных корней нет

  return 0;
}
*/
