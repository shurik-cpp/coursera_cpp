#include <iostream>
#include <string>
#include <set>

using namespace std;

int main(){
  set<string> many;
  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    string word;
    cin >> word;
    many.insert(word);
  }
  cout << many.size() << endl;

  return 0;
}
