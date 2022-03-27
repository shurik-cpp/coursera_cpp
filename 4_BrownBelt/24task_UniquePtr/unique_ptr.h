#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <cstddef>

template <typename T>
class UniquePtr {
private:
	T* ptr_;

	void TryCleanMemory() {
		if (ptr_ != nullptr) {
			delete ptr_;
			ptr_ = nullptr;
		}
	}

public:
	// Конструктор по умолчанию, создающий пустой умный указатель.
	explicit UniquePtr() : ptr_(nullptr) { }
	// Конструктор, принимающий T* и захватывающий владение этой динамической памятью.
	explicit UniquePtr(T* ptr) : ptr_(ptr) {}
	// Конструктор перемещения, получающий на вход rvalue-ссылку на другой UniquePtr и отбирающий у него владение ресурсом.
	explicit UniquePtr(UniquePtr&& other) : ptr_(other.Release()) {	}

	// В вашем классе должны быть запрещены конструктор копирования и обычный оператор присваивания.
	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator= (const UniquePtr&) = delete;

	// Оператор присваивания, получающий на вход nullptr (тип - nullptr_t, определенный в заголовочном файле cstddef).
	// В результате умный указатель должен стать пустым.
	UniquePtr& operator= (std::nullptr_t) {
		TryCleanMemory();
		return *this;
	}
	// Move-оператор присваивания, получающий на вход rvalue-ссылку на другой UniquePtr.
	UniquePtr& operator= (UniquePtr&& other) {
		TryCleanMemory();
		ptr_ = other.Release();
		return *this;
	}

	~UniquePtr() {
		TryCleanMemory();
	}

	// operator *, который возвращает T&.
	T& operator* () const {
		return *ptr_;
	}
	// Оператор -> (он должен вернуть указатель на обычную структуру, к которому можно применить обычный ->).
	T* operator-> () const {
		return ptr_;
	}

	// Функцию T* Release(), отменяющую владение объектом и возвращающую хранящийся внутри указатель.
	T* Release() {
		T* res = ptr_;
		ptr_ = nullptr;
		return res;
	}
	// Функцию void Reset(T* ptr), после выполнения которой умный указатель должен захватить ptr.
	void Reset(T* ptr) {
		TryCleanMemory();
		ptr_ = ptr;
	}
	// Функцию void Swap(UniquePtr& other), обменивающуюся содержимым с другим умным указателем.
	void Swap(UniquePtr& other) {
		T* tmp = ptr_;
		ptr_ = other.Release();
		other.Reset(tmp);
	}
	// Функцию T* Get() const, возвращающую указатель.
	T* Get() const {
		return ptr_;
	}
};

#endif // UNIQUE_PTR_H
