/* Напишите функцию, которая:
 * называется PalindromFilter
 * возвращает vector<string>
 *
 * принимает vector<string> words и int minLength и
 * возвращает все строки из вектора words, которые являются палиндромами и имеют длину не меньше minLength
 *
 * Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
 *
 * На проверку пришлите файл с реализацией функции PalindromFilter.
 * Ваш файл может содержать и другие функции, если они вам необходимы.
 * В этой задаче ваша программа не обязана что-то считывать из stdin и записывать в stdout —
 * тестирующая система будет вызывать вашу функцию PalindromFilter напрямую
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> PalindromFilter(vector<string> words, uint16_t minLength) {
  //cout << "======================================" << endl;
  //cout << "Start PalindromFilter(" << minLength << ')' << endl;
  //cout << "***" << endl;
  vector<string> filteredWords = {};

  for (uint16_t i = 0; i < words.size(); ++i) { // перебор вектора words
    // Проверка на палиндром
    bool check = true;

    for (uint16_t j = 0, k = words[i].length() - 1; j < words[i].length(); ++j, --k) {
      if (words[i][j] != words[i][k]) check = false;
    }
    //cout << "check palindrom for string "<< i << ": " << check << endl;
    //cout << "words[i] = " << words[i] << endl;
    //cout << "words[i].length() = " << words[i].length() << endl;

    // Если палиндром-OK и длина больше минимальной
    if (check && words[i].length() >= minLength) {
      filteredWords.push_back(words[i]);
      //cout << "Add to filteredWords vector" << endl;
    }
    else {
      //cout << "Don't added " << endl;
    }
    //cout << "***" << endl;
  }
  //cout << endl << "filteredWords.size() = " << filteredWords.size() << endl;

  //cout << endl << "======================================" << endl;
  return filteredWords;
}

/*
// определяет, является ли строка s палиндромом
bool IsPalindrom(string s) {

  // переберём все символы s[i] из первой половины строки
  for (size_t i = 0; i < s.size() / 2; ++i) {
    // s[s.size() - i - 1] — символ, симметричный символу s[i]
    if (s[i] != s[s.size() - i - 1]) {
      return false;  // если они не совпадают, строка точно не палиндром
    }
  }

  // если все пары символов совпадают, строка — палиндром
  return true;
}

vector<string> PalindromFilter(vector<string> words, int min_length) {
  vector<string> result;
  // перебираем все элементы вектора words
  for (auto s : words) {
    // если требуеые условия выполняются, добавляем s к ответу
    if (s.size() >= min_length && IsPalindrom(s)) {
      result.push_back(s);
    }
  }
  return result;
}
*/
