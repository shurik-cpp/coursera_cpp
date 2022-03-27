#include <iostream>
#include <map>
#include <set>
//#include <string>

using namespace std;

bool isExist(const string& word1, const string& word2, const set<map<string, string>>& synonyms){

  // трясем set
  for (const auto& k : synonyms){
    // трясем map, который лежит в set
    map<string, string> checkSynonym = k;
    for (auto c : checkSynonym){
      if ((word1 == c.first && word2 == c.second) || (word1 == c.second && word2 == c.first)){
        return true;
      }
    }
  }
  // если в цикле не вышли с true, возвращаем false
  return false;
}

int main(){
  // будем собирать в кучу словари из одного ключ-значение
  set<map<string, string>> synonyms;

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i){
    string command;
    cin >> command;

    if (command == "ADD"){
      string word1, word2;
      cin >> word1 >> word2;

      map<string, string> addedSynonym;
      addedSynonym[word1] = word2; // записываем словарь
    }
    else if (command == "COUNT"){
      int countOfHit = 0; // счетчик совпадений
      string word;
      cin >> word;

      for (const auto& oneItemOfSynonyms : synonyms) {
        map<string, string> oneSynonym = oneItemOfSynonyms;

        for (auto& k : oneSynonym) {
          if (k.first == word || k.second == word) ++countOfHit;
        }
      }
      cout << countOfHit << endl;
    }
    else if (command == "CHECK"){
      string word1, word2;
      cin >> word1 >> word2;

      if (isExist(word1, word2, synonyms)){
        cout << "YES" << endl;
      }
      else {
        cout << "NO" << endl;
      }
    }
    else if (command == "DEBUG"){ // для дебага
      cout << "synonyms.size() = " << synonyms.size() << endl;
      for (const auto& debug : synonyms){
        map<string, string> printMap = debug;
        for (auto p :printMap) {
          cout << "synonim: " << p.first << " - " << p.second << endl;
        }
      }
    }
  }

  return 0;
}
