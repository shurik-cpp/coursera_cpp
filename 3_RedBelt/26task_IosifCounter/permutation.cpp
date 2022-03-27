#include "test_runner.h"
#include "profile.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <list>
#include <iostream>
#include <utility>

using namespace std;

//template <typename RandomIt>
//void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
//    // Перемещение итератора с использованием std::make_move_iterator, который перемещает элементы
//    vector<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
//    size_t cur_pos = 0;
//    while (!pool.empty()) {
//        *(first++) = move(pool[cur_pos]);
//        pool.erase(pool.begin() + cur_pos);
//        if (pool.empty()) {
//            break;
//        }
//        cur_pos = (cur_pos + step_size - 1) % pool.size();
//    }
//}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    // Перемещение итератора с использованием std::make_move_iterator, который перемещает элементы
    list<typename RandomIt::value_type> pool(make_move_iterator(first), make_move_iterator(last));
    auto it = begin(pool);
    while (!pool.empty()) {
        *(first++) = move(*it);
        auto tmp_it = next(it);
        pool.erase(it);
        if (pool.empty()) {
            break;
        }
        it = prev(tmp_it);
        for (size_t i = 0; i != step_size ; ++i) {
            it++;
            if (it == end(pool)) {
                it = begin(pool);
            }
        }
    }
}

vector<int> MakeTestVector() {
    vector<int> numbers(100000);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    { LOG_DURATION("Josephus /1");
        vector<int> numbers = MakeTestVector();
        MakeJosephusPermutation(begin(numbers), end(numbers), 1);
        vector<int> numbers_copy(begin(numbers), end(numbers));
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    { LOG_DURATION("Josephus /10");
        vector<int> numbers = MakeTestVector();
        MakeJosephusPermutation(begin(numbers), end(numbers), 10);
        vector<int> numbers_copy(begin(numbers), end(numbers));
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    { LOG_DURATION("Josephus /100");
        vector<int> numbers = MakeTestVector();
        MakeJosephusPermutation(begin(numbers), end(numbers), 100);
        vector<int> numbers_copy(begin(numbers), end(numbers));
        ASSERT_EQUAL(numbers_copy, numbers);
    }
}

struct NoncopyableInt {
    int value;

    NoncopyableInt(int value) : value(value) {}

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});

    ASSERT_EQUAL(numbers, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}
