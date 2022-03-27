#pragma once

#include <memory>
#include <string>

// Так как Expression — это абстрактный класс, работать с ним можно только через указатель или ссылку.
// Чтобы не заниматься ручным управлением памятью, будем использовать умный указатель unique_ptr.
class Expression {
public:
	virtual ~Expression() = default;

	// Evaluate() возвращает численное значение выражения. Для нашего примера "2*(3+4)" это будет 14.
	virtual int Evaluate() const = 0;

	// ToString() форматирует выражение как строку.
	// Для простоты реализации, чтобы не учитывать приоритеты операций, каждый узел берётся в скобки.
	// То есть для нашего примера "2*(3+4)" этот метод вернёт строку "(2)*((3)+(4))".
	virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

// Value() возвращает дерево из одного узла, представляющего целое число.
ExpressionPtr Value(int value);
// Sum() возвращает новое дерево, которое представляет сумму двух переданных выражений.
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);
// Product() возвращает новое дерево, которое представляет произведение двух переданных выражений.
// Таким образом, следующий код создаст дерево для выражения "2*(3+4)":
// Product(Value(2), Sum(Value(3), Value(4)));
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right);
