#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype> // для tolower()

using namespace std;

void stringToLower(string& s){
  for (unsigned int i = 0; i < s.length(); ++i){
    char symbol;
    symbol = s[i];
    s[i] = tolower(symbol); // преобразуем все символы в строке в нижний регистр
  }
}

int main(){
  vector<string> v;

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i){
    string s;
    cin >> s;
    v.push_back(s);
  }

  sort(begin(v), end(v), [](string a, string b){
    stringToLower(a);
    stringToLower(b);
    return a < b;
  });

  for (const auto& k : v){
    cout << k << ' ';
  }
  return 0;
}

/*
// сортируем
  sort(begin(v), end(v),
       // компаратор для сортировки — лямбда-функция, сравнивающая строки без учёта регистра
       [](const string& l, const string& r) {
         // сравниваем лексикографически...
         return lexicographical_compare(
             // ... все символы строки l ...
             begin(l), end(l),
             // ... со всеми символами строки r ...
             begin(r), end(r),
             // ..., используя в качестве компаратора сравнение отдельных символов без учёта регистра
             [](char cl, char cr) { return tolower(cl) < tolower(cr); }
         );
       }
  );
*/
