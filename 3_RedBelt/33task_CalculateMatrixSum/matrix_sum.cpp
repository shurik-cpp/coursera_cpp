#include "test_runner.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>

using namespace std;

template<typename T>
int64_t SumVector(T range_begin, T range_end) {
    int64_t result = 0;
    for (auto it = range_begin; it != range_end; ++it) {
        result += accumulate(begin(*it), end(*it), 0);
    }
    return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    auto middle = begin(matrix) + (matrix.size() / 2);
    future<int64_t> first_half = async([&matrix, middle] {
        return SumVector(begin(matrix), middle);
    });
    int64_t second_half = SumVector(middle, end(matrix));
    return first_half.get() + second_half;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
