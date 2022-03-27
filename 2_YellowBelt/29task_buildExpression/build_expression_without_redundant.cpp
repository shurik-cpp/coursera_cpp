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

  string last_operator;
  for (int i = 0; i < N; ++i) {
    string _operator, _operand, operation;
    cin >> _operator >> _operand;
    operation = " " + _operator + " " + _operand;

    if ((_operator == "*" || _operator == "/") &&
        (last_operator == "+" || last_operator == "-")) {
      PutInBrackets(expression);
    }
    expression.push_back(operation);
    last_operator = _operator;
  }

  for (auto it : expression) {
    cout << it;
  }
  cout << endl;

  return 0;
}
