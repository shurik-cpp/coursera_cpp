#include <iostream>
#include <algorithm>

using namespace std;

class ReversibleString {
public:
  ReversibleString(){} // пустой конструктор
  ReversibleString(const string& s){ // конструктор с параметрами
    savedString = s;
  }
  void Reverse(){
    reverse(savedString.begin(), savedString.end());
  }
  string ToString() const {
    return savedString;
  }
private:
  string savedString;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;

  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;

  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;

  return 0;
}
