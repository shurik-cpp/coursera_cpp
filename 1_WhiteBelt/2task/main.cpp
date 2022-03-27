#include <iostream>
#include <string>

using namespace std;

int main() {
  string a, b, c;

  cin >> a >> b >> c;
  // мой код:
  if (a < b && a < c) cout << a;
  else if (b < a && b < c) cout << b;
  else if (c < a && c < b) cout << c;
  else {
    if (a == b && b < c) cout << a;
    else if (a == c && a < b) cout << a;
    else if (b == c && b < a) cout << b;
    else cout << c;
  }

  /* код coursera.org:

    if (a <= b && a <= c) {
    cout << a;
    } else if (b <= a && b <= c) {
    cout << b;
    } else {
    cout << c;
    }

  */

  return 0;
}
