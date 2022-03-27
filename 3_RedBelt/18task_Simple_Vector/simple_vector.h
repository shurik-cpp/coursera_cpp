#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
    SimpleVector() {}
    explicit SimpleVector(size_t size) {
        _size = size;
        _capacity = _size;
        // выделяется непрерывный блок памяти для size - количества переменных типа T
        _data = new T[_capacity];
    }
    ~SimpleVector() {
        delete[] _data;
    }

    T& operator[](size_t index) { return _data[index]; }

    T* begin() { return _data; }
    T* end() { return _data + _size; }
    const T* begin() const { return _data; }
    const T* end() const { return _data + _size; }

    // метод Size должен возвращать количество элементов в векторе
    size_t Size() const { return _size; }

    //метод Capacity должен возвращать текущую ёмкость вектора — количество элементов,
    // которое помещается в блок памяти, выделенный вектором в данный момент
    size_t Capacity() const { return _capacity; }

    // метод PushBack добавляет новый элемент в конец вектора;
    // если в текущем выделенном блоке памяти не осталось свободного места (т.е. Size() == Capacity()),
    // вектор должен выделить блок размера 2 * Capacity(), скопировать в него все элементы и удалить старый.
    void PushBack(const T& value) {
        if (_data == nullptr) {
            _data = new T[0];
            _capacity = 1;
        }
        else if (_size == _capacity) {
            T* last_address = _data;
            _data = new T[2 * _capacity];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = last_address[i];
            }
            delete[] last_address;
            _capacity *= 2;
        }
        _size++;
        _data[_size - 1] = value;
    }

private:
    T* _data = nullptr;
    size_t _capacity = 0;
    size_t _size = 0;
};
