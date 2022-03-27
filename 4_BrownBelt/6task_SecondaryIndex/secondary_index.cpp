// Вторичный индекс в базе данных

#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <future>

using namespace std;

struct Record {
	string id;
	string title;
	string user;
	int timestamp;
	int karma;

	bool operator==(const Record &other) const {
		return id == other.id;
	}
};

class Database {
public:
	// Операция Put должна возвращать true, если вставка удалась, и false, если вставка не удалась,
	// потому что в базе данных уже есть запись с таким же id. В последнем случае состояние базы данных не должно меняться.
	bool Put(const Record& record) {
		if (reference_db.count(record.id) == 0) {
			db.push_front(move(record));
			auto it = begin(db);
			reference_db[it->id] = it;
			timestamp_db.insert(pair{it->timestamp, it});
			karma_db.insert(pair{it->karma, it});
			user_db.insert(pair{it->user, it});
			return true;
		}
		return false;
	}

	// Операция GetById должна возвращать nullptr, если в базе данных нет записи с указанным id.
	const Record* GetById(const string& id) const {
		Record* ref = nullptr;
		auto it = reference_db.find(id);
		if (it != reference_db.end()) {
			ref = &(*it->second);
		}
		return ref;
	}

	// Операция Erase должна возвращать true, если удалось удалить элемент с заданным id, и false,
	// если элемент с заданным id не был найден. В последнем случае состояние базы данных не должно меняться.
	bool Erase(const string& id) {
		auto it = reference_db.find(id);
		if (it == reference_db.end())	{
			return false;
		}

		auto it_r = reference_db.find(it->second->id);
		reference_db.erase(it_r);

		RemoveItem(timestamp_db, it->second, it->second->timestamp);
		RemoveItem(karma_db, it->second, it->second->karma);
		RemoveItem(user_db, it->second, it->second->user);

		db.erase(it->second);

		return true;
	}

	// Операции RangeByTimestamp, RangeByKarma и AllByUser принимают функтор callback.
	// Подразумевается, что он имеет оператор (), принимающий в качестве аргумента объект типа Record и возвращающий bool.
	// Так же, как и RangeByTimestamp, методы RangeByKarma и AllByUser должны вызывать callback для каждой записи,
	// по которой они итерируются, и прекращать итерацию, если callback вернул false.
	// Параметр callback позволяет управлять процессом обхода: он должен возвращать true,
	// если требуется продолжить обход найденных записей, и false в противном случае.
	// Например, это позволит вывести первые 10 записей или найти первую запись, удовлетворяющую дополнительному критерию.
	// --------------
	// Операция RangeByTimestamp должна обходить все записи, у которых поле timestamp находится в диапазоне [low, high]
	// (обе границы включены), и для каждой из них один раз вызывать callback.
	// Если очередной вызов callback вернул false, итерация прекращается.
	template <typename Callback>
	void RangeByTimestamp(int low, int high, Callback callback) const {
		auto range_begin = timestamp_db.lower_bound(low);
		auto range_end = timestamp_db.upper_bound(high);
		while (range_begin != range_end && callback(*range_begin->second)) {
			++range_begin;
		}
	}

	// Операция RangeByKarma должна обходить все записи, у которых поле karma находится в диапазоне [low, high].
	template <typename Callback>
	void RangeByKarma(int low, int high, Callback callback) const {
		auto range_begin = karma_db.lower_bound(low);
		auto range_end = karma_db.upper_bound(high);
		while (range_begin != range_end && callback(*range_begin->second)) {
			++range_begin;
		}
	}

	// Операция AllByUser должна обходить все записи в хранилище данных, у которых поле user равно значению параметра user.
	template <typename Callback>
	void AllByUser(const string& user, Callback callback) const {
		auto range = user_db.equal_range(user);
		while (range.first != range.second && callback(*range.first->second)) {
			++range.first;
		}
	}

private:
	list<Record> db;

	using Iterator = list<Record>::iterator;

	unordered_map<string_view, Iterator> reference_db; // <id, ref_Record>
	multimap<int, Iterator> timestamp_db;              // <timestamp, ref_Record>
	multimap<int, Iterator> karma_db;                  // <karma, ref_Record>
	multimap<string, Iterator> user_db;                // <user, ref_Record>

	template<typename C, typename T>
	void RemoveItem(C &collection, Iterator it, T type) {
		auto range = collection.equal_range(type);
		while (range.first != range.second) {
			if (range.first->second->user == it->user) {
				collection.erase(range.first);
				break;
			}
			++range.first;
		}
	}
};

void TestRangeBoundaries() {
	const int good_karma = 1000;
	const int bad_karma = -10;

	Database db;
	db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
	db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

	int count = 0;
	db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
		++count;
		return true;
	});

	ASSERT_EQUAL(2, count);
}

void TestSameUser() {
	Database db;
	db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
	db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

	int count = 0;
	db.AllByUser("master", [&count](const Record&) {
		++count;
		return true;
	});

	ASSERT_EQUAL(2, count);
}

void TestReplacement() {
	const string final_body = "Feeling sad";

	Database db;
	db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
	db.Erase("id");
	db.Put({"id", final_body, "not-master", 1536107260, -10});

	auto record = db.GetById("id");
	ASSERT(record != nullptr);
	ASSERT_EQUAL(final_body, record->title);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestRangeBoundaries);
	RUN_TEST(tr, TestSameUser);
	RUN_TEST(tr, TestReplacement);
	return 0;
}
