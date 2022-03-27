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
		if (id_db.count(record.id) == 0) {
			RecordInfo& rec = id_db[record.id];
			rec.record = move(record);
			rec.timestamp_iter = timestamp_db.emplace(rec.record.timestamp, &rec.record);
			rec.karma_iter = karma_db.emplace(rec.record.karma, &rec.record);
			rec.user_iter = user_db.emplace(rec.record.user, &rec.record);
			return true;
		}
		return false;
	}

	// Операция GetById должна возвращать nullptr, если в базе данных нет записи с указанным id.
	const Record* GetById(const string& id) const {
		auto it = id_db.find(id);
		if (it == end(id_db)) {
			return nullptr;
		}
		return &(it->second.record);
	}

	// Операция Erase должна возвращать true, если удалось удалить элемент с заданным id, и false,
	// если элемент с заданным id не был найден. В последнем случае состояние базы данных не должно меняться.
	bool Erase(const string& id) {
		if (id_db.count(id) == 0)	{
			return false;
		}
		RecordInfo& rec = id_db[id];
		timestamp_db.erase(rec.timestamp_iter);      // <timestamp, ref_Record>
		karma_db.erase(rec.karma_iter);               // <karma, ref_Record>
		user_db.erase(rec.user_iter);                 // <user, ref_Record>

		id_db.erase(id);

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
	//using ptr_Record = shared_ptr<Record>;
	using TimeStampDB = multimap<int, const Record*>;
	using KarmaDB = multimap<int, const Record*>;
	using UserDB = multimap<std::string, const Record*>;

	struct RecordInfo {
		Record record;
		multimap<int, const Record*>   ::iterator timestamp_iter;
		multimap<int, const Record*>   ::iterator karma_iter;
		multimap<string, const Record*>::iterator user_iter;
	};

	unordered_map<string, RecordInfo> id_db;                  // <id, ref_Record>

	TimeStampDB timestamp_db;               // <timestamp, ref_Record>
	KarmaDB karma_db;                       // <karma, ref_Record>
	UserDB user_db;                         // <user, ref_Record>

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
