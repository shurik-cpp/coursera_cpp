#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
private:
  set<string> dict; // было vector<string> dict;

public:

  /*
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (find(dict.begin(), dict.end(), word) == dict.end()) {
        ++newWords;
        dict.push_back(word);
      }
    }
    return newWords;
  }*/
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (!dict.count(word)) {
        ++newWords;
        dict.insert(word);
      }
    }
    return newWords;
  }

  /*
  vector<string> KnownWords() {
    sort(dict.begin(), dict.end());
    dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return dict;
  }
  */
  vector<string> KnownWords() {
    return vector<string>{dict.begin(), dict.end()};
  }
};
