#include "node.h"

template<class T>
bool isCompare(Comparison cmp, const T& a, const T& b) {
  switch (cmp) {
  case Comparison::Equal: return a == b;
  case Comparison::Less: return a < b;
  case Comparison::LessOrEqual: return a <= b;
  case Comparison::Greater: return a > b;
  case Comparison::GreaterOrEqual: return a >= b;
  case Comparison::NotEqual: return a != b;
  }

  throw invalid_argument("Invalid comparison operator");
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
  (void) date;
  (void) event;
  return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
  (void) event;
  return isCompare(_cmp, date, _date);
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
  (void) date;
  return isCompare(_cmp, event, _event);
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
  switch(_logical_operation) {
  case LogicalOperation::Or:
    return _left->Evaluate(date, event) || _right->Evaluate(date, event);

  case LogicalOperation::And:
    return _left->Evaluate(date, event) && _right->Evaluate(date, event);
  }

  throw invalid_argument("Invalid logical operation");
}
