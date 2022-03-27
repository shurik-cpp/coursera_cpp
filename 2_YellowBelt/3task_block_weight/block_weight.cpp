#include <iostream>
#include <cstdint>
#include <limits>

using namespace std;

int main() {

  //cout << numeric_limits<uint64_t>:: max();

  uint64_t number, density;
  cin >> number >> density; // берем количество блоков и массу одного блока

  uint64_t total_weight = 0;

  for (uint64_t i = 0; i < number; ++i) {
    uint64_t W, H, D;
    cin >> W >> H >> D;
    uint64_t capacity = W * H * D;
    total_weight += capacity * density;
  }

  cout << total_weight << endl;

  return 0;
}

/*
#include <cstdint>
#include <iostream>

using namespace std;

int main() {
  int N, R;
  cin >> N >> R;
  uint64_t answer = 0;
  for (types = 0; i < N; ++i) {
    int W, H, D;
    cin >> W >> H >> D;
    // Если не привести W к типу uint64_t перед умножением,
    // произведение будет иметь тип int и случится переполнение.
    // Альтернативное решение — хранить сами W, H, D в uint64_t
    answer += static_cast<uint64_t>(W) * H * D;
  }
  answer *= R;
  cout << answer << endl;
  return 0;
}
*/
