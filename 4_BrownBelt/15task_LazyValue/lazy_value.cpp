#include "test_runner.h"

#include <functional>
#include <string>
#include <mutex>
#include <optional>

using namespace std;

template <typename T>
class LazyValue {
public:
	// Объект класса LazyValue<T> не должен конструировать объект типа T при своём создании
	explicit LazyValue(std::function<T()> init)
		: foo(move(init)) {}

	bool HasValue() const {
		return value.has_value();
	}

	// При первом вызове метода LazyValue<T>::Get должен создаваться объект типа T с помощью функции,
	// переданной в конструктор LazyValue<T>
	// Последующие вызовы метода Get не должны вызывать функцию, переданную в конструктор
	const T& Get() const {
		if (lock_guard<mutex> g(m); !value.has_value()) { // можно написать просто !value вместо !value.has_value()
			value = foo();
		}
		return value.value();
	}

private:
	std::function<T()> foo;
	mutable optional<T> value;
	mutable mutex m; // mutex тоже должен быть mutable!
};

void UseExample() {
	const string big_string = "Giant amounts of memory";

	LazyValue<string> lazy_string([&big_string] { return big_string; });

	ASSERT(!lazy_string.HasValue());
	ASSERT_EQUAL(lazy_string.Get(), big_string);
	ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
	bool called = false;

	{
		LazyValue<int> lazy_int([&called] {
			called = true;
			return 0;
		});
	}
	ASSERT(!called);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, UseExample);
	RUN_TEST(tr, TestInitializerIsntCalled);
	return 0;
}
