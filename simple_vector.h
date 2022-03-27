#pragma once

#include <algorithm>

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;  // = defaul, это просьба компилятору, чтобы он сам сгенерировал этот конструктор и не прописывать пустой конструктор самостоятельно
  explicit SimpleVector(size_t size);
  SimpleVector(const SimpleVector& other);
  SimpleVector(SimpleVector&& other);
  ~SimpleVector();

  T& operator[](size_t index);
	SimpleVector& operator=(const SimpleVector& other); // оператор копирования
	SimpleVector& operator=(SimpleVector&& other);      // оператор перемещения (&&)

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
  : data(new T[size])
  , size(size)
  , capacity(size)
{
}

// конструктор копирования:
template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other)
  : data(new T[other.capacity]) // первым делом, занимаем нужный размер памяти в куче
  , size(other.size) // присваиваем размер контейнера
  , capacity(other.capacity) // присваиваем вместимость контейнера, на данный момент
{
    // при помощи <algorithm>
		std::copy(other.begin(), other.end(), this->begin());
}
// конструктор перемещения (не const параметр, но по rvalue-ссылке (&&)): (https://habr.com/ru/post/226229/)
template <typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T>&& other)
  : data(other.data)
  , size(other.size)
  , capacity(other.capacity)
{
    other.data = nullptr;
    other.size = other.capacity = 0;
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
  delete[] data;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
  return data[index];
}

// оператор копирования
template <typename T>
SimpleVector<T>& SimpleVector<T>::operator=(const SimpleVector<T>& other) {
	if (this != &other) {
    if (capacity < other.size) {
        delete[] data;
        data = new T[other.capacity];
    }
    size = other.size;
    capacity = other.capacity;
		std::copy(other.begin(), other.end(), this->begin());
	}
	return *this;
}
// оператор перемещения
template <typename T>
SimpleVector<T>& SimpleVector<T>::operator=(SimpleVector<T>&& other) {
	if (this != &other) {
    data = other.data;
    size = other.size;
    capacity = other.capacity;
    other.data = nullptr;
    other.size = other.capacity = 0;
	}
	return *this;
}

template <typename T>
size_t SimpleVector<T>::Size() const {
  return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
  return capacity;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
  if (size >= capacity) {
    auto new_cap = capacity == 0 ? 1 : 2 * capacity;
    auto new_data = new T[new_cap];
    copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;
    capacity = new_cap;
  }
  data[size++] = value;
}

template <typename T>
T* SimpleVector<T>::begin() {
  return data;
}

template <typename T>
T* SimpleVector<T>::end() {
  return data + size;
}

template <typename T>
const T* SimpleVector<T>::begin() const {
  return data;
}

template <typename T>
const T* SimpleVector<T>::end() const {
  return data + size;
}
