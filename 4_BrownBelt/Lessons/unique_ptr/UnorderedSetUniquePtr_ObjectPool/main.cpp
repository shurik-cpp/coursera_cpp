#include "test_runner.h"

#include <algorithm>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <memory>

using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate();
	T* TryAllocate();

	void Deallocate(T* object);

private:
	// Убрали свой компаратор

	queue<unique_ptr<T>> free;
	unordered_set<unique_ptr<T>> allocated;  // Изменили на unordered_set
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
	// Придётся создать некоторый unique_ptr, который мы будем искать. Создать его будет не сложно.
	// У нас же есть конструктор, который принимает сырой указатель.
	// Однако, использование такого конструктора противоречит соглашениям по владению динамическими объектами.
	// Но в данном случае у нас нет выхода. Нам необходимо создать unique_ptr.
//// Поэтому мы сознательно отступаем от соглашений.
	unique_ptr<T> ptr(object); // Добавили создание временного unique_ptr через конструктор

	auto it = allocated.find(ptr); // Ищем в контейнере

	// Мы знаем, что unique_ptr удаляет объект, поскольку он владеет им.
	// Нам же нужно создать что-то вроде "невладеющего" unique_ptr.
	// Прямо так в С++ сделать нельзя (к слову, для shared_ptr это сделать можно, и в последней лекции курса мы узнаем как).
	// Но зато можно отозвать владение у unique_ptr. Для этого он предоставляет метод release().
	// Этот метод возвращает сырой указатель, которым владел unique_ptr, а сам unique_ptr при этом обнуляется.
	// Объект же не удаляется, и владение им передаётся вызывающей стороне.
	ptr.release();
	// Вот такой интересный финт, который иногда может быть полезен.
	// Мы создали unique_ptr не потому, что нам нужно было управлять динамической памятью,
	// а просто потому, что нам нужен был сам unique_ptr. Чтобы посчитать его хеш.

	if (it == allocated.end()) {
		throw invalid_argument("");
	}
	free.push(move(allocated.extract(it).value()));
}

// Заметим, что отступление от соглашений может быть чревато. Действительно, если во время работы метода find()
// возникнет исключение, то ptr.release() не будет вызван, и переданный объект будет удалён в деструкторе ptr.
// Что в дальнейшем приведёт к ошибке в результате двойного удаления, ведь у объекта где-то есть реальный владелец,
// который попытается его удалить. Ну и в целом, удалять объект, переданный по сырому указателю, который,
// является невладеющим - прямой и точный выстрел себе в ногу.
//
// На практике, конечно, крайне маловероятно, что метод find() бросит исключение.
// Тем не менее, есть возможность сделать решение надёжным на 100% и предусмотреть даже такой экзотический случай.
// Для этого нам понадобится техника RAII, о которой мы расскажем в следующем блоке.
// Реализация конкретного решения этой проблемы с помощью техники RAII остаётся упражнением для самостоятельного выполнения.

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
