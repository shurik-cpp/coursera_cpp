/* Слова называются анаграммами друг друга, если одно из них можно получить
 * перестановкой букв в другом.
 * Например, слово «eat» можно получить перестановкой букв слова «tea»,
 * поэтому эти слова являются анаграммами друг друга.
 * Даны пары слов, проверьте для каждой из них,
 * являются ли слова этой пары анаграммами друг друга.
 *
 * Указание
 * Один из способов проверки того, являются ли слова анаграммами друг друга,
 * заключается в следующем. Для каждого слова с помощью словаря подсчитаем,
 * сколько раз в нём встречается каждая буква. Если для обоих слов эти словари равны
 * (а это проверяется с помощью обычного оператора ==),
 * то слова являются анаграммами друг друга, в противном случае не являются.
 *
 * При этом построение такого словаря по слову удобно вынести в отдельную функцию BuildCharCounters.
 *
 * Формат ввода
 * Сначала дано число пар слов N, затем в N строках содержатся пары слов,
 * которые необходимо проверить.
 * Гарантируется, что все слова состоят лишь из строчных латинских букв.
 *
 * Формат вывода
 * Выведите N строк: для каждой введённой пары слов YES,
 * если эти слова являются анаграммами, и NO в противном случае.
 *
 * Пример
 * -------
 * Ввод
 * -------
 * 3
 * eat tea
 * find search
 * master stream
 *
 * -------
 * Вывод
 * -------
 * YES
 * NO
 * YES
 *
*/
#include <iostream>
#include <map>
#include <string>

using namespace std;

bool BuildCharCounters(string& a, string& b) {

  map<char, char> a_word, b_word;
  for (auto i : a) {
    ++a_word[i];
  }
  for (auto i : b) {
    ++b_word[i];
  }

  if (a_word == b_word) return true;
  else return false;

}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string a, b;
    cin >> a >> b;
    if (BuildCharCounters(a, b)) {
      cout << "YES" << endl;
    }
    else {
      cout << "NO" << endl;
    }
  }

  return 0;
}

/*
map<char, int> BuildCharCounters(const string& word) {
  map<char, int> counters;
  for (char c : word) {
    ++counters[c];
  }
  return counters;
}

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    string first_word, second_word;
    cin >> first_word >> second_word;
    if (BuildCharCounters(first_word) == BuildCharCounters(second_word)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}
*/
