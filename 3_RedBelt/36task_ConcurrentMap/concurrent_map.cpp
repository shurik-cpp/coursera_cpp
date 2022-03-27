#include "test_runner.h"
#include "profile.h"


#include <algorithm>
#include <future>
#include <mutex>
#include <map>
#include <vector>
#include <string>
#include <random>

using namespace std;


template <typename K, typename V>
class ConcurrentMap {
public:
    // static_assert в начале класса говорит, что в данной задаче предполагается,
    // что ключами ConcurrentMap'а могут быть только целые числа
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    // Структура Access, должна вести себя так же, как и в шаблоне Synchronized,
    // — предоставлять ссылку на значение словаря и обеспечивать синхронизацию доступа к нему
    struct Access {
        lock_guard<mutex> guard;
        V& ref_to_value;

        Access(const K& key, pair<mutex, map<K, V>>& bucket)
            : guard(bucket.first)
            , ref_to_value(bucket.second[key]) { }
    };

    // Конструктор класса ConcurrentMap<K, V> принимает количество подсловарей,
    // на которые надо разбить всё пространство ключей
    explicit ConcurrentMap(size_t bucket_count)
        : data(bucket_count) { }

    // operator[] должен вести себя так же, как аналогичный оператор у map — если ключ key присутствует в словаре,
    // он должен возвращать объект класса Access, содержащий ссылку на соответствующее ему значение;
    // если же key отсутствует в словаре, в него надо добавить пару (key, V()) и вернуть объект класса Access,
    // содержащий ссылку на только что добавленное значение.
    Access operator[](const K& key) {
        auto& bucket = data[Abs(key) % data.size()];
        return {key, bucket};
    }

    // Метод BuildOrdinaryMap должен сливать вместе части словаря и возвращать весь словарь целиком.
    // При этом он должен быть потокобезопасным, то есть корректно работать,
    // когда другие потоки выполняют операции с ConcurrentMap
    map<K, V> BuildOrdinaryMap() {
        map<K, V> result;
        for (auto& [mtx, mapping] : data) {
            auto g = Lock(mtx);
            result.insert(begin(mapping), end(mapping));
        }
        return result;
    }

private:
    vector<pair<mutex, map<K, V>>> data;

    template <typename T>
    T Abs(T x) {
        return x < 0 ? -x : x;
    }

    auto Lock(mutex& m) {
        return lock_guard<mutex>{m};
    }
};

void RunConcurrentUpdates(ConcurrentMap<int, int>& cm, size_t thread_count, int key_count) {
    auto kernel = [&cm, key_count](int seed) {
        vector<int> updates(key_count);
        iota(begin(updates), end(updates), -key_count / 2);
        shuffle(begin(updates), end(updates), default_random_engine(seed));

        for (int i = 0; i < 2; ++i) {
            for (auto key : updates) {
                cm[key].ref_to_value++;
            }
        }
    };

    vector<future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i) {
        futures.push_back(async(kernel, i));
    }
}

void TestConcurrentUpdate() {
    const size_t thread_count = 3;
    const size_t key_count = 50000;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);
    for (auto& [k, v] : result) {
        AssertEqual(v, 6, "Key = " + to_string(k));
    }
}

void TestReadAndWrite() {
    ConcurrentMap<size_t, string> cm(5);

    auto updater = [&cm] {
        for (size_t i = 0; i < 50000; ++i) {
            cm[i].ref_to_value += 'a';
        }
    };
    auto reader = [&cm] {
        vector<string> result(50000);
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = async(updater);
    auto r1 = async(reader);
    auto u2 = async(updater);
    auto r2 = async(reader);

    u1.get();
    u2.get();

    for (auto f : {&r1, &r2}) {
        auto result = f->get();
        ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
            return s.empty() || s == "a" || s == "aa";
        }));
    }
}

void TestSpeedup() {
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(100);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestReadAndWrite);
    RUN_TEST(tr, TestSpeedup);
}
