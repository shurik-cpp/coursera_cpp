#include "test_runner.h"
#include <exception>
#include <iostream>


using namespace std;

bool IsPalindrom(const string& s) {
  // переберём все символы s[i] из первой половины строки
  for (size_t i = 0; i < s.size() / 2 ; ++i) {
    // s[s.size() - i - 1] — символ, симметричный символу s[i]
    if (s[i] != s[s.size() - i - 1]) {
      return false;  // если они не совпадают, строка точно не палиндром
    }
  }
  // если все пары символов совпадают, строка — палиндром
  return true;
}

void TestPailndrom() {
  Assert(IsPalindrom("madammadam"), "simple palindrom");
  // считает пустую строку палиндромом;
  Assert(IsPalindrom(""), "empty");
  // считает строку из одного символа палиндромом;
  Assert(IsPalindrom("f"), "one symbol");
  // осуществляет обычное сравнение символов на равенство,
  // не игнорируя никакие символы, в том числе пробельные
  Assert(IsPalindrom("m ada m"), "palindrom with space");
}

void AdditionalTest() {
  AssertEqual(IsPalindrom("wasitacaroracatisaw"), true, "last character");
  // При разработке тестов подумайте, какие ошибки можно допустить
  // при реализации функции IsPalindrom. Примеры ошибок:
  // игнорируется первый или последний символ;
  AssertEqual(IsPalindrom("smadam"), false, "first character");
  AssertEqual(IsPalindrom("madams"), false, "last character");
  // сравнение соответствующих символов завершается не в середине строки, а раньше;
  AssertEqual(IsPalindrom("madamedmadam"), false, "center character(1)");
  AssertEqual(IsPalindrom("wasitacaroracatisaw ls wasitacaroracatisaw"), false, "center character(2)");
  // игнорируются пробелы
  AssertEqual(IsPalindrom("wasitacar  oracatisaw"), false, "ignore space (1)");
  AssertEqual(IsPalindrom("m a dr a m"), false, "ignore space (2)");
  AssertEqual(IsPalindrom("          "), true, "ignore space (3)");
  AssertEqual(IsPalindrom("m ad a  m"), false, "ignore space (4)");
  // большие-маленькие символы
  AssertEqual(IsPalindrom("Madam"), false, "upper-lower character (1)");
  AssertEqual(IsPalindrom("MadAm"), false, "upper-lower character (2)");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestPailndrom, "Test Pailndrom");
  runner.RunTest(AdditionalTest, "Additional Test");

  return 0;
}
