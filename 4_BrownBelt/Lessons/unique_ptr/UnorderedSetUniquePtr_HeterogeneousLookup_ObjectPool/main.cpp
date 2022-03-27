// Забудем про изменения из предыдущей секции и снова посмотрим, что нам нужно изменить относительно реализации,
// использующей контейнер set. Нам понадобится только изменить тип контейнера allocated на unordered_set,
// причём таким образом, чтобы заработал гетерогенный поиск. Остальной код трогать вообще не будем.
// Окончательная реализация класса ObjectPool с использованием контейнера unordered_set в стиле C++20 (с гетерогенным поиском)
// (комментарии указывают разницу с реализацией на set):

#include "test_runner.h"

#include <algorithm>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <memory>

using namespace std;

// Посмотрим, что пишет документация про перегрузки (3) и (4) метода find():

// 3,4) [...] This overload only participates in overload resolution if `Hash::is_transparent` and `KeyEqual::is_transparent`
// are valid and each denotes a type. [...]

// Как видим, если для set нам было необходимо наличие типа Compare::is_transparent, то для unordered_set необходимо
// наличие типов Hash::is_transparent и KeyEqual::is_transparent.

// Из документации контейнера unordered_set ясно, что типы Hash и KeyEqual передаются в шаблон и определяют,
// каким образом ключи хешируются и сравниваются. Что ж, давайте их определим и укажем в шаблоне:

// Добавили свои классы для хеширования и сравнения ключей
struct Hash {
	using is_transparent = void;
	template <class P>
	size_t operator()(const P& p) const {
		return hash<P>()(p);
	}
};

// Тип KeyEqual предоставляет operator() для сравнения unique_ptr и обычного указателя между собой, в разных комбинациях.
// Заметим, что комбинация сравнения обычного указателя с обычным нам здесь не нужна.
// Также обратите внимание, что когда мы писали компаратор для контейнера set, в нём мы сравнивали указатели с помощью
// функтора less. Это было необходимо, т.к. тогда нам был важен порядок указателей. А здесь нам важно только их равенство.
// Проверка на равенство это более простая операция, и, независимо от сложности устройства указателей,
// компилятор всегда может выполнить её оптимально. Поэтому стандартные операции сравнения "==" и "!="
// для указателей ведут себя ожидаемым образом, и мы можем использовать их напрямую.
struct KeyEqual {
	using is_transparent = void;
	template <class P, class Q>
	bool operator()(const P& lhs, const Q& rhs) const {
		// функция to_address - принимает на вход произвольный указатель (не важно, умный или обычный) и
		// возвращает обычный указатель
		return to_address(lhs) == to_address(rhs);
	}
};
// Такая реализация стала короче и позволяет использовать указатель любого вида для поиска в контейнере.
// Например, shared_ptr, или даже какой-то свой особо умный указатель, для которого предоставлены подходящие специализации
// классов hash и pointer_traits (он используется функцией to_address()).

// Для обоих типов Hash и KeyEqual мы определили вложенный тип is_transparent,
// чтобы включить нужные нам перегрузки функции find(). Тип Hash предоставляет operator() для unique_ptr
// и для обычного указателя.

template <class T>
class ObjectPool {
public:
	T* Allocate();
	T* TryAllocate();

	void Deallocate(T* object);

private:
	// Убрали свой компаратор

	queue<unique_ptr<T>> free;
	// Изменили на unordered_set с соответствующими параметрами
	unordered_set<unique_ptr<T>, Hash, KeyEqual> allocated;
};

template <typename T>
T* ObjectPool<T>::Allocate() {
	if (free.empty()) {
		free.push(make_unique<T>());
	}
	auto ptr = move(free.front());
	free.pop();
	T* ret = ptr.get();
	allocated.insert(move(ptr));
	return ret;
}

template <typename T>
T* ObjectPool<T>::TryAllocate() {
	if (free.empty()) {
		return nullptr;
	}
	return Allocate();
}

// Убрали функции сравнения, они больше не нужны

template <typename T>
void ObjectPool<T>::Deallocate(T* object) {
	auto it = allocated.find(object);
	if (it == allocated.end()) {
		throw invalid_argument("");
	}
	free.push(move(allocated.extract(it).value()));
}


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
