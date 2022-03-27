#include "test_runner.h"

#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <map>

using namespace std;

// Объект класса ObjectPool должен поддерживать два набора объектов:
// выделенные и освобождённые, — изначально оба набора пусты.
template <class T>
class ObjectPool {
public:
    // Методы Allocate и TryAllocate должны возвращать объекты в порядке FIFO(FirstInFirstOut),
    // т.е. множество освобождённых объектов должно представлять собой очередь:
    // методы [Try]Allocate должны извлекать объекты из её начала,
    // а метод Deallocate должен помещать освобождаемый объект в её конец.
    //========================================
    // Метод Allocate (Выделить) должен работать так:
    // 1. если же освобождённых объектов нет, то создаётся новый объект, помещается в множество выделенных,
    //    и указатель на него возвращается в качестве результата функции
    // 2. если есть хотя бы один освобождённый объект, то его надо перенести в множество выделенных
    //    и вернуть указатель на него в качестве результата функции
    T* Allocate() {

        if (deallocated.empty()) {
            T* ptr = new T;
            allocated[ptr] = true;
            return ptr;
        }
        return ChangeObjectsStatus();
    }

    // Метод TryAllocate работает аналогично, однако если освобождённых объектов нет, он должен просто возвращать nullptr.
    T* TryAllocate() {
        if (deallocated.empty()) {
            return nullptr;
        }
        return ChangeObjectsStatus();
    }

    // Метод Deallocate переносит объект из множества выделенных в множество освобождённых;
    // если переданный объект не содержится в множестве выделенных, должен бросать исключение invalid_argument.
    void Deallocate(T* object) {
        if (!allocated.count(object) || allocated[object] == false) {
            throw invalid_argument("");
        }
        allocated[object] = false;
        deallocated.push(object);
    }

    // Деструктор объекта ObjectPool должен уничтожать все объекты пула, как выделенные, так и освобождённые.
    ~ObjectPool() {
        for (auto& it : allocated) {
            delete it.first;
        }
    }

private:
    map<T*, bool> allocated; // объект - его активность
    queue<T*> deallocated;   // очередь освобожденных

    T* ChangeObjectsStatus() {
        T* ptr;
        ptr = deallocated.front();
        allocated[ptr] = true;
        deallocated.pop();
        return ptr;
    }
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
