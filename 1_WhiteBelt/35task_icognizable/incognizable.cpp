#include <iostream>

using namespace std;

struct Incognizable {
  int one;
  int two;
};

int main() {
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
  return 0;
}
