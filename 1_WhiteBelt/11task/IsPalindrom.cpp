#include <string>
using namespace std;

bool IsPalindrom(string s) {
  bool check = true;

  string n = "";
  if (s == n) return check;

  for (uint64_t i = 0, j = s.length() - 1; i < s.length(); ++i, --j) {
    if (s[i] != s[j]) check = false;
  }
  return check;
}

//
/*
bool IsPalindrom(string s) {
    // Замечание: более правильным было бы использовать здесь тип size_t вместо int
    // О причинах Вы узнаете на Жёлтом поясе
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
*/
