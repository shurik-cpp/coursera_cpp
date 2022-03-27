#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "learner.h"
#include "profile.h"

using namespace std;

int main() {
  Learner learner;
  string line;
  {
    LOG_DURATION("random");
    for (int i = 0; i < 25000; ++i) {
      line += to_string(rand()) + ' ';
    }
  }
  //while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    {
      LOG_DURATION("learner.Learn");
      cout << learner.Learn(words) << "\n";
    }
  //}
  cout << "=== known words ===\n";

  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
  cout << "size = " << learner.KnownWords().size() << endl;
}
