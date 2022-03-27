/* Напишите функцию, которая
 *
 * называется IsPalindrom
 * возвращает bool
 * принимает параметр типа string и возвращает, является ли переданная строка палиндромом
 *
 * Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево.
 * Пустая строка является палиндромом.
*/
#include <iostream>
#include <string>
#include <IsPalindrom.cpp>

using namespace std;



int main() {
  string checkPalindrom = "";
  cin >> checkPalindrom;
  cout << checkPalindrom << endl;
  cout << IsPalindrom(checkPalindrom);

  return 0;
}
