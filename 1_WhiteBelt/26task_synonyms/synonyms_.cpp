#include <iostream>
#include <map>
#include <set>

using namespace std;


int main(){
  map<string, set<string>> synonyms; // у ключа множество значений

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i){
    string command;
    cin >> command;

    if (command == "ADD"){
      string word1, word2;
      cin >> word1 >> word2;

      synonyms[word1].insert(word2); // добавляем синоним в словарь
      synonyms[word2].insert(word1); // добавляем инверсию

    }
    else if (command == "COUNT"){
      string word;
      cin >> word;

      cout << synonyms[word].size() << endl; // выводим количество синонимов для word-слова
    }
    else if (command == "CHECK"){
      string word1, word2;
      cin >> word1 >> word2;

      if (synonyms.count(word1)){
        if (synonyms[word1].count(word2)){
          cout << "YES" << endl;
        }
        else {
          cout << "NO" << endl;
        }
      }
      else {
        cout << "NO" << endl;
        synonyms.erase(word1);
      }
    }
    else if (command == "DEBUG"){ // для дебага
      cout << "synonyms.size() = " << synonyms.size() << endl;
      for (const auto& debug : synonyms){
        cout << debug.first << ": ";
        set<string> printMap = debug.second;
        for (auto p : printMap) {
          cout << p << ' ';
        }
        cout << endl;
      }
    }
  }

  return 0;
}
