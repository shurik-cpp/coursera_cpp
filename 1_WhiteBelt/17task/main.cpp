/* Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
 * Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.
 *
 * Гарантируется, что среднее арифметическое значений температуры является целым числом.
 *
 * Формат ввода
 * Вводится число N, затем N неотрицательных целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день.
 *
 * Формат вывода
 * Первое число K — количество дней, значение температуры в которых выше среднего арифметического.
 * Затем K целых чисел — номера этих дней.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> temper(N);
  // заполняем вектор значениями температур
  for (auto& i : temper) {
    cin >> i;
  }

  int a = 0;
  // считаем среднее арефметическое в переменную a
  for (auto& i : temper) {
    a += i;
  }
  a /= N; // или так: a /= temper.size();

  // считаем количество дней, сравниваем и выводим что требуется
  int counter = 0;
  for (int i = 0; i < N; ++i) {
    if (temper[i] > a) ++counter;
  }
  cout << counter << endl;

  for (int i = 0; i < N; ++i) {
    if (temper[i] > a) {
      cout << i << ' ';
    }
  }


  return 0;
}

/*
int main() {
  int n;
  cin >> n;
  vector<int> temperatures(n);
  int sum = 0;
  for (int& temperature : temperatures) {
    cin >> temperature;
    sum += temperature;
  }

  int average = sum / n;
  vector<int> result_indices;
  for (int i = 0; i < n; ++i) {
    if (temperatures[i] > average) {
      result_indices.push_back(i);
    }
  }

  cout << result_indices.size() << endl;
  for (int result_index : result_indices) {
    cout << result_index << " ";
  }
  cout << endl;

  return 0;
}
*/
