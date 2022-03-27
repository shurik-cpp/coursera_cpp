/* Напишите функцию MoveStrings, которая:
 * принимает два вектора строк, source и destination,
 * и дописывает все строки из первого вектора в конец второго.
 * После выполнения функции вектор source должен оказаться пустым.
 *
 * Чтобы очистить содержимое вектора, надо вызвать у него метод clear:
 * vector<string> words = {"hey", "hi"};
 * words.clear();
 * // Теперь вектор words пуст
 *
 * Пример:
 * vector<string> source = {"a", "b", "c"};
 * vector<string> destination = {"z"};
 * MoveStrings(source, destination);
 * // source должен оказаться пустым
 * // destination должен содержать строки "z", "a", "b", "c" именно в таком порядке
*/

#include <iostream>
#include <string>
#include <vector>
#include <move_strings.cpp>

using namespace std;

int main() {
  vector<string> a = {"hey ", "you"};
  vector<string> b = {"destination ", "now ", "added: "};

  cout << "a = ";
  for (auto i : a) {
    cout << i;
  }
  cout << endl << "b = ";
  for (auto i : b) {
    cout << i;
  }

  cout << "MoveStrings(a, b);" << endl;
  MoveStrings(a, b);

  cout << "a_now = ";
  for (auto i : a) {
    cout << i;
  }

  cout << endl << "b_now = ";
  for (auto i : b) {
    cout << i;
  }
  return 0;
}
