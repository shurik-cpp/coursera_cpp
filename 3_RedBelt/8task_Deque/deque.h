#pragma once

#include <stdexcept>
#include <vector>

template<typename T>
class Deque {
private:
  std::vector<T> front;
  std::vector<T> back;
  //std::vector<T> deque;

public:
  // конструктор по умолчанию
  Deque() {}

  // константный метод Empty, возвращающий true, если дек не содержит ни одного элемента;
  bool Empty() const {
    return front.empty() && back.empty();
  }

  // константный метод Size, возвращающий количество элементов в деке;
  size_t Size() const {
    return front.size() + back.size();
  }

  // T& operator[](size_t index) и const T& operator[](size_t index) const;
  T& operator[](const size_t index) {
    if (index >= front.size()) return back[index - front.size()];
    return front[front.size() - 1 - index];
  }
  const T& operator[](const size_t index) const {
    if (index >= front.size()) return back[index - front.size()];
    return front[front.size() - 1 - index];
  }

  // константный и неконстантный метод At(size_t index),
  // генерирующий стандартное исключение out_of_range,
  // если индекс больше или равен количеству элементов в деке;
  T& At(const size_t index) {
    if (index >= front.size()) return back.at(index - front.size());
    return front.at(front.size() - 1 - index);
  }
  const T& At(const size_t index) const {
    if (index >= front.size()) return back.at(index - front.size());
    return front.at(front.size() - 1 - index);
  }

  // константные и неконстантные версии методов Front и Back,
  // возвращающих ссылки на первый и последний элемент дека соответственно;
  T& Front() {
    if (!front.empty()) return front.back();
    return back.front();
  }
  const T& Front() const {
    if (!front.empty()) return front.back();
    return back.front();
  }
  T& Back() {
    if (back.empty()) return front.front();
    return back.back();
  }
  const T& Back() const {
    if (back.empty()) return front.front();
    return back.back();
  }

  // методы PushFront и PushBack.
  void PushFront(const T& val) {
    front.push_back(val);
  }
  void PushBack(const T& val) {
    back.push_back(val);
  }
};



