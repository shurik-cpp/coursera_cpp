#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Напишите функцию SplitIntoWords, разбивающую строку на слова по пробелам.
// Рекомендуется следующий способ решения задачи:
// - искать очередной пробел с помощью алгоритма find;
// - создавать очередное слово с помощью конструктора строки по двум итераторам.
vector<string> SplitIntoWords(const string& s) {
  vector<string> result;
  auto word_begin = s.begin();
  auto word_end = word_begin;

  for (size_t i = 0; i < s.size(); ++i) {

    if (s[i] == ' ') {
      result.push_back({word_begin, word_end});
      word_begin = word_end;
      ++word_begin;
    }
    ++word_end;

  }

  result.push_back({word_begin, word_end});

  return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  //cout << endl;

  return 0;
}

