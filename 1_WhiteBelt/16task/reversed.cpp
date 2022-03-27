/* Реализуйте функцию vector<int> Reversed(const vector<int>& v),
 * возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v) {
  vector<int> vr;

  for (int i = v.size() - 1; i >= 0; i--) {
    vr.push_back(v[i]);
  }
 return vr;
}

/*
vector<int> Reversed(const vector<int>& input)
{
    vector<int> result;
    for (int i = input.size() - 1; i >= 0; --i) {
        result.push_back(input[i]);
    }
    return result;
}
*/
