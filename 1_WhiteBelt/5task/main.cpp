/* Написать программу вычисления стоимости покупки товара с учётом скидки.
 * Если исходная стоимость товара больше A рублей, то на неё устанавливается скидка в X процентов.
 * Если исходная стоимость товара больше B рублей, то на неё устанавливается скидка в Y процентов.
 *
 * На вход программе даны пять вещественных чисел: N, A, B, X, Y (A < B) - где N - исходная стоимость товара.
 * Выведите стоимость покупки товара с учётом скидки.
 */


#include <iostream>

using namespace std;

// мой код:
int main() {
  double N, A, B, X, Y;
  cin >> N >> A >> B >> X >> Y;
  if (A > B) return 1;

  if (N > B) {
     cout << N - (N * Y / 100);
  }
  else if (N > A) {
    cout << N - (N * X / 100);
  }
  else cout << N;
  return 0;
}

/* код coursera.org:
int main() {
    double n, a, b, x, y;
    cin >> n >> a >> b >> x >> y;
    if (n > b) {
        n *= (1 - y / 100);
    } else if (n > a) {
        n *= (1 - x / 100);
    }
    cout << n;

    return 0;
}
*/
