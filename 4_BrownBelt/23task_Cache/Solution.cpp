#include "Common.h"

#include <list>
#include <unordered_map>
#include <mutex>

using namespace std;

// Кэширование производится методом вытеснения давно неиспользуемых элементов (Least Recently Used, LRU).
// Каждый элемент кэша имеет ранг.
class LruCache : public ICache {
public:
	LruCache(shared_ptr<IBooksUnpacker> books_unpacker, const Settings& settings)
		: booksUnpacker_(move(books_unpacker))
		, settings_(settings) {	}

	// При вызове метода GetBook(), если книга с таким названием уже есть в кэше, её ранг поднимается до максимального
	// (строго больше, чем у всех остальных). Если такой книги нет в кэше, то она добавляется в кэш, и её ранг,
	// опять же, выставляется в максимальный. При этом, если общий размер книг превышает ограничение max_memory,
	// из кэша удаляются книги с наименьшим рангом, пока это необходимо. Возможно, пока он полностью не будет опустошён.
	// Если же размер запрошенной книги уже превышает max_memory, то после вызова метода кэш остаётся пустым,
	// то есть книга в него не добавляется.
	// Искать давно неиспользуемые элементы можно перебором всех имеющихся.
	// GetBook() может вызываться одновременно из нескольких потоков, поэтому необходимо обеспечить ему безопасность
	BookPtr GetBook(const string& book_name) override { // using BookPtr = shared_ptr<const IBook>;
		lock_guard guard(mut_);
		// реализуйте метод
		if (bookByName_.count(book_name)) {
			BookPtr bookPtr = move(*bookByName_[book_name]);
			rangedBooks_.erase(bookByName_[book_name]);
			rangedBooks_.push_back(move(bookPtr));
			bookByName_[book_name] = --rangedBooks_.end();
		}
		else {
			auto book = booksUnpacker_->UnpackBook(book_name);

			if (book->GetContent().size() > settings_.max_memory) {
				return move(book);
			}

			rangedBooks_.push_back(move(book));
			bookByName_[book_name] = --rangedBooks_.end();
			currentCommonSize_ += rangedBooks_.back()->GetContent().size();

			while (currentCommonSize_ > settings_.max_memory) {
				BookPtr bookPtr = move(*rangedBooks_.begin());
				bookByName_.erase(bookPtr->GetName());
				currentCommonSize_ -= bookPtr->GetContent().size();
				rangedBooks_.erase(rangedBooks_.begin());
			}
		}

		return *bookByName_[book_name];
	}

private:
	shared_ptr<IBooksUnpacker> booksUnpacker_;
	const Settings settings_;
	size_t currentCommonSize_;
	mutex mut_;

	list<BookPtr> rangedBooks_;
	using RangeIt = list<BookPtr>::iterator;
	unordered_map<string, RangeIt> bookByName_;
};

// Для создания объекта ICache используется функция MakeCache(), которую вам необходимо реализовать.
// Она принимает объект IBooksUnpacker, а также объект ICache::Settings - настройки кэша.
// В нашей задаче настройки содержат всего один параметр max_memory — максимальный суммарный размер всех книг
// в кэше в байтах, — но в реальности их может быть больше. Именно поэтому мы оформили настройки в виде структуры.
// Размером книги считается размер её текста в байтах.
unique_ptr<ICache> MakeCache(shared_ptr<IBooksUnpacker> books_unpacker, const ICache::Settings& settings) {
	return make_unique<LruCache>(move(books_unpacker), settings);
}
