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

using namespace std;

void UpdateIfGreater(int first, int& second) {
  if (first > second) second = first;
}
