#include <iostream>
#include <deque>

using namespace std;

void PutInBrackets(deque<string>& exp) {
  exp.push_front("(");
  exp.push_back(")");
}


int main() {
  deque<string> expression;
  string x;
  cin >> x;

  expression.push_back(x);


  int N;
  cin >> N;
  if (N != 0) {
    PutInBrackets(expression);
  }

  for (int i = 0; i < N; ++i) {
    string _operator, _operand, operation;
    cin >> _operator >> _operand;
    operation = " " + _operator + " " + _operand;
    expression.push_back(operation);
    if (i != N - 1) {
      PutInBrackets(expression);
    }
  }

  for (auto it : expression) {
    cout << it;
  }
  cout << endl;

  return 0;
}
