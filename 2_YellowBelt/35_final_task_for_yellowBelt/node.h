#pragma once
#include <iostream>
#include <memory>
#include "date.h"

using namespace std;

enum class LogicalOperation {
  Or,
  And
};

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

struct Node {
  // Evaluate - Оценивать
  virtual bool Evaluate(const Date& date, const string& event) const = 0;

};

struct EmptyNode : public Node {
  bool Evaluate(const Date& date, const string& event) const override;
};


class DateComparisonNode : public Node {
public:
  DateComparisonNode(const Comparison& cmp, const Date& date)
      : _cmp(cmp),
        _date(date) {}

  bool Evaluate(const Date& date, const string& event) const override;

private:
  const Comparison _cmp;
  const Date _date;
};

class EventComparisonNode : public Node {
public:
  EventComparisonNode(const Comparison& cmp, const string& event)
      : _cmp(cmp),
        _event(event) {}

  bool Evaluate(const Date& date, const string& event) const override;

private:
  const Comparison _cmp;
  const string _event;
};

class LogicalOperationNode : public Node {
public:
  LogicalOperationNode(LogicalOperation logical_operation,
                       const shared_ptr<Node>& left,
                       const shared_ptr<Node>& right)
      : _logical_operation(logical_operation),
        _left(left),
        _right(right) {}

  bool Evaluate(const Date& date, const string& event) const override;

private:
  const LogicalOperation _logical_operation;
  const shared_ptr<Node> _left, _right;
};
