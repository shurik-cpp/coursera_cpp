/* Напишите функцию UpdateIfGreater, которая:
 *
 * принимает два целочисленных аргумента: first и second.
 * Если first оказался больше second, Ваша функция должна
 * записывать в second значение параметра first.
 * При этом указанная функция не должна ничего возвращать,
 * а изменение параметра second должно быть видно на вызывающей стороне.
 *
 * Пример:
 * int a = 4;
 * int b = 2;
 * UpdateIfGreater(a, b);
 * // b должно стать равно 4
 *
 * Замечание!
 *
 * В данной задаче вам нужно самостоятельно выбрать типы для параметров функции UpdateIfGreater.
 * Подумайте, какой из них обязан быть ссылкой, а какой может быть просто int.
 * При этом учтите разные варианты вызова функции:
 * UpdateIfGreater(x, y);
 * update_ifUpdateIfGreater(5, y);
*/

#include <iostream>
#include <update_if_greater.cpp>

using namespace std;

int main() {
  int a = 4;
  int b = 2;
  UpdateIfGreater(a, b);
  cout << b;
  return 0;
}

/* Compile error: b'/tmp/submissionw6_h8ym1/update_if_greater.cpp:
 * 40:1: fatal error: static_assert failed due to requirement \
 * 'std::is_same_v<void (*)(const int &, int &), void (*)(int, int &)>\'
 * "Function void UpdateIfGreater(int, int&) not found in your submission"\
 * nstatic_assert(\n^\n1 error generated.\n'
*/
