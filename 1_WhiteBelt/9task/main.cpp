/* На вход дано целое положительное число N.
 * Выведите его в двоичной системе счисления без ведущих нулей.
 *
 * Подсказка:
 * число N можно считывать в переменную типа int
 * алгоритм перевода из десятичной системы счисления в двоичную,
 * может быть найден, например, здесь:
 * https://www.yaklass.ru/p/informatika/10-klass/informatciia-i-informatcionnye-protcessy-11955/predstavlenie-chislovoi-informatcii-v-kompiutere-11901/re-62e8903e-ba93-478a-85b5-ae45af40c658
 * в этой задаче вам может пригодиться контейнер vector; напоминаем,
 * что добавление значения x в конец вектора v делается так: v.push_back(x);
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int a;
  vector<int> bin;

  cin >> a;

  while (a >= 2) {
    if (a % 2 == 0) bin.push_back(0);
    else bin.push_back(1);
    a /= 2;
  }
  if (a != 0) bin.push_back(1);
  else bin.push_back(0);

  for (int i = bin.size() - 1; i >= 0; i--) {
    cout << bin[i];
  }

  cout << endl << endl;

  return 0;
}

// код coursera.org:
/*
int main() {
    int n;
    vector<int> bits;

    cin >> n;
    while (n > 0) {
        bits.push_back(n % 2);
        n /= 2;
    }

    for (int i = bits.size() - 1; i >= 0; --i) {
        cout << bits[i];
    }
    return 0;
}
*/
